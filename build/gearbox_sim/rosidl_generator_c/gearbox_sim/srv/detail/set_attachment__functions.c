// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from gearbox_sim:srv/SetAttachment.idl
// generated code does not contain a copyright notice
#include "gearbox_sim/srv/detail/set_attachment__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `robot_name`
// Member `tool_frame`
// Member `part_name`
// Member `part_frame`
// Member `part_link`
#include "rosidl_runtime_c/string_functions.h"

bool
gearbox_sim__srv__SetAttachment_Request__init(gearbox_sim__srv__SetAttachment_Request * msg)
{
  if (!msg) {
    return false;
  }
  // robot_name
  if (!rosidl_runtime_c__String__init(&msg->robot_name)) {
    gearbox_sim__srv__SetAttachment_Request__fini(msg);
    return false;
  }
  // tool_frame
  if (!rosidl_runtime_c__String__init(&msg->tool_frame)) {
    gearbox_sim__srv__SetAttachment_Request__fini(msg);
    return false;
  }
  // part_name
  if (!rosidl_runtime_c__String__init(&msg->part_name)) {
    gearbox_sim__srv__SetAttachment_Request__fini(msg);
    return false;
  }
  // part_frame
  if (!rosidl_runtime_c__String__init(&msg->part_frame)) {
    gearbox_sim__srv__SetAttachment_Request__fini(msg);
    return false;
  }
  // part_link
  if (!rosidl_runtime_c__String__init(&msg->part_link)) {
    gearbox_sim__srv__SetAttachment_Request__fini(msg);
    return false;
  }
  // attach
  return true;
}

void
gearbox_sim__srv__SetAttachment_Request__fini(gearbox_sim__srv__SetAttachment_Request * msg)
{
  if (!msg) {
    return;
  }
  // robot_name
  rosidl_runtime_c__String__fini(&msg->robot_name);
  // tool_frame
  rosidl_runtime_c__String__fini(&msg->tool_frame);
  // part_name
  rosidl_runtime_c__String__fini(&msg->part_name);
  // part_frame
  rosidl_runtime_c__String__fini(&msg->part_frame);
  // part_link
  rosidl_runtime_c__String__fini(&msg->part_link);
  // attach
}

bool
gearbox_sim__srv__SetAttachment_Request__are_equal(const gearbox_sim__srv__SetAttachment_Request * lhs, const gearbox_sim__srv__SetAttachment_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // robot_name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->robot_name), &(rhs->robot_name)))
  {
    return false;
  }
  // tool_frame
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->tool_frame), &(rhs->tool_frame)))
  {
    return false;
  }
  // part_name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->part_name), &(rhs->part_name)))
  {
    return false;
  }
  // part_frame
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->part_frame), &(rhs->part_frame)))
  {
    return false;
  }
  // part_link
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->part_link), &(rhs->part_link)))
  {
    return false;
  }
  // attach
  if (lhs->attach != rhs->attach) {
    return false;
  }
  return true;
}

bool
gearbox_sim__srv__SetAttachment_Request__copy(
  const gearbox_sim__srv__SetAttachment_Request * input,
  gearbox_sim__srv__SetAttachment_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // robot_name
  if (!rosidl_runtime_c__String__copy(
      &(input->robot_name), &(output->robot_name)))
  {
    return false;
  }
  // tool_frame
  if (!rosidl_runtime_c__String__copy(
      &(input->tool_frame), &(output->tool_frame)))
  {
    return false;
  }
  // part_name
  if (!rosidl_runtime_c__String__copy(
      &(input->part_name), &(output->part_name)))
  {
    return false;
  }
  // part_frame
  if (!rosidl_runtime_c__String__copy(
      &(input->part_frame), &(output->part_frame)))
  {
    return false;
  }
  // part_link
  if (!rosidl_runtime_c__String__copy(
      &(input->part_link), &(output->part_link)))
  {
    return false;
  }
  // attach
  output->attach = input->attach;
  return true;
}

gearbox_sim__srv__SetAttachment_Request *
gearbox_sim__srv__SetAttachment_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__srv__SetAttachment_Request * msg = (gearbox_sim__srv__SetAttachment_Request *)allocator.allocate(sizeof(gearbox_sim__srv__SetAttachment_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(gearbox_sim__srv__SetAttachment_Request));
  bool success = gearbox_sim__srv__SetAttachment_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
gearbox_sim__srv__SetAttachment_Request__destroy(gearbox_sim__srv__SetAttachment_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    gearbox_sim__srv__SetAttachment_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
gearbox_sim__srv__SetAttachment_Request__Sequence__init(gearbox_sim__srv__SetAttachment_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__srv__SetAttachment_Request * data = NULL;

  if (size) {
    data = (gearbox_sim__srv__SetAttachment_Request *)allocator.zero_allocate(size, sizeof(gearbox_sim__srv__SetAttachment_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = gearbox_sim__srv__SetAttachment_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        gearbox_sim__srv__SetAttachment_Request__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
gearbox_sim__srv__SetAttachment_Request__Sequence__fini(gearbox_sim__srv__SetAttachment_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      gearbox_sim__srv__SetAttachment_Request__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

gearbox_sim__srv__SetAttachment_Request__Sequence *
gearbox_sim__srv__SetAttachment_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__srv__SetAttachment_Request__Sequence * array = (gearbox_sim__srv__SetAttachment_Request__Sequence *)allocator.allocate(sizeof(gearbox_sim__srv__SetAttachment_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = gearbox_sim__srv__SetAttachment_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
gearbox_sim__srv__SetAttachment_Request__Sequence__destroy(gearbox_sim__srv__SetAttachment_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    gearbox_sim__srv__SetAttachment_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
gearbox_sim__srv__SetAttachment_Request__Sequence__are_equal(const gearbox_sim__srv__SetAttachment_Request__Sequence * lhs, const gearbox_sim__srv__SetAttachment_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!gearbox_sim__srv__SetAttachment_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
gearbox_sim__srv__SetAttachment_Request__Sequence__copy(
  const gearbox_sim__srv__SetAttachment_Request__Sequence * input,
  gearbox_sim__srv__SetAttachment_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(gearbox_sim__srv__SetAttachment_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    gearbox_sim__srv__SetAttachment_Request * data =
      (gearbox_sim__srv__SetAttachment_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!gearbox_sim__srv__SetAttachment_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          gearbox_sim__srv__SetAttachment_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!gearbox_sim__srv__SetAttachment_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
gearbox_sim__srv__SetAttachment_Response__init(gearbox_sim__srv__SetAttachment_Response * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    gearbox_sim__srv__SetAttachment_Response__fini(msg);
    return false;
  }
  return true;
}

void
gearbox_sim__srv__SetAttachment_Response__fini(gearbox_sim__srv__SetAttachment_Response * msg)
{
  if (!msg) {
    return;
  }
  // success
  // message
  rosidl_runtime_c__String__fini(&msg->message);
}

bool
gearbox_sim__srv__SetAttachment_Response__are_equal(const gearbox_sim__srv__SetAttachment_Response * lhs, const gearbox_sim__srv__SetAttachment_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  return true;
}

bool
gearbox_sim__srv__SetAttachment_Response__copy(
  const gearbox_sim__srv__SetAttachment_Response * input,
  gearbox_sim__srv__SetAttachment_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  return true;
}

gearbox_sim__srv__SetAttachment_Response *
gearbox_sim__srv__SetAttachment_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__srv__SetAttachment_Response * msg = (gearbox_sim__srv__SetAttachment_Response *)allocator.allocate(sizeof(gearbox_sim__srv__SetAttachment_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(gearbox_sim__srv__SetAttachment_Response));
  bool success = gearbox_sim__srv__SetAttachment_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
gearbox_sim__srv__SetAttachment_Response__destroy(gearbox_sim__srv__SetAttachment_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    gearbox_sim__srv__SetAttachment_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
gearbox_sim__srv__SetAttachment_Response__Sequence__init(gearbox_sim__srv__SetAttachment_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__srv__SetAttachment_Response * data = NULL;

  if (size) {
    data = (gearbox_sim__srv__SetAttachment_Response *)allocator.zero_allocate(size, sizeof(gearbox_sim__srv__SetAttachment_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = gearbox_sim__srv__SetAttachment_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        gearbox_sim__srv__SetAttachment_Response__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
gearbox_sim__srv__SetAttachment_Response__Sequence__fini(gearbox_sim__srv__SetAttachment_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      gearbox_sim__srv__SetAttachment_Response__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

gearbox_sim__srv__SetAttachment_Response__Sequence *
gearbox_sim__srv__SetAttachment_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__srv__SetAttachment_Response__Sequence * array = (gearbox_sim__srv__SetAttachment_Response__Sequence *)allocator.allocate(sizeof(gearbox_sim__srv__SetAttachment_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = gearbox_sim__srv__SetAttachment_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
gearbox_sim__srv__SetAttachment_Response__Sequence__destroy(gearbox_sim__srv__SetAttachment_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    gearbox_sim__srv__SetAttachment_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
gearbox_sim__srv__SetAttachment_Response__Sequence__are_equal(const gearbox_sim__srv__SetAttachment_Response__Sequence * lhs, const gearbox_sim__srv__SetAttachment_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!gearbox_sim__srv__SetAttachment_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
gearbox_sim__srv__SetAttachment_Response__Sequence__copy(
  const gearbox_sim__srv__SetAttachment_Response__Sequence * input,
  gearbox_sim__srv__SetAttachment_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(gearbox_sim__srv__SetAttachment_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    gearbox_sim__srv__SetAttachment_Response * data =
      (gearbox_sim__srv__SetAttachment_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!gearbox_sim__srv__SetAttachment_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          gearbox_sim__srv__SetAttachment_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!gearbox_sim__srv__SetAttachment_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `info`
#include "service_msgs/msg/detail/service_event_info__functions.h"
// Member `request`
// Member `response`
// already included above
// #include "gearbox_sim/srv/detail/set_attachment__functions.h"

bool
gearbox_sim__srv__SetAttachment_Event__init(gearbox_sim__srv__SetAttachment_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    gearbox_sim__srv__SetAttachment_Event__fini(msg);
    return false;
  }
  // request
  if (!gearbox_sim__srv__SetAttachment_Request__Sequence__init(&msg->request, 0)) {
    gearbox_sim__srv__SetAttachment_Event__fini(msg);
    return false;
  }
  // response
  if (!gearbox_sim__srv__SetAttachment_Response__Sequence__init(&msg->response, 0)) {
    gearbox_sim__srv__SetAttachment_Event__fini(msg);
    return false;
  }
  return true;
}

void
gearbox_sim__srv__SetAttachment_Event__fini(gearbox_sim__srv__SetAttachment_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  gearbox_sim__srv__SetAttachment_Request__Sequence__fini(&msg->request);
  // response
  gearbox_sim__srv__SetAttachment_Response__Sequence__fini(&msg->response);
}

bool
gearbox_sim__srv__SetAttachment_Event__are_equal(const gearbox_sim__srv__SetAttachment_Event * lhs, const gearbox_sim__srv__SetAttachment_Event * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__are_equal(
      &(lhs->info), &(rhs->info)))
  {
    return false;
  }
  // request
  if (!gearbox_sim__srv__SetAttachment_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!gearbox_sim__srv__SetAttachment_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
gearbox_sim__srv__SetAttachment_Event__copy(
  const gearbox_sim__srv__SetAttachment_Event * input,
  gearbox_sim__srv__SetAttachment_Event * output)
{
  if (!input || !output) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__copy(
      &(input->info), &(output->info)))
  {
    return false;
  }
  // request
  if (!gearbox_sim__srv__SetAttachment_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!gearbox_sim__srv__SetAttachment_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

gearbox_sim__srv__SetAttachment_Event *
gearbox_sim__srv__SetAttachment_Event__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__srv__SetAttachment_Event * msg = (gearbox_sim__srv__SetAttachment_Event *)allocator.allocate(sizeof(gearbox_sim__srv__SetAttachment_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(gearbox_sim__srv__SetAttachment_Event));
  bool success = gearbox_sim__srv__SetAttachment_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
gearbox_sim__srv__SetAttachment_Event__destroy(gearbox_sim__srv__SetAttachment_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    gearbox_sim__srv__SetAttachment_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
gearbox_sim__srv__SetAttachment_Event__Sequence__init(gearbox_sim__srv__SetAttachment_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__srv__SetAttachment_Event * data = NULL;

  if (size) {
    data = (gearbox_sim__srv__SetAttachment_Event *)allocator.zero_allocate(size, sizeof(gearbox_sim__srv__SetAttachment_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = gearbox_sim__srv__SetAttachment_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        gearbox_sim__srv__SetAttachment_Event__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
gearbox_sim__srv__SetAttachment_Event__Sequence__fini(gearbox_sim__srv__SetAttachment_Event__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      gearbox_sim__srv__SetAttachment_Event__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

gearbox_sim__srv__SetAttachment_Event__Sequence *
gearbox_sim__srv__SetAttachment_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__srv__SetAttachment_Event__Sequence * array = (gearbox_sim__srv__SetAttachment_Event__Sequence *)allocator.allocate(sizeof(gearbox_sim__srv__SetAttachment_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = gearbox_sim__srv__SetAttachment_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
gearbox_sim__srv__SetAttachment_Event__Sequence__destroy(gearbox_sim__srv__SetAttachment_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    gearbox_sim__srv__SetAttachment_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
gearbox_sim__srv__SetAttachment_Event__Sequence__are_equal(const gearbox_sim__srv__SetAttachment_Event__Sequence * lhs, const gearbox_sim__srv__SetAttachment_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!gearbox_sim__srv__SetAttachment_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
gearbox_sim__srv__SetAttachment_Event__Sequence__copy(
  const gearbox_sim__srv__SetAttachment_Event__Sequence * input,
  gearbox_sim__srv__SetAttachment_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(gearbox_sim__srv__SetAttachment_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    gearbox_sim__srv__SetAttachment_Event * data =
      (gearbox_sim__srv__SetAttachment_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!gearbox_sim__srv__SetAttachment_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          gearbox_sim__srv__SetAttachment_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!gearbox_sim__srv__SetAttachment_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
