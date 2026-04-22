// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from gearbox_sim:srv/SetAttachment.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "gearbox_sim/srv/set_attachment.h"


#ifndef GEARBOX_SIM__SRV__DETAIL__SET_ATTACHMENT__STRUCT_H_
#define GEARBOX_SIM__SRV__DETAIL__SET_ATTACHMENT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'robot_name'
// Member 'tool_frame'
// Member 'part_name'
// Member 'part_frame'
// Member 'part_link'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/SetAttachment in the package gearbox_sim.
typedef struct gearbox_sim__srv__SetAttachment_Request
{
  rosidl_runtime_c__String robot_name;
  rosidl_runtime_c__String tool_frame;
  rosidl_runtime_c__String part_name;
  rosidl_runtime_c__String part_frame;
  rosidl_runtime_c__String part_link;
  bool attach;
} gearbox_sim__srv__SetAttachment_Request;

// Struct for a sequence of gearbox_sim__srv__SetAttachment_Request.
typedef struct gearbox_sim__srv__SetAttachment_Request__Sequence
{
  gearbox_sim__srv__SetAttachment_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} gearbox_sim__srv__SetAttachment_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/SetAttachment in the package gearbox_sim.
typedef struct gearbox_sim__srv__SetAttachment_Response
{
  bool success;
  rosidl_runtime_c__String message;
} gearbox_sim__srv__SetAttachment_Response;

// Struct for a sequence of gearbox_sim__srv__SetAttachment_Response.
typedef struct gearbox_sim__srv__SetAttachment_Response__Sequence
{
  gearbox_sim__srv__SetAttachment_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} gearbox_sim__srv__SetAttachment_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  gearbox_sim__srv__SetAttachment_Event__request__MAX_SIZE = 1
};
// response
enum
{
  gearbox_sim__srv__SetAttachment_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/SetAttachment in the package gearbox_sim.
typedef struct gearbox_sim__srv__SetAttachment_Event
{
  service_msgs__msg__ServiceEventInfo info;
  gearbox_sim__srv__SetAttachment_Request__Sequence request;
  gearbox_sim__srv__SetAttachment_Response__Sequence response;
} gearbox_sim__srv__SetAttachment_Event;

// Struct for a sequence of gearbox_sim__srv__SetAttachment_Event.
typedef struct gearbox_sim__srv__SetAttachment_Event__Sequence
{
  gearbox_sim__srv__SetAttachment_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} gearbox_sim__srv__SetAttachment_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // GEARBOX_SIM__SRV__DETAIL__SET_ATTACHMENT__STRUCT_H_
