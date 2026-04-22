// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from gearbox_sim:srv/SetAttachment.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "gearbox_sim/srv/set_attachment.hpp"


#ifndef GEARBOX_SIM__SRV__DETAIL__SET_ATTACHMENT__TRAITS_HPP_
#define GEARBOX_SIM__SRV__DETAIL__SET_ATTACHMENT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "gearbox_sim/srv/detail/set_attachment__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace gearbox_sim
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetAttachment_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: robot_name
  {
    out << "robot_name: ";
    rosidl_generator_traits::value_to_yaml(msg.robot_name, out);
    out << ", ";
  }

  // member: tool_frame
  {
    out << "tool_frame: ";
    rosidl_generator_traits::value_to_yaml(msg.tool_frame, out);
    out << ", ";
  }

  // member: part_name
  {
    out << "part_name: ";
    rosidl_generator_traits::value_to_yaml(msg.part_name, out);
    out << ", ";
  }

  // member: part_frame
  {
    out << "part_frame: ";
    rosidl_generator_traits::value_to_yaml(msg.part_frame, out);
    out << ", ";
  }

  // member: part_link
  {
    out << "part_link: ";
    rosidl_generator_traits::value_to_yaml(msg.part_link, out);
    out << ", ";
  }

  // member: attach
  {
    out << "attach: ";
    rosidl_generator_traits::value_to_yaml(msg.attach, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetAttachment_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: robot_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "robot_name: ";
    rosidl_generator_traits::value_to_yaml(msg.robot_name, out);
    out << "\n";
  }

  // member: tool_frame
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tool_frame: ";
    rosidl_generator_traits::value_to_yaml(msg.tool_frame, out);
    out << "\n";
  }

  // member: part_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "part_name: ";
    rosidl_generator_traits::value_to_yaml(msg.part_name, out);
    out << "\n";
  }

  // member: part_frame
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "part_frame: ";
    rosidl_generator_traits::value_to_yaml(msg.part_frame, out);
    out << "\n";
  }

  // member: part_link
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "part_link: ";
    rosidl_generator_traits::value_to_yaml(msg.part_link, out);
    out << "\n";
  }

  // member: attach
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "attach: ";
    rosidl_generator_traits::value_to_yaml(msg.attach, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetAttachment_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace gearbox_sim

namespace rosidl_generator_traits
{

[[deprecated("use gearbox_sim::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const gearbox_sim::srv::SetAttachment_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  gearbox_sim::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use gearbox_sim::srv::to_yaml() instead")]]
inline std::string to_yaml(const gearbox_sim::srv::SetAttachment_Request & msg)
{
  return gearbox_sim::srv::to_yaml(msg);
}

template<>
inline const char * data_type<gearbox_sim::srv::SetAttachment_Request>()
{
  return "gearbox_sim::srv::SetAttachment_Request";
}

template<>
inline const char * name<gearbox_sim::srv::SetAttachment_Request>()
{
  return "gearbox_sim/srv/SetAttachment_Request";
}

template<>
struct has_fixed_size<gearbox_sim::srv::SetAttachment_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<gearbox_sim::srv::SetAttachment_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<gearbox_sim::srv::SetAttachment_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace gearbox_sim
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetAttachment_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetAttachment_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetAttachment_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace gearbox_sim

namespace rosidl_generator_traits
{

[[deprecated("use gearbox_sim::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const gearbox_sim::srv::SetAttachment_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  gearbox_sim::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use gearbox_sim::srv::to_yaml() instead")]]
inline std::string to_yaml(const gearbox_sim::srv::SetAttachment_Response & msg)
{
  return gearbox_sim::srv::to_yaml(msg);
}

template<>
inline const char * data_type<gearbox_sim::srv::SetAttachment_Response>()
{
  return "gearbox_sim::srv::SetAttachment_Response";
}

template<>
inline const char * name<gearbox_sim::srv::SetAttachment_Response>()
{
  return "gearbox_sim/srv/SetAttachment_Response";
}

template<>
struct has_fixed_size<gearbox_sim::srv::SetAttachment_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<gearbox_sim::srv::SetAttachment_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<gearbox_sim::srv::SetAttachment_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__traits.hpp"

namespace gearbox_sim
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetAttachment_Event & msg,
  std::ostream & out)
{
  out << "{";
  // member: info
  {
    out << "info: ";
    to_flow_style_yaml(msg.info, out);
    out << ", ";
  }

  // member: request
  {
    if (msg.request.size() == 0) {
      out << "request: []";
    } else {
      out << "request: [";
      size_t pending_items = msg.request.size();
      for (auto item : msg.request) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: response
  {
    if (msg.response.size() == 0) {
      out << "response: []";
    } else {
      out << "response: [";
      size_t pending_items = msg.response.size();
      for (auto item : msg.response) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetAttachment_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: info
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "info:\n";
    to_block_style_yaml(msg.info, out, indentation + 2);
  }

  // member: request
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.request.size() == 0) {
      out << "request: []\n";
    } else {
      out << "request:\n";
      for (auto item : msg.request) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: response
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.response.size() == 0) {
      out << "response: []\n";
    } else {
      out << "response:\n";
      for (auto item : msg.response) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetAttachment_Event & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace gearbox_sim

namespace rosidl_generator_traits
{

[[deprecated("use gearbox_sim::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const gearbox_sim::srv::SetAttachment_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  gearbox_sim::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use gearbox_sim::srv::to_yaml() instead")]]
inline std::string to_yaml(const gearbox_sim::srv::SetAttachment_Event & msg)
{
  return gearbox_sim::srv::to_yaml(msg);
}

template<>
inline const char * data_type<gearbox_sim::srv::SetAttachment_Event>()
{
  return "gearbox_sim::srv::SetAttachment_Event";
}

template<>
inline const char * name<gearbox_sim::srv::SetAttachment_Event>()
{
  return "gearbox_sim/srv/SetAttachment_Event";
}

template<>
struct has_fixed_size<gearbox_sim::srv::SetAttachment_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<gearbox_sim::srv::SetAttachment_Event>
  : std::integral_constant<bool, has_bounded_size<gearbox_sim::srv::SetAttachment_Request>::value && has_bounded_size<gearbox_sim::srv::SetAttachment_Response>::value && has_bounded_size<service_msgs::msg::ServiceEventInfo>::value> {};

template<>
struct is_message<gearbox_sim::srv::SetAttachment_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<gearbox_sim::srv::SetAttachment>()
{
  return "gearbox_sim::srv::SetAttachment";
}

template<>
inline const char * name<gearbox_sim::srv::SetAttachment>()
{
  return "gearbox_sim/srv/SetAttachment";
}

template<>
struct has_fixed_size<gearbox_sim::srv::SetAttachment>
  : std::integral_constant<
    bool,
    has_fixed_size<gearbox_sim::srv::SetAttachment_Request>::value &&
    has_fixed_size<gearbox_sim::srv::SetAttachment_Response>::value
  >
{
};

template<>
struct has_bounded_size<gearbox_sim::srv::SetAttachment>
  : std::integral_constant<
    bool,
    has_bounded_size<gearbox_sim::srv::SetAttachment_Request>::value &&
    has_bounded_size<gearbox_sim::srv::SetAttachment_Response>::value
  >
{
};

template<>
struct is_service<gearbox_sim::srv::SetAttachment>
  : std::true_type
{
};

template<>
struct is_service_request<gearbox_sim::srv::SetAttachment_Request>
  : std::true_type
{
};

template<>
struct is_service_response<gearbox_sim::srv::SetAttachment_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // GEARBOX_SIM__SRV__DETAIL__SET_ATTACHMENT__TRAITS_HPP_
