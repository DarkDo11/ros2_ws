#!/usr/bin/env python3
"""Unit tests for assembly_fsm.py — FSM state logic without a live ROS2 stack."""

import sys
import types
import unittest
from pathlib import Path
from unittest.mock import MagicMock, patch

# ---------------------------------------------------------------------------
# Stub out ROS2 / YASMIN so tests run without a running ROS2 environment
# ---------------------------------------------------------------------------

def _make_stub_module(name):
    mod = types.ModuleType(name)
    sys.modules[name] = mod
    return mod

# rclpy
rclpy_mod = _make_stub_module("rclpy")
rclpy_mod.init = MagicMock()
rclpy_mod.spin = MagicMock()
rclpy_mod.shutdown = MagicMock()
_make_stub_module("rclpy.node").Node = object
_make_stub_module("rclpy.action").ActionClient = MagicMock
_make_stub_module("rclpy.action.client")
_make_stub_module("rclpy.action.server")
_make_stub_module("rclpy.qos")
_make_stub_module("rclpy.callback_groups")

# geometry_msgs / tf2
for m in ["geometry_msgs", "geometry_msgs.msg",
          "tf2_ros", "tf2_geometry_msgs",
          "sensor_msgs", "sensor_msgs.msg",
          "std_msgs", "std_msgs.msg",
          "trajectory_msgs", "trajectory_msgs.msg",
          "action_msgs", "action_msgs.msg"]:
    _make_stub_module(m)

geometry_msg_mod = sys.modules["geometry_msgs.msg"]
geometry_msg_mod.TransformStamped = MagicMock
geometry_msg_mod.Transform = MagicMock
geometry_msg_mod.Quaternion = MagicMock
sys.modules["tf2_ros"].Buffer = MagicMock
sys.modules["tf2_ros"].TransformBroadcaster = MagicMock
sys.modules["tf2_ros"].TransformListener = MagicMock
std_msg_mod = sys.modules["std_msgs.msg"]
std_msg_mod.Float64MultiArray = MagicMock
std_msg_mod.String = MagicMock

# gearbox_sim actions / services
for m in ["gearbox_sim", "gearbox_sim.action", "gearbox_sim.srv"]:
    _make_stub_module(m)
sys.modules["gearbox_sim.action"].RunScrewdriver = MagicMock
sys.modules["gearbox_sim.srv"].RunPressCycle = MagicMock
sys.modules["gearbox_sim.srv"].SetAttachment = MagicMock

# motion_planner
mp_mod = _make_stub_module("motion_planner")
mp_mod.MotionPlannerFacade = MagicMock

# yasmin
yasmin_mod = _make_stub_module("yasmin")

class _Blackboard(dict):
    pass

class _State:
    def __init__(self, outcomes):
        self.outcomes = list(outcomes)

yasmin_mod.Blackboard = _Blackboard
yasmin_mod.State = _State
yasmin_mod.StateMachine = MagicMock

yasmin_ros_mod = _make_stub_module("yasmin_ros")
yasmin_ros_mod.set_ros_loggers = MagicMock

yasmin_viewer_mod = _make_stub_module("yasmin_viewer")
yasmin_viewer_mod.YasminViewerPub = MagicMock

yaml_mod = _make_stub_module("yaml")
yaml_mod.safe_load = MagicMock(return_value={})

# ---------------------------------------------------------------------------
# Now we can safely import the module under test
# ---------------------------------------------------------------------------
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
import assembly_fsm as fsm

# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

def _make_node(logger=None):
    """Return a minimal mock node with a get_logger() that works."""
    node = MagicMock()
    lg = logger or MagicMock()
    node.get_logger.return_value = lg
    node.motion = MagicMock()
    return node


def _bb(**kwargs):
    bb = fsm.Blackboard()
    bb.update(kwargs)
    return bb


# ---------------------------------------------------------------------------
# Tests: bb_get
# ---------------------------------------------------------------------------

class TestBbGet(unittest.TestCase):

    def test_existing_key(self):
        bb = _bb(foo="bar")
        self.assertEqual(fsm.bb_get(bb, "foo"), "bar")

    def test_missing_key_returns_default(self):
        bb = _bb()
        self.assertIsNone(fsm.bb_get(bb, "missing"))

    def test_missing_key_custom_default(self):
        bb = _bb()
        self.assertEqual(fsm.bb_get(bb, "missing", 42), 42)

    def test_falsy_value_not_replaced(self):
        bb = _bb(val=0)
        self.assertEqual(fsm.bb_get(bb, "val", 99), 0)


# ---------------------------------------------------------------------------
# Tests: DelayState
# ---------------------------------------------------------------------------

class TestDelayState(unittest.TestCase):

    def test_execute_returns_ok(self):
        node = _make_node()
        state = fsm.DelayState(node, start_delay_sec=0.0)
        bb = _bb()
        result = state.execute(bb)
        self.assertEqual(result, fsm.OK)

    def test_execute_initialises_blackboard_keys(self):
        node = _make_node()
        state = fsm.DelayState(node, start_delay_sec=0.0)
        bb = _bb()
        state.execute(bb)
        self.assertEqual(bb["recovery_attempts"], {})
        self.assertEqual(bb["last_error"], "")
        self.assertEqual(bb["resume_state"], "")
        self.assertEqual(bb["recovery_robot"], "")


# ---------------------------------------------------------------------------
# Tests: TerminalState
# ---------------------------------------------------------------------------

class TestTerminalState(unittest.TestCase):

    def test_done_returns_succeeded(self):
        node = _make_node()
        state = fsm.TerminalState(node, "DONE", fsm.SUCCEEDED, "All done")
        result = state.execute(_bb())
        self.assertEqual(result, fsm.SUCCEEDED)
        node.get_logger().info.assert_called()

    def test_abort_returns_aborted(self):
        node = _make_node()
        state = fsm.TerminalState(node, "ABORT", fsm.ABORTED, "Aborted")
        result = state.execute(_bb())
        self.assertEqual(result, fsm.ABORTED)
        node.get_logger().error.assert_called()

    def test_abort_logs_last_error(self):
        node = _make_node()
        state = fsm.TerminalState(node, "ABORT", fsm.ABORTED, "Abort msg")
        bb = _bb(last_error="gripper timeout")
        state.execute(bb)
        call_args = str(node.get_logger().error.call_args)
        self.assertIn("gripper timeout", call_args)


# ---------------------------------------------------------------------------
# Tests: ErrorRecoveryState
# ---------------------------------------------------------------------------

class TestErrorRecoveryState(unittest.TestCase):

    def _make_state(self, resumable=("PICK_PART",)):
        node = _make_node()
        state = fsm.ErrorRecoveryState(node, "ERROR_RECOVERY", resumable)
        return node, state

    def test_first_retry_returns_resume_state(self):
        node, state = self._make_state(["PICK_PART"])
        bb = _bb(resume_state="PICK_PART", recovery_robot="", recovery_attempts={})
        result = state.execute(bb)
        self.assertEqual(result, "PICK_PART")

    def test_attempts_incremented(self):
        node, state = self._make_state(["PICK_PART"])
        bb = _bb(resume_state="PICK_PART", recovery_robot="", recovery_attempts={})
        state.execute(bb)
        self.assertEqual(bb["recovery_attempts"]["PICK_PART"], 1)

    def test_unknown_resume_state_returns_failed(self):
        node, state = self._make_state(["PICK_PART"])
        bb = _bb(resume_state="UNKNOWN_STATE", recovery_robot="", recovery_attempts={})
        result = state.execute(bb)
        self.assertEqual(result, fsm.FAILED)

    def test_exhausted_retries_returns_failed(self):
        """After all BIAS_SEQUENCE retries, must return FAILED."""
        node, state = self._make_state(["PICK_PART"])
        attempts = {"PICK_PART": len(fsm.BIAS_SEQUENCE) - 1}
        bb = _bb(resume_state="PICK_PART", recovery_robot="", recovery_attempts=attempts)
        result = state.execute(bb)
        self.assertEqual(result, fsm.FAILED)

    def test_safe_pose_called_when_robot_set(self):
        node, state = self._make_state(["PICK_PART"])
        bb = _bb(resume_state="PICK_PART", recovery_robot="ur5e_press", recovery_attempts={})
        state.execute(bb)
        node.motion.move_to_safe_pose.assert_called_once_with("ur5e_press")

    def test_safe_pose_exception_does_not_crash(self):
        node, state = self._make_state(["PICK_PART"])
        node.motion.move_to_safe_pose.side_effect = RuntimeError("comm error")
        bb = _bb(resume_state="PICK_PART", recovery_robot="ur5e_press", recovery_attempts={})
        result = state.execute(bb)
        # Should still return the resume state, not crash
        self.assertEqual(result, "PICK_PART")

    def test_empty_resume_state_returns_failed(self):
        node, state = self._make_state(["PICK_PART"])
        bb = _bb(resume_state="", recovery_robot="", recovery_attempts={})
        result = state.execute(bb)
        self.assertEqual(result, fsm.FAILED)

    def test_multiple_states_second_retry(self):
        node, state = self._make_state(["STEP_A", "STEP_B"])
        bb = _bb(resume_state="STEP_B", recovery_robot="", recovery_attempts={"STEP_B": 1})
        result = state.execute(bb)
        self.assertEqual(result, "STEP_B")
        self.assertEqual(bb["recovery_attempts"]["STEP_B"], 2)


# ---------------------------------------------------------------------------
# Tests: HomingState
# ---------------------------------------------------------------------------

class TestHomingState(unittest.TestCase):

    def test_returns_ok_when_motion_succeeds(self):
        node = _make_node()
        node.motion.robot_configs = ["ur5e_press", "ur5e_assembly"]
        node.motion.move_to_safe_pose.return_value = None
        state = fsm.HomingState(node)
        result = state.execute(_bb())
        self.assertEqual(result, fsm.OK)

    def test_returns_failed_when_motion_raises(self):
        node = _make_node()
        node.motion.robot_configs = ["ur5e_press"]
        node.motion.move_to_safe_pose.side_effect = RuntimeError("IK fail")
        state = fsm.HomingState(node)
        result = state.execute(_bb())
        self.assertEqual(result, fsm.FAILED)

    def test_homing_sets_recovery_robot_on_failure(self):
        node = _make_node()
        node.motion.robot_configs = ["ur5e_press"]
        node.motion.move_to_safe_pose.side_effect = RuntimeError("IK fail")
        state = fsm.HomingState(node)
        bb = _bb()
        state.execute(bb)
        self.assertIn("ur5e_press", bb.get("recovery_robot", "") or bb.get("last_error", ""))


# ---------------------------------------------------------------------------
# Tests: BIAS_SEQUENCE
# ---------------------------------------------------------------------------

class TestBiasSequence(unittest.TestCase):

    def test_first_bias_is_zero(self):
        self.assertEqual(fsm.BIAS_SEQUENCE[0], (0.0, 0.0))

    def test_has_five_entries(self):
        self.assertEqual(len(fsm.BIAS_SEQUENCE), 5)

    def test_all_entries_are_pairs(self):
        for entry in fsm.BIAS_SEQUENCE:
            self.assertEqual(len(entry), 2)


# ---------------------------------------------------------------------------
# Tests: CallbackState
# ---------------------------------------------------------------------------

class TestCallbackState(unittest.TestCase):

    def test_returns_ok_when_callback_succeeds(self):
        node = _make_node()
        callback = MagicMock(return_value=None)
        state = fsm.CallbackState(node, "TEST_STATE", callback)
        result = state.execute(_bb())
        self.assertEqual(result, fsm.OK)
        callback.assert_called_once()

    def test_returns_failed_when_callback_raises(self):
        node = _make_node()
        callback = MagicMock(side_effect=RuntimeError("fail"))
        state = fsm.CallbackState(node, "TEST_STATE", callback)
        result = state.execute(_bb())
        self.assertEqual(result, fsm.FAILED)


class TestDemoUnloadGuards(unittest.TestCase):

    def test_hide_parts_fails_when_visual_unload_demo_disabled(self):
        node = _make_node()
        node.visual_unload_demo = False
        with self.assertRaisesRegex(RuntimeError, "demo-only"):
            fsm.AssemblyFsmNode._hide_all_loose_parts(node, _bb(), (0.0, 0.0))

    def test_pick_assembled_fails_when_visual_unload_demo_disabled(self):
        node = _make_node()
        node.visual_unload_demo = False
        with self.assertRaisesRegex(RuntimeError, "demo-only"):
            fsm.AssemblyFsmNode._pick_assembled_gearbox(node, _bb(), (0.0, 0.0))

    def test_place_assembled_fails_when_visual_unload_demo_disabled(self):
        node = _make_node()
        node.visual_unload_demo = False
        with self.assertRaisesRegex(RuntimeError, "demo-only"):
            fsm.AssemblyFsmNode._place_assembled_at_output(node, _bb(), (0.0, 0.0))


class TestVisionAndFtGuards(unittest.TestCase):

    def test_vision_guard_accepts_fresh_status(self):
        node = _make_node()
        node.require_vision_status = True
        node.vision_status_timeout_sec = 10.0
        node.vision_statuses = {
            "sun_gear": (
                fsm.time.monotonic(),
                {
                    "part_name": "sun_gear",
                    "accepted": True,
                    "detected_frame": "vision_sun_gear_pose_frame",
                },
            )
        }
        fsm.AssemblyFsmNode._ensure_vision_ready(node, "sun_gear", "pick sun_gear")

    def test_vision_guard_rejects_missing_status(self):
        node = _make_node()
        node.require_vision_status = True
        node.vision_statuses = {}
        with self.assertRaisesRegex(RuntimeError, "no vision status"):
            fsm.AssemblyFsmNode._ensure_vision_ready(node, "sun_gear", "pick sun_gear")

    def test_ft_guard_rejects_force_limit(self):
        node = _make_node()
        node.ft_logic_enabled = True
        node.require_ft_samples = False
        node.max_contact_force_n = 40.0
        node.max_contact_torque_nm = 6.0
        node.ft_status_timeout_sec = 10.0
        node.ft_states = {
            "ur5e_assembly": fsm.FtState(
                force_mag_n=41.0,
                torque_mag_nm=1.0,
                stamp_monotonic=fsm.time.monotonic(),
            )
        }
        with self.assertRaisesRegex(RuntimeError, "force limit"):
            fsm.AssemblyFsmNode._check_ft_ok(
                node,
                "ur5e_assembly",
                "after placing sun_gear",
            )

    def test_ft_guard_allows_missing_samples_in_demo_mode(self):
        node = _make_node()
        node.ft_logic_enabled = True
        node.require_ft_samples = False
        node.ft_states = {}
        node._missing_ft_warned = set()
        fsm.AssemblyFsmNode._check_ft_ok(
            node,
            "ur5e_assembly",
            "before placing sun_gear",
        )


if __name__ == "__main__":
    unittest.main(verbosity=2)
