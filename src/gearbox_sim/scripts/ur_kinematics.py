#!/usr/bin/env python3
"""Analytical-grade kinematics for the UR arms in gearbox_sim.

Numerical damped-least-squares IK built on URDF-exact forward kinematics. No
MoveIt dependency: deterministic and stable in dry_run. Seeding each waypoint
with the previous joint solution keeps the chain near a non-singular branch and
avoids the wrist-flip singularity, so callers get smooth, continuous motion.

FK root frame is the UR ``<prefix>base_link`` (NOT base_link_inertia); the
base_link->base_link_inertia rpy=[0 0 pi] flip is folded in as the first fixed
transform so results match ``tf2_echo <prefix>base_link <prefix>tool0``.
"""
from __future__ import annotations

import math
from typing import Dict, List, Sequence, Tuple

import numpy as np


def _rpy_to_matrix(roll: float, pitch: float, yaw: float) -> np.ndarray:
    cr, sr = math.cos(roll), math.sin(roll)
    cp, sp = math.cos(pitch), math.sin(pitch)
    cy, sy = math.cos(yaw), math.sin(yaw)
    # URDF convention: R = Rz(yaw) @ Ry(pitch) @ Rx(roll)
    rz = np.array([[cy, -sy, 0.0], [sy, cy, 0.0], [0.0, 0.0, 1.0]])
    ry = np.array([[cp, 0.0, sp], [0.0, 1.0, 0.0], [-sp, 0.0, cp]])
    rx = np.array([[1.0, 0.0, 0.0], [0.0, cr, -sr], [0.0, sr, cr]])
    return rz @ ry @ rx


def _xform(xyz: Sequence[float], rpy: Sequence[float]) -> np.ndarray:
    t = np.eye(4)
    t[:3, :3] = _rpy_to_matrix(rpy[0], rpy[1], rpy[2])
    t[:3, 3] = xyz
    return t


def _rot_z(theta: float) -> np.ndarray:
    c, s = math.cos(theta), math.sin(theta)
    t = np.eye(4)
    t[0, 0], t[0, 1] = c, -s
    t[1, 0], t[1, 1] = s, c
    return t


# Per-UR-type joint chain, from base_link to tool0, expressed as the fixed
# transform that PRECEDES each revolute joint's variable Z rotation, taken
# verbatim from the expanded URDF (default_kinematics.yaml calibration).
# Each entry: (xyz, rpy) of the joint origin; the joint rotates about local Z.
# A leading fixed transform folds in base_link -> base_link_inertia (rpy=[0 0 pi]).
_UR_CHAINS: Dict[str, Dict[str, object]] = {
    "ur5e": {
        "base_flip": ([0.0, 0.0, 0.0], [0.0, 0.0, math.pi]),
        "joints": [
            ([0.0, 0.0, 0.1625], [0.0, 0.0, 0.0]),
            ([0.0, 0.0, 0.0], [math.pi / 2.0, 0.0, 0.0]),
            ([-0.425, 0.0, 0.0], [0.0, 0.0, 0.0]),
            ([-0.3922, 0.0, 0.1333], [0.0, 0.0, 0.0]),
            ([0.0, -0.0997, 0.0], [math.pi / 2.0, 0.0, 0.0]),
            ([0.0, 0.0996, 0.0], [math.pi / 2.0, math.pi, math.pi]),
        ],
        # wrist_3_link -> flange -> tool0 (two fixed transforms, composed)
        "tool0": ([0.0, 0.0, 0.0], [0.0, 0.0, 0.0]),
    },
    "ur3e": {
        "base_flip": ([0.0, 0.0, 0.0], [0.0, 0.0, math.pi]),
        "joints": [
            ([0.0, 0.0, 0.15185], [0.0, 0.0, 0.0]),
            ([0.0, 0.0, 0.0], [math.pi / 2.0, 0.0, 0.0]),
            ([-0.24355, 0.0, 0.0], [0.0, 0.0, 0.0]),
            ([-0.2132, 0.0, 0.13105], [0.0, 0.0, 0.0]),
            ([0.0, -0.08535, 0.0], [math.pi / 2.0, 0.0, 0.0]),
            ([0.0, 0.0921, 0.0], [math.pi / 2.0, math.pi, math.pi]),
        ],
        "tool0": ([0.0, 0.0, 0.0], [0.0, 0.0, 0.0]),
    },
}

# wrist_3_link -> flange (rpy=[0 -pi/2 -pi/2]) then flange -> tool0
# (rpy=[pi/2 0 pi/2]); both translations zero. Composed once at import.
_FLANGE = _xform([0.0, 0.0, 0.0], [0.0, -math.pi / 2.0, -math.pi / 2.0])
_FLANGE_TO_TOOL0 = _xform([0.0, 0.0, 0.0], [math.pi / 2.0, 0.0, math.pi / 2.0])
_WRIST3_TO_TOOL0 = _FLANGE @ _FLANGE_TO_TOOL0


def fk(ur_type: str, joints: Sequence[float]) -> np.ndarray:
    """Forward kinematics: base_link -> tool0 as a 4x4 matrix."""
    chain = _UR_CHAINS[ur_type]
    t = _xform(*chain["base_flip"])  # base_link -> base_link_inertia
    for (xyz, rpy), theta in zip(chain["joints"], joints):
        t = t @ _xform(xyz, rpy) @ _rot_z(theta)
    return t @ _WRIST3_TO_TOOL0


def _pose_error(current: np.ndarray, target: np.ndarray) -> np.ndarray:
    """6-vector error [dx,dy,dz, drx,dry,drz] from current to target pose."""
    pos_err = target[:3, 3] - current[:3, 3]
    r_err = target[:3, :3] @ current[:3, :3].T
    # log-map of the rotation error to an axis-angle 3-vector
    trace_val = max(-1.0, min(3.0, float(np.trace(r_err))))
    angle = math.acos(max(-1.0, min(1.0, (trace_val - 1.0) / 2.0)))
    if abs(angle) < 1e-9:
        rot_err = np.zeros(3)
    elif abs(angle - math.pi) < 1e-6:
        # Near π: sin(angle) ≈ 0, use alternative axis extraction from
        # the symmetric part of r_err to avoid division by zero.
        # axis = normalize(diag(R) + 1) with sign from off-diagonals
        diag = np.array([r_err[0, 0], r_err[1, 1], r_err[2, 2]])
        axis = np.sqrt(np.maximum((diag + 1.0) / 2.0, 0.0))
        # Resolve sign ambiguity from off-diagonal elements
        if abs(axis[0]) > 1e-6:
            if r_err[0, 1] + r_err[1, 0] < 0:
                axis[1] = -axis[1]
            if r_err[0, 2] + r_err[2, 0] < 0:
                axis[2] = -axis[2]
        elif abs(axis[1]) > 1e-6:
            if r_err[1, 2] + r_err[2, 1] < 0:
                axis[2] = -axis[2]
        norm = np.linalg.norm(axis)
        if norm > 1e-12:
            axis /= norm
        rot_err = math.pi * axis
    else:
        rx = r_err[2, 1] - r_err[1, 2]
        ry = r_err[0, 2] - r_err[2, 0]
        rz = r_err[1, 0] - r_err[0, 1]
        rot_err = (angle / (2.0 * math.sin(angle))) * np.array([rx, ry, rz])
    return np.concatenate([pos_err, rot_err])


def _jacobian(ur_type: str, joints: np.ndarray, eps: float = 1e-6) -> np.ndarray:
    """Numerical 6x6 geometric Jacobian of tool0 w.r.t. the 6 joints."""
    base = fk(ur_type, joints)
    jac = np.zeros((6, 6))
    for i in range(6):
        perturbed = joints.copy()
        perturbed[i] += eps
        jac[:, i] = _pose_error(base, fk(ur_type, perturbed)) / eps
    return jac


def ik(
    ur_type: str,
    target: np.ndarray,
    seed: Sequence[float],
    max_iters: int = 120,
    tol: float = 1e-4,
    damping: float = 0.06,
    rot_weight: float = 1.0,
) -> Tuple[List[float], bool]:
    """Damped-least-squares IK for tool0.

    Seeded from ``seed`` (typically the previous waypoint's solution) so the
    result stays on a continuous, non-singular branch. Returns (joints, ok)
    where ok indicates the POSITION converged within ``tol`` (metres).

    ``rot_weight`` < 1 trades orientation accuracy for position reach. Near full
    arm extension (e.g. far pallet picks at ~0.79 m of 0.82 m max), demanding an
    exact straight-down tool axis is infeasible, but a position-priority solve
    (rot_weight≈0.1) still lets the gripper physically reach the part with only a
    few degrees of tool tilt. ``ok`` is judged on position alone for that reason.
    """
    q = np.array(seed, dtype=float)
    w = np.diag([1.0, 1.0, 1.0, rot_weight, rot_weight, rot_weight])
    for _ in range(max_iters):
        err = _pose_error(fk(ur_type, q), target)
        if np.linalg.norm(err[:3]) < tol:
            return list(q), True
        jac = w @ _jacobian(ur_type, q)
        ew = w @ err
        # DLS: dq = J^T (J J^T + λ²I)^-1 e
        jjt = jac @ jac.T + (damping ** 2) * np.eye(6)
        dq = jac.T @ np.linalg.solve(jjt, ew)
        # Clamp per-step joint change for stability.
        max_step = 0.35
        norm = np.linalg.norm(dq)
        if norm > max_step:
            dq *= max_step / norm
        q = q + dq
    err = _pose_error(fk(ur_type, q), target)
    return list(q), bool(np.linalg.norm(err[:3]) < tol)



