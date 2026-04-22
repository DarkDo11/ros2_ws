// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from gearbox_sim:srv/RunPressCycle.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "gearbox_sim/srv/run_press_cycle.h"


#ifndef GEARBOX_SIM__SRV__DETAIL__RUN_PRESS_CYCLE__STRUCT_H_
#define GEARBOX_SIM__SRV__DETAIL__RUN_PRESS_CYCLE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'recipe_name'
// Member 'target_frame'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/RunPressCycle in the package gearbox_sim.
typedef struct gearbox_sim__srv__RunPressCycle_Request
{
  rosidl_runtime_c__String recipe_name;
  rosidl_runtime_c__String target_frame;
  double approach_height_m;
  double stroke_m;
  double dwell_sec;
} gearbox_sim__srv__RunPressCycle_Request;

// Struct for a sequence of gearbox_sim__srv__RunPressCycle_Request.
typedef struct gearbox_sim__srv__RunPressCycle_Request__Sequence
{
  gearbox_sim__srv__RunPressCycle_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} gearbox_sim__srv__RunPressCycle_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/RunPressCycle in the package gearbox_sim.
typedef struct gearbox_sim__srv__RunPressCycle_Response
{
  bool success;
  rosidl_runtime_c__String message;
} gearbox_sim__srv__RunPressCycle_Response;

// Struct for a sequence of gearbox_sim__srv__RunPressCycle_Response.
typedef struct gearbox_sim__srv__RunPressCycle_Response__Sequence
{
  gearbox_sim__srv__RunPressCycle_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} gearbox_sim__srv__RunPressCycle_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  gearbox_sim__srv__RunPressCycle_Event__request__MAX_SIZE = 1
};
// response
enum
{
  gearbox_sim__srv__RunPressCycle_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/RunPressCycle in the package gearbox_sim.
typedef struct gearbox_sim__srv__RunPressCycle_Event
{
  service_msgs__msg__ServiceEventInfo info;
  gearbox_sim__srv__RunPressCycle_Request__Sequence request;
  gearbox_sim__srv__RunPressCycle_Response__Sequence response;
} gearbox_sim__srv__RunPressCycle_Event;

// Struct for a sequence of gearbox_sim__srv__RunPressCycle_Event.
typedef struct gearbox_sim__srv__RunPressCycle_Event__Sequence
{
  gearbox_sim__srv__RunPressCycle_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} gearbox_sim__srv__RunPressCycle_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // GEARBOX_SIM__SRV__DETAIL__RUN_PRESS_CYCLE__STRUCT_H_
