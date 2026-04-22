// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from gearbox_sim:action/RunScrewdriver.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "gearbox_sim/action/run_screwdriver.h"


#ifndef GEARBOX_SIM__ACTION__DETAIL__RUN_SCREWDRIVER__STRUCT_H_
#define GEARBOX_SIM__ACTION__DETAIL__RUN_SCREWDRIVER__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'screw_frame'
#include "rosidl_runtime_c/string.h"

/// Struct defined in action/RunScrewdriver in the package gearbox_sim.
typedef struct gearbox_sim__action__RunScrewdriver_Goal
{
  rosidl_runtime_c__String screw_frame;
  double approach_height_m;
  double descend_depth_m;
  double spin_rps;
  double duration_sec;
  bool feed_from_autofeeder;
} gearbox_sim__action__RunScrewdriver_Goal;

// Struct for a sequence of gearbox_sim__action__RunScrewdriver_Goal.
typedef struct gearbox_sim__action__RunScrewdriver_Goal__Sequence
{
  gearbox_sim__action__RunScrewdriver_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} gearbox_sim__action__RunScrewdriver_Goal__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in action/RunScrewdriver in the package gearbox_sim.
typedef struct gearbox_sim__action__RunScrewdriver_Result
{
  bool success;
  rosidl_runtime_c__String message;
} gearbox_sim__action__RunScrewdriver_Result;

// Struct for a sequence of gearbox_sim__action__RunScrewdriver_Result.
typedef struct gearbox_sim__action__RunScrewdriver_Result__Sequence
{
  gearbox_sim__action__RunScrewdriver_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} gearbox_sim__action__RunScrewdriver_Result__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'phase'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in action/RunScrewdriver in the package gearbox_sim.
typedef struct gearbox_sim__action__RunScrewdriver_Feedback
{
  double progress;
  rosidl_runtime_c__String phase;
} gearbox_sim__action__RunScrewdriver_Feedback;

// Struct for a sequence of gearbox_sim__action__RunScrewdriver_Feedback.
typedef struct gearbox_sim__action__RunScrewdriver_Feedback__Sequence
{
  gearbox_sim__action__RunScrewdriver_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} gearbox_sim__action__RunScrewdriver_Feedback__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "gearbox_sim/action/detail/run_screwdriver__struct.h"

/// Struct defined in action/RunScrewdriver in the package gearbox_sim.
typedef struct gearbox_sim__action__RunScrewdriver_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  gearbox_sim__action__RunScrewdriver_Goal goal;
} gearbox_sim__action__RunScrewdriver_SendGoal_Request;

// Struct for a sequence of gearbox_sim__action__RunScrewdriver_SendGoal_Request.
typedef struct gearbox_sim__action__RunScrewdriver_SendGoal_Request__Sequence
{
  gearbox_sim__action__RunScrewdriver_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} gearbox_sim__action__RunScrewdriver_SendGoal_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/RunScrewdriver in the package gearbox_sim.
typedef struct gearbox_sim__action__RunScrewdriver_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} gearbox_sim__action__RunScrewdriver_SendGoal_Response;

// Struct for a sequence of gearbox_sim__action__RunScrewdriver_SendGoal_Response.
typedef struct gearbox_sim__action__RunScrewdriver_SendGoal_Response__Sequence
{
  gearbox_sim__action__RunScrewdriver_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} gearbox_sim__action__RunScrewdriver_SendGoal_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  gearbox_sim__action__RunScrewdriver_SendGoal_Event__request__MAX_SIZE = 1
};
// response
enum
{
  gearbox_sim__action__RunScrewdriver_SendGoal_Event__response__MAX_SIZE = 1
};

/// Struct defined in action/RunScrewdriver in the package gearbox_sim.
typedef struct gearbox_sim__action__RunScrewdriver_SendGoal_Event
{
  service_msgs__msg__ServiceEventInfo info;
  gearbox_sim__action__RunScrewdriver_SendGoal_Request__Sequence request;
  gearbox_sim__action__RunScrewdriver_SendGoal_Response__Sequence response;
} gearbox_sim__action__RunScrewdriver_SendGoal_Event;

// Struct for a sequence of gearbox_sim__action__RunScrewdriver_SendGoal_Event.
typedef struct gearbox_sim__action__RunScrewdriver_SendGoal_Event__Sequence
{
  gearbox_sim__action__RunScrewdriver_SendGoal_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} gearbox_sim__action__RunScrewdriver_SendGoal_Event__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/RunScrewdriver in the package gearbox_sim.
typedef struct gearbox_sim__action__RunScrewdriver_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} gearbox_sim__action__RunScrewdriver_GetResult_Request;

// Struct for a sequence of gearbox_sim__action__RunScrewdriver_GetResult_Request.
typedef struct gearbox_sim__action__RunScrewdriver_GetResult_Request__Sequence
{
  gearbox_sim__action__RunScrewdriver_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} gearbox_sim__action__RunScrewdriver_GetResult_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "gearbox_sim/action/detail/run_screwdriver__struct.h"

/// Struct defined in action/RunScrewdriver in the package gearbox_sim.
typedef struct gearbox_sim__action__RunScrewdriver_GetResult_Response
{
  int8_t status;
  gearbox_sim__action__RunScrewdriver_Result result;
} gearbox_sim__action__RunScrewdriver_GetResult_Response;

// Struct for a sequence of gearbox_sim__action__RunScrewdriver_GetResult_Response.
typedef struct gearbox_sim__action__RunScrewdriver_GetResult_Response__Sequence
{
  gearbox_sim__action__RunScrewdriver_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} gearbox_sim__action__RunScrewdriver_GetResult_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
// already included above
// #include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  gearbox_sim__action__RunScrewdriver_GetResult_Event__request__MAX_SIZE = 1
};
// response
enum
{
  gearbox_sim__action__RunScrewdriver_GetResult_Event__response__MAX_SIZE = 1
};

/// Struct defined in action/RunScrewdriver in the package gearbox_sim.
typedef struct gearbox_sim__action__RunScrewdriver_GetResult_Event
{
  service_msgs__msg__ServiceEventInfo info;
  gearbox_sim__action__RunScrewdriver_GetResult_Request__Sequence request;
  gearbox_sim__action__RunScrewdriver_GetResult_Response__Sequence response;
} gearbox_sim__action__RunScrewdriver_GetResult_Event;

// Struct for a sequence of gearbox_sim__action__RunScrewdriver_GetResult_Event.
typedef struct gearbox_sim__action__RunScrewdriver_GetResult_Event__Sequence
{
  gearbox_sim__action__RunScrewdriver_GetResult_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} gearbox_sim__action__RunScrewdriver_GetResult_Event__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "gearbox_sim/action/detail/run_screwdriver__struct.h"

/// Struct defined in action/RunScrewdriver in the package gearbox_sim.
typedef struct gearbox_sim__action__RunScrewdriver_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  gearbox_sim__action__RunScrewdriver_Feedback feedback;
} gearbox_sim__action__RunScrewdriver_FeedbackMessage;

// Struct for a sequence of gearbox_sim__action__RunScrewdriver_FeedbackMessage.
typedef struct gearbox_sim__action__RunScrewdriver_FeedbackMessage__Sequence
{
  gearbox_sim__action__RunScrewdriver_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} gearbox_sim__action__RunScrewdriver_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // GEARBOX_SIM__ACTION__DETAIL__RUN_SCREWDRIVER__STRUCT_H_
