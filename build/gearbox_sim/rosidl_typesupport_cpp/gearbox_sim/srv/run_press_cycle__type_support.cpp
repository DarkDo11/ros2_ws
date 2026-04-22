// generated from rosidl_typesupport_cpp/resource/idl__type_support.cpp.em
// with input from gearbox_sim:srv/RunPressCycle.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "gearbox_sim/srv/detail/run_press_cycle__functions.h"
#include "gearbox_sim/srv/detail/run_press_cycle__struct.hpp"
#include "rosidl_typesupport_cpp/identifier.hpp"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
#include "rosidl_typesupport_cpp/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace gearbox_sim
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _RunPressCycle_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _RunPressCycle_Request_type_support_ids_t;

static const _RunPressCycle_Request_type_support_ids_t _RunPressCycle_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
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
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, gearbox_sim, srv, RunPressCycle_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, gearbox_sim, srv, RunPressCycle_Request)),
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
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_RunPressCycle_Request_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &gearbox_sim__srv__RunPressCycle_Request__get_type_hash,
  &gearbox_sim__srv__RunPressCycle_Request__get_type_description,
  &gearbox_sim__srv__RunPressCycle_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace gearbox_sim

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<gearbox_sim::srv::RunPressCycle_Request>()
{
  return &::gearbox_sim::srv::rosidl_typesupport_cpp::RunPressCycle_Request_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, gearbox_sim, srv, RunPressCycle_Request)() {
  return get_message_type_support_handle<gearbox_sim::srv::RunPressCycle_Request>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "gearbox_sim/srv/detail/run_press_cycle__functions.h"
// already included above
// #include "gearbox_sim/srv/detail/run_press_cycle__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace gearbox_sim
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _RunPressCycle_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _RunPressCycle_Response_type_support_ids_t;

static const _RunPressCycle_Response_type_support_ids_t _RunPressCycle_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
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
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, gearbox_sim, srv, RunPressCycle_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, gearbox_sim, srv, RunPressCycle_Response)),
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
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_RunPressCycle_Response_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &gearbox_sim__srv__RunPressCycle_Response__get_type_hash,
  &gearbox_sim__srv__RunPressCycle_Response__get_type_description,
  &gearbox_sim__srv__RunPressCycle_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace gearbox_sim

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<gearbox_sim::srv::RunPressCycle_Response>()
{
  return &::gearbox_sim::srv::rosidl_typesupport_cpp::RunPressCycle_Response_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, gearbox_sim, srv, RunPressCycle_Response)() {
  return get_message_type_support_handle<gearbox_sim::srv::RunPressCycle_Response>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "gearbox_sim/srv/detail/run_press_cycle__functions.h"
// already included above
// #include "gearbox_sim/srv/detail/run_press_cycle__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace gearbox_sim
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _RunPressCycle_Event_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _RunPressCycle_Event_type_support_ids_t;

static const _RunPressCycle_Event_type_support_ids_t _RunPressCycle_Event_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
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
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, gearbox_sim, srv, RunPressCycle_Event)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, gearbox_sim, srv, RunPressCycle_Event)),
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
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_RunPressCycle_Event_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &gearbox_sim__srv__RunPressCycle_Event__get_type_hash,
  &gearbox_sim__srv__RunPressCycle_Event__get_type_description,
  &gearbox_sim__srv__RunPressCycle_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace gearbox_sim

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<gearbox_sim::srv::RunPressCycle_Event>()
{
  return &::gearbox_sim::srv::rosidl_typesupport_cpp::RunPressCycle_Event_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, gearbox_sim, srv, RunPressCycle_Event)() {
  return get_message_type_support_handle<gearbox_sim::srv::RunPressCycle_Event>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "gearbox_sim/srv/detail/run_press_cycle__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/service_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace gearbox_sim
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _RunPressCycle_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _RunPressCycle_type_support_ids_t;

static const _RunPressCycle_type_support_ids_t _RunPressCycle_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
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
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, gearbox_sim, srv, RunPressCycle)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, gearbox_sim, srv, RunPressCycle)),
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
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_RunPressCycle_service_typesupport_map),
  ::rosidl_typesupport_cpp::get_service_typesupport_handle_function,
  ::rosidl_typesupport_cpp::get_message_type_support_handle<gearbox_sim::srv::RunPressCycle_Request>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<gearbox_sim::srv::RunPressCycle_Response>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<gearbox_sim::srv::RunPressCycle_Event>(),
  &::rosidl_typesupport_cpp::service_create_event_message<gearbox_sim::srv::RunPressCycle>,
  &::rosidl_typesupport_cpp::service_destroy_event_message<gearbox_sim::srv::RunPressCycle>,
  &gearbox_sim__srv__RunPressCycle__get_type_hash,
  &gearbox_sim__srv__RunPressCycle__get_type_description,
  &gearbox_sim__srv__RunPressCycle__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace gearbox_sim

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<gearbox_sim::srv::RunPressCycle>()
{
  return &::gearbox_sim::srv::rosidl_typesupport_cpp::RunPressCycle_service_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_cpp, gearbox_sim, srv, RunPressCycle)() {
  return ::rosidl_typesupport_cpp::get_service_type_support_handle<gearbox_sim::srv::RunPressCycle>();
}

#ifdef __cplusplus
}
#endif
