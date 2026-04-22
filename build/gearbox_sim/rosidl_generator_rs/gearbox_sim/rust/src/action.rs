
#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to gearbox_sim__action__RunScrewdriver_Goal

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunScrewdriver_Goal {

    // This member is not documented.
    #[allow(missing_docs)]
    pub screw_frame: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub approach_height_m: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub descend_depth_m: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub spin_rps: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub duration_sec: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub feed_from_autofeeder: bool,

}



impl Default for RunScrewdriver_Goal {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::RunScrewdriver_Goal::default())
  }
}

impl rosidl_runtime_rs::Message for RunScrewdriver_Goal {
  type RmwMsg = super::action::rmw::RunScrewdriver_Goal;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        screw_frame: msg.screw_frame.as_str().into(),
        approach_height_m: msg.approach_height_m,
        descend_depth_m: msg.descend_depth_m,
        spin_rps: msg.spin_rps,
        duration_sec: msg.duration_sec,
        feed_from_autofeeder: msg.feed_from_autofeeder,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        screw_frame: msg.screw_frame.as_str().into(),
      approach_height_m: msg.approach_height_m,
      descend_depth_m: msg.descend_depth_m,
      spin_rps: msg.spin_rps,
      duration_sec: msg.duration_sec,
      feed_from_autofeeder: msg.feed_from_autofeeder,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      screw_frame: msg.screw_frame.to_string(),
      approach_height_m: msg.approach_height_m,
      descend_depth_m: msg.descend_depth_m,
      spin_rps: msg.spin_rps,
      duration_sec: msg.duration_sec,
      feed_from_autofeeder: msg.feed_from_autofeeder,
    }
  }
}


// Corresponds to gearbox_sim__action__RunScrewdriver_Result

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunScrewdriver_Result {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,

}



impl Default for RunScrewdriver_Result {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::RunScrewdriver_Result::default())
  }
}

impl rosidl_runtime_rs::Message for RunScrewdriver_Result {
  type RmwMsg = super::action::rmw::RunScrewdriver_Result;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        message: msg.message.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
        message: msg.message.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      message: msg.message.to_string(),
    }
  }
}


// Corresponds to gearbox_sim__action__RunScrewdriver_Feedback

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunScrewdriver_Feedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub progress: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub phase: std::string::String,

}



impl Default for RunScrewdriver_Feedback {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::RunScrewdriver_Feedback::default())
  }
}

impl rosidl_runtime_rs::Message for RunScrewdriver_Feedback {
  type RmwMsg = super::action::rmw::RunScrewdriver_Feedback;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        progress: msg.progress,
        phase: msg.phase.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      progress: msg.progress,
        phase: msg.phase.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      progress: msg.progress,
      phase: msg.phase.to_string(),
    }
  }
}


// Corresponds to gearbox_sim__action__RunScrewdriver_FeedbackMessage

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunScrewdriver_FeedbackMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub feedback: super::action::RunScrewdriver_Feedback,

}



impl Default for RunScrewdriver_FeedbackMessage {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::RunScrewdriver_FeedbackMessage::default())
  }
}

impl rosidl_runtime_rs::Message for RunScrewdriver_FeedbackMessage {
  type RmwMsg = super::action::rmw::RunScrewdriver_FeedbackMessage;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
        feedback: super::action::RunScrewdriver_Feedback::into_rmw_message(std::borrow::Cow::Owned(msg.feedback)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
        feedback: super::action::RunScrewdriver_Feedback::into_rmw_message(std::borrow::Cow::Borrowed(&msg.feedback)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
      feedback: super::action::RunScrewdriver_Feedback::from_rmw_message(msg.feedback),
    }
  }
}






// Corresponds to gearbox_sim__action__RunScrewdriver_SendGoal_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunScrewdriver_SendGoal_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: super::action::RunScrewdriver_Goal,

}



impl Default for RunScrewdriver_SendGoal_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::RunScrewdriver_SendGoal_Request::default())
  }
}

impl rosidl_runtime_rs::Message for RunScrewdriver_SendGoal_Request {
  type RmwMsg = super::action::rmw::RunScrewdriver_SendGoal_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
        goal: super::action::RunScrewdriver_Goal::into_rmw_message(std::borrow::Cow::Owned(msg.goal)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
        goal: super::action::RunScrewdriver_Goal::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
      goal: super::action::RunScrewdriver_Goal::from_rmw_message(msg.goal),
    }
  }
}


// Corresponds to gearbox_sim__action__RunScrewdriver_SendGoal_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunScrewdriver_SendGoal_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::Time,

}



impl Default for RunScrewdriver_SendGoal_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::RunScrewdriver_SendGoal_Response::default())
  }
}

impl rosidl_runtime_rs::Message for RunScrewdriver_SendGoal_Response {
  type RmwMsg = super::action::rmw::RunScrewdriver_SendGoal_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        accepted: msg.accepted,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Owned(msg.stamp)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      accepted: msg.accepted,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Borrowed(&msg.stamp)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      accepted: msg.accepted,
      stamp: builtin_interfaces::msg::Time::from_rmw_message(msg.stamp),
    }
  }
}


// Corresponds to gearbox_sim__action__RunScrewdriver_GetResult_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunScrewdriver_GetResult_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,

}



impl Default for RunScrewdriver_GetResult_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::RunScrewdriver_GetResult_Request::default())
  }
}

impl rosidl_runtime_rs::Message for RunScrewdriver_GetResult_Request {
  type RmwMsg = super::action::rmw::RunScrewdriver_GetResult_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
    }
  }
}


// Corresponds to gearbox_sim__action__RunScrewdriver_GetResult_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunScrewdriver_GetResult_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result: super::action::RunScrewdriver_Result,

}



impl Default for RunScrewdriver_GetResult_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::RunScrewdriver_GetResult_Response::default())
  }
}

impl rosidl_runtime_rs::Message for RunScrewdriver_GetResult_Response {
  type RmwMsg = super::action::rmw::RunScrewdriver_GetResult_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        status: msg.status,
        result: super::action::RunScrewdriver_Result::into_rmw_message(std::borrow::Cow::Owned(msg.result)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      status: msg.status,
        result: super::action::RunScrewdriver_Result::into_rmw_message(std::borrow::Cow::Borrowed(&msg.result)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      status: msg.status,
      result: super::action::RunScrewdriver_Result::from_rmw_message(msg.result),
    }
  }
}






#[link(name = "gearbox_sim__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__gearbox_sim__action__RunScrewdriver_SendGoal() -> *const std::ffi::c_void;
}

// Corresponds to gearbox_sim__action__RunScrewdriver_SendGoal
#[allow(missing_docs, non_camel_case_types)]
pub struct RunScrewdriver_SendGoal;

impl rosidl_runtime_rs::Service for RunScrewdriver_SendGoal {
    type Request = RunScrewdriver_SendGoal_Request;
    type Response = RunScrewdriver_SendGoal_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__gearbox_sim__action__RunScrewdriver_SendGoal() }
    }
}




#[link(name = "gearbox_sim__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__gearbox_sim__action__RunScrewdriver_GetResult() -> *const std::ffi::c_void;
}

// Corresponds to gearbox_sim__action__RunScrewdriver_GetResult
#[allow(missing_docs, non_camel_case_types)]
pub struct RunScrewdriver_GetResult;

impl rosidl_runtime_rs::Service for RunScrewdriver_GetResult {
    type Request = RunScrewdriver_GetResult_Request;
    type Response = RunScrewdriver_GetResult_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__gearbox_sim__action__RunScrewdriver_GetResult() }
    }
}






#[link(name = "gearbox_sim__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_action_type_support_handle__gearbox_sim__action__RunScrewdriver() -> *const std::ffi::c_void;
}

// Corresponds to gearbox_sim__action__RunScrewdriver
#[allow(missing_docs, non_camel_case_types)]
pub struct RunScrewdriver;

impl rosidl_runtime_rs::Action for RunScrewdriver {
  // --- Associated types for client library users ---
  /// The goal message defined in the action definition.
  type Goal = RunScrewdriver_Goal;

  /// The result message defined in the action definition.
  type Result = RunScrewdriver_Result;

  /// The feedback message defined in the action definition.
  type Feedback = RunScrewdriver_Feedback;

  // --- Associated types for client library implementation ---
  /// The feedback message with generic fields which wraps the feedback message.
  type FeedbackMessage = super::action::RunScrewdriver_FeedbackMessage;

  /// The send_goal service using a wrapped version of the goal message as a request.
  type SendGoalService = super::action::RunScrewdriver_SendGoal;

  /// The generic service to cancel a goal.
  type CancelGoalService = action_msgs::srv::rmw::CancelGoal;

  /// The get_result service using a wrapped version of the result message as a response.
  type GetResultService = super::action::RunScrewdriver_GetResult;

  // --- Methods for client library implementation ---
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_action_type_support_handle__gearbox_sim__action__RunScrewdriver() }
  }

  fn create_goal_request(
    goal_id: &[u8; 16],
    goal: super::action::rmw::RunScrewdriver_Goal,
  ) -> super::action::rmw::RunScrewdriver_SendGoal_Request {
   super::action::rmw::RunScrewdriver_SendGoal_Request {
      goal_id: unique_identifier_msgs::msg::rmw::UUID { uuid: *goal_id },
      goal,
    }
  }

  fn split_goal_request(
    request: super::action::rmw::RunScrewdriver_SendGoal_Request,
  ) -> (
    [u8; 16],
   super::action::rmw::RunScrewdriver_Goal,
  ) {
    (request.goal_id.uuid, request.goal)
  }

  fn create_goal_response(
    accepted: bool,
    stamp: (i32, u32),
  ) -> super::action::rmw::RunScrewdriver_SendGoal_Response {
   super::action::rmw::RunScrewdriver_SendGoal_Response {
      accepted,
      stamp: builtin_interfaces::msg::rmw::Time {
        sec: stamp.0,
        nanosec: stamp.1,
      },
    }
  }

  fn get_goal_response_accepted(
    response: &super::action::rmw::RunScrewdriver_SendGoal_Response,
  ) -> bool {
    response.accepted
  }

  fn get_goal_response_stamp(
    response: &super::action::rmw::RunScrewdriver_SendGoal_Response,
  ) -> (i32, u32) {
    (response.stamp.sec, response.stamp.nanosec)
  }

  fn create_feedback_message(
    goal_id: &[u8; 16],
    feedback: super::action::rmw::RunScrewdriver_Feedback,
  ) -> super::action::rmw::RunScrewdriver_FeedbackMessage {
    let mut message = super::action::rmw::RunScrewdriver_FeedbackMessage::default();
    message.goal_id.uuid = *goal_id;
    message.feedback = feedback;
    message
  }

  fn split_feedback_message(
    feedback: super::action::rmw::RunScrewdriver_FeedbackMessage,
  ) -> (
    [u8; 16],
   super::action::rmw::RunScrewdriver_Feedback,
  ) {
    (feedback.goal_id.uuid, feedback.feedback)
  }

  fn create_result_request(
    goal_id: &[u8; 16],
  ) -> super::action::rmw::RunScrewdriver_GetResult_Request {
   super::action::rmw::RunScrewdriver_GetResult_Request {
      goal_id: unique_identifier_msgs::msg::rmw::UUID { uuid: *goal_id },
    }
  }

  fn get_result_request_uuid(
    request: &super::action::rmw::RunScrewdriver_GetResult_Request,
  ) -> &[u8; 16] {
    &request.goal_id.uuid
  }

  fn create_result_response(
    status: i8,
    result: super::action::rmw::RunScrewdriver_Result,
  ) -> super::action::rmw::RunScrewdriver_GetResult_Response {
   super::action::rmw::RunScrewdriver_GetResult_Response {
      status,
      result,
    }
  }

  fn split_result_response(
    response: super::action::rmw::RunScrewdriver_GetResult_Response
  ) -> (
    i8,
   super::action::rmw::RunScrewdriver_Result,
  ) {
    (response.status, response.result)
  }
}


