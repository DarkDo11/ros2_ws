#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};




// Corresponds to gearbox_sim__srv__RunPressCycle_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunPressCycle_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub recipe_name: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub target_frame: std::string::String,


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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::RunPressCycle_Request::default())
  }
}

impl rosidl_runtime_rs::Message for RunPressCycle_Request {
  type RmwMsg = super::srv::rmw::RunPressCycle_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        recipe_name: msg.recipe_name.as_str().into(),
        target_frame: msg.target_frame.as_str().into(),
        approach_height_m: msg.approach_height_m,
        stroke_m: msg.stroke_m,
        dwell_sec: msg.dwell_sec,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        recipe_name: msg.recipe_name.as_str().into(),
        target_frame: msg.target_frame.as_str().into(),
      approach_height_m: msg.approach_height_m,
      stroke_m: msg.stroke_m,
      dwell_sec: msg.dwell_sec,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      recipe_name: msg.recipe_name.to_string(),
      target_frame: msg.target_frame.to_string(),
      approach_height_m: msg.approach_height_m,
      stroke_m: msg.stroke_m,
      dwell_sec: msg.dwell_sec,
    }
  }
}


// Corresponds to gearbox_sim__srv__RunPressCycle_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunPressCycle_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,

}



impl Default for RunPressCycle_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::RunPressCycle_Response::default())
  }
}

impl rosidl_runtime_rs::Message for RunPressCycle_Response {
  type RmwMsg = super::srv::rmw::RunPressCycle_Response;

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


// Corresponds to gearbox_sim__srv__SetAttachment_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SetAttachment_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub robot_name: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub tool_frame: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub part_name: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub part_frame: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub part_link: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub attach: bool,

}



impl Default for SetAttachment_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::SetAttachment_Request::default())
  }
}

impl rosidl_runtime_rs::Message for SetAttachment_Request {
  type RmwMsg = super::srv::rmw::SetAttachment_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        robot_name: msg.robot_name.as_str().into(),
        tool_frame: msg.tool_frame.as_str().into(),
        part_name: msg.part_name.as_str().into(),
        part_frame: msg.part_frame.as_str().into(),
        part_link: msg.part_link.as_str().into(),
        attach: msg.attach,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        robot_name: msg.robot_name.as_str().into(),
        tool_frame: msg.tool_frame.as_str().into(),
        part_name: msg.part_name.as_str().into(),
        part_frame: msg.part_frame.as_str().into(),
        part_link: msg.part_link.as_str().into(),
      attach: msg.attach,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      robot_name: msg.robot_name.to_string(),
      tool_frame: msg.tool_frame.to_string(),
      part_name: msg.part_name.to_string(),
      part_frame: msg.part_frame.to_string(),
      part_link: msg.part_link.to_string(),
      attach: msg.attach,
    }
  }
}


// Corresponds to gearbox_sim__srv__SetAttachment_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SetAttachment_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,

}



impl Default for SetAttachment_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::SetAttachment_Response::default())
  }
}

impl rosidl_runtime_rs::Message for SetAttachment_Response {
  type RmwMsg = super::srv::rmw::SetAttachment_Response;

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


