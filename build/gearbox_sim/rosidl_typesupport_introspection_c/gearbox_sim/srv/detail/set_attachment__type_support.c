// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from gearbox_sim:srv/SetAttachment.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "gearbox_sim/srv/detail/set_attachment__rosidl_typesupport_introspection_c.h"
#include "gearbox_sim/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "gearbox_sim/srv/detail/set_attachment__functions.h"
#include "gearbox_sim/srv/detail/set_attachment__struct.h"


// Include directives for member types
// Member `robot_name`
// Member `tool_frame`
// Member `part_name`
// Member `part_frame`
// Member `part_link`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void gearbox_sim__srv__SetAttachment_Request__rosidl_typesupport_introspection_c__SetAttachment_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  gearbox_sim__srv__SetAttachment_Request__init(message_memory);
}

void gearbox_sim__srv__SetAttachment_Request__rosidl_typesupport_introspection_c__SetAttachment_Request_fini_function(void * message_memory)
{
  gearbox_sim__srv__SetAttachment_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember gearbox_sim__srv__SetAttachment_Request__rosidl_typesupport_introspection_c__SetAttachment_Request_message_member_array[6] = {
  {
    "robot_name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(gearbox_sim__srv__SetAttachment_Request, robot_name),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "tool_frame",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(gearbox_sim__srv__SetAttachment_Request, tool_frame),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "part_name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(gearbox_sim__srv__SetAttachment_Request, part_name),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "part_frame",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(gearbox_sim__srv__SetAttachment_Request, part_frame),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "part_link",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(gearbox_sim__srv__SetAttachment_Request, part_link),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "attach",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(gearbox_sim__srv__SetAttachment_Request, attach),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers gearbox_sim__srv__SetAttachment_Request__rosidl_typesupport_introspection_c__SetAttachment_Request_message_members = {
  "gearbox_sim__srv",  // message namespace
  "SetAttachment_Request",  // message name
  6,  // number of fields
  sizeof(gearbox_sim__srv__SetAttachment_Request),
  false,  // has_any_key_member_
  gearbox_sim__srv__SetAttachment_Request__rosidl_typesupport_introspection_c__SetAttachment_Request_message_member_array,  // message members
  gearbox_sim__srv__SetAttachment_Request__rosidl_typesupport_introspection_c__SetAttachment_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  gearbox_sim__srv__SetAttachment_Request__rosidl_typesupport_introspection_c__SetAttachment_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t gearbox_sim__srv__SetAttachment_Request__rosidl_typesupport_introspection_c__SetAttachment_Request_message_type_support_handle = {
  0,
  &gearbox_sim__srv__SetAttachment_Request__rosidl_typesupport_introspection_c__SetAttachment_Request_message_members,
  get_message_typesupport_handle_function,
  &gearbox_sim__srv__SetAttachment_Request__get_type_hash,
  &gearbox_sim__srv__SetAttachment_Request__get_type_description,
  &gearbox_sim__srv__SetAttachment_Request__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_gearbox_sim
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, gearbox_sim, srv, SetAttachment_Request)() {
  if (!gearbox_sim__srv__SetAttachment_Request__rosidl_typesupport_introspection_c__SetAttachment_Request_message_type_support_handle.typesupport_identifier) {
    gearbox_sim__srv__SetAttachment_Request__rosidl_typesupport_introspection_c__SetAttachment_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &gearbox_sim__srv__SetAttachment_Request__rosidl_typesupport_introspection_c__SetAttachment_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "gearbox_sim/srv/detail/set_attachment__rosidl_typesupport_introspection_c.h"
// already included above
// #include "gearbox_sim/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "gearbox_sim/srv/detail/set_attachment__functions.h"
// already included above
// #include "gearbox_sim/srv/detail/set_attachment__struct.h"


// Include directives for member types
// Member `message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void gearbox_sim__srv__SetAttachment_Response__rosidl_typesupport_introspection_c__SetAttachment_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  gearbox_sim__srv__SetAttachment_Response__init(message_memory);
}

void gearbox_sim__srv__SetAttachment_Response__rosidl_typesupport_introspection_c__SetAttachment_Response_fini_function(void * message_memory)
{
  gearbox_sim__srv__SetAttachment_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember gearbox_sim__srv__SetAttachment_Response__rosidl_typesupport_introspection_c__SetAttachment_Response_message_member_array[2] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(gearbox_sim__srv__SetAttachment_Response, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(gearbox_sim__srv__SetAttachment_Response, message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers gearbox_sim__srv__SetAttachment_Response__rosidl_typesupport_introspection_c__SetAttachment_Response_message_members = {
  "gearbox_sim__srv",  // message namespace
  "SetAttachment_Response",  // message name
  2,  // number of fields
  sizeof(gearbox_sim__srv__SetAttachment_Response),
  false,  // has_any_key_member_
  gearbox_sim__srv__SetAttachment_Response__rosidl_typesupport_introspection_c__SetAttachment_Response_message_member_array,  // message members
  gearbox_sim__srv__SetAttachment_Response__rosidl_typesupport_introspection_c__SetAttachment_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  gearbox_sim__srv__SetAttachment_Response__rosidl_typesupport_introspection_c__SetAttachment_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t gearbox_sim__srv__SetAttachment_Response__rosidl_typesupport_introspection_c__SetAttachment_Response_message_type_support_handle = {
  0,
  &gearbox_sim__srv__SetAttachment_Response__rosidl_typesupport_introspection_c__SetAttachment_Response_message_members,
  get_message_typesupport_handle_function,
  &gearbox_sim__srv__SetAttachment_Response__get_type_hash,
  &gearbox_sim__srv__SetAttachment_Response__get_type_description,
  &gearbox_sim__srv__SetAttachment_Response__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_gearbox_sim
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, gearbox_sim, srv, SetAttachment_Response)() {
  if (!gearbox_sim__srv__SetAttachment_Response__rosidl_typesupport_introspection_c__SetAttachment_Response_message_type_support_handle.typesupport_identifier) {
    gearbox_sim__srv__SetAttachment_Response__rosidl_typesupport_introspection_c__SetAttachment_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &gearbox_sim__srv__SetAttachment_Response__rosidl_typesupport_introspection_c__SetAttachment_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "gearbox_sim/srv/detail/set_attachment__rosidl_typesupport_introspection_c.h"
// already included above
// #include "gearbox_sim/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "gearbox_sim/srv/detail/set_attachment__functions.h"
// already included above
// #include "gearbox_sim/srv/detail/set_attachment__struct.h"


// Include directives for member types
// Member `info`
#include "service_msgs/msg/service_event_info.h"
// Member `info`
#include "service_msgs/msg/detail/service_event_info__rosidl_typesupport_introspection_c.h"
// Member `request`
// Member `response`
#include "gearbox_sim/srv/set_attachment.h"
// Member `request`
// Member `response`
// already included above
// #include "gearbox_sim/srv/detail/set_attachment__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__SetAttachment_Event_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  gearbox_sim__srv__SetAttachment_Event__init(message_memory);
}

void gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__SetAttachment_Event_fini_function(void * message_memory)
{
  gearbox_sim__srv__SetAttachment_Event__fini(message_memory);
}

size_t gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__size_function__SetAttachment_Event__request(
  const void * untyped_member)
{
  const gearbox_sim__srv__SetAttachment_Request__Sequence * member =
    (const gearbox_sim__srv__SetAttachment_Request__Sequence *)(untyped_member);
  return member->size;
}

const void * gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__get_const_function__SetAttachment_Event__request(
  const void * untyped_member, size_t index)
{
  const gearbox_sim__srv__SetAttachment_Request__Sequence * member =
    (const gearbox_sim__srv__SetAttachment_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void * gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__get_function__SetAttachment_Event__request(
  void * untyped_member, size_t index)
{
  gearbox_sim__srv__SetAttachment_Request__Sequence * member =
    (gearbox_sim__srv__SetAttachment_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__fetch_function__SetAttachment_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const gearbox_sim__srv__SetAttachment_Request * item =
    ((const gearbox_sim__srv__SetAttachment_Request *)
    gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__get_const_function__SetAttachment_Event__request(untyped_member, index));
  gearbox_sim__srv__SetAttachment_Request * value =
    (gearbox_sim__srv__SetAttachment_Request *)(untyped_value);
  *value = *item;
}

void gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__assign_function__SetAttachment_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  gearbox_sim__srv__SetAttachment_Request * item =
    ((gearbox_sim__srv__SetAttachment_Request *)
    gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__get_function__SetAttachment_Event__request(untyped_member, index));
  const gearbox_sim__srv__SetAttachment_Request * value =
    (const gearbox_sim__srv__SetAttachment_Request *)(untyped_value);
  *item = *value;
}

bool gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__resize_function__SetAttachment_Event__request(
  void * untyped_member, size_t size)
{
  gearbox_sim__srv__SetAttachment_Request__Sequence * member =
    (gearbox_sim__srv__SetAttachment_Request__Sequence *)(untyped_member);
  gearbox_sim__srv__SetAttachment_Request__Sequence__fini(member);
  return gearbox_sim__srv__SetAttachment_Request__Sequence__init(member, size);
}

size_t gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__size_function__SetAttachment_Event__response(
  const void * untyped_member)
{
  const gearbox_sim__srv__SetAttachment_Response__Sequence * member =
    (const gearbox_sim__srv__SetAttachment_Response__Sequence *)(untyped_member);
  return member->size;
}

const void * gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__get_const_function__SetAttachment_Event__response(
  const void * untyped_member, size_t index)
{
  const gearbox_sim__srv__SetAttachment_Response__Sequence * member =
    (const gearbox_sim__srv__SetAttachment_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void * gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__get_function__SetAttachment_Event__response(
  void * untyped_member, size_t index)
{
  gearbox_sim__srv__SetAttachment_Response__Sequence * member =
    (gearbox_sim__srv__SetAttachment_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__fetch_function__SetAttachment_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const gearbox_sim__srv__SetAttachment_Response * item =
    ((const gearbox_sim__srv__SetAttachment_Response *)
    gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__get_const_function__SetAttachment_Event__response(untyped_member, index));
  gearbox_sim__srv__SetAttachment_Response * value =
    (gearbox_sim__srv__SetAttachment_Response *)(untyped_value);
  *value = *item;
}

void gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__assign_function__SetAttachment_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  gearbox_sim__srv__SetAttachment_Response * item =
    ((gearbox_sim__srv__SetAttachment_Response *)
    gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__get_function__SetAttachment_Event__response(untyped_member, index));
  const gearbox_sim__srv__SetAttachment_Response * value =
    (const gearbox_sim__srv__SetAttachment_Response *)(untyped_value);
  *item = *value;
}

bool gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__resize_function__SetAttachment_Event__response(
  void * untyped_member, size_t size)
{
  gearbox_sim__srv__SetAttachment_Response__Sequence * member =
    (gearbox_sim__srv__SetAttachment_Response__Sequence *)(untyped_member);
  gearbox_sim__srv__SetAttachment_Response__Sequence__fini(member);
  return gearbox_sim__srv__SetAttachment_Response__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__SetAttachment_Event_message_member_array[3] = {
  {
    "info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(gearbox_sim__srv__SetAttachment_Event, info),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "request",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(gearbox_sim__srv__SetAttachment_Event, request),  // bytes offset in struct
    NULL,  // default value
    gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__size_function__SetAttachment_Event__request,  // size() function pointer
    gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__get_const_function__SetAttachment_Event__request,  // get_const(index) function pointer
    gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__get_function__SetAttachment_Event__request,  // get(index) function pointer
    gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__fetch_function__SetAttachment_Event__request,  // fetch(index, &value) function pointer
    gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__assign_function__SetAttachment_Event__request,  // assign(index, value) function pointer
    gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__resize_function__SetAttachment_Event__request  // resize(index) function pointer
  },
  {
    "response",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(gearbox_sim__srv__SetAttachment_Event, response),  // bytes offset in struct
    NULL,  // default value
    gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__size_function__SetAttachment_Event__response,  // size() function pointer
    gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__get_const_function__SetAttachment_Event__response,  // get_const(index) function pointer
    gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__get_function__SetAttachment_Event__response,  // get(index) function pointer
    gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__fetch_function__SetAttachment_Event__response,  // fetch(index, &value) function pointer
    gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__assign_function__SetAttachment_Event__response,  // assign(index, value) function pointer
    gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__resize_function__SetAttachment_Event__response  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__SetAttachment_Event_message_members = {
  "gearbox_sim__srv",  // message namespace
  "SetAttachment_Event",  // message name
  3,  // number of fields
  sizeof(gearbox_sim__srv__SetAttachment_Event),
  false,  // has_any_key_member_
  gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__SetAttachment_Event_message_member_array,  // message members
  gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__SetAttachment_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__SetAttachment_Event_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__SetAttachment_Event_message_type_support_handle = {
  0,
  &gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__SetAttachment_Event_message_members,
  get_message_typesupport_handle_function,
  &gearbox_sim__srv__SetAttachment_Event__get_type_hash,
  &gearbox_sim__srv__SetAttachment_Event__get_type_description,
  &gearbox_sim__srv__SetAttachment_Event__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_gearbox_sim
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, gearbox_sim, srv, SetAttachment_Event)() {
  gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__SetAttachment_Event_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_msgs, msg, ServiceEventInfo)();
  gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__SetAttachment_Event_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, gearbox_sim, srv, SetAttachment_Request)();
  gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__SetAttachment_Event_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, gearbox_sim, srv, SetAttachment_Response)();
  if (!gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__SetAttachment_Event_message_type_support_handle.typesupport_identifier) {
    gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__SetAttachment_Event_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__SetAttachment_Event_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "gearbox_sim/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "gearbox_sim/srv/detail/set_attachment__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers gearbox_sim__srv__detail__set_attachment__rosidl_typesupport_introspection_c__SetAttachment_service_members = {
  "gearbox_sim__srv",  // service namespace
  "SetAttachment",  // service name
  // the following fields are initialized below on first access
  NULL,  // request message
  // gearbox_sim__srv__detail__set_attachment__rosidl_typesupport_introspection_c__SetAttachment_Request_message_type_support_handle,
  NULL,  // response message
  // gearbox_sim__srv__detail__set_attachment__rosidl_typesupport_introspection_c__SetAttachment_Response_message_type_support_handle
  NULL  // event_message
  // gearbox_sim__srv__detail__set_attachment__rosidl_typesupport_introspection_c__SetAttachment_Response_message_type_support_handle
};


static rosidl_service_type_support_t gearbox_sim__srv__detail__set_attachment__rosidl_typesupport_introspection_c__SetAttachment_service_type_support_handle = {
  0,
  &gearbox_sim__srv__detail__set_attachment__rosidl_typesupport_introspection_c__SetAttachment_service_members,
  get_service_typesupport_handle_function,
  &gearbox_sim__srv__SetAttachment_Request__rosidl_typesupport_introspection_c__SetAttachment_Request_message_type_support_handle,
  &gearbox_sim__srv__SetAttachment_Response__rosidl_typesupport_introspection_c__SetAttachment_Response_message_type_support_handle,
  &gearbox_sim__srv__SetAttachment_Event__rosidl_typesupport_introspection_c__SetAttachment_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    gearbox_sim,
    srv,
    SetAttachment
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    gearbox_sim,
    srv,
    SetAttachment
  ),
  &gearbox_sim__srv__SetAttachment__get_type_hash,
  &gearbox_sim__srv__SetAttachment__get_type_description,
  &gearbox_sim__srv__SetAttachment__get_type_description_sources,
};

// Forward declaration of message type support functions for service members
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, gearbox_sim, srv, SetAttachment_Request)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, gearbox_sim, srv, SetAttachment_Response)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, gearbox_sim, srv, SetAttachment_Event)(void);

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_gearbox_sim
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, gearbox_sim, srv, SetAttachment)(void) {
  if (!gearbox_sim__srv__detail__set_attachment__rosidl_typesupport_introspection_c__SetAttachment_service_type_support_handle.typesupport_identifier) {
    gearbox_sim__srv__detail__set_attachment__rosidl_typesupport_introspection_c__SetAttachment_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)gearbox_sim__srv__detail__set_attachment__rosidl_typesupport_introspection_c__SetAttachment_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, gearbox_sim, srv, SetAttachment_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, gearbox_sim, srv, SetAttachment_Response)()->data;
  }
  if (!service_members->event_members_) {
    service_members->event_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, gearbox_sim, srv, SetAttachment_Event)()->data;
  }

  return &gearbox_sim__srv__detail__set_attachment__rosidl_typesupport_introspection_c__SetAttachment_service_type_support_handle;
}
