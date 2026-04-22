// generated from rosidl_generator_c/resource/idl__type_support.h.em
// with input from gearbox_sim:srv/RunPressCycle.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "gearbox_sim/srv/run_press_cycle.h"


#ifndef GEARBOX_SIM__SRV__DETAIL__RUN_PRESS_CYCLE__TYPE_SUPPORT_H_
#define GEARBOX_SIM__SRV__DETAIL__RUN_PRESS_CYCLE__TYPE_SUPPORT_H_

#include "rosidl_typesupport_interface/macros.h"

#include "gearbox_sim/msg/rosidl_generator_c__visibility_control.h"

#ifdef __cplusplus
extern "C"
{
#endif

#include "rosidl_runtime_c/message_type_support_struct.h"

// Forward declare the get type support functions for this type.
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c,
  gearbox_sim,
  srv,
  RunPressCycle_Request
)(void);

// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"

// Forward declare the get type support functions for this type.
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c,
  gearbox_sim,
  srv,
  RunPressCycle_Response
)(void);

// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"

// Forward declare the get type support functions for this type.
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c,
  gearbox_sim,
  srv,
  RunPressCycle_Event
)(void);

#include "rosidl_runtime_c/service_type_support_struct.h"

// Forward declare the get type support functions for this type.
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
  rosidl_typesupport_c,
  gearbox_sim,
  srv,
  RunPressCycle
)(void);

// Forward declare the function to create a service event message for this type.
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
void *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c,
  gearbox_sim,
  srv,
  RunPressCycle
)(
  const rosidl_service_introspection_info_t * info,
  rcutils_allocator_t * allocator,
  const void * request_message,
  const void * response_message);

// Forward declare the function to destroy a service event message for this type.
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
bool
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_c,
  gearbox_sim,
  srv,
  RunPressCycle
)(
  void * event_msg,
  rcutils_allocator_t * allocator);

#ifdef __cplusplus
}
#endif

#endif  // GEARBOX_SIM__SRV__DETAIL__RUN_PRESS_CYCLE__TYPE_SUPPORT_H_
