// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from gearbox_sim:srv/SetAttachment.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "gearbox_sim/srv/set_attachment.hpp"


#ifndef GEARBOX_SIM__SRV__DETAIL__SET_ATTACHMENT__BUILDER_HPP_
#define GEARBOX_SIM__SRV__DETAIL__SET_ATTACHMENT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "gearbox_sim/srv/detail/set_attachment__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace gearbox_sim
{

namespace srv
{

namespace builder
{

class Init_SetAttachment_Request_attach
{
public:
  explicit Init_SetAttachment_Request_attach(::gearbox_sim::srv::SetAttachment_Request & msg)
  : msg_(msg)
  {}
  ::gearbox_sim::srv::SetAttachment_Request attach(::gearbox_sim::srv::SetAttachment_Request::_attach_type arg)
  {
    msg_.attach = std::move(arg);
    return std::move(msg_);
  }

private:
  ::gearbox_sim::srv::SetAttachment_Request msg_;
};

class Init_SetAttachment_Request_part_link
{
public:
  explicit Init_SetAttachment_Request_part_link(::gearbox_sim::srv::SetAttachment_Request & msg)
  : msg_(msg)
  {}
  Init_SetAttachment_Request_attach part_link(::gearbox_sim::srv::SetAttachment_Request::_part_link_type arg)
  {
    msg_.part_link = std::move(arg);
    return Init_SetAttachment_Request_attach(msg_);
  }

private:
  ::gearbox_sim::srv::SetAttachment_Request msg_;
};

class Init_SetAttachment_Request_part_frame
{
public:
  explicit Init_SetAttachment_Request_part_frame(::gearbox_sim::srv::SetAttachment_Request & msg)
  : msg_(msg)
  {}
  Init_SetAttachment_Request_part_link part_frame(::gearbox_sim::srv::SetAttachment_Request::_part_frame_type arg)
  {
    msg_.part_frame = std::move(arg);
    return Init_SetAttachment_Request_part_link(msg_);
  }

private:
  ::gearbox_sim::srv::SetAttachment_Request msg_;
};

class Init_SetAttachment_Request_part_name
{
public:
  explicit Init_SetAttachment_Request_part_name(::gearbox_sim::srv::SetAttachment_Request & msg)
  : msg_(msg)
  {}
  Init_SetAttachment_Request_part_frame part_name(::gearbox_sim::srv::SetAttachment_Request::_part_name_type arg)
  {
    msg_.part_name = std::move(arg);
    return Init_SetAttachment_Request_part_frame(msg_);
  }

private:
  ::gearbox_sim::srv::SetAttachment_Request msg_;
};

class Init_SetAttachment_Request_tool_frame
{
public:
  explicit Init_SetAttachment_Request_tool_frame(::gearbox_sim::srv::SetAttachment_Request & msg)
  : msg_(msg)
  {}
  Init_SetAttachment_Request_part_name tool_frame(::gearbox_sim::srv::SetAttachment_Request::_tool_frame_type arg)
  {
    msg_.tool_frame = std::move(arg);
    return Init_SetAttachment_Request_part_name(msg_);
  }

private:
  ::gearbox_sim::srv::SetAttachment_Request msg_;
};

class Init_SetAttachment_Request_robot_name
{
public:
  Init_SetAttachment_Request_robot_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetAttachment_Request_tool_frame robot_name(::gearbox_sim::srv::SetAttachment_Request::_robot_name_type arg)
  {
    msg_.robot_name = std::move(arg);
    return Init_SetAttachment_Request_tool_frame(msg_);
  }

private:
  ::gearbox_sim::srv::SetAttachment_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::gearbox_sim::srv::SetAttachment_Request>()
{
  return gearbox_sim::srv::builder::Init_SetAttachment_Request_robot_name();
}

}  // namespace gearbox_sim


namespace gearbox_sim
{

namespace srv
{

namespace builder
{

class Init_SetAttachment_Response_message
{
public:
  explicit Init_SetAttachment_Response_message(::gearbox_sim::srv::SetAttachment_Response & msg)
  : msg_(msg)
  {}
  ::gearbox_sim::srv::SetAttachment_Response message(::gearbox_sim::srv::SetAttachment_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::gearbox_sim::srv::SetAttachment_Response msg_;
};

class Init_SetAttachment_Response_success
{
public:
  Init_SetAttachment_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetAttachment_Response_message success(::gearbox_sim::srv::SetAttachment_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_SetAttachment_Response_message(msg_);
  }

private:
  ::gearbox_sim::srv::SetAttachment_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::gearbox_sim::srv::SetAttachment_Response>()
{
  return gearbox_sim::srv::builder::Init_SetAttachment_Response_success();
}

}  // namespace gearbox_sim


namespace gearbox_sim
{

namespace srv
{

namespace builder
{

class Init_SetAttachment_Event_response
{
public:
  explicit Init_SetAttachment_Event_response(::gearbox_sim::srv::SetAttachment_Event & msg)
  : msg_(msg)
  {}
  ::gearbox_sim::srv::SetAttachment_Event response(::gearbox_sim::srv::SetAttachment_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::gearbox_sim::srv::SetAttachment_Event msg_;
};

class Init_SetAttachment_Event_request
{
public:
  explicit Init_SetAttachment_Event_request(::gearbox_sim::srv::SetAttachment_Event & msg)
  : msg_(msg)
  {}
  Init_SetAttachment_Event_response request(::gearbox_sim::srv::SetAttachment_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_SetAttachment_Event_response(msg_);
  }

private:
  ::gearbox_sim::srv::SetAttachment_Event msg_;
};

class Init_SetAttachment_Event_info
{
public:
  Init_SetAttachment_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetAttachment_Event_request info(::gearbox_sim::srv::SetAttachment_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_SetAttachment_Event_request(msg_);
  }

private:
  ::gearbox_sim::srv::SetAttachment_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::gearbox_sim::srv::SetAttachment_Event>()
{
  return gearbox_sim::srv::builder::Init_SetAttachment_Event_info();
}

}  // namespace gearbox_sim

#endif  // GEARBOX_SIM__SRV__DETAIL__SET_ATTACHMENT__BUILDER_HPP_
