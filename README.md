# ros2_ws

## Gearbox assembly FSM

`gearbox_sim` uses `scripts/assembly_fsm.py` as the strategic controller for
the planetary gearbox assembly cell. The node is a YASMIN hierarchical finite
state machine. The old linear implementation is preserved as
`scripts/assembly_sequence_legacy.py`; `scripts/assembly_state_machine.py` is
also left in place for compatibility.

### Current implementation scope

The package is a digital dry-run bench for validating the operation order,
workspace layout, TF frame structure, logical grasping, press cycles and screw
station sequencing.

Important limits of the current model:

- Part targets are TF-driven, but loose parts are synchronized in Gazebo through
  a logical attacher and `set_pose` calls rather than real contact grasping.
- The final unload now carries the real assembled stack: the FSM reparents the
  installed part frames under `lower_housing_current_frame`, grasps the lower
  housing, and moves the visible stack to the output tray. The old prebuilt
  visual handoff is no longer part of the normal route.
- Camera models and image bridges are present. A perception node that publishes
  TF-derived demo poses and status gates is included as
  `vision_status_node.py`; it is a perception surrogate, not image detection.
- The press controller has demo and strict modes. Strict mode requires interlock,
  fixture-ready and F/T samples, but no certified safety PLC, light curtain or
  hardware safety loop is modeled.
- F/T summaries from `ft_monitor.py` are part of FSM logic. The FSM checks force
  and torque limits around pick, place, press and screw operations.
- The screwdriver action simulates the tool slide/spin cycle; the FSM is
  responsible for moving UR3e to each screw frame before the tool cycle starts.
  In strict mode the action fails until real torque/seating feedback is added.

### Dependencies

Check what is already available after sourcing ROS 2:

```bash
source /opt/ros/$ROS_DISTRO/setup.bash
ros2 pkg list | grep -E "yasmin|smach"
```

If YASMIN is missing, install it explicitly:

```bash
sudo apt update
sudo apt install ros-$ROS_DISTRO-yasmin ros-$ROS_DISTRO-yasmin-ros ros-$ROS_DISTRO-yasmin-viewer
```

If Debian packages are not available for the ROS distro, build from source:

```bash
cd ~/ros2_ws/src
git clone https://github.com/uleroboticsgroup/yasmin.git
cd ~/ros2_ws
rosdep install --from-paths src --ignore-src -r -y
colcon build
```

### Run

Build and launch the full dry-run assembly cell:

```bash
cd ~/ros2_ws
source /opt/ros/$ROS_DISTRO/setup.bash
colcon build --packages-select gearbox_sim
source install/setup.bash
ros2 launch gearbox_sim assembly_cell.launch.py planner_dry_run:=true
```

Run only the FSM node in an already running cell:

```bash
ros2 run gearbox_sim assembly_fsm.py --ros-args \
  -p dry_run:=true \
  -p start_delay_sec:=5.0
```

The launch file starts the node as `assembly_fsm`. The node logs every state
entry and transition in the form:

```text
FSM enter: HOMING
FSM transition: HOMING --ok--> PRESS_SUBFSM
```

### Viewer graph

Start the YASMIN web viewer in another terminal:

```bash
source /opt/ros/$ROS_DISTRO/setup.bash
source ~/ros2_ws/install/setup.bash
ros2 run yasmin_viewer yasmin_viewer_node
```

Open `http://localhost:5000/` and select `GEARBOX_ASSEMBLY_FSM`. Use the
browser screenshot tool to capture the graph for the report. The top level is
kept readable and shows:

`IDLE`, `HOMING`, `PRESS_SUBFSM`, `ASSEMBLY_SUBFSM`, `SCREW_SUBFSM`,
`PICK_ASSEMBLY_STACK`, `PLACE_ASSEMBLY_STACK_AT_OUTPUT`, `ERROR_RECOVERY`,
`DONE`, `ABORT`.

### Top-level transition table

| State | Action | Success transition | Failure transition |
|---|---|---|---|
| `IDLE` | Initialize blackboard and wait `start_delay_sec` | `HOMING` | `ABORT` |
| `HOMING` | Move `ur5e_press`, `ur5e_assembly`, `ur3e_screw` to safe poses | `PRESS_SUBFSM` | `ERROR_RECOVERY` |
| `PRESS_SUBFSM` | Bearing/ring pressing operations | `ASSEMBLY_SUBFSM` | `ERROR_RECOVERY` |
| `ASSEMBLY_SUBFSM` | Main assembly station operations | `SCREW_SUBFSM` | `ERROR_RECOVERY` |
| `SCREW_SUBFSM` | Move UR3e to all configured screw frames and run the screwdriver action | `PICK_ASSEMBLY_STACK` | `ERROR_RECOVERY` |
| `PICK_ASSEMBLY_STACK` | Bind the installed real parts under `lower_housing_current_frame`, then pick the lower housing | `PLACE_ASSEMBLY_STACK_AT_OUTPUT` | `ERROR_RECOVERY` |
| `PLACE_ASSEMBLY_STACK_AT_OUTPUT` | Place the real assembled stack at `assembly.output_frame` | `DONE` | `ERROR_RECOVERY` |
| `ERROR_RECOVERY` | Safe-pose recovery and retry with next XY bias | failed top-level state | `ABORT` |
| `DONE` | Report successful completion | final `succeeded` | - |
| `ABORT` | Report unrecoverable failure | final `aborted` | - |

### Nested FSM transition summary

`PRESS_SUBFSM` repeats this sequence for the three press pairs
`lower_housing/main_bearing`, `cover/small_bearing`, and `housing/ring_gear`:

| Step pattern | Meaning |
|---|---|
| `PICK_<BASE>_FOR_PRESS` | Pick base part from its current frame |
| `PLACE_<BASE>_IN_PRESS` | Place base part into the press fixture |
| `PICK_<INSERT>` | Pick bearing or ring gear |
| `PLACE_<INSERT>_IN_PRESS` | Place insert part into the press fixture |
| `PRESS_<BASE>_<INSERT>` | Call `RunPressCycle` |
| `UPDATE_<INSERT>_ON_PRESS` | Reparent pressed child frame to the base press frame |
| `PICK_<BASE>_FROM_PRESS` | Pick the pressed subassembly |
| `PLACE_<BASE>_IN_BUFFER` | Move the subassembly to its buffer frame |
| `UPDATE_<INSERT>_ON_BUFFER` | Reparent pressed child frame to the buffer frame |

`ASSEMBLY_SUBFSM` performs:

| Sequence | Meaning |
|---|---|
| `PICK_LOWER_HOUSING_FROM_BUFFER -> PLACE_LOWER_HOUSING_AT_ASSEMBLY` | Move lower housing subassembly to assembly fixture |
| `UPDATE_MAIN_BEARING_AT_ASSEMBLY` | Reparent main bearing to assembly lower housing frame |
| `PICK/PLACE_PLANET_1`, `PICK/PLACE_PLANET_2`, `PICK/PLACE_PLANET_3` | Install three planet gears |
| `PICK/PLACE_SUN_GEAR -> PICK/PLACE_CARRIER` | Install sun gear and carrier |
| `PICK_HOUSING_FROM_BUFFER -> PLACE_HOUSING_AT_ASSEMBLY` | Install housing subassembly |
| `UPDATE_RING_GEAR_AT_ASSEMBLY` | Reparent ring gear to assembly housing frame |
| `PICK_COVER_FROM_BUFFER -> PLACE_COVER_AT_ASSEMBLY` | Install cover subassembly |
| `UPDATE_SMALL_BEARING_AT_ASSEMBLY` | Reparent small bearing to assembly cover frame |

`SCREW_SUBFSM` contains `RUN_SCREW_1` through `RUN_SCREW_4`, generated from
`assembly.screw_frames` in `config/assembly_cell.yaml`. Each screw operation
first moves the UR3e TCP to the screw frame and then calls the screwdriver
action server for the slide/spin cycle.

Every motion/action/service operation is a single-attempt state. On failure it
transitions to the nearest `ERROR_RECOVERY`, which calls `move_to_safe_pose`,
increments the retry index, applies the next XY bias from
`(0,0)`, `(0.0025,0)`, `(-0.0025,0)`, `(0,0.0025)`, `(0,-0.0025)`, and then
returns to the failed operation. After the last bias the FSM aborts.

### Demo and strict modes

The default launch keeps demo behavior enabled so the full dry-run sequence can
be shown end to end.

`vision_status_node.py` publishes:

- `/vision/part_status` as `std_msgs/String` with JSON fields such as
  `part_name`, `type_id`, `detected_frame`, `accepted`, `installing`,
  `teeth_aligned` and `done`.
- `/vision/part_pose/<part_name>` as `geometry_msgs/PoseStamped`.
- `vision_<part_name>_pose_frame` TF frames.

The current node uses known fixture/pallet TF frames as a perception surrogate.
With `assembly_fsm.py -p require_vision_status:=true`, pick transitions require
a fresh accepted status for the part.

`ft_monitor.py` publishes `/ur5e_press/ft_summary`,
`/ur5e_assembly/ft_summary` and `/ur3e_screw/ft_summary`. The FSM uses these
summaries when `ft_logic_enabled:=true`. Set `require_ft_samples:=true` to make
missing or stale F/T data fail the operation instead of only warning.

`assembly_fsm.py` uses `visual_unload_demo:=false` by default. The normal unload
sequence carries the real stack of part models to the output tray. If
`visual_unload_demo:=true` is passed, the node logs a deprecation warning; the
normal FSM path still uses the real stack rather than the prebuilt visual model.

`press_controller.py` uses `demo_mode:=true` by default. To make the press
service fail when safety or sensor evidence is missing, set:

```bash
ros2 run gearbox_sim press_controller.py --ros-args \
  -p demo_mode:=false \
  -p safety_interlock_closed:=true \
  -p fixture_ready:=true
```

`screwdriver_server.py` uses `demo_mode:=true` by default. In that mode success
means the simulated slide/spin cycle completed; torque and screw seating are not
verified. With `demo_mode:=false`, goals fail until a real driver feedback path
is implemented. `simulate_failure:=true` can be used to test FSM recovery:

```bash
ros2 run gearbox_sim screwdriver_server.py --ros-args \
  -p simulate_failure:=true
```
