// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from gearbox_sim:action/RunScrewdriver.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "gearbox_sim/action/run_screwdriver.hpp"


#ifndef GEARBOX_SIM__ACTION__DETAIL__RUN_SCREWDRIVER__BUILDER_HPP_
#define GEARBOX_SIM__ACTION__DETAIL__RUN_SCREWDRIVER__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "gearbox_sim/action/detail/run_screwdriver__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace gearbox_sim
{

namespace action
{

namespace builder
{

class Init_RunScrewdriver_Goal_feed_from_autofeeder
{
public:
  explicit Init_RunScrewdriver_Goal_feed_from_autofeeder(::gearbox_sim::action::RunScrewdriver_Goal & msg)
  : msg_(msg)
  {}
  ::gearbox_sim::action::RunScrewdriver_Goal feed_from_autofeeder(::gearbox_sim::action::RunScrewdriver_Goal::_feed_from_autofeeder_type arg)
  {
    msg_.feed_from_autofeeder = std::move(arg);
    return std::move(msg_);
  }

private:
  ::gearbox_sim::action::RunScrewdriver_Goal msg_;
};

class Init_RunScrewdriver_Goal_duration_sec
{
public:
  explicit Init_RunScrewdriver_Goal_duration_sec(::gearbox_sim::action::RunScrewdriver_Goal & msg)
  : msg_(msg)
  {}
  Init_RunScrewdriver_Goal_feed_from_autofeeder duration_sec(::gearbox_sim::action::RunScrewdriver_Goal::_duration_sec_type arg)
  {
    msg_.duration_sec = std::move(arg);
    return Init_RunScrewdriver_Goal_feed_from_autofeeder(msg_);
  }

private:
  ::gearbox_sim::action::RunScrewdriver_Goal msg_;
};

class Init_RunScrewdriver_Goal_spin_rps
{
public:
  explicit Init_RunScrewdriver_Goal_spin_rps(::gearbox_sim::action::RunScrewdriver_Goal & msg)
  : msg_(msg)
  {}
  Init_RunScrewdriver_Goal_duration_sec spin_rps(::gearbox_sim::action::RunScrewdriver_Goal::_spin_rps_type arg)
  {
    msg_.spin_rps = std::move(arg);
    return Init_RunScrewdriver_Goal_duration_sec(msg_);
  }

private:
  ::gearbox_sim::action::RunScrewdriver_Goal msg_;
};

class Init_RunScrewdriver_Goal_descend_depth_m
{
public:
  explicit Init_RunScrewdriver_Goal_descend_depth_m(::gearbox_sim::action::RunScrewdriver_Goal & msg)
  : msg_(msg)
  {}
  Init_RunScrewdriver_Goal_spin_rps descend_depth_m(::gearbox_sim::action::RunScrewdriver_Goal::_descend_depth_m_type arg)
  {
    msg_.descend_depth_m = std::move(arg);
    return Init_RunScrewdriver_Goal_spin_rps(msg_);
  }

private:
  ::gearbox_sim::action::RunScrewdriver_Goal msg_;
};

class Init_RunScrewdriver_Goal_approach_height_m
{
public:
  explicit Init_RunScrewdriver_Goal_approach_height_m(::gearbox_sim::action::RunScrewdriver_Goal & msg)
  : msg_(msg)
  {}
  Init_RunScrewdriver_Goal_descend_depth_m approach_height_m(::gearbox_sim::action::RunScrewdriver_Goal::_approach_height_m_type arg)
  {
    msg_.approach_height_m = std::move(arg);
    return Init_RunScrewdriver_Goal_descend_depth_m(msg_);
  }

private:
  ::gearbox_sim::action::RunScrewdriver_Goal msg_;
};

class Init_RunScrewdriver_Goal_screw_frame
{
public:
  Init_RunScrewdriver_Goal_screw_frame()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RunScrewdriver_Goal_approach_height_m screw_frame(::gearbox_sim::action::RunScrewdriver_Goal::_screw_frame_type arg)
  {
    msg_.screw_frame = std::move(arg);
    return Init_RunScrewdriver_Goal_approach_height_m(msg_);
  }

private:
  ::gearbox_sim::action::RunScrewdriver_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::gearbox_sim::action::RunScrewdriver_Goal>()
{
  return gearbox_sim::action::builder::Init_RunScrewdriver_Goal_screw_frame();
}

}  // namespace gearbox_sim


namespace gearbox_sim
{

namespace action
{

namespace builder
{

class Init_RunScrewdriver_Result_message
{
public:
  explicit Init_RunScrewdriver_Result_message(::gearbox_sim::action::RunScrewdriver_Result & msg)
  : msg_(msg)
  {}
  ::gearbox_sim::action::RunScrewdriver_Result message(::gearbox_sim::action::RunScrewdriver_Result::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::gearbox_sim::action::RunScrewdriver_Result msg_;
};

class Init_RunScrewdriver_Result_success
{
public:
  Init_RunScrewdriver_Result_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RunScrewdriver_Result_message success(::gearbox_sim::action::RunScrewdriver_Result::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_RunScrewdriver_Result_message(msg_);
  }

private:
  ::gearbox_sim::action::RunScrewdriver_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::gearbox_sim::action::RunScrewdriver_Result>()
{
  return gearbox_sim::action::builder::Init_RunScrewdriver_Result_success();
}

}  // namespace gearbox_sim


namespace gearbox_sim
{

namespace action
{

namespace builder
{

class Init_RunScrewdriver_Feedback_phase
{
public:
  explicit Init_RunScrewdriver_Feedback_phase(::gearbox_sim::action::RunScrewdriver_Feedback & msg)
  : msg_(msg)
  {}
  ::gearbox_sim::action::RunScrewdriver_Feedback phase(::gearbox_sim::action::RunScrewdriver_Feedback::_phase_type arg)
  {
    msg_.phase = std::move(arg);
    return std::move(msg_);
  }

private:
  ::gearbox_sim::action::RunScrewdriver_Feedback msg_;
};

class Init_RunScrewdriver_Feedback_progress
{
public:
  Init_RunScrewdriver_Feedback_progress()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RunScrewdriver_Feedback_phase progress(::gearbox_sim::action::RunScrewdriver_Feedback::_progress_type arg)
  {
    msg_.progress = std::move(arg);
    return Init_RunScrewdriver_Feedback_phase(msg_);
  }

private:
  ::gearbox_sim::action::RunScrewdriver_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::gearbox_sim::action::RunScrewdriver_Feedback>()
{
  return gearbox_sim::action::builder::Init_RunScrewdriver_Feedback_progress();
}

}  // namespace gearbox_sim


namespace gearbox_sim
{

namespace action
{

namespace builder
{

class Init_RunScrewdriver_SendGoal_Request_goal
{
public:
  explicit Init_RunScrewdriver_SendGoal_Request_goal(::gearbox_sim::action::RunScrewdriver_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::gearbox_sim::action::RunScrewdriver_SendGoal_Request goal(::gearbox_sim::action::RunScrewdriver_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::gearbox_sim::action::RunScrewdriver_SendGoal_Request msg_;
};

class Init_RunScrewdriver_SendGoal_Request_goal_id
{
public:
  Init_RunScrewdriver_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RunScrewdriver_SendGoal_Request_goal goal_id(::gearbox_sim::action::RunScrewdriver_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_RunScrewdriver_SendGoal_Request_goal(msg_);
  }

private:
  ::gearbox_sim::action::RunScrewdriver_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::gearbox_sim::action::RunScrewdriver_SendGoal_Request>()
{
  return gearbox_sim::action::builder::Init_RunScrewdriver_SendGoal_Request_goal_id();
}

}  // namespace gearbox_sim


namespace gearbox_sim
{

namespace action
{

namespace builder
{

class Init_RunScrewdriver_SendGoal_Response_stamp
{
public:
  explicit Init_RunScrewdriver_SendGoal_Response_stamp(::gearbox_sim::action::RunScrewdriver_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::gearbox_sim::action::RunScrewdriver_SendGoal_Response stamp(::gearbox_sim::action::RunScrewdriver_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::gearbox_sim::action::RunScrewdriver_SendGoal_Response msg_;
};

class Init_RunScrewdriver_SendGoal_Response_accepted
{
public:
  Init_RunScrewdriver_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RunScrewdriver_SendGoal_Response_stamp accepted(::gearbox_sim::action::RunScrewdriver_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_RunScrewdriver_SendGoal_Response_stamp(msg_);
  }

private:
  ::gearbox_sim::action::RunScrewdriver_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::gearbox_sim::action::RunScrewdriver_SendGoal_Response>()
{
  return gearbox_sim::action::builder::Init_RunScrewdriver_SendGoal_Response_accepted();
}

}  // namespace gearbox_sim


namespace gearbox_sim
{

namespace action
{

namespace builder
{

class Init_RunScrewdriver_SendGoal_Event_response
{
public:
  explicit Init_RunScrewdriver_SendGoal_Event_response(::gearbox_sim::action::RunScrewdriver_SendGoal_Event & msg)
  : msg_(msg)
  {}
  ::gearbox_sim::action::RunScrewdriver_SendGoal_Event response(::gearbox_sim::action::RunScrewdriver_SendGoal_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::gearbox_sim::action::RunScrewdriver_SendGoal_Event msg_;
};

class Init_RunScrewdriver_SendGoal_Event_request
{
public:
  explicit Init_RunScrewdriver_SendGoal_Event_request(::gearbox_sim::action::RunScrewdriver_SendGoal_Event & msg)
  : msg_(msg)
  {}
  Init_RunScrewdriver_SendGoal_Event_response request(::gearbox_sim::action::RunScrewdriver_SendGoal_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_RunScrewdriver_SendGoal_Event_response(msg_);
  }

private:
  ::gearbox_sim::action::RunScrewdriver_SendGoal_Event msg_;
};

class Init_RunScrewdriver_SendGoal_Event_info
{
public:
  Init_RunScrewdriver_SendGoal_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RunScrewdriver_SendGoal_Event_request info(::gearbox_sim::action::RunScrewdriver_SendGoal_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_RunScrewdriver_SendGoal_Event_request(msg_);
  }

private:
  ::gearbox_sim::action::RunScrewdriver_SendGoal_Event msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::gearbox_sim::action::RunScrewdriver_SendGoal_Event>()
{
  return gearbox_sim::action::builder::Init_RunScrewdriver_SendGoal_Event_info();
}

}  // namespace gearbox_sim


namespace gearbox_sim
{

namespace action
{

namespace builder
{

class Init_RunScrewdriver_GetResult_Request_goal_id
{
public:
  Init_RunScrewdriver_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::gearbox_sim::action::RunScrewdriver_GetResult_Request goal_id(::gearbox_sim::action::RunScrewdriver_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::gearbox_sim::action::RunScrewdriver_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::gearbox_sim::action::RunScrewdriver_GetResult_Request>()
{
  return gearbox_sim::action::builder::Init_RunScrewdriver_GetResult_Request_goal_id();
}

}  // namespace gearbox_sim


namespace gearbox_sim
{

namespace action
{

namespace builder
{

class Init_RunScrewdriver_GetResult_Response_result
{
public:
  explicit Init_RunScrewdriver_GetResult_Response_result(::gearbox_sim::action::RunScrewdriver_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::gearbox_sim::action::RunScrewdriver_GetResult_Response result(::gearbox_sim::action::RunScrewdriver_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::gearbox_sim::action::RunScrewdriver_GetResult_Response msg_;
};

class Init_RunScrewdriver_GetResult_Response_status
{
public:
  Init_RunScrewdriver_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RunScrewdriver_GetResult_Response_result status(::gearbox_sim::action::RunScrewdriver_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_RunScrewdriver_GetResult_Response_result(msg_);
  }

private:
  ::gearbox_sim::action::RunScrewdriver_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::gearbox_sim::action::RunScrewdriver_GetResult_Response>()
{
  return gearbox_sim::action::builder::Init_RunScrewdriver_GetResult_Response_status();
}

}  // namespace gearbox_sim


namespace gearbox_sim
{

namespace action
{

namespace builder
{

class Init_RunScrewdriver_GetResult_Event_response
{
public:
  explicit Init_RunScrewdriver_GetResult_Event_response(::gearbox_sim::action::RunScrewdriver_GetResult_Event & msg)
  : msg_(msg)
  {}
  ::gearbox_sim::action::RunScrewdriver_GetResult_Event response(::gearbox_sim::action::RunScrewdriver_GetResult_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::gearbox_sim::action::RunScrewdriver_GetResult_Event msg_;
};

class Init_RunScrewdriver_GetResult_Event_request
{
public:
  explicit Init_RunScrewdriver_GetResult_Event_request(::gearbox_sim::action::RunScrewdriver_GetResult_Event & msg)
  : msg_(msg)
  {}
  Init_RunScrewdriver_GetResult_Event_response request(::gearbox_sim::action::RunScrewdriver_GetResult_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_RunScrewdriver_GetResult_Event_response(msg_);
  }

private:
  ::gearbox_sim::action::RunScrewdriver_GetResult_Event msg_;
};

class Init_RunScrewdriver_GetResult_Event_info
{
public:
  Init_RunScrewdriver_GetResult_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RunScrewdriver_GetResult_Event_request info(::gearbox_sim::action::RunScrewdriver_GetResult_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_RunScrewdriver_GetResult_Event_request(msg_);
  }

private:
  ::gearbox_sim::action::RunScrewdriver_GetResult_Event msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::gearbox_sim::action::RunScrewdriver_GetResult_Event>()
{
  return gearbox_sim::action::builder::Init_RunScrewdriver_GetResult_Event_info();
}

}  // namespace gearbox_sim


namespace gearbox_sim
{

namespace action
{

namespace builder
{

class Init_RunScrewdriver_FeedbackMessage_feedback
{
public:
  explicit Init_RunScrewdriver_FeedbackMessage_feedback(::gearbox_sim::action::RunScrewdriver_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::gearbox_sim::action::RunScrewdriver_FeedbackMessage feedback(::gearbox_sim::action::RunScrewdriver_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::gearbox_sim::action::RunScrewdriver_FeedbackMessage msg_;
};

class Init_RunScrewdriver_FeedbackMessage_goal_id
{
public:
  Init_RunScrewdriver_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RunScrewdriver_FeedbackMessage_feedback goal_id(::gearbox_sim::action::RunScrewdriver_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_RunScrewdriver_FeedbackMessage_feedback(msg_);
  }

private:
  ::gearbox_sim::action::RunScrewdriver_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::gearbox_sim::action::RunScrewdriver_FeedbackMessage>()
{
  return gearbox_sim::action::builder::Init_RunScrewdriver_FeedbackMessage_goal_id();
}

}  // namespace gearbox_sim

#endif  // GEARBOX_SIM__ACTION__DETAIL__RUN_SCREWDRIVER__BUILDER_HPP_
