#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



#[link(name = "gearbox_sim__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__gearbox_sim__srv__RunPressCycle_Request() -> *const std::ffi::c_void;
}

#[link(name = "gearbox_sim__rosidl_generator_c")]
extern "C" {
    fn gearbox_sim__srv__RunPressCycle_Request__init(msg: *mut RunPressCycle_Request) -> bool;
    fn gearbox_sim__srv__RunPressCycle_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<RunPressCycle_Request>, size: usize) -> bool;
    fn gearbox_sim__srv__RunPressCycle_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<RunPressCycle_Request>);
    fn gearbox_sim__srv__RunPressCycle_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<RunPressCycle_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<RunPressCycle_Request>) -> bool;
}

// Corresponds to gearbox_sim__srv__RunPressCycle_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunPressCycle_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub recipe_name: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub target_frame: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub approach_height_m: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stroke_m: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub dwell_sec: f64,

}



impl Default for RunPressCycle_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !gearbox_sim__srv__RunPressCycle_Request__init(&mut msg as *mut _) {
        panic!("Call to gearbox_sim__srv__RunPressCycle_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for RunPressCycle_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__srv__RunPressCycle_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__srv__RunPressCycle_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__srv__RunPressCycle_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for RunPressCycle_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for RunPressCycle_Request where Self: Sized {
  const TYPE_NAME: &'static str = "gearbox_sim/srv/RunPressCycle_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__gearbox_sim__srv__RunPressCycle_Request() }
  }
}


#[link(name = "gearbox_sim__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__gearbox_sim__srv__RunPressCycle_Response() -> *const std::ffi::c_void;
}

#[link(name = "gearbox_sim__rosidl_generator_c")]
extern "C" {
    fn gearbox_sim__srv__RunPressCycle_Response__init(msg: *mut RunPressCycle_Response) -> bool;
    fn gearbox_sim__srv__RunPressCycle_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<RunPressCycle_Response>, size: usize) -> bool;
    fn gearbox_sim__srv__RunPressCycle_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<RunPressCycle_Response>);
    fn gearbox_sim__srv__RunPressCycle_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<RunPressCycle_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<RunPressCycle_Response>) -> bool;
}

// Corresponds to gearbox_sim__srv__RunPressCycle_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunPressCycle_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}



impl Default for RunPressCycle_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !gearbox_sim__srv__RunPressCycle_Response__init(&mut msg as *mut _) {
        panic!("Call to gearbox_sim__srv__RunPressCycle_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for RunPressCycle_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__srv__RunPressCycle_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__srv__RunPressCycle_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__srv__RunPressCycle_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for RunPressCycle_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for RunPressCycle_Response where Self: Sized {
  const TYPE_NAME: &'static str = "gearbox_sim/srv/RunPressCycle_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__gearbox_sim__srv__RunPressCycle_Response() }
  }
}


#[link(name = "gearbox_sim__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__gearbox_sim__srv__SetAttachment_Request() -> *const std::ffi::c_void;
}

#[link(name = "gearbox_sim__rosidl_generator_c")]
extern "C" {
    fn gearbox_sim__srv__SetAttachment_Request__init(msg: *mut SetAttachment_Request) -> bool;
    fn gearbox_sim__srv__SetAttachment_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SetAttachment_Request>, size: usize) -> bool;
    fn gearbox_sim__srv__SetAttachment_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SetAttachment_Request>);
    fn gearbox_sim__srv__SetAttachment_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SetAttachment_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<SetAttachment_Request>) -> bool;
}

// Corresponds to gearbox_sim__srv__SetAttachment_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SetAttachment_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub robot_name: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub tool_frame: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub part_name: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub part_frame: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub part_link: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub attach: bool,

}



impl Default for SetAttachment_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !gearbox_sim__srv__SetAttachment_Request__init(&mut msg as *mut _) {
        panic!("Call to gearbox_sim__srv__SetAttachment_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SetAttachment_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__srv__SetAttachment_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__srv__SetAttachment_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__srv__SetAttachment_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SetAttachment_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SetAttachment_Request where Self: Sized {
  const TYPE_NAME: &'static str = "gearbox_sim/srv/SetAttachment_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__gearbox_sim__srv__SetAttachment_Request() }
  }
}


#[link(name = "gearbox_sim__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__gearbox_sim__srv__SetAttachment_Response() -> *const std::ffi::c_void;
}

#[link(name = "gearbox_sim__rosidl_generator_c")]
extern "C" {
    fn gearbox_sim__srv__SetAttachment_Response__init(msg: *mut SetAttachment_Response) -> bool;
    fn gearbox_sim__srv__SetAttachment_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SetAttachment_Response>, size: usize) -> bool;
    fn gearbox_sim__srv__SetAttachment_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SetAttachment_Response>);
    fn gearbox_sim__srv__SetAttachment_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SetAttachment_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<SetAttachment_Response>) -> bool;
}

// Corresponds to gearbox_sim__srv__SetAttachment_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SetAttachment_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}



impl Default for SetAttachment_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !gearbox_sim__srv__SetAttachment_Response__init(&mut msg as *mut _) {
        panic!("Call to gearbox_sim__srv__SetAttachment_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SetAttachment_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__srv__SetAttachment_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__srv__SetAttachment_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { gearbox_sim__srv__SetAttachment_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SetAttachment_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SetAttachment_Response where Self: Sized {
  const TYPE_NAME: &'static str = "gearbox_sim/srv/SetAttachment_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__gearbox_sim__srv__SetAttachment_Response() }
  }
}






#[link(name = "gearbox_sim__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__gearbox_sim__srv__RunPressCycle() -> *const std::ffi::c_void;
}

// Corresponds to gearbox_sim__srv__RunPressCycle
#[allow(missing_docs, non_camel_case_types)]
pub struct RunPressCycle;

impl rosidl_runtime_rs::Service for RunPressCycle {
    type Request = RunPressCycle_Request;
    type Response = RunPressCycle_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__gearbox_sim__srv__RunPressCycle() }
    }
}




#[link(name = "gearbox_sim__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__gearbox_sim__srv__SetAttachment() -> *const std::ffi::c_void;
}

// Corresponds to gearbox_sim__srv__SetAttachment
#[allow(missing_docs, non_camel_case_types)]
pub struct SetAttachment;

impl rosidl_runtime_rs::Service for SetAttachment {
    type Request = SetAttachment_Request;
    type Response = SetAttachment_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__gearbox_sim__srv__SetAttachment() }
    }
}


