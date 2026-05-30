# ros2_ws

## Gearbox assembly FSM

`gearbox_sim` uses `scripts/assembly_fsm.py` as the strategic controller for
the planetary gearbox assembly cell. The node is a YASMIN hierarchical finite
state machine. The old linear implementation is preserved as
`scripts/assembly_sequence_legacy.py`; `scripts/assembly_state_machine.py` is
also left in place for compatibility.

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

`IDLE`, `HOMING`, `PRESS_SUBFSM`, `ASSEMBLY_SUBFSM`, `SCREW_SUBFSM`, `UNLOAD`,
`ERROR_RECOVERY`, `DONE`, `ABORT`.

### Top-level transition table

| State | Action | Success transition | Failure transition |
|---|---|---|---|
| `IDLE` | Initialize blackboard and wait `start_delay_sec` | `HOMING` | `ABORT` |
| `HOMING` | Move `ur5e_press`, `ur5e_assembly`, `ur3e_screw` to safe poses | `PRESS_SUBFSM` | `ERROR_RECOVERY` |
| `PRESS_SUBFSM` | Bearing/ring pressing operations | `ASSEMBLY_SUBFSM` | `ERROR_RECOVERY` |
| `ASSEMBLY_SUBFSM` | Main assembly station operations | `SCREW_SUBFSM` | `ERROR_RECOVERY` |
| `SCREW_SUBFSM` | Tighten all configured screw frames | `UNLOAD` | `ERROR_RECOVERY` |
| `UNLOAD` | Move finished assembly to `assembly.output_frame` | `DONE` | `ERROR_RECOVERY` |
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
`assembly.screw_frames` in `config/assembly_cell.yaml`.

Every motion/action/service operation is a single-attempt state. On failure it
transitions to the nearest `ERROR_RECOVERY`, which calls `move_to_safe_pose`,
increments the retry index, applies the next XY bias from
`(0,0)`, `(0.0025,0)`, `(-0.0025,0)`, `(0,0.0025)`, `(0,-0.0025)`, and then
returns to the failed operation. After the last bias the FSM aborts.
