
#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "gearbox_sim__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__gearbox_sim__action__RunScrewdriver_Goal() -> *const std::ffi::c_void;
}

#[link(name = "gearbox_sim__rosidl_generator_c")]
extern "C" {
    fn gearbox_sim__action__RunScrewdriver_Goal__init(msg: *mut RunScrewdriver_Goal) -> bool;
    fn gearbox_sim__action__RunScrewdriver_Goal__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<RunScrewdriver_Goal>, size: usize) -> bool;
    fn gearbox_sim__action__RunScrewdriver_Goal__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<RunScrewdriver_Goal>);
    fn gearbox_sim__action__RunScrewdriver_Goal__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<RunScrewdriver_Goal>, out_seq: *mut rosidl_runtime_rs::Sequence<RunScrewdriver_Goal>) -> bool;
}

// Corresponds to gearbox_sim__action__RunScrewdriver_Goal
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunScrewdriver_Goal {

    // This member is not documented.
    #[allow(missing_docs)]
    pub screw_frame: rosidl_runtime_rs::String,


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
    unsafe {
      let mut msg = std::mem::zeroed();
      if !gearbox_sim__action__RunScrewdriver_Goal__init(&mut msg as *mut _) {
        panic!("Call to gearbox_sim__action__RunScrewdriver_Goal__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for RunScrewdriver_Goal {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__action__RunScrewdriver_Goal__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__action__RunScrewdriver_Goal__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__action__RunScrewdriver_Goal__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for RunScrewdriver_Goal {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for RunScrewdriver_Goal where Self: Sized {
  const TYPE_NAME: &'static str = "gearbox_sim/action/RunScrewdriver_Goal";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__gearbox_sim__action__RunScrewdriver_Goal() }
  }
}


#[link(name = "gearbox_sim__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__gearbox_sim__action__RunScrewdriver_Result() -> *const std::ffi::c_void;
}

#[link(name = "gearbox_sim__rosidl_generator_c")]
extern "C" {
    fn gearbox_sim__action__RunScrewdriver_Result__init(msg: *mut RunScrewdriver_Result) -> bool;
    fn gearbox_sim__action__RunScrewdriver_Result__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<RunScrewdriver_Result>, size: usize) -> bool;
    fn gearbox_sim__action__RunScrewdriver_Result__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<RunScrewdriver_Result>);
    fn gearbox_sim__action__RunScrewdriver_Result__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<RunScrewdriver_Result>, out_seq: *mut rosidl_runtime_rs::Sequence<RunScrewdriver_Result>) -> bool;
}

// Corresponds to gearbox_sim__action__RunScrewdriver_Result
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunScrewdriver_Result {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}



impl Default for RunScrewdriver_Result {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !gearbox_sim__action__RunScrewdriver_Result__init(&mut msg as *mut _) {
        panic!("Call to gearbox_sim__action__RunScrewdriver_Result__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for RunScrewdriver_Result {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__action__RunScrewdriver_Result__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__action__RunScrewdriver_Result__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__action__RunScrewdriver_Result__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for RunScrewdriver_Result {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for RunScrewdriver_Result where Self: Sized {
  const TYPE_NAME: &'static str = "gearbox_sim/action/RunScrewdriver_Result";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__gearbox_sim__action__RunScrewdriver_Result() }
  }
}


#[link(name = "gearbox_sim__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__gearbox_sim__action__RunScrewdriver_Feedback() -> *const std::ffi::c_void;
}

#[link(name = "gearbox_sim__rosidl_generator_c")]
extern "C" {
    fn gearbox_sim__action__RunScrewdriver_Feedback__init(msg: *mut RunScrewdriver_Feedback) -> bool;
    fn gearbox_sim__action__RunScrewdriver_Feedback__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<RunScrewdriver_Feedback>, size: usize) -> bool;
    fn gearbox_sim__action__RunScrewdriver_Feedback__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<RunScrewdriver_Feedback>);
    fn gearbox_sim__action__RunScrewdriver_Feedback__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<RunScrewdriver_Feedback>, out_seq: *mut rosidl_runtime_rs::Sequence<RunScrewdriver_Feedback>) -> bool;
}

// Corresponds to gearbox_sim__action__RunScrewdriver_Feedback
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunScrewdriver_Feedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub progress: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub phase: rosidl_runtime_rs::String,

}



impl Default for RunScrewdriver_Feedback {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !gearbox_sim__action__RunScrewdriver_Feedback__init(&mut msg as *mut _) {
        panic!("Call to gearbox_sim__action__RunScrewdriver_Feedback__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for RunScrewdriver_Feedback {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__action__RunScrewdriver_Feedback__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__action__RunScrewdriver_Feedback__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__action__RunScrewdriver_Feedback__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for RunScrewdriver_Feedback {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for RunScrewdriver_Feedback where Self: Sized {
  const TYPE_NAME: &'static str = "gearbox_sim/action/RunScrewdriver_Feedback";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__gearbox_sim__action__RunScrewdriver_Feedback() }
  }
}


#[link(name = "gearbox_sim__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__gearbox_sim__action__RunScrewdriver_FeedbackMessage() -> *const std::ffi::c_void;
}

#[link(name = "gearbox_sim__rosidl_generator_c")]
extern "C" {
    fn gearbox_sim__action__RunScrewdriver_FeedbackMessage__init(msg: *mut RunScrewdriver_FeedbackMessage) -> bool;
    fn gearbox_sim__action__RunScrewdriver_FeedbackMessage__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<RunScrewdriver_FeedbackMessage>, size: usize) -> bool;
    fn gearbox_sim__action__RunScrewdriver_FeedbackMessage__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<RunScrewdriver_FeedbackMessage>);
    fn gearbox_sim__action__RunScrewdriver_FeedbackMessage__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<RunScrewdriver_FeedbackMessage>, out_seq: *mut rosidl_runtime_rs::Sequence<RunScrewdriver_FeedbackMessage>) -> bool;
}

// Corresponds to gearbox_sim__action__RunScrewdriver_FeedbackMessage
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunScrewdriver_FeedbackMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub feedback: super::super::action::rmw::RunScrewdriver_Feedback,

}



impl Default for RunScrewdriver_FeedbackMessage {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !gearbox_sim__action__RunScrewdriver_FeedbackMessage__init(&mut msg as *mut _) {
        panic!("Call to gearbox_sim__action__RunScrewdriver_FeedbackMessage__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for RunScrewdriver_FeedbackMessage {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__action__RunScrewdriver_FeedbackMessage__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__action__RunScrewdriver_FeedbackMessage__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__action__RunScrewdriver_FeedbackMessage__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for RunScrewdriver_FeedbackMessage {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for RunScrewdriver_FeedbackMessage where Self: Sized {
  const TYPE_NAME: &'static str = "gearbox_sim/action/RunScrewdriver_FeedbackMessage";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__gearbox_sim__action__RunScrewdriver_FeedbackMessage() }
  }
}




#[link(name = "gearbox_sim__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__gearbox_sim__action__RunScrewdriver_SendGoal_Request() -> *const std::ffi::c_void;
}

#[link(name = "gearbox_sim__rosidl_generator_c")]
extern "C" {
    fn gearbox_sim__action__RunScrewdriver_SendGoal_Request__init(msg: *mut RunScrewdriver_SendGoal_Request) -> bool;
    fn gearbox_sim__action__RunScrewdriver_SendGoal_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<RunScrewdriver_SendGoal_Request>, size: usize) -> bool;
    fn gearbox_sim__action__RunScrewdriver_SendGoal_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<RunScrewdriver_SendGoal_Request>);
    fn gearbox_sim__action__RunScrewdriver_SendGoal_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<RunScrewdriver_SendGoal_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<RunScrewdriver_SendGoal_Request>) -> bool;
}

// Corresponds to gearbox_sim__action__RunScrewdriver_SendGoal_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunScrewdriver_SendGoal_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: super::super::action::rmw::RunScrewdriver_Goal,

}



impl Default for RunScrewdriver_SendGoal_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !gearbox_sim__action__RunScrewdriver_SendGoal_Request__init(&mut msg as *mut _) {
        panic!("Call to gearbox_sim__action__RunScrewdriver_SendGoal_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for RunScrewdriver_SendGoal_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__action__RunScrewdriver_SendGoal_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__action__RunScrewdriver_SendGoal_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__action__RunScrewdriver_SendGoal_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for RunScrewdriver_SendGoal_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for RunScrewdriver_SendGoal_Request where Self: Sized {
  const TYPE_NAME: &'static str = "gearbox_sim/action/RunScrewdriver_SendGoal_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__gearbox_sim__action__RunScrewdriver_SendGoal_Request() }
  }
}


#[link(name = "gearbox_sim__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__gearbox_sim__action__RunScrewdriver_SendGoal_Response() -> *const std::ffi::c_void;
}

#[link(name = "gearbox_sim__rosidl_generator_c")]
extern "C" {
    fn gearbox_sim__action__RunScrewdriver_SendGoal_Response__init(msg: *mut RunScrewdriver_SendGoal_Response) -> bool;
    fn gearbox_sim__action__RunScrewdriver_SendGoal_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<RunScrewdriver_SendGoal_Response>, size: usize) -> bool;
    fn gearbox_sim__action__RunScrewdriver_SendGoal_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<RunScrewdriver_SendGoal_Response>);
    fn gearbox_sim__action__RunScrewdriver_SendGoal_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<RunScrewdriver_SendGoal_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<RunScrewdriver_SendGoal_Response>) -> bool;
}

// Corresponds to gearbox_sim__action__RunScrewdriver_SendGoal_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunScrewdriver_SendGoal_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::rmw::Time,

}



impl Default for RunScrewdriver_SendGoal_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !gearbox_sim__action__RunScrewdriver_SendGoal_Response__init(&mut msg as *mut _) {
        panic!("Call to gearbox_sim__action__RunScrewdriver_SendGoal_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for RunScrewdriver_SendGoal_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__action__RunScrewdriver_SendGoal_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__action__RunScrewdriver_SendGoal_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__action__RunScrewdriver_SendGoal_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for RunScrewdriver_SendGoal_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for RunScrewdriver_SendGoal_Response where Self: Sized {
  const TYPE_NAME: &'static str = "gearbox_sim/action/RunScrewdriver_SendGoal_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__gearbox_sim__action__RunScrewdriver_SendGoal_Response() }
  }
}


#[link(name = "gearbox_sim__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__gearbox_sim__action__RunScrewdriver_GetResult_Request() -> *const std::ffi::c_void;
}

#[link(name = "gearbox_sim__rosidl_generator_c")]
extern "C" {
    fn gearbox_sim__action__RunScrewdriver_GetResult_Request__init(msg: *mut RunScrewdriver_GetResult_Request) -> bool;
    fn gearbox_sim__action__RunScrewdriver_GetResult_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<RunScrewdriver_GetResult_Request>, size: usize) -> bool;
    fn gearbox_sim__action__RunScrewdriver_GetResult_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<RunScrewdriver_GetResult_Request>);
    fn gearbox_sim__action__RunScrewdriver_GetResult_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<RunScrewdriver_GetResult_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<RunScrewdriver_GetResult_Request>) -> bool;
}

// Corresponds to gearbox_sim__action__RunScrewdriver_GetResult_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunScrewdriver_GetResult_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,

}



impl Default for RunScrewdriver_GetResult_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !gearbox_sim__action__RunScrewdriver_GetResult_Request__init(&mut msg as *mut _) {
        panic!("Call to gearbox_sim__action__RunScrewdriver_GetResult_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for RunScrewdriver_GetResult_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__action__RunScrewdriver_GetResult_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__action__RunScrewdriver_GetResult_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__action__RunScrewdriver_GetResult_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for RunScrewdriver_GetResult_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for RunScrewdriver_GetResult_Request where Self: Sized {
  const TYPE_NAME: &'static str = "gearbox_sim/action/RunScrewdriver_GetResult_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__gearbox_sim__action__RunScrewdriver_GetResult_Request() }
  }
}


#[link(name = "gearbox_sim__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__gearbox_sim__action__RunScrewdriver_GetResult_Response() -> *const std::ffi::c_void;
}

#[link(name = "gearbox_sim__rosidl_generator_c")]
extern "C" {
    fn gearbox_sim__action__RunScrewdriver_GetResult_Response__init(msg: *mut RunScrewdriver_GetResult_Response) -> bool;
    fn gearbox_sim__action__RunScrewdriver_GetResult_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<RunScrewdriver_GetResult_Response>, size: usize) -> bool;
    fn gearbox_sim__action__RunScrewdriver_GetResult_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<RunScrewdriver_GetResult_Response>);
    fn gearbox_sim__action__RunScrewdriver_GetResult_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<RunScrewdriver_GetResult_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<RunScrewdriver_GetResult_Response>) -> bool;
}

// Corresponds to gearbox_sim__action__RunScrewdriver_GetResult_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunScrewdriver_GetResult_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result: super::super::action::rmw::RunScrewdriver_Result,

}



impl Default for RunScrewdriver_GetResult_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !gearbox_sim__action__RunScrewdriver_GetResult_Response__init(&mut msg as *mut _) {
        panic!("Call to gearbox_sim__action__RunScrewdriver_GetResult_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for RunScrewdriver_GetResult_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__action__RunScrewdriver_GetResult_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__action__RunScrewdriver_GetResult_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__action__RunScrewdriver_GetResult_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for RunScrewdriver_GetResult_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for RunScrewdriver_GetResult_Response where Self: Sized {
  const TYPE_NAME: &'static str = "gearbox_sim/action/RunScrewdriver_GetResult_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__gearbox_sim__action__RunScrewdriver_GetResult_Response() }
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


