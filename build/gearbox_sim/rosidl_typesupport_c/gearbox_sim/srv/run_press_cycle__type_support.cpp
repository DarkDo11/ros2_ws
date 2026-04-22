// generated from rosidl_typesupport_c/resource/idl__type_support.cpp.em
// with input from gearbox_sim:srv/RunPressCycle.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "gearbox_sim/srv/detail/run_press_cycle__struct.h"
#include "gearbox_sim/srv/detail/run_press_cycle__type_support.h"
#include "gearbox_sim/srv/detail/run_press_cycle__functions.h"
#include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/message_type_support_dispatch.h"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_c/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace gearbox_sim
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _RunPressCycle_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _RunPressCycle_Request_type_support_ids_t;

static const _RunPressCycle_Request_type_support_ids_t _RunPressCycle_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _RunPressCycle_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _RunPressCycle_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _RunPressCycle_Request_type_support_symbol_names_t _RunPressCycle_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, gearbox_sim, srv, RunPressCycle_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, gearbox_sim, srv, RunPressCycle_Request)),
  }
};

typedef struct _RunPressCycle_Request_type_support_data_t
{
  void * data[2];
} _RunPressCycle_Request_type_support_data_t;

static _RunPressCycle_Request_type_support_data_t _RunPressCycle_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _RunPressCycle_Request_message_typesupport_map = {
  2,
  "gearbox_sim",
  &_RunPressCycle_Request_message_typesupport_ids.typesupport_identifier[0],
  &_RunPressCycle_Request_message_typesupport_symbol_names.symbol_name[0],
  &_RunPressCycle_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t RunPressCycle_Request_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_RunPressCycle_Request_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &gearbox_sim__srv__RunPressCycle_Request__get_type_hash,
  &gearbox_sim__srv__RunPressCycle_Request__get_type_description,
  &gearbox_sim__srv__RunPressCycle_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace gearbox_sim

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, gearbox_sim, srv, RunPressCycle_Request)() {
  return &::gearbox_sim::srv::rosidl_typesupport_c::RunPressCycle_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "gearbox_sim/srv/detail/run_press_cycle__struct.h"
// already included above
// #include "gearbox_sim/srv/detail/run_press_cycle__type_support.h"
// already included above
// #include "gearbox_sim/srv/detail/run_press_cycle__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace gearbox_sim
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _RunPressCycle_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _RunPressCycle_Response_type_support_ids_t;

static const _RunPressCycle_Response_type_support_ids_t _RunPressCycle_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _RunPressCycle_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _RunPressCycle_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _RunPressCycle_Response_type_support_symbol_names_t _RunPressCycle_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, gearbox_sim, srv, RunPressCycle_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, gearbox_sim, srv, RunPressCycle_Response)),
  }
};

typedef struct _RunPressCycle_Response_type_support_data_t
{
  void * data[2];
} _RunPressCycle_Response_type_support_data_t;

static _RunPressCycle_Response_type_support_data_t _RunPressCycle_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _RunPressCycle_Response_message_typesupport_map = {
  2,
  "gearbox_sim",
  &_RunPressCycle_Response_message_typesupport_ids.typesupport_identifier[0],
  &_RunPressCycle_Response_message_typesupport_symbol_names.symbol_name[0],
  &_RunPressCycle_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t RunPressCycle_Response_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_RunPressCycle_Response_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &gearbox_sim__srv__RunPressCycle_Response__get_type_hash,
  &gearbox_sim__srv__RunPressCycle_Response__get_type_description,
  &gearbox_sim__srv__RunPressCycle_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace gearbox_sim

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, gearbox_sim, srv, RunPressCycle_Response)() {
  return &::gearbox_sim::srv::rosidl_typesupport_c::RunPressCycle_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "gearbox_sim/srv/detail/run_press_cycle__struct.h"
// already included above
// #include "gearbox_sim/srv/detail/run_press_cycle__type_support.h"
// already included above
// #include "gearbox_sim/srv/detail/run_press_cycle__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace gearbox_sim
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _RunPressCycle_Event_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _RunPressCycle_Event_type_support_ids_t;

static const _RunPressCycle_Event_type_support_ids_t _RunPressCycle_Event_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _RunPressCycle_Event_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _RunPressCycle_Event_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _RunPressCycle_Event_type_support_symbol_names_t _RunPressCycle_Event_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, gearbox_sim, srv, RunPressCycle_Event)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, gearbox_sim, srv, RunPressCycle_Event)),
  }
};

typedef struct _RunPressCycle_Event_type_support_data_t
{
  void * data[2];
} _RunPressCycle_Event_type_support_data_t;

static _RunPressCycle_Event_type_support_data_t _RunPressCycle_Event_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _RunPressCycle_Event_message_typesupport_map = {
  2,
  "gearbox_sim",
  &_RunPressCycle_Event_message_typesupport_ids.typesupport_identifier[0],
  &_RunPressCycle_Event_message_typesupport_symbol_names.symbol_name[0],
  &_RunPressCycle_Event_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t RunPressCycle_Event_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_RunPressCycle_Event_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &gearbox_sim__srv__RunPressCycle_Event__get_type_hash,
  &gearbox_sim__srv__RunPressCycle_Event__get_type_description,
  &gearbox_sim__srv__RunPressCycle_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace gearbox_sim

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, gearbox_sim, srv, RunPressCycle_Event)() {
  return &::gearbox_sim::srv::rosidl_typesupport_c::RunPressCycle_Event_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "gearbox_sim/srv/detail/run_press_cycle__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/service_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
#include "service_msgs/msg/service_event_info.h"
#include "builtin_interfaces/msg/time.h"

namespace gearbox_sim
{

namespace srv
{

namespace rosidl_typesupport_c
{
typedef struct _RunPressCycle_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _RunPressCycle_type_support_ids_t;

static const _RunPressCycle_type_support_ids_t _RunPressCycle_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _RunPressCycle_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _RunPressCycle_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _RunPressCycle_type_support_symbol_names_t _RunPressCycle_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, gearbox_sim, srv, RunPressCycle)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, gearbox_sim, srv, RunPressCycle)),
  }
};

typedef struct _RunPressCycle_type_support_data_t
{
  void * data[2];
} _RunPressCycle_type_support_data_t;

static _RunPressCycle_type_support_data_t _RunPressCycle_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _RunPressCycle_service_typesupport_map = {
  2,
  "gearbox_sim",
  &_RunPressCycle_service_typesupport_ids.typesupport_identifier[0],
  &_RunPressCycle_service_typesupport_symbol_names.symbol_name[0],
  &_RunPressCycle_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t RunPressCycle_service_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_RunPressCycle_service_typesupport_map),
  rosidl_typesupport_c__get_service_typesupport_handle_function,
  &RunPressCycle_Request_message_type_support_handle,
  &RunPressCycle_Response_message_type_support_handle,
  &RunPressCycle_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    gearbox_sim,
    srv,
    RunPressCycle
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    gearbox_sim,
    srv,
    RunPressCycle
  ),
  &gearbox_sim__srv__RunPressCycle__get_type_hash,
  &gearbox_sim__srv__RunPressCycle__get_type_description,
  &gearbox_sim__srv__RunPressCycle__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace gearbox_sim

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, gearbox_sim, srv, RunPressCycle)() {
  return &::gearbox_sim::srv::rosidl_typesupport_c::RunPressCycle_service_type_support_handle;
}

#ifdef __cplusplus
}
#endif
