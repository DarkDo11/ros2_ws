# Отчёт об обнаруженных багах — gearbox_sim

Дата анализа: 2026-06-11

---

## 🔴 Критические баги

### B01. `assembly_fsm.py:381` — `TransformListener` без `spin_thread=True`

**Файл:** `scripts/assembly_fsm.py`, строка 381  
**Проблема:**  
```python
self.tf_listener = TransformListener(self.tf_buffer, self)
```
FSM выполняется в отдельном daemon-потоке (`threading.Thread`), а `_lookup_part_relative_pose` делает `tf_buffer.lookup_transform`. Без `spin_thread=True` TF listener зависит от `rclpy.spin()` в main thread. Если main spin заблокирован или задержан, lookup из FSM-потока получит устаревшие данные или зависнет на timeout.

Во всех остальных нодах проекта (`motion_planner.py`, `vision_status_node.py`, `grasp_attacher.py`) используется `spin_thread=True`.

**Исправление:**
```python
self.tf_listener = TransformListener(self.tf_buffer, self, spin_thread=True)
```

---

### B02. `press_controller.py` — гонка данных на `_ft_capturing`

**Файл:** `scripts/press_controller.py`, строки 51, 91-93, 140-149  
**Проблема:**  
Флаг `_ft_capturing` пишется в service callback (строка 140: `self._ft_capturing = True`) и читается в subscription callback `_ft_callback` (строка 92: `if self._ft_capturing`) без синхронизации. Lock `_ft_lock` используется только вокруг `_ft_samples = []`, но не вокруг `_ft_capturing`.

Последовательность:
1. `_handle_cycle` делает `self._ft_samples = []` внутри lock
2. Затем `self._ft_capturing = True` **вне** lock
3. Между этими двумя операциями callback может начать писать в старый пустой список

В CPython GIL формально защищает, но:
- При free-threaded Python 3.13+ это сломается
- Семантически capture window может начаться между clear и flag-set, теряя первые семплы

**Исправление:** Обернуть start/stop capture в единый lock или использовать `threading.Event`.

---

### B03. `assembly_state_machine.py` / `assembly_sequence_legacy.py` — `main_bearing` и `small_bearing` не переносятся на output_frame при финальной выгрузке

**Файл:** `scripts/assembly_state_machine.py`, строки 344-351  
**Файл:** `scripts/assembly_sequence_legacy.py`, строки 344-351  
**Проблема:**  
В финальной последовательности выгрузки на output tray:
```python
self._move_part("ur5e_assembly", "lower_housing", self.config["assembly"]["output_frame"], precise=False)
self._set_part_frame("housing", ...)
self._set_part_frame("cover", ...)
self._set_part_frame("ring_gear", ...)
self._set_part_frame("carrier", ...)
self._set_part_frame("sun_gear", ...)
self._set_part_frame("planet_1", ...)
self._set_part_frame("planet_2", ...)
self._set_part_frame("planet_3", ...)
```

**Отсутствуют:**
- `self._set_part_frame("main_bearing", self.config["assembly"]["output_frame"])`
- `self._set_part_frame("small_bearing", self.config["assembly"]["output_frame"])`

В итоге эти два подшипника остаются визуально привязаны к `assembly_lower_housing_frame` и `assembly_cover_frame` соответственно, а не к output tray. При перемещении lower_housing на output, main_bearing и small_bearing остаются на месте сборки (в legacy-скриптах — они не используют reparent через lookup_transform как в assembly_fsm.py).

**Примечание:** в основном FSM (`assembly_fsm.py`) эта проблема решена через `_bind_final_assembly_stack()`, но оба legacy-скрипта всё ещё используются (зарегистрированы в CMakeLists.txt).

---

### B04. `assembly_cell.launch.py` — параметр `dry_run` передаётся как строка вместо bool

**Файл:** `launch/assembly_cell.launch.py`, строки 196, 211  
**Проблема:**  
```python
planner_dry_run = LaunchConfiguration("planner_dry_run")
# ...
"dry_run": planner_dry_run,  # LaunchConfiguration → string "true"/"false"
```

`LaunchConfiguration` в ROS2 launch передаётся как строка. Ноды `motion_planner.py` и `assembly_fsm.py` объявляют:
```python
self.declare_parameter("dry_run", True)  # bool default
```

Когда ROS2 launch передаёт строку `"true"` в параметр с bool default, rclpy **автоматически** конвертирует строку в bool. Однако если default не был объявлен (или при использовании `ParameterValue(type_=Parameter.Type.BOOL)`), строка `"true"` не будет конвертирована и `.bool_value` вернёт `False`.

Текущий код работает благодаря implicit conversion в rclpy, но это хрупкое поведение. При рефакторинге или добавлении нового node parameter без default может сломаться.

**Рекомендация:** Явно передавать bool через ParameterValue:
```python
from launch_ros.parameter_descriptions import ParameterValue
"dry_run": ParameterValue(planner_dry_run, value_type=bool),
```

---

## 🟡 Средние баги

### B05. `screwdriver_server.py` — `time.sleep()` блокирует single-threaded executor

**Файл:** `scripts/screwdriver_server.py`, строки ~109, ~114  
**Проблема:**  
```python
time.sleep(goal.duration_sec)  # 1.5с по умолчанию
time.sleep(goal.duration_sec)  # ещё 1.5с
```

Нода использует `rclpy.spin(node)` (single-threaded executor). Во время `time.sleep` (суммарно 3с) нода не обрабатывает:
- Новые goal requests
- Cancel requests для текущего goal
- Другие подписки

**Сравнение:** `press_controller.py` правильно использует `MultiThreadedExecutor`.

**Исправление:** Использовать `MultiThreadedExecutor` или неблокирующий цикл с проверкой `goal_handle.is_cancel_requested`.

---

### B06. `grasp_attacher.py` — неограниченное порождение daemon-потоков

**Файл:** `scripts/grasp_attacher.py`, метод `_move_model`  
**Проблема:**  
```python
threading.Thread(target=_run, daemon=True).start()
```

При 20 Hz sync (таймер 0.05с) + 6.7 Hz sync для unattached parts (таймер 0.15с), если `gz service` отвечает медленно (timeout 800ms), потоки могут накапливаться. `_in_flight` set помогает дедупликации, но при:
1. Медленных ответах gz service (>800ms)
2. Множестве частей (11 в проекте)

Можно получить десятки одновременных потоков. При масштабировании это приведёт к исчерпанию ресурсов.

**Исправление:** Использовать `concurrent.futures.ThreadPoolExecutor(max_workers=4)`.

---

### B07. `motion_planner.py` — `_joint_state_cb` crash при пустых velocity/effort

**Файл:** `scripts/motion_planner.py`, строки 126-145  
**Проблема:**  
```python
existing = dict(zip(self._latest_joint_state.name, zip(
    self._latest_joint_state.position,
    self._latest_joint_state.velocity,
    self._latest_joint_state.effort,
)))
```

Если предыдущее сообщение `JointState` имеет `velocity=[]` или `effort=[]` (что допустимо по спецификации `sensor_msgs/JointState`), то `zip()` усечёт результат до длины самого короткого списка. Результат: **потеря позиций суставов** для всех joints после первого отсутствующего velocity/effort.

Газебо-бриджи нередко публикуют JointState без velocity и effort.

**Исправление:** Проверять длину списков перед zip, или использовать `itertools.zip_longest`.

---

### B08. `assembly_fsm.py` — top-level ERROR_RECOVERY не покрывает sub-FSM-состояния

**Файл:** `scripts/assembly_fsm.py`, строка ~1167  
**Проблема:**  
```python
top_recovery = ErrorRecoveryState(
    self, "ERROR_RECOVERY",
    ["HOMING", "PICK_ASSEMBLY_STACK", "PLACE_ASSEMBLY_STACK_AT_OUTPUT"],
)
```

Когда sub-FSM (PRESS/ASSEMBLY/SCREW) **полностью** исчерпывает все 5 bias-retry и возвращает FAILED наверх, blackboard содержит `resume_state` = внутреннее состояние sub-FSM (например `"PICK_LOWER_HOUSING_FOR_PRESS"`). Top-level recovery не находит его в своём resumable-списке → немедленный ABORT.

**Последствие:** При любом неудачном sub-FSM (после исчерпания retry) нет возможности сделать homing и перезапустить sub-FSM целиком.

**Исправление:** Добавить `"PRESS_SUBFSM"`, `"ASSEMBLY_SUBFSM"`, `"SCREW_SUBFSM"` в resumable-список top-level recovery, или очищать `resume_state` при выходе из sub-FSM.

---

### B09. `press_controller.py` — CSV file handle leak

**Файл:** `scripts/press_controller.py`, строка ~72  
**Проблема:**  
```python
self._csv_file = open(csv_path, "a", newline="", encoding="utf-8")
```

Файл закрывается только в `destroy_node()`. При:
- Unhandled exception в конструкторе после open
- SIGKILL/OOM kill
- Crash в другом месте

Буферизованные данные будут потеряны. Python не гарантирует flush при аварийном завершении.

**Исправление:** Использовать context manager или `atexit.register(self._csv_file.close)`.

---

### B10. `assembly_demo.py` — `rclpy.shutdown()` вызывается из timer callback

**Файл:** `scripts/assembly_demo.py`, строки 302, 310  
**Проблема:**  
```python
def _finish_current_waypoint(self):
    # ...
    if rclpy.ok():
        rclpy.shutdown()
```

`_finish_current_waypoint` вызывается из timer callback (`_settle_current_waypoint`, `_waypoint_timeout_cb`), который исполняется внутри `rclpy.spin()`. Вызов `rclpy.shutdown()` изнутри spin loop может привести к deadlock или undefined behavior в зависимости от версии rclpy.

**Исправление:** Установить флаг `self._shutdown_requested = True` и проверять его снаружи spin, или использовать `self.executor.cancel()`.

---

### B11. `get_joints.py` / `assembly_demo.py` — `rclpy.shutdown()` из subscription callback

**Файл:** `scripts/get_joints.py`, строка 48  
**Проблема:** Аналогичная B10. `rclpy.shutdown()` вызывается из `_joint_state_cb`, которая исполняется внутри `rclpy.spin()`.

---

## 🟠 Баги симуляции (Gazebo / URDF / SDF)

### B12. `workcell_macros.xacro` — screwdriver tool topic mismatch с launch файлом

**Файл:** `urdf/include/workcell_macros.xacro`, строка в `screwdriver_tool` macro  
**Проблема:**  
В макросе `ur_robot_with_tool` screwdriver создаётся с:
```xml
<xacro:screwdriver_tool prefix="${prefix}" parent="${prefix}ft_sensor_link"
                        slide_topic="/${prefix}tool/joint_trajectory" .../>
```

Для ur3e_screw это даёт `slide_topic="/ur3e_screw_tool/joint_trajectory"`.

В launch файле `assembly_cell.launch.py` bridge topic:
```python
"/ur3e_screw_tool/joint_trajectory@trajectory_msgs/msg/JointTrajectory]gz.msgs.JointTrajectory",
```

Но `screwdriver_server.py` публикует на:
```python
self.declare_parameter("trajectory_topic", "/ur3e_screw_tool/joint_trajectory")
```

Это **совпадает** корректно. Однако в URDF topic задан как `/${prefix}tool/joint_trajectory` = `/ur3e_screw_tool/joint_trajectory`. **Проблема** в том, что ROS-Gazebo bridge переводит ROS topic → Gz topic, но в Gazebo plugin topic задан без leading `/`:

В `screwdriver_tool` macro:
```xml
<topic>${slide_topic}</topic>  → "/ur3e_screw_tool/joint_trajectory"
```

Gz плагины ожидают topic **без** leading slash в некоторых версиях Gazebo Harmonic. Если Gazebo игнорирует leading slash — работает; если нет — screwdriver slide joint не будет реагировать.

**Рекомендация:** Убрать leading `/` из `slide_topic` в macro вызове.

---

### B13. `workcell_macros.xacro` — gripper topic pattern несовместим с FSM

**Файл:** `urdf/include/workcell_macros.xacro`, строка в `simple_gripper_tool`  
**Проблема:**  
Gazebo gripper controller:
```xml
<topic>/${prefix}gripper/joint_trajectory</topic>
```

Для ur5e_press: `/${prefix}gripper/joint_trajectory` = `/ur5e_press_gripper/joint_trajectory`.

В FSM:
```python
self._gripper_pubs = {
    "ur5e_press": self.create_publisher(
        JointTrajectory, "/ur5e_press_gripper/joint_trajectory", 10
    ),
```

Но bridge в launch файле:
```python
"/ur5e_press_gripper/joint_trajectory@trajectory_msgs/msg/JointTrajectory]gz.msgs.JointTrajectory",
```

**Замечание:** Совпадает правильно. Но если Gazebo topic внутри — `/ur5e_press_gripper/joint_trajectory` — bridge direction `]` (ROS→GZ) пересылает на Gz topic с тем же именем. Но Gz plugin подписан на `/${prefix}gripper/joint_trajectory`. Для `prefix="ur5e_press_"` это `/ur5e_press_gripper/joint_trajectory` ≠ `/${prefix}gripper/...` = `/ur5e_press_gripper/...`. 

Фактически `/${prefix}gripper/joint_trajectory` раскрывается в `/ur5e_press_gripper/joint_trajectory` — **ОК**, совпадает. Однако обратите внимание: prefix включает trailing underscore (`ur5e_press_`), поэтому topic = `/ur5e_press_gripper/joint_trajectory`. Но launch bridge использует `/ur5e_press_gripper/joint_trajectory` — **нет underscore** перед gripper!

`prefix = "ur5e_press_"` → `/${prefix}gripper/...` = `/ur5e_press_gripper/...` ✓

Это совпадает. Баг отсутствует, оставляю как **потенциальное место путаницы**.

---

### B14. `assembly_cell.sdf` — минимальный мир без furniture/fixtures

**Файл:** `worlds/assembly_cell.sdf`  
**Проблема:**  
SDF мир содержит только:
- Ground plane
- Directional light
- Physics и системные plugins

Все fixtures, столы, роботы, паллеты подгружаются через URDF spawn (OpaqueFunction → xacro → spawn). Это **by design**, но SDF мир не содержит:
- `gz::sim::systems::Contact` plugin (нет контактной физики между частями)
- `gz::sim::systems::JointPositionController` (используется JointTrajectoryController через URDF)

**Последствие:** Части проваливаются сквозь столы/fixtures если их kinematic flag не установлен. Spawn из `part_spawner.py` ставит `<kinematic>true</kinematic>` и `<gravity>false</gravity>` — это предотвращает падение, но исключает любое физическое взаимодействие (collision response отсутствует).

---

### B15. `part_spawner.py` — spawn позиции не совпадают с TF pick frames

**Файл:** `scripts/part_spawner.py`  
**Проблема:**  
Части спавнятся в фиксированных мировых координатах:
```python
{"name": "lower_housing", ..., "x": -1.26, "y": -0.24, "z": 0.915},
```

Pick frame в URDF:
```xml
<xacro:fixed_frame parent="world" name="pallet_a_lower_housing_pick_frame"
                   xyz="${pallet_a_xyz[0]} ${pallet_a_xyz[1] + 0.03} ${pallet_a_xyz[2] + 0.12}"
                   rpy="3.14159 0 0"/>
```

Где `pallet_a_xyz = [-1.26, -0.27, 0.84]`, так что pick frame = `(-1.26, -0.24, 0.96)`.

Spawn: `z=0.915`, pick frame: `z=0.96`. Разница 45 мм. Это означает, что `grasp_attacher` будет синхронизировать Gz модель с `current_frame` TF (который изначально = pick_frame), так что модель телепортируется в 0.96 при первом sync tick.

**Последствие:** Визуальный скачок при старте: часть появляется на z=0.915, затем через ~0.15с перепрыгивает на z=0.96. Не критично для логики, но видно визуально.

---

### B16. `motion_planner.py` — `tcp_offset_from_tool0_m` не задан в конфиге для ur3e_screw

**Файл:** `scripts/motion_planner.py`, строка 95 + `config/assembly_cell.yaml`  
**Проблема:**  
```python
tcp_z = float(data.get("tcp_offset_from_tool0_m", 0.203))
```

Дефолт 0.203 — это offset для gripper (ur5e). Но для ur3e_screw TCP offset совсем другой: из URDF `screwdriver_tool` macro:
- ft_sensor → screwdriver_body: 0.018
- body → slide_joint origin: 0.05
- slide: limit upper=0.08 (variable, but at 0 = origin)
- slide → spindle origin: 0.12
- spindle → tcp_frame: 0.055
- Total static (slide=0): 0.018 + 0.05 + 0.12 + 0.055 = 0.243

Но `wrist_3_to_ft_joint` origin = 0.009, а tool0 определяется через flange transforms. Реальный tcp_offset_from_tool0 для screwdriver ≈ 0.009 + 0.018 + 0.05 + 0.12 + 0.055 = 0.252, не 0.203.

Разница ~49 мм. Это влияет на IK — screwdriver TCP будет вычисляться неверно.

**Исправление:** Добавить в `assembly_cell.yaml`:
```yaml
ur3e_screw:
  tcp_offset_from_tool0_m: 0.252
```

---

### B17. `motion_planner.py` — `_kin_cache` никогда не инвалидируется

**Файл:** `scripts/motion_planner.py`  
**Проблема:**  
```python
self._kin_cache: Dict[str, tuple] = {}
```
Кэш `(T_world_base, T_tool0_tcp)` заполняется один раз при первом обращении. Если TF для base_link или tool_frame изменится — кэш не обновится.

В данном проекте роботы неподвижны, но:
- При динамическом перемещении базы (relocatable robots)
- При изменении tool (tool change)
- При перезапуске симуляции без перезапуска ноды

кэш будет содержать устаревшие данные.

**Серьёзность:** Низкая для текущего проекта, средняя в общем случае.

---

## 🟢 Незначительные / стилистические проблемы

### B18. `assembly_state_machine.py` — таймер `_start_once` не отменяется

**Файл:** `scripts/assembly_state_machine.py`, строка 73  
**Проблема:**  
```python
self.create_timer(start_delay, self._start_once)
```

Таймер `create_timer` с `period=start_delay_sec` будет **повторяться** каждые N секунд. Хотя `_started` флаг предотвращает повторный запуск, таймер продолжает вызывать `_start_once()` каждые 5 секунд бесполезно.

В `assembly_fsm.py` используется `create_timer(0.1, self._start_once)` — тоже не отменяется после первого вызова, но срабатывает каждые 100 мс.

**Исправление:** Отменять таймер после первого вызова:
```python
def _start_once(self):
    if self._started:
        return
    self._started = True
    self._start_timer.cancel()  # остановить повторные вызовы
```

---

### B19. `vision_status_node.py` — потеря точности timestamp

**Файл:** `scripts/vision_status_node.py`  
**Проблема:**  
```python
status["stamp_sec"] = float(self.get_clock().now().nanoseconds) * 1e-9
```

`nanoseconds` для 2026 года ≈ 1.75×10^18. `float64` имеет ~15-16 значащих цифр → потеря точности в младших наносекундах (~100 нс). Не критично для текущего использования, но timestamps могут не быть строго монотонными.

---

### B20. `ur_kinematics.py` — `_pose_error` некорректна для углов близких к π

**Файл:** `scripts/ur_kinematics.py`, функция `_pose_error`  
**Проблема:**  
```python
angle = math.acos(max(-1.0, min(1.0, (np.trace(r_err) - 1.0) / 2.0)))
if abs(angle) < 1e-9:
    rot_err = np.zeros(3)
else:
    rx = r_err[2, 1] - r_err[1, 2]
    ry = r_err[0, 2] - r_err[2, 0]
    rz = r_err[1, 0] - r_err[0, 1]
    rot_err = (angle / (2.0 * math.sin(angle))) * np.array([rx, ry, rz])
```

При angle ≈ π, `sin(angle)` ≈ 0, и деление `angle / (2.0 * sin(angle))` → ∞. Это численно нестабильно для больших ошибок ориентации (180° поворот). Damped-least-squares IK с таким seed не сойдётся.

**Последствие:** IK будет выдавать NaN/Inf если начальный seed далеко от target по ориентации. На практике seed — предыдущий waypoint, и ошибка мала, но при первом waypoint далёкого от home это может проявиться.

**Исправление:** Добавить проверку:
```python
if abs(math.sin(angle)) < 1e-6:
    # Near-pi: use alternative axis extraction
    ...
```

---

### B21. `assembly_fsm.py` — `HomingState` использует `self.state_name` вместо `self.fsm_key`

**Файл:** `scripts/assembly_fsm.py`, класс `HomingState`  
**Проблема:**  
```python
blackboard["resume_state"] = self.state_name
```

В текущей реализации `state_name = "HOMING"` и `fsm_key` тоже устанавливается в `"HOMING"` в `_add_state`. Но паттерн отличается от `OperationState`/`CallbackState` которые используют `self.fsm_key`. При рефакторинге или переименовании это создаст несоответствие.

---

### B22. `ros_gz_bridge.yaml` — устаревший config для старого single-arm launch

**Файл:** `config/ros_gz_bridge.yaml`  
**Проблема:**  
YAML config описывает bridge для:
- `/ur5e/joint_states_gz`
- `/ur5e/ft_sensor`
- `/ur5e/joint_trajectory`

Это соответствует **старому** `sim_assembly.launch.py` (single UR5e). Основной launch файл `assembly_cell.launch.py` использует:
- `/ur5e_press/...`
- `/ur5e_assembly/...`
- `/ur3e_screw/...`

И задаёт bridge через аргументы command-line в ноде, а не через YAML. YAML config не используется в основном launch — это мёртвый код, который может запутать разработчиков.

---

### B23. `part_spawner.py` — `use_sim_time=True` без `rclpy.spin()`

**Файл:** `scripts/part_spawner.py`  
**Проблема:**  
```python
node.spawn_all()  # блокирует main thread, sync calls
# rclpy.spin() никогда не вызывается
```

С `use_sim_time=True` clock node нуждается в spin для получения `/clock` сообщений. Но `spawn_all()` выполняется синхронно и завершает ноду. `node.get_clock().now()` никогда не обновляется — всегда вернёт time=0.

Это не влияет на функциональность (spawner не использует timestamps), но timestamps в логах будут нулевые.

---

### B24. `assembly_fsm.py` / `motion_planner.py` — busy-wait в `_wait_for_future`

**Файл:** `scripts/assembly_fsm.py`, `scripts/motion_planner.py`  
**Проблема:**  
```python
while rclpy.ok() and not future.done():
    time.sleep(0.01)
```

Busy-wait с 10мс poll interval. За одну FSM операцию (pick/place) может быть 2-4 service/action calls по 5-10с timeout каждый. Суммарно: ~100-400 итераций × 2-4 вызова = сотни wakeups.

Не критично, но неидиоматично для rclpy. Правильный паттерн — `rclpy.spin_until_future_complete()`, но он несовместим с daemon-thread архитектурой FSM.

---

### B25. `assembly_cell.launch.py` — `gz_headless` launch argument объявлен, но не используется

**Файл:** `launch/assembly_cell.launch.py`, строка 250  
**Проблема:**  
```python
DeclareLaunchArgument("gz_headless", default_value="false"),
```

Этот аргумент объявлен, но нигде не проверяется в launch логике. GUI управляется через `gz_gui` аргумент. `gz_headless` — мёртвый параметр.

---

## 🟠 Дополнительные баги симуляции

### B26. `gearbox_gazebo.urdf.xacro` — sun gear использует mesh `satellite.STL` (неправильное имя)

**Файл:** `urdf/gearbox_gazebo.urdf.xacro`, строка 103, 232  
**Проблема:**  
```xml
<!-- sun_collision_mesh / sun visual -->
<mesh filename="file://$(find gearbox_sim)/meshes/satellite.STL" .../>
```

Mesh файл `meshes/satellite.STL` — это **солнечная шестерня** (sun gear), но файл назван "satellite" (так по-русски называют сателлит/planet gear). При этом в `part_spawner.py` для планет (planet_1/2/3) тоже используется `satellite.STL` из `meshes/nema17/`:
```python
{"name": "planet_1", "stl": "satellite.STL", ...},
```

А для sun_gear:
```python
{"name": "sun_gear", "stl": "Sun_gear.STL", ...},
```

**Итого:**
- `meshes/satellite.STL` — используется в `gearbox_gazebo.urdf.xacro` для **sun gear** (неверное зубчатое колесо!)
- `meshes/nema17/satellite.STL` — используется в `part_spawner.py` для **planet gears** (корректно, сателлит = planet)
- `meshes/nema17/Sun_gear.STL` — используется в `part_spawner.py` для **sun gear** (корректно)

В `gearbox_gazebo.urdf.xacro` sun gear визуально отображается как planet gear mesh. Это **визуальная ошибка** в sim_assembly.launch.py demo.

---

### B27. `workcell_macros.xacro` — PID gains для ur3e wrist joints слишком высокие

**Файл:** `urdf/include/workcell_macros.xacro`, macro `ur_robot_motion_plugins`  
**Проблема:**  
PID-контроллер для **всех** роботов использует одинаковые gains:
```xml
<!-- wrist_1: -->
<position_p_gain>140.0</position_p_gain>
<position_cmd_max>60.0</position_cmd_max>
```

Но UR3e wrist joints имеют max_effort = **9.0 Nm** (из `joint_limits.yaml`), тогда как UR5e — 28.0 Nm. PID с `position_cmd_max=60.0` превышает физический effort limit UR3e в ~6.7 раз. Gazebo будет насыщать команды на реальном effort limit joint'a, но:
1. Высокий P gain + низкий effort limit → oscillations (контроллер "хочет" приложить 60 Нм, может только 9 → overshoot → reverse → oscillation)
2. Screwdriver slide и spindle не имеют gains в основном macro — добавлены отдельно в `screwdriver_tool` с корректными значениями

**Последствие:** Wrist-joints UR3e будут осциллировать/дрожать при больших перемещениях, что заметно на screw station precision operations.

**Исправление:** Уменьшить gains для ur3e или параметризовать per-robot-type.

---

### B28. `workcell_macros.xacro` — FT sensor без `<force_torque><noise>` даёт идеальные показания

**Файл:** `urdf/include/workcell_macros.xacro`, строка в `ur_robot_with_tool`  
**Проблема:**  
```xml
<sensor name="${prefix}force_torque_sensor" type="force_torque">
  <force_torque>
    <frame>child</frame>
    <measure_direction>parent_to_child</measure_direction>
  </force_torque>
</sensor>
```

Нет `<noise>` элемента. В Gazebo Harmonic FT sensor без шума публикует абсолютно чистые данные (0.000 N при отсутствии нагрузки). Это делает:
1. `ft_monitor.py` threshold crossing **никогда не сработает** в idle (force_mag = 0.0 < threshold 5.0 — ОК), но при реальном контакте сразу даст perfect step response
2. `assembly_fsm.py` `_check_ft_ok` с `max_contact_force_n=85.0` никогда не сработает ложно

**Последствие:** Тестирование FSM с FT guard в симуляции не покрывает реальные шумные условия. При переходе на реальный робот threshold будет ложно триггериться из-за baseline noise.

**Рекомендация:** Добавить реалистичный шум:
```xml
<force_torque>
  <noise>
    <type>gaussian</type>
    <mean>0.0</mean>
    <stddev>0.5</stddev>
  </noise>
</force_torque>
```

---

### B29. `assembly_cell.sdf` — нет `<contact>` plugin → collision response не работает

**Файл:** `worlds/assembly_cell.sdf`  
**Проблема:**  
SDF мир загружает только:
```xml
<plugin filename="gz-sim-physics-system" name="gz::sim::systems::Physics"/>
<plugin filename="gz-sim-forcetorque-system" name="gz::sim::systems::ForceTorque"/>
```

Но **не** загружает:
- `gz::sim::systems::Contact` — без него невозможно получать contact events
- `gz::sim::systems::Imu` — нет IMU сенсоров (не используется)

Без Contact plugin:
- Части спавненные `part_spawner.py` с `<kinematic>true</kinematic>` не имеют collision response и проваливаются сквозь стол если отключить kinematic
- Даже при включённой физике, press ram не физически давит на деталь — collision detection работает (для force_torque sensor), но feedback нет
- Если убрать `<gravity>false</gravity>` у частей, они провалятся сквозь паллеты

**Последствие:** Симуляция не может моделировать реальное прессование — FT sensor показывает силы только от инерции робота, не от контакта с деталью.

---

### B30. `part_spawner.py` — SDF `<kinematic>true</kinematic>` deprecated syntax в Gazebo Harmonic

**Файл:** `scripts/part_spawner.py`, функция `_build_sdf`  
**Проблема:**  
```python
f'<kinematic>true</kinematic>'
```

В Gazebo Harmonic (gz-sim 8+) `<kinematic>` тег внутри `<link>` deprecated в пользу `<link>` + отсутствие `<inertial>` или использования плагина `gz::sim::systems::PosePublisher`. В некоторых версиях `<kinematic>` просто игнорируется.

**Текущее поведение:** Части спавнятся с `<gravity>false</gravity>` что предотвращает падение, но `<kinematic>true</kinematic>` может не работать → `set_pose` может не перемещать модель (зависит от версии Gz).

**Исправление:** Использовать `<static>false</static>` на уровне модели + `<gravity>false</gravity>` на уровне link, или проверить версию Gazebo и использовать актуальный API.

---

### B31. `workcell_macros.xacro` — одинаковые `velocity_p_gain` только у последнего joint в `ur5e_robotiq_ft.urdf.xacro`

**Файл:** `urdf/ur5e_robotiq_ft.urdf.xacro`, строки 268-271  
**Проблема:**  
В JointTrajectoryController plugin для single-arm demo:
```xml
<joint_name>$(arg prefix)wrist_3_joint</joint_name>
...
<velocity_p_gain>2.0</velocity_p_gain>
<velocity_i_gain>0.0</velocity_i_gain>
<velocity_d_gain>0.2</velocity_d_gain>
```

`velocity_p_gain`/`velocity_d_gain` указаны **только** после последнего joint. В Gz `JointTrajectoryController` эти параметры применяются **к предыдущему** определению joint (wrist_3). Остальные 5 joints остаются с default velocity gains (0 или 1, зависит от версии).

В `workcell_macros.xacro` для multi-arm scene velocity gains не указаны вовсе — все joints используют defaults.

**Последствие:** wrist_3 в single-arm demo имеет velocity damping, остальные — нет. Это создаёт асимметричное поведение при trajectory following: wrist_3 будет более стабильным при tracking, но shoulder/elbow могут иметь overshoot.

---

### B32. `workcell_macros.xacro` — camera sensors без `<update_rate>` matching bridge frequency

**Файл:** `urdf/include/workcell_macros.xacro`, macro `camera_stub`  
**Проблема:**  
```xml
<sensor name="${prefix}_camera_sensor" type="camera">
  <always_on>true</always_on>
  <update_rate>15.0</update_rate>
  <topic>${topic}</topic>
```

Камеры обновляются на 15 Hz. Bridge (`ros_gz_image image_bridge`) не имеет throttling — он будет пересылать все 15 fps. Но:
1. Нет `<trigger>` или `<triggered>` — камеры всегда снимают даже когда vision_status_node их не использует (TF-based surrogate)
2. 5 камер × 640×480 × 3 bytes × 15 fps = **~70 MB/s** пропускной способности shared memory
3. `assembly_cell.launch.py` запускает **все 5 image bridges** безусловно

**Последствие:** Значительная нагрузка на GPU (rendering) и CPU (bridge + transport) без реальной пользы — никакой perception node не обрабатывает images. Это может замедлять физику (Sensors system и Physics system делят render thread в ogre2).

---

### B33. `assembly_cell.launch.py` — Gz GUI запускается без задержки параллельно с server

**Файл:** `launch/assembly_cell.launch.py`, строки 123, 258-259  
**Проблема:**  
```python
gz_gui = ExecuteProcess(
    cmd=["gz", "sim", "-g", "-v", "2"],
    ...
)
# ...
gz_sim,
gz_gui,  # запускается параллельно с server
```

GUI процесс (`gz sim -g`) подключается к server через transport. Если GUI запустится **раньше** чем server инициализирует world, GUI не увидит мир и покажет пустую сцену. Комментарий в коде говорит "Started after a short delay so the server is up", но фактически `gz_gui` стоит на том же уровне что и `gz_sim` — они запускаются **одновременно**.

**Исправление:** Обернуть gz_gui в `TimerAction(period=2.0, actions=[gz_gui])`.

---

### B34. `part_spawner.py` — `time.sleep(2.0)` между spawn'ами избыточна и ненадёжна

**Файл:** `scripts/part_spawner.py`, строка в `spawn_all`  
**Проблема:**  
```python
for part in PARTS:
    _spawn_part(self, part)
    time.sleep(2.0)
```

11 частей × 2.0с delay = **22 секунды** на spawn всех частей. При этом:
- `gz service` вызов уже синхронный (timeout 10s)  
- Между spawn'ами нет необходимости ждать — Gazebo обрабатывает EntityFactory мгновенно
- Assembly FSM стартует через `start_delay_sec=5.0` (в launch через `TimerAction period=4+4=8s` + `TimerAction period=8s` для spawner = 16s после gz_sim start)

Но spawner сам начинает работу через 16с, и spawn всех частей занимает ещё 22с. FSM (стартует через 12с после gz_sim) будет искать части через TF — а `grasp_attacher` sync зависит от spawn. Если FSM стартует раньше чем spawner закончит, части будут отсутствовать в Gazebo.

**Timing:**
- gz_sim start: t=0
- spawn_scene (URDF): t=4
- press_controller, motion_planner, assembly_fsm: t=8
- part_spawner starts: t=12 (TimerAction 4+8=12)
- part_spawner wait_for_gazebo: +?s
- part_spawner spawn_all finishes: t=12 + 22 = t=34

assembly_fsm: стартует при t=8, delay=5s → FSM starts at t=13. Spawner finishes at t=34.  
**FSM пытается pick части которые ещё не spawn'ены!**

TF frames (pallet pick frames) существуют из URDF spawn, но Gazebo models частей ещё нет. `grasp_attacher` будет пытаться `set_pose` для несуществующих моделей — fail silently. Визуально: части появляются во время выполнения FSM, что создаёт скачки.

**Исправление:** Увеличить `start_delay_sec` FSM до 40+с, или убрать `time.sleep(2.0)` между spawn'ами, или добавить readiness check.

---

### B35. `workcell_macros.xacro` — press ram axis `-Z` может путать с stroke direction

**Файл:** `urdf/include/workcell_macros.xacro`, строка 587  
**Проблема:**  
```xml
<joint name="${prefix}ram_joint" type="prismatic">
  <axis xyz="0 0 -1"/>
  <limit lower="0.0" upper="0.12" .../>
</joint>
```

Axis `-Z` + `lower=0, upper=0.12` означает: при joint position 0 → ram в верхней позиции, при position 0.12 → ram смещён на 0.12м **вниз** (в направлении -Z).

`press_controller.py`:
```python
self._publish(joint_name, [0.0, request.stroke_m, 0.0], [0.5, 1.2, 2.2])
```

Отправляет `stroke_m=0.035` → joint position 0.035 → ram опускается на 35 мм. Это **корректно**.

Однако `force_torque` sensor на `wrist_3_to_ft_joint` робота ur5e_press измеряет force на **роботе**, не на прессе. Press ram двигается независимо от робота. FT показания press_controller.py (`msg.force.z`) — это сила на FT sensor руки, которая НЕ держит деталь в прессе (рука уже ушла). 

**Последствие:** `press_controller.py` пишет в CSV `peak_Fz` от **робота** ur5e_press (через `/ur5e_press/ft_sensor`), а не от press ram. После того как рука ушла от пресса, FT sensor на руке покажет ~0. CSV log будет содержать бессмысленные данные (peak≈0) для всех press cycles.

**Исправление:** Добавить FT sensor на press ram joint, или подписаться на force данные непосредственно от press contact.

---

### B36. `assembly_scene.sdf` — workbench links без `<joint>` связи → модель нефизична

**Файл:** `worlds/assembly_scene.sdf`  
**Проблема:**  
```xml
<model name="workbench">
  <static>true</static>
  <link name="bench_top">...</link>
  <link name="leg_fl">...</link>
  <link name="leg_fr">...</link>
  <link name="leg_rl">...</link>
  <link name="leg_rr">...</link>
  <!-- NO <joint> elements connecting legs to bench_top -->
</model>
```

В SDF, links без joints внутри static model — это **допустимо** (все links зафиксированы в world frame по их `<pose>`). Но в Gazebo Harmonic, если `<static>true</static>` удалить (для dynamic simulation), ноги упадут отдельно от столешницы. Это не баг как таковой (static=true), но делает модель непортируемой.

---

### B37. `gearbox_gazebo.urdf.xacro` — `<gazebo><static>true</static></gazebo>` конфликтует с `sim_assembly.launch.py` spawn position

**Файл:** `urdf/gearbox_gazebo.urdf.xacro`  
**Проблема:**  
В `base` variant:
```xml
<gazebo>
  <static>true</static>
</gazebo>
```

Модель spawn'ится из `sim_assembly.launch.py`:
```python
spawn_gearbox_base = Node(
    package="ros_gz_sim", executable="create",
    arguments=["-x", "-0.33", "-y", "0.34", "-z", "0.79", ...],
)
```

Но `<static>true</static>` в URDF → Gazebo `<static>` = true в SDF. Static модель **не перемещается** через `set_pose` или spawn coordinates в некоторых версиях Gz Sim (spawn position через `-x/-y/-z` аргументы `ros_gz_sim create` применяется к **model pose**, что работает для static моделей). Это **не** баг, но стоит проверить на конкретной версии.

---

## Сводная таблица

| # | Файл | Серьёзность | Категория | Суть |
|---|---|---|---|---|
| B01 | assembly_fsm.py | 🔴 Крит. | Threading | TF listener без spin_thread |
| B02 | press_controller.py | 🔴 Крит. | Race cond. | _ft_capturing без lock |
| B03 | assembly_state_machine.py | 🔴 Крит. | Логика | main_bearing/small_bearing не на output |
| B04 | assembly_cell.launch.py | 🟡 Средн. | Config | dry_run как string вместо bool |
| B05 | screwdriver_server.py | 🟡 Средн. | Threading | sleep блокирует executor |
| B06 | grasp_attacher.py | 🟡 Средн. | Resources | Неогр. thread spawn |
| B07 | motion_planner.py | 🟡 Средн. | Data | JointState zip truncation |
| B08 | assembly_fsm.py | 🟡 Средн. | FSM | Top-level recovery ≠ sub-FSM |
| B09 | press_controller.py | 🟡 Средн. | Resources | CSV handle leak |
| B10 | assembly_demo.py | 🟡 Средн. | Threading | shutdown() из callback |
| B11 | get_joints.py | 🟡 Средн. | Threading | shutdown() из callback |
| B12 | workcell_macros.xacro | 🟠 Сим. | Topics | Potential leading slash issue |
| B14 | assembly_cell.sdf | 🟠 Сим. | Physics | Нет contact plugin |
| B15 | part_spawner.py | 🟠 Сим. | Visual | Spawn Z ≠ pick frame Z |
| B16 | motion_planner.py | 🟠 Сим. | IK | tcp_offset default неверен для ur3e |
| B17 | motion_planner.py | 🟢 Низк. | Cache | Кэш не инвалидируется |
| B18 | assembly_state_machine.py | 🟢 Низк. | Timer | Таймер не отменяется |
| B19 | vision_status_node.py | 🟢 Низк. | Precision | Потеря точности timestamp |
| B20 | ur_kinematics.py | 🟢 Низк. | Math | _pose_error нестабильна при π |
| B21 | assembly_fsm.py | 🟢 Низк. | Style | state_name vs fsm_key |
| B22 | ros_gz_bridge.yaml | 🟢 Низк. | Dead code | Устаревший bridge config |
| B23 | part_spawner.py | 🟢 Низк. | Sim time | use_sim_time без spin |
| B24 | assembly_fsm.py | 🟢 Низк. | Perf | Busy-wait polling |
| B25 | assembly_cell.launch.py | 🟢 Низк. | Dead code | gz_headless не используется |
| B26 | gearbox_gazebo.urdf.xacro | 🟠 Сим. | Mesh | Sun gear использует mesh satellite.STL |
| B27 | workcell_macros.xacro | 🟠 Сим. | PID | UR3e wrist gains слишком высокие |
| B28 | workcell_macros.xacro | 🟠 Сим. | Sensor | FT sensor без noise |
| B29 | assembly_cell.sdf | 🟠 Сим. | Physics | Нет Contact plugin |
| B30 | part_spawner.py | 🟠 Сим. | API | kinematic tag deprecated |
| B31 | ur5e_robotiq_ft.urdf.xacro | 🟠 Сим. | PID | velocity gains только у wrist_3 |
| B32 | workcell_macros.xacro | 🟠 Сим. | Perf | 5 камер @15fps без использования |
| B33 | assembly_cell.launch.py | 🟠 Сим. | Timing | GUI запускается раньше server |
| B34 | part_spawner.py | 🔴 Крит. | Timing | FSM стартует до spawn всех частей |
| B35 | press_controller.py | 🟠 Сим. | Sensor | FT подписан на робот, не на press |
| B36 | assembly_scene.sdf | 🟢 Низк. | Model | Workbench links без joints |
| B37 | gearbox_gazebo.urdf.xacro | 🟢 Низк. | Static | static=true портируемость |

---

## Дополнение — верифицированный проход (2026-06-11)

Отдельный, более консервативный проход. Здесь только то, что удалось подтвердить
запуском или прямой проверкой кода/конфигов. Где находка пересекается с B01–B25 —
указано явно. Среда: ROS2/Gazebo локально недоступны, поэтому рантайм-баги Gazebo
помечены как «инференс», а не «воспроизведено».

### N1. 🔴 Сломан весь набор юнит-тестов (ВОСПРОИЗВЕДЕНО) — НОВОЕ, в B01–B25 отсутствует

**Файлы:** `tests/test_assembly_fsm.py:34-40`, `scripts/assembly_fsm.py:14`

Тест-харнесс заглушает ROS-модули, но **не заглушает `builtin_interfaces.msg`**.
В `assembly_fsm.py:14` есть `from builtin_interfaces.msg import Duration`
(добавлено вместе с логикой гриппера). Поэтому `import assembly_fsm` падает ещё на
этапе сбора тестов:

```
tests/test_assembly_fsm.py:94: in <module>
    import assembly_fsm as fsm
scripts/assembly_fsm.py:14: in <module>
    from builtin_interfaces.msg import Duration
E   ModuleNotFoundError: No module named 'builtin_interfaces'
```

Следствие: `ament_add_pytest_test` (`CMakeLists.txt:54`) падает в CI/`colcon test`.

**Проверено:** после добавления заглушки `builtin_interfaces.msg.Duration = MagicMock`
**все 38 тестов проходят** (`38 passed in 0.05s`).

**Исправление:** в список заглушек добавить
```python
for m in [..., "builtin_interfaces", "builtin_interfaces.msg", ...]:
    _make_stub_module(m)
sys.modules["builtin_interfaces.msg"].Duration = MagicMock
```

### N2. 🟠 `ur3e_screw` использует TCP-смещение гриппера — дубль B16 (подтверждён)

**Файлы:** `scripts/motion_planner.py:95`, `config/assembly_cell.yaml`

`tcp_z = float(data.get("tcp_offset_from_tool0_m", 0.203))`. Проверено `grep`-ом:
поле `tcp_offset_from_tool0_m` **нигде в конфиге не задано**, поэтому все три руки,
включая шуруповёрт, получают гриппер-дефолт `0.203`. IK-цели для `ur3e_screw`
считаются с неверной длиной инструмента. Совпадает с B16; добавить поле в конфиг
для `ur3e_screw` (и явно для гриппер-рук).

### N3. 🟠 Устаревший/мёртвый `ros_gz_bridge.yaml` — дубль B22 (подтверждён)

**Файл:** `config/ros_gz_bridge.yaml`

Описывает топики одиночной руки `/ur5e/ft_sensor`, `/ur5e/joint_states_gz`,
`/ur5e/joint_trajectory`, которых нет в трёхрукой сцене. Проверено `grep`-ом:
файл **не подключён ни в launch, ни в скриптах** — мост задан инлайн-аргументами в
`assembly_cell.launch.py:69-87`. Привести к трём рукам или удалить.

### N4. 🟡 Лимит момента F/T не переопределён в launch (риск ложных abort) — НОВОЕ

**Файлы:** `launch/assembly_cell.launch.py:217`, `scripts/assembly_fsm.py:283`

В launch переопределён только `max_contact_force_n=85.0`, а `max_contact_torque_nm`
остаётся дефолтным `6.0` Н·м. Для гриппер-рук момент на запястном F/T от массы
инструмента/пальцев при манёврах может пробить 6 Н·м → ложный `ERROR_RECOVERY`/ABORT
на pick/place. Код сам отключает F/T-гейт для винтовой руки по этой же причине
(`assembly_fsm.py:756-760`), но для гриппер-рук — нет. Проверить эмпирически в
Gazebo; при необходимости поднять `max_contact_torque_nm` в launch.

### N5. ⚪ Мелочи окружения — НОВОЕ

- `scripts/get_current_pose.py` отсутствует, но в `__pycache__` лежит его `.pyc` —
  устаревший артефакт.
- Осиротевшие миры `worlds/assembly_scene.sdf`, `assembly_scene_calibration.sdf`
  (launch грузит только `assembly_cell.sdf`).
- `.mcp.json` указывает на путь `/home/dark/ros2_ws` (Linux), тогда как репозиторий
  сейчас в `/Users/darkdoll/Documents/ros2_ws` — filesystem-MCP смотрит не туда.

### Что перепроверено и оказалось корректным
Имена world (`assembly_world`), gz-сервисы `set_pose`/`create`, имена joint'ов
(`press_ram_joint`, `*_finger_joint`, `*_screwdriver_slide_joint`), топики трасс и
гриппера, лимиты призматических суставов (0.022<0.026; 0.035<0.12; 0.020<0.08),
раскладка `ft_summary` `[fx,fy,fz,|f|,tx,ty,tz,|t|]` ↔ индексы `[3]`/`[7]` в FSM,
все фреймы из конфига определены в URDF, контракт ключей retry между
`OperationState` и `ErrorRecoveryState` — согласованы.
