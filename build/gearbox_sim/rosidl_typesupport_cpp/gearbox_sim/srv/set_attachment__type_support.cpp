// generated from rosidl_typesupport_cpp/resource/idl__type_support.cpp.em
// with input from gearbox_sim:srv/SetAttachment.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "gearbox_sim/srv/detail/set_attachment__functions.h"
#include "gearbox_sim/srv/detail/set_attachment__struct.hpp"
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

typedef struct _SetAttachment_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _SetAttachment_Request_type_support_ids_t;

static const _SetAttachment_Request_type_support_ids_t _SetAttachment_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _SetAttachment_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _SetAttachment_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _SetAttachment_Request_type_support_symbol_names_t _SetAttachment_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, gearbox_sim, srv, SetAttachment_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, gearbox_sim, srv, SetAttachment_Request)),
  }
};

typedef struct _SetAttachment_Request_type_support_data_t
{
  void * data[2];
} _SetAttachment_Request_type_support_data_t;

static _SetAttachment_Request_type_support_data_t _SetAttachment_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _SetAttachment_Request_message_typesupport_map = {
  2,
  "gearbox_sim",
  &_SetAttachment_Request_message_typesupport_ids.typesupport_identifier[0],
  &_SetAttachment_Request_message_typesupport_symbol_names.symbol_name[0],
  &_SetAttachment_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t SetAttachment_Request_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_SetAttachment_Request_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &gearbox_sim__srv__SetAttachment_Request__get_type_hash,
  &gearbox_sim__srv__SetAttachment_Request__get_type_description,
  &gearbox_sim__srv__SetAttachment_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace gearbox_sim

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<gearbox_sim::srv::SetAttachment_Request>()
{
  return &::gearbox_sim::srv::rosidl_typesupport_cpp::SetAttachment_Request_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, gearbox_sim, srv, SetAttachment_Request)() {
  return get_message_type_support_handle<gearbox_sim::srv::SetAttachment_Request>();
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
// #include "gearbox_sim/srv/detail/set_attachment__functions.h"
// already included above
// #include "gearbox_sim/srv/detail/set_attachment__struct.hpp"
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

typedef struct _SetAttachment_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _SetAttachment_Response_type_support_ids_t;

static const _SetAttachment_Response_type_support_ids_t _SetAttachment_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _SetAttachment_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _SetAttachment_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _SetAttachment_Response_type_support_symbol_names_t _SetAttachment_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, gearbox_sim, srv, SetAttachment_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, gearbox_sim, srv, SetAttachment_Response)),
  }
};

typedef struct _SetAttachment_Response_type_support_data_t
{
  void * data[2];
} _SetAttachment_Response_type_support_data_t;

static _SetAttachment_Response_type_support_data_t _SetAttachment_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _SetAttachment_Response_message_typesupport_map = {
  2,
  "gearbox_sim",
  &_SetAttachment_Response_message_typesupport_ids.typesupport_identifier[0],
  &_SetAttachment_Response_message_typesupport_symbol_names.symbol_name[0],
  &_SetAttachment_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t SetAttachment_Response_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_SetAttachment_Response_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &gearbox_sim__srv__SetAttachment_Response__get_type_hash,
  &gearbox_sim__srv__SetAttachment_Response__get_type_description,
  &gearbox_sim__srv__SetAttachment_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace gearbox_sim

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<gearbox_sim::srv::SetAttachment_Response>()
{
  return &::gearbox_sim::srv::rosidl_typesupport_cpp::SetAttachment_Response_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, gearbox_sim, srv, SetAttachment_Response)() {
  return get_message_type_support_handle<gearbox_sim::srv::SetAttachment_Response>();
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
// #include "gearbox_sim/srv/detail/set_attachment__functions.h"
// already included above
// #include "gearbox_sim/srv/detail/set_attachment__struct.hpp"
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

typedef struct _SetAttachment_Event_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _SetAttachment_Event_type_support_ids_t;

static const _SetAttachment_Event_type_support_ids_t _SetAttachment_Event_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _SetAttachment_Event_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _SetAttachment_Event_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _SetAttachment_Event_type_support_symbol_names_t _SetAttachment_Event_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, gearbox_sim, srv, SetAttachment_Event)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, gearbox_sim, srv, SetAttachment_Event)),
  }
};

typedef struct _SetAttachment_Event_type_support_data_t
{
  void * data[2];
} _SetAttachment_Event_type_support_data_t;

static _SetAttachment_Event_type_support_data_t _SetAttachment_Event_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _SetAttachment_Event_message_typesupport_map = {
  2,
  "gearbox_sim",
  &_SetAttachment_Event_message_typesupport_ids.typesupport_identifier[0],
  &_SetAttachment_Event_message_typesupport_symbol_names.symbol_name[0],
  &_SetAttachment_Event_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t SetAttachment_Event_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_SetAttachment_Event_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &gearbox_sim__srv__SetAttachment_Event__get_type_hash,
  &gearbox_sim__srv__SetAttachment_Event__get_type_description,
  &gearbox_sim__srv__SetAttachment_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace gearbox_sim

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<gearbox_sim::srv::SetAttachment_Event>()
{
  return &::gearbox_sim::srv::rosidl_typesupport_cpp::SetAttachment_Event_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, gearbox_sim, srv, SetAttachment_Event)() {
  return get_message_type_support_handle<gearbox_sim::srv::SetAttachment_Event>();
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
// #include "gearbox_sim/srv/detail/set_attachment__struct.hpp"
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

typedef struct _SetAttachment_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _SetAttachment_type_support_ids_t;

static const _SetAttachment_type_support_ids_t _SetAttachment_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _SetAttachment_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _SetAttachment_type_support_symbol_names_t;
#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _SetAttachment_type_support_symbol_names_t _SetAttachment_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, gearbox_sim, srv, SetAttachment)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, gearbox_sim, srv, SetAttachment)),
  }
};

typedef struct _SetAttachment_type_support_data_t
{
  void * data[2];
} _SetAttachment_type_support_data_t;

static _SetAttachment_type_support_data_t _SetAttachment_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _SetAttachment_service_typesupport_map = {
  2,
  "gearbox_sim",
  &_SetAttachment_service_typesupport_ids.typesupport_identifier[0],
  &_SetAttachment_service_typesupport_symbol_names.symbol_name[0],
  &_SetAttachment_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t SetAttachment_service_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_SetAttachment_service_typesupport_map),
  ::rosidl_typesupport_cpp::get_service_typesupport_handle_function,
  ::rosidl_typesupport_cpp::get_message_type_support_handle<gearbox_sim::srv::SetAttachment_Request>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<gearbox_sim::srv::SetAttachment_Response>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<gearbox_sim::srv::SetAttachment_Event>(),
  &::rosidl_typesupport_cpp::service_create_event_message<gearbox_sim::srv::SetAttachment>,
  &::rosidl_typesupport_cpp::service_destroy_event_message<gearbox_sim::srv::SetAttachment>,
  &gearbox_sim__srv__SetAttachment__get_type_hash,
  &gearbox_sim__srv__SetAttachment__get_type_description,
  &gearbox_sim__srv__SetAttachment__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace gearbox_sim

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<gearbox_sim::srv::SetAttachment>()
{
  return &::gearbox_sim::srv::rosidl_typesupport_cpp::SetAttachment_service_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_cpp, gearbox_sim, srv, SetAttachment)() {
  return ::rosidl_typesupport_cpp::get_service_type_support_handle<gearbox_sim::srv::SetAttachment>();
}

#ifdef __cplusplus
}
#endif
