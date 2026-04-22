// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from gearbox_sim:srv/RunPressCycle.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "gearbox_sim/srv/run_press_cycle.hpp"


#ifndef GEARBOX_SIM__SRV__DETAIL__RUN_PRESS_CYCLE__BUILDER_HPP_
#define GEARBOX_SIM__SRV__DETAIL__RUN_PRESS_CYCLE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "gearbox_sim/srv/detail/run_press_cycle__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace gearbox_sim
{

namespace srv
{

namespace builder
{

class Init_RunPressCycle_Request_dwell_sec
{
public:
  explicit Init_RunPressCycle_Request_dwell_sec(::gearbox_sim::srv::RunPressCycle_Request & msg)
  : msg_(msg)
  {}
  ::gearbox_sim::srv::RunPressCycle_Request dwell_sec(::gearbox_sim::srv::RunPressCycle_Request::_dwell_sec_type arg)
  {
    msg_.dwell_sec = std::move(arg);
    return std::move(msg_);
  }

private:
  ::gearbox_sim::srv::RunPressCycle_Request msg_;
};

class Init_RunPressCycle_Request_stroke_m
{
public:
  explicit Init_RunPressCycle_Request_stroke_m(::gearbox_sim::srv::RunPressCycle_Request & msg)
  : msg_(msg)
  {}
  Init_RunPressCycle_Request_dwell_sec stroke_m(::gearbox_sim::srv::RunPressCycle_Request::_stroke_m_type arg)
  {
    msg_.stroke_m = std::move(arg);
    return Init_RunPressCycle_Request_dwell_sec(msg_);
  }

private:
  ::gearbox_sim::srv::RunPressCycle_Request msg_;
};

class Init_RunPressCycle_Request_approach_height_m
{
public:
  explicit Init_RunPressCycle_Request_approach_height_m(::gearbox_sim::srv::RunPressCycle_Request & msg)
  : msg_(msg)
  {}
  Init_RunPressCycle_Request_stroke_m approach_height_m(::gearbox_sim::srv::RunPressCycle_Request::_approach_height_m_type arg)
  {
    msg_.approach_height_m = std::move(arg);
    return Init_RunPressCycle_Request_stroke_m(msg_);
  }

private:
  ::gearbox_sim::srv::RunPressCycle_Request msg_;
};

class Init_RunPressCycle_Request_target_frame
{
public:
  explicit Init_RunPressCycle_Request_target_frame(::gearbox_sim::srv::RunPressCycle_Request & msg)
  : msg_(msg)
  {}
  Init_RunPressCycle_Request_approach_height_m target_frame(::gearbox_sim::srv::RunPressCycle_Request::_target_frame_type arg)
  {
    msg_.target_frame = std::move(arg);
    return Init_RunPressCycle_Request_approach_height_m(msg_);
  }

private:
  ::gearbox_sim::srv::RunPressCycle_Request msg_;
};

class Init_RunPressCycle_Request_recipe_name
{
public:
  Init_RunPressCycle_Request_recipe_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RunPressCycle_Request_target_frame recipe_name(::gearbox_sim::srv::RunPressCycle_Request::_recipe_name_type arg)
  {
    msg_.recipe_name = std::move(arg);
    return Init_RunPressCycle_Request_target_frame(msg_);
  }

private:
  ::gearbox_sim::srv::RunPressCycle_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::gearbox_sim::srv::RunPressCycle_Request>()
{
  return gearbox_sim::srv::builder::Init_RunPressCycle_Request_recipe_name();
}

}  // namespace gearbox_sim


namespace gearbox_sim
{

namespace srv
{

namespace builder
{

class Init_RunPressCycle_Response_message
{
public:
  explicit Init_RunPressCycle_Response_message(::gearbox_sim::srv::RunPressCycle_Response & msg)
  : msg_(msg)
  {}
  ::gearbox_sim::srv::RunPressCycle_Response message(::gearbox_sim::srv::RunPressCycle_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::gearbox_sim::srv::RunPressCycle_Response msg_;
};

class Init_RunPressCycle_Response_success
{
public:
  Init_RunPressCycle_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RunPressCycle_Response_message success(::gearbox_sim::srv::RunPressCycle_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_RunPressCycle_Response_message(msg_);
  }

private:
  ::gearbox_sim::srv::RunPressCycle_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::gearbox_sim::srv::RunPressCycle_Response>()
{
  return gearbox_sim::srv::builder::Init_RunPressCycle_Response_success();
}

}  // namespace gearbox_sim


namespace gearbox_sim
{

namespace srv
{

namespace builder
{

class Init_RunPressCycle_Event_response
{
public:
  explicit Init_RunPressCycle_Event_response(::gearbox_sim::srv::RunPressCycle_Event & msg)
  : msg_(msg)
  {}
  ::gearbox_sim::srv::RunPressCycle_Event response(::gearbox_sim::srv::RunPressCycle_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::gearbox_sim::srv::RunPressCycle_Event msg_;
};

class Init_RunPressCycle_Event_request
{
public:
  explicit Init_RunPressCycle_Event_request(::gearbox_sim::srv::RunPressCycle_Event & msg)
  : msg_(msg)
  {}
  Init_RunPressCycle_Event_response request(::gearbox_sim::srv::RunPressCycle_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_RunPressCycle_Event_response(msg_);
  }

private:
  ::gearbox_sim::srv::RunPressCycle_Event msg_;
};

class Init_RunPressCycle_Event_info
{
public:
  Init_RunPressCycle_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RunPressCycle_Event_request info(::gearbox_sim::srv::RunPressCycle_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_RunPressCycle_Event_request(msg_);
  }

private:
  ::gearbox_sim::srv::RunPressCycle_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::gearbox_sim::srv::RunPressCycle_Event>()
{
  return gearbox_sim::srv::builder::Init_RunPressCycle_Event_info();
}

}  // namespace gearbox_sim

#endif  // GEARBOX_SIM__SRV__DETAIL__RUN_PRESS_CYCLE__BUILDER_HPP_
