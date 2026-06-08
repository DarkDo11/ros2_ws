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
rclpy_mod.time = types.SimpleNamespace(Time=MagicMock)
rclpy_mod.duration = types.SimpleNamespace(Duration=MagicMock)
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
trajectory_msg_mod = sys.modules["trajectory_msgs.msg"]
trajectory_msg_mod.JointTrajectory = MagicMock
trajectory_msg_mod.JointTrajectoryPoint = MagicMock

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


def _tf(x, y, z, qx=0.0, qy=0.0, qz=0.0, qw=1.0):
    transform = types.SimpleNamespace()
    transform.transform = types.SimpleNamespace(
        translation=types.SimpleNamespace(x=x, y=y, z=z),
        rotation=types.SimpleNamespace(x=qx, y=qy, z=qz, w=qw),
    )
    return transform


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

    def test_failure_uses_registration_key_for_recovery(self):
        node = _make_node()
        callback = MagicMock(side_effect=RuntimeError("tf unavailable"))
        state = fsm.CallbackState(node, "SUBFSM/UPDATE_INSERT", callback)
        state.fsm_key = "UPDATE_INSERT"
        bb = _bb()
        result = state.execute(bb)
        self.assertEqual(result, fsm.FAILED)
        self.assertEqual(bb["resume_state"], "UPDATE_INSERT")


class TestRealStackUnload(unittest.TestCase):

    def test_bind_final_stack_reparents_parts_under_lower_housing(self):
        node = _make_node()
        node._LOOSE_PARTS = list(fsm.AssemblyFsmNode._LOOSE_PARTS)
        node._ASSEMBLY_ROOT_PART = fsm.AssemblyFsmNode._ASSEMBLY_ROOT_PART
        node.part_states = {
            name: fsm.PartState(parent_frame="world", link_name=name)
            for name in node._LOOSE_PARTS
        }

        def lookup_transform(parent_frame, child_frame, *_args, **_kwargs):
            self.assertEqual(parent_frame, "lower_housing_current_frame")
            index = node._LOOSE_PARTS.index(child_frame.replace("_current_frame", ""))
            return _tf(0.01 * index, 0.02 * index, 0.03 * index)

        node.tf_buffer.lookup_transform.side_effect = lookup_transform
        node._lookup_part_relative_pose = (
            lambda root, part: fsm.AssemblyFsmNode._lookup_part_relative_pose(
                node,
                root,
                part,
            )
        )

        fsm.AssemblyFsmNode._bind_final_assembly_stack(node)

        self.assertEqual(
            node.part_states["lower_housing"].parent_frame,
            "world",
        )
        for part_name in node._LOOSE_PARTS:
            if part_name == "lower_housing":
                continue
            self.assertEqual(
                node.part_states[part_name].parent_frame,
                "lower_housing_current_frame",
            )

    def test_pick_real_stack_binds_then_picks_root(self):
        node = _make_node()
        node._ASSEMBLY_ROOT_PART = "lower_housing"
        node._bind_final_assembly_stack = MagicMock()
        node._pick_part = MagicMock()

        fsm.AssemblyFsmNode._pick_real_assembly_stack(node, _bb(), (0.001, 0.0))

        node._bind_final_assembly_stack.assert_called_once_with()
        node._pick_part.assert_called_once_with(
            "ur5e_assembly",
            "lower_housing",
            (0.001, 0.0),
        )

    def test_place_real_stack_places_root_at_output_frame(self):
        node = _make_node()
        node._ASSEMBLY_ROOT_PART = "lower_housing"
        node.config = {"assembly": {"output_frame": "output_tray_drop_frame"}}
        node._place_part = MagicMock()

        fsm.AssemblyFsmNode._place_real_assembly_stack_at_output(
            node,
            _bb(),
            (0.0, -0.001),
        )

        node._place_part.assert_called_once_with(
            "ur5e_assembly",
            "lower_housing",
            "output_tray_drop_frame",
            (0.0, -0.001),
            precise=True,
        )


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


class TestSubFsmRetryKeyContract(unittest.TestCase):
    """Regression for the sub-FSM retry key mismatch (B3).

    OperationState writes resume_state/recovery_attempts using its fsm_key,
    while ErrorRecoveryState matches resume_state against its resumable set
    of registration keys. Before the fix, OperationState used the long
    display label (state_name, e.g. "PRESS_SUBFSM/PICK_X") that never matched
    the short registration key, so bias-retries inside any sub-FSM were
    silently dead and a single failure aborted the whole sub-FSM.
    """

    def _op_state(self, fsm_key, operation, robot_name="ur5e_press"):
        node = _make_node()
        state = fsm.OperationState(node, "SUBFSM/" + fsm_key, robot_name, operation)
        # _add_state sets fsm_key to the registration key; emulate that here.
        state.fsm_key = fsm_key
        return node, state

    def test_failure_writes_registration_key_to_resume_state(self):
        node, state = self._op_state(
            "PICK_X", MagicMock(side_effect=RuntimeError("ik fail"))
        )
        bb = _bb(recovery_attempts={})
        result = state.execute(bb)
        self.assertEqual(result, fsm.FAILED)
        # resume_state must be the registration key, NOT the display label.
        self.assertEqual(bb["resume_state"], "PICK_X")

    def test_recovery_resumes_operation_inside_subfsm(self):
        """End-to-end: OperationState failure -> ErrorRecoveryState resumes it."""
        node, op = self._op_state(
            "PICK_X", MagicMock(side_effect=RuntimeError("ik fail"))
        )
        bb = _bb(recovery_attempts={})
        op.execute(bb)

        recovery = fsm.ErrorRecoveryState(node, "SUBFSM/ERROR_RECOVERY", ["PICK_X"])
        recovery.fsm_key = "SUBFSM_ERROR_RECOVERY"
        result = recovery.execute(bb)
        # The recovery routes back to the operation instead of bailing to FAILED.
        self.assertEqual(result, "PICK_X")
        self.assertEqual(bb["recovery_attempts"]["PICK_X"], 1)

    def test_bias_advances_with_attempts(self):
        """The bias index is read from recovery_attempts under fsm_key."""
        seen_bias = []
        node, op = self._op_state(
            "PICK_X",
            lambda _bb, bias: seen_bias.append(bias),
        )
        bb = _bb(recovery_attempts={"PICK_X": 2})
        op.execute(bb)
        self.assertEqual(seen_bias, [fsm.BIAS_SEQUENCE[2]])


class TestInsertFollowsBase(unittest.TestCase):
    """Regression for the insert-teleport bug (B1).

    Pressed-in inserts were anchored to STATIC world frames (press_*/buffer_*),
    so when the arm carried the base part ~1.1 m between stations the insert
    stayed behind and the next UPDATE reparent snapped it across the cell.
    The fix anchors the insert to the base part's current_frame so it rides
    along, preserving the relative offset captured at bind time.
    """

    def test_reparent_binds_insert_to_base_current_frame(self):
        node = _make_node()
        node.part_states = {
            "main_bearing": fsm.PartState(parent_frame="world", link_name="main_bearing"),
            "lower_housing": fsm.PartState(parent_frame="world", link_name="lower_housing"),
        }

        def lookup_transform(parent_frame, child_frame, *_a, **_k):
            self.assertEqual(parent_frame, "lower_housing_current_frame")
            self.assertEqual(child_frame, "main_bearing_current_frame")
            return _tf(0.001, -0.002, 0.004)

        node.tf_buffer.lookup_transform.side_effect = lookup_transform
        node._lookup_part_relative_pose = (
            lambda parent, child: fsm.AssemblyFsmNode._lookup_part_relative_pose(
                node, parent, child
            )
        )

        fsm.AssemblyFsmNode._reparent_part_to_part(node, "main_bearing", "lower_housing")

        state = node.part_states["main_bearing"]
        self.assertEqual(state.parent_frame, "lower_housing_current_frame")
        self.assertEqual(state.xyz, (0.001, -0.002, 0.004))
        node._publish_part_frames.assert_called_once_with()
        # base part itself is untouched
        self.assertEqual(node.part_states["lower_housing"].parent_frame, "world")

    def test_bind_insert_state_returns_callback_that_reparents(self):
        node = _make_node()
        node._reparent_part_to_part = MagicMock()
        state = fsm.AssemblyFsmNode._bind_insert_state(
            node, "SUBFSM/UPDATE_MAIN_BEARING_ON_PRESS", "main_bearing", "lower_housing"
        )
        result = state.execute(_bb())
        self.assertEqual(result, fsm.OK)
        node._reparent_part_to_part.assert_called_once_with("main_bearing", "lower_housing")


if __name__ == "__main__":
    unittest.main(verbosity=2)
