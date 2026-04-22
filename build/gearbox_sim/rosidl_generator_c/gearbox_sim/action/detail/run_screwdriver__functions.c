// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from gearbox_sim:action/RunScrewdriver.idl
// generated code does not contain a copyright notice
#include "gearbox_sim/action/detail/run_screwdriver__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `screw_frame`
#include "rosidl_runtime_c/string_functions.h"

bool
gearbox_sim__action__RunScrewdriver_Goal__init(gearbox_sim__action__RunScrewdriver_Goal * msg)
{
  if (!msg) {
    return false;
  }
  // screw_frame
  if (!rosidl_runtime_c__String__init(&msg->screw_frame)) {
    gearbox_sim__action__RunScrewdriver_Goal__fini(msg);
    return false;
  }
  // approach_height_m
  // descend_depth_m
  // spin_rps
  // duration_sec
  // feed_from_autofeeder
  return true;
}

void
gearbox_sim__action__RunScrewdriver_Goal__fini(gearbox_sim__action__RunScrewdriver_Goal * msg)
{
  if (!msg) {
    return;
  }
  // screw_frame
  rosidl_runtime_c__String__fini(&msg->screw_frame);
  // approach_height_m
  // descend_depth_m
  // spin_rps
  // duration_sec
  // feed_from_autofeeder
}

bool
gearbox_sim__action__RunScrewdriver_Goal__are_equal(const gearbox_sim__action__RunScrewdriver_Goal * lhs, const gearbox_sim__action__RunScrewdriver_Goal * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // screw_frame
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->screw_frame), &(rhs->screw_frame)))
  {
    return false;
  }
  // approach_height_m
  if (lhs->approach_height_m != rhs->approach_height_m) {
    return false;
  }
  // descend_depth_m
  if (lhs->descend_depth_m != rhs->descend_depth_m) {
    return false;
  }
  // spin_rps
  if (lhs->spin_rps != rhs->spin_rps) {
    return false;
  }
  // duration_sec
  if (lhs->duration_sec != rhs->duration_sec) {
    return false;
  }
  // feed_from_autofeeder
  if (lhs->feed_from_autofeeder != rhs->feed_from_autofeeder) {
    return false;
  }
  return true;
}

bool
gearbox_sim__action__RunScrewdriver_Goal__copy(
  const gearbox_sim__action__RunScrewdriver_Goal * input,
  gearbox_sim__action__RunScrewdriver_Goal * output)
{
  if (!input || !output) {
    return false;
  }
  // screw_frame
  if (!rosidl_runtime_c__String__copy(
      &(input->screw_frame), &(output->screw_frame)))
  {
    return false;
  }
  // approach_height_m
  output->approach_height_m = input->approach_height_m;
  // descend_depth_m
  output->descend_depth_m = input->descend_depth_m;
  // spin_rps
  output->spin_rps = input->spin_rps;
  // duration_sec
  output->duration_sec = input->duration_sec;
  // feed_from_autofeeder
  output->feed_from_autofeeder = input->feed_from_autofeeder;
  return true;
}

gearbox_sim__action__RunScrewdriver_Goal *
gearbox_sim__action__RunScrewdriver_Goal__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__action__RunScrewdriver_Goal * msg = (gearbox_sim__action__RunScrewdriver_Goal *)allocator.allocate(sizeof(gearbox_sim__action__RunScrewdriver_Goal), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(gearbox_sim__action__RunScrewdriver_Goal));
  bool success = gearbox_sim__action__RunScrewdriver_Goal__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
gearbox_sim__action__RunScrewdriver_Goal__destroy(gearbox_sim__action__RunScrewdriver_Goal * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    gearbox_sim__action__RunScrewdriver_Goal__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
gearbox_sim__action__RunScrewdriver_Goal__Sequence__init(gearbox_sim__action__RunScrewdriver_Goal__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__action__RunScrewdriver_Goal * data = NULL;

  if (size) {
    data = (gearbox_sim__action__RunScrewdriver_Goal *)allocator.zero_allocate(size, sizeof(gearbox_sim__action__RunScrewdriver_Goal), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = gearbox_sim__action__RunScrewdriver_Goal__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        gearbox_sim__action__RunScrewdriver_Goal__fini(&data[i - 1]);
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
gearbox_sim__action__RunScrewdriver_Goal__Sequence__fini(gearbox_sim__action__RunScrewdriver_Goal__Sequence * array)
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
      gearbox_sim__action__RunScrewdriver_Goal__fini(&array->data[i]);
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

gearbox_sim__action__RunScrewdriver_Goal__Sequence *
gearbox_sim__action__RunScrewdriver_Goal__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__action__RunScrewdriver_Goal__Sequence * array = (gearbox_sim__action__RunScrewdriver_Goal__Sequence *)allocator.allocate(sizeof(gearbox_sim__action__RunScrewdriver_Goal__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = gearbox_sim__action__RunScrewdriver_Goal__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
gearbox_sim__action__RunScrewdriver_Goal__Sequence__destroy(gearbox_sim__action__RunScrewdriver_Goal__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    gearbox_sim__action__RunScrewdriver_Goal__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
gearbox_sim__action__RunScrewdriver_Goal__Sequence__are_equal(const gearbox_sim__action__RunScrewdriver_Goal__Sequence * lhs, const gearbox_sim__action__RunScrewdriver_Goal__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!gearbox_sim__action__RunScrewdriver_Goal__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
gearbox_sim__action__RunScrewdriver_Goal__Sequence__copy(
  const gearbox_sim__action__RunScrewdriver_Goal__Sequence * input,
  gearbox_sim__action__RunScrewdriver_Goal__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(gearbox_sim__action__RunScrewdriver_Goal);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    gearbox_sim__action__RunScrewdriver_Goal * data =
      (gearbox_sim__action__RunScrewdriver_Goal *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!gearbox_sim__action__RunScrewdriver_Goal__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          gearbox_sim__action__RunScrewdriver_Goal__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!gearbox_sim__action__RunScrewdriver_Goal__copy(
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
gearbox_sim__action__RunScrewdriver_Result__init(gearbox_sim__action__RunScrewdriver_Result * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    gearbox_sim__action__RunScrewdriver_Result__fini(msg);
    return false;
  }
  return true;
}

void
gearbox_sim__action__RunScrewdriver_Result__fini(gearbox_sim__action__RunScrewdriver_Result * msg)
{
  if (!msg) {
    return;
  }
  // success
  // message
  rosidl_runtime_c__String__fini(&msg->message);
}

bool
gearbox_sim__action__RunScrewdriver_Result__are_equal(const gearbox_sim__action__RunScrewdriver_Result * lhs, const gearbox_sim__action__RunScrewdriver_Result * rhs)
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
gearbox_sim__action__RunScrewdriver_Result__copy(
  const gearbox_sim__action__RunScrewdriver_Result * input,
  gearbox_sim__action__RunScrewdriver_Result * output)
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

gearbox_sim__action__RunScrewdriver_Result *
gearbox_sim__action__RunScrewdriver_Result__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__action__RunScrewdriver_Result * msg = (gearbox_sim__action__RunScrewdriver_Result *)allocator.allocate(sizeof(gearbox_sim__action__RunScrewdriver_Result), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(gearbox_sim__action__RunScrewdriver_Result));
  bool success = gearbox_sim__action__RunScrewdriver_Result__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
gearbox_sim__action__RunScrewdriver_Result__destroy(gearbox_sim__action__RunScrewdriver_Result * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    gearbox_sim__action__RunScrewdriver_Result__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
gearbox_sim__action__RunScrewdriver_Result__Sequence__init(gearbox_sim__action__RunScrewdriver_Result__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__action__RunScrewdriver_Result * data = NULL;

  if (size) {
    data = (gearbox_sim__action__RunScrewdriver_Result *)allocator.zero_allocate(size, sizeof(gearbox_sim__action__RunScrewdriver_Result), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = gearbox_sim__action__RunScrewdriver_Result__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        gearbox_sim__action__RunScrewdriver_Result__fini(&data[i - 1]);
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
gearbox_sim__action__RunScrewdriver_Result__Sequence__fini(gearbox_sim__action__RunScrewdriver_Result__Sequence * array)
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
      gearbox_sim__action__RunScrewdriver_Result__fini(&array->data[i]);
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

gearbox_sim__action__RunScrewdriver_Result__Sequence *
gearbox_sim__action__RunScrewdriver_Result__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__action__RunScrewdriver_Result__Sequence * array = (gearbox_sim__action__RunScrewdriver_Result__Sequence *)allocator.allocate(sizeof(gearbox_sim__action__RunScrewdriver_Result__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = gearbox_sim__action__RunScrewdriver_Result__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
gearbox_sim__action__RunScrewdriver_Result__Sequence__destroy(gearbox_sim__action__RunScrewdriver_Result__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    gearbox_sim__action__RunScrewdriver_Result__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
gearbox_sim__action__RunScrewdriver_Result__Sequence__are_equal(const gearbox_sim__action__RunScrewdriver_Result__Sequence * lhs, const gearbox_sim__action__RunScrewdriver_Result__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!gearbox_sim__action__RunScrewdriver_Result__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
gearbox_sim__action__RunScrewdriver_Result__Sequence__copy(
  const gearbox_sim__action__RunScrewdriver_Result__Sequence * input,
  gearbox_sim__action__RunScrewdriver_Result__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(gearbox_sim__action__RunScrewdriver_Result);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    gearbox_sim__action__RunScrewdriver_Result * data =
      (gearbox_sim__action__RunScrewdriver_Result *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!gearbox_sim__action__RunScrewdriver_Result__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          gearbox_sim__action__RunScrewdriver_Result__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!gearbox_sim__action__RunScrewdriver_Result__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `phase`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
gearbox_sim__action__RunScrewdriver_Feedback__init(gearbox_sim__action__RunScrewdriver_Feedback * msg)
{
  if (!msg) {
    return false;
  }
  // progress
  // phase
  if (!rosidl_runtime_c__String__init(&msg->phase)) {
    gearbox_sim__action__RunScrewdriver_Feedback__fini(msg);
    return false;
  }
  return true;
}

void
gearbox_sim__action__RunScrewdriver_Feedback__fini(gearbox_sim__action__RunScrewdriver_Feedback * msg)
{
  if (!msg) {
    return;
  }
  // progress
  // phase
  rosidl_runtime_c__String__fini(&msg->phase);
}

bool
gearbox_sim__action__RunScrewdriver_Feedback__are_equal(const gearbox_sim__action__RunScrewdriver_Feedback * lhs, const gearbox_sim__action__RunScrewdriver_Feedback * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // progress
  if (lhs->progress != rhs->progress) {
    return false;
  }
  // phase
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->phase), &(rhs->phase)))
  {
    return false;
  }
  return true;
}

bool
gearbox_sim__action__RunScrewdriver_Feedback__copy(
  const gearbox_sim__action__RunScrewdriver_Feedback * input,
  gearbox_sim__action__RunScrewdriver_Feedback * output)
{
  if (!input || !output) {
    return false;
  }
  // progress
  output->progress = input->progress;
  // phase
  if (!rosidl_runtime_c__String__copy(
      &(input->phase), &(output->phase)))
  {
    return false;
  }
  return true;
}

gearbox_sim__action__RunScrewdriver_Feedback *
gearbox_sim__action__RunScrewdriver_Feedback__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__action__RunScrewdriver_Feedback * msg = (gearbox_sim__action__RunScrewdriver_Feedback *)allocator.allocate(sizeof(gearbox_sim__action__RunScrewdriver_Feedback), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(gearbox_sim__action__RunScrewdriver_Feedback));
  bool success = gearbox_sim__action__RunScrewdriver_Feedback__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
gearbox_sim__action__RunScrewdriver_Feedback__destroy(gearbox_sim__action__RunScrewdriver_Feedback * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    gearbox_sim__action__RunScrewdriver_Feedback__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
gearbox_sim__action__RunScrewdriver_Feedback__Sequence__init(gearbox_sim__action__RunScrewdriver_Feedback__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__action__RunScrewdriver_Feedback * data = NULL;

  if (size) {
    data = (gearbox_sim__action__RunScrewdriver_Feedback *)allocator.zero_allocate(size, sizeof(gearbox_sim__action__RunScrewdriver_Feedback), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = gearbox_sim__action__RunScrewdriver_Feedback__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        gearbox_sim__action__RunScrewdriver_Feedback__fini(&data[i - 1]);
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
gearbox_sim__action__RunScrewdriver_Feedback__Sequence__fini(gearbox_sim__action__RunScrewdriver_Feedback__Sequence * array)
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
      gearbox_sim__action__RunScrewdriver_Feedback__fini(&array->data[i]);
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

gearbox_sim__action__RunScrewdriver_Feedback__Sequence *
gearbox_sim__action__RunScrewdriver_Feedback__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__action__RunScrewdriver_Feedback__Sequence * array = (gearbox_sim__action__RunScrewdriver_Feedback__Sequence *)allocator.allocate(sizeof(gearbox_sim__action__RunScrewdriver_Feedback__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = gearbox_sim__action__RunScrewdriver_Feedback__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
gearbox_sim__action__RunScrewdriver_Feedback__Sequence__destroy(gearbox_sim__action__RunScrewdriver_Feedback__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    gearbox_sim__action__RunScrewdriver_Feedback__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
gearbox_sim__action__RunScrewdriver_Feedback__Sequence__are_equal(const gearbox_sim__action__RunScrewdriver_Feedback__Sequence * lhs, const gearbox_sim__action__RunScrewdriver_Feedback__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!gearbox_sim__action__RunScrewdriver_Feedback__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
gearbox_sim__action__RunScrewdriver_Feedback__Sequence__copy(
  const gearbox_sim__action__RunScrewdriver_Feedback__Sequence * input,
  gearbox_sim__action__RunScrewdriver_Feedback__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(gearbox_sim__action__RunScrewdriver_Feedback);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    gearbox_sim__action__RunScrewdriver_Feedback * data =
      (gearbox_sim__action__RunScrewdriver_Feedback *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!gearbox_sim__action__RunScrewdriver_Feedback__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          gearbox_sim__action__RunScrewdriver_Feedback__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!gearbox_sim__action__RunScrewdriver_Feedback__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
#include "unique_identifier_msgs/msg/detail/uuid__functions.h"
// Member `goal`
// already included above
// #include "gearbox_sim/action/detail/run_screwdriver__functions.h"

bool
gearbox_sim__action__RunScrewdriver_SendGoal_Request__init(gearbox_sim__action__RunScrewdriver_SendGoal_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    gearbox_sim__action__RunScrewdriver_SendGoal_Request__fini(msg);
    return false;
  }
  // goal
  if (!gearbox_sim__action__RunScrewdriver_Goal__init(&msg->goal)) {
    gearbox_sim__action__RunScrewdriver_SendGoal_Request__fini(msg);
    return false;
  }
  return true;
}

void
gearbox_sim__action__RunScrewdriver_SendGoal_Request__fini(gearbox_sim__action__RunScrewdriver_SendGoal_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // goal
  gearbox_sim__action__RunScrewdriver_Goal__fini(&msg->goal);
}

bool
gearbox_sim__action__RunScrewdriver_SendGoal_Request__are_equal(const gearbox_sim__action__RunScrewdriver_SendGoal_Request * lhs, const gearbox_sim__action__RunScrewdriver_SendGoal_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  // goal
  if (!gearbox_sim__action__RunScrewdriver_Goal__are_equal(
      &(lhs->goal), &(rhs->goal)))
  {
    return false;
  }
  return true;
}

bool
gearbox_sim__action__RunScrewdriver_SendGoal_Request__copy(
  const gearbox_sim__action__RunScrewdriver_SendGoal_Request * input,
  gearbox_sim__action__RunScrewdriver_SendGoal_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  // goal
  if (!gearbox_sim__action__RunScrewdriver_Goal__copy(
      &(input->goal), &(output->goal)))
  {
    return false;
  }
  return true;
}

gearbox_sim__action__RunScrewdriver_SendGoal_Request *
gearbox_sim__action__RunScrewdriver_SendGoal_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__action__RunScrewdriver_SendGoal_Request * msg = (gearbox_sim__action__RunScrewdriver_SendGoal_Request *)allocator.allocate(sizeof(gearbox_sim__action__RunScrewdriver_SendGoal_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(gearbox_sim__action__RunScrewdriver_SendGoal_Request));
  bool success = gearbox_sim__action__RunScrewdriver_SendGoal_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
gearbox_sim__action__RunScrewdriver_SendGoal_Request__destroy(gearbox_sim__action__RunScrewdriver_SendGoal_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    gearbox_sim__action__RunScrewdriver_SendGoal_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
gearbox_sim__action__RunScrewdriver_SendGoal_Request__Sequence__init(gearbox_sim__action__RunScrewdriver_SendGoal_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__action__RunScrewdriver_SendGoal_Request * data = NULL;

  if (size) {
    data = (gearbox_sim__action__RunScrewdriver_SendGoal_Request *)allocator.zero_allocate(size, sizeof(gearbox_sim__action__RunScrewdriver_SendGoal_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = gearbox_sim__action__RunScrewdriver_SendGoal_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        gearbox_sim__action__RunScrewdriver_SendGoal_Request__fini(&data[i - 1]);
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
gearbox_sim__action__RunScrewdriver_SendGoal_Request__Sequence__fini(gearbox_sim__action__RunScrewdriver_SendGoal_Request__Sequence * array)
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
      gearbox_sim__action__RunScrewdriver_SendGoal_Request__fini(&array->data[i]);
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

gearbox_sim__action__RunScrewdriver_SendGoal_Request__Sequence *
gearbox_sim__action__RunScrewdriver_SendGoal_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__action__RunScrewdriver_SendGoal_Request__Sequence * array = (gearbox_sim__action__RunScrewdriver_SendGoal_Request__Sequence *)allocator.allocate(sizeof(gearbox_sim__action__RunScrewdriver_SendGoal_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = gearbox_sim__action__RunScrewdriver_SendGoal_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
gearbox_sim__action__RunScrewdriver_SendGoal_Request__Sequence__destroy(gearbox_sim__action__RunScrewdriver_SendGoal_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    gearbox_sim__action__RunScrewdriver_SendGoal_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
gearbox_sim__action__RunScrewdriver_SendGoal_Request__Sequence__are_equal(const gearbox_sim__action__RunScrewdriver_SendGoal_Request__Sequence * lhs, const gearbox_sim__action__RunScrewdriver_SendGoal_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!gearbox_sim__action__RunScrewdriver_SendGoal_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
gearbox_sim__action__RunScrewdriver_SendGoal_Request__Sequence__copy(
  const gearbox_sim__action__RunScrewdriver_SendGoal_Request__Sequence * input,
  gearbox_sim__action__RunScrewdriver_SendGoal_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(gearbox_sim__action__RunScrewdriver_SendGoal_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    gearbox_sim__action__RunScrewdriver_SendGoal_Request * data =
      (gearbox_sim__action__RunScrewdriver_SendGoal_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!gearbox_sim__action__RunScrewdriver_SendGoal_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          gearbox_sim__action__RunScrewdriver_SendGoal_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!gearbox_sim__action__RunScrewdriver_SendGoal_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"

bool
gearbox_sim__action__RunScrewdriver_SendGoal_Response__init(gearbox_sim__action__RunScrewdriver_SendGoal_Response * msg)
{
  if (!msg) {
    return false;
  }
  // accepted
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    gearbox_sim__action__RunScrewdriver_SendGoal_Response__fini(msg);
    return false;
  }
  return true;
}

void
gearbox_sim__action__RunScrewdriver_SendGoal_Response__fini(gearbox_sim__action__RunScrewdriver_SendGoal_Response * msg)
{
  if (!msg) {
    return;
  }
  // accepted
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
}

bool
gearbox_sim__action__RunScrewdriver_SendGoal_Response__are_equal(const gearbox_sim__action__RunScrewdriver_SendGoal_Response * lhs, const gearbox_sim__action__RunScrewdriver_SendGoal_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // accepted
  if (lhs->accepted != rhs->accepted) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->stamp), &(rhs->stamp)))
  {
    return false;
  }
  return true;
}

bool
gearbox_sim__action__RunScrewdriver_SendGoal_Response__copy(
  const gearbox_sim__action__RunScrewdriver_SendGoal_Response * input,
  gearbox_sim__action__RunScrewdriver_SendGoal_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // accepted
  output->accepted = input->accepted;
  // stamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->stamp), &(output->stamp)))
  {
    return false;
  }
  return true;
}

gearbox_sim__action__RunScrewdriver_SendGoal_Response *
gearbox_sim__action__RunScrewdriver_SendGoal_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__action__RunScrewdriver_SendGoal_Response * msg = (gearbox_sim__action__RunScrewdriver_SendGoal_Response *)allocator.allocate(sizeof(gearbox_sim__action__RunScrewdriver_SendGoal_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(gearbox_sim__action__RunScrewdriver_SendGoal_Response));
  bool success = gearbox_sim__action__RunScrewdriver_SendGoal_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
gearbox_sim__action__RunScrewdriver_SendGoal_Response__destroy(gearbox_sim__action__RunScrewdriver_SendGoal_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    gearbox_sim__action__RunScrewdriver_SendGoal_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
gearbox_sim__action__RunScrewdriver_SendGoal_Response__Sequence__init(gearbox_sim__action__RunScrewdriver_SendGoal_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__action__RunScrewdriver_SendGoal_Response * data = NULL;

  if (size) {
    data = (gearbox_sim__action__RunScrewdriver_SendGoal_Response *)allocator.zero_allocate(size, sizeof(gearbox_sim__action__RunScrewdriver_SendGoal_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = gearbox_sim__action__RunScrewdriver_SendGoal_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        gearbox_sim__action__RunScrewdriver_SendGoal_Response__fini(&data[i - 1]);
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
gearbox_sim__action__RunScrewdriver_SendGoal_Response__Sequence__fini(gearbox_sim__action__RunScrewdriver_SendGoal_Response__Sequence * array)
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
      gearbox_sim__action__RunScrewdriver_SendGoal_Response__fini(&array->data[i]);
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

gearbox_sim__action__RunScrewdriver_SendGoal_Response__Sequence *
gearbox_sim__action__RunScrewdriver_SendGoal_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__action__RunScrewdriver_SendGoal_Response__Sequence * array = (gearbox_sim__action__RunScrewdriver_SendGoal_Response__Sequence *)allocator.allocate(sizeof(gearbox_sim__action__RunScrewdriver_SendGoal_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = gearbox_sim__action__RunScrewdriver_SendGoal_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
gearbox_sim__action__RunScrewdriver_SendGoal_Response__Sequence__destroy(gearbox_sim__action__RunScrewdriver_SendGoal_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    gearbox_sim__action__RunScrewdriver_SendGoal_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
gearbox_sim__action__RunScrewdriver_SendGoal_Response__Sequence__are_equal(const gearbox_sim__action__RunScrewdriver_SendGoal_Response__Sequence * lhs, const gearbox_sim__action__RunScrewdriver_SendGoal_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!gearbox_sim__action__RunScrewdriver_SendGoal_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
gearbox_sim__action__RunScrewdriver_SendGoal_Response__Sequence__copy(
  const gearbox_sim__action__RunScrewdriver_SendGoal_Response__Sequence * input,
  gearbox_sim__action__RunScrewdriver_SendGoal_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(gearbox_sim__action__RunScrewdriver_SendGoal_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    gearbox_sim__action__RunScrewdriver_SendGoal_Response * data =
      (gearbox_sim__action__RunScrewdriver_SendGoal_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!gearbox_sim__action__RunScrewdriver_SendGoal_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          gearbox_sim__action__RunScrewdriver_SendGoal_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!gearbox_sim__action__RunScrewdriver_SendGoal_Response__copy(
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
// #include "gearbox_sim/action/detail/run_screwdriver__functions.h"

bool
gearbox_sim__action__RunScrewdriver_SendGoal_Event__init(gearbox_sim__action__RunScrewdriver_SendGoal_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    gearbox_sim__action__RunScrewdriver_SendGoal_Event__fini(msg);
    return false;
  }
  // request
  if (!gearbox_sim__action__RunScrewdriver_SendGoal_Request__Sequence__init(&msg->request, 0)) {
    gearbox_sim__action__RunScrewdriver_SendGoal_Event__fini(msg);
    return false;
  }
  // response
  if (!gearbox_sim__action__RunScrewdriver_SendGoal_Response__Sequence__init(&msg->response, 0)) {
    gearbox_sim__action__RunScrewdriver_SendGoal_Event__fini(msg);
    return false;
  }
  return true;
}

void
gearbox_sim__action__RunScrewdriver_SendGoal_Event__fini(gearbox_sim__action__RunScrewdriver_SendGoal_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  gearbox_sim__action__RunScrewdriver_SendGoal_Request__Sequence__fini(&msg->request);
  // response
  gearbox_sim__action__RunScrewdriver_SendGoal_Response__Sequence__fini(&msg->response);
}

bool
gearbox_sim__action__RunScrewdriver_SendGoal_Event__are_equal(const gearbox_sim__action__RunScrewdriver_SendGoal_Event * lhs, const gearbox_sim__action__RunScrewdriver_SendGoal_Event * rhs)
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
  if (!gearbox_sim__action__RunScrewdriver_SendGoal_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!gearbox_sim__action__RunScrewdriver_SendGoal_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
gearbox_sim__action__RunScrewdriver_SendGoal_Event__copy(
  const gearbox_sim__action__RunScrewdriver_SendGoal_Event * input,
  gearbox_sim__action__RunScrewdriver_SendGoal_Event * output)
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
  if (!gearbox_sim__action__RunScrewdriver_SendGoal_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!gearbox_sim__action__RunScrewdriver_SendGoal_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

gearbox_sim__action__RunScrewdriver_SendGoal_Event *
gearbox_sim__action__RunScrewdriver_SendGoal_Event__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__action__RunScrewdriver_SendGoal_Event * msg = (gearbox_sim__action__RunScrewdriver_SendGoal_Event *)allocator.allocate(sizeof(gearbox_sim__action__RunScrewdriver_SendGoal_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(gearbox_sim__action__RunScrewdriver_SendGoal_Event));
  bool success = gearbox_sim__action__RunScrewdriver_SendGoal_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
gearbox_sim__action__RunScrewdriver_SendGoal_Event__destroy(gearbox_sim__action__RunScrewdriver_SendGoal_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    gearbox_sim__action__RunScrewdriver_SendGoal_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
gearbox_sim__action__RunScrewdriver_SendGoal_Event__Sequence__init(gearbox_sim__action__RunScrewdriver_SendGoal_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__action__RunScrewdriver_SendGoal_Event * data = NULL;

  if (size) {
    data = (gearbox_sim__action__RunScrewdriver_SendGoal_Event *)allocator.zero_allocate(size, sizeof(gearbox_sim__action__RunScrewdriver_SendGoal_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = gearbox_sim__action__RunScrewdriver_SendGoal_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        gearbox_sim__action__RunScrewdriver_SendGoal_Event__fini(&data[i - 1]);
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
gearbox_sim__action__RunScrewdriver_SendGoal_Event__Sequence__fini(gearbox_sim__action__RunScrewdriver_SendGoal_Event__Sequence * array)
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
      gearbox_sim__action__RunScrewdriver_SendGoal_Event__fini(&array->data[i]);
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

gearbox_sim__action__RunScrewdriver_SendGoal_Event__Sequence *
gearbox_sim__action__RunScrewdriver_SendGoal_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__action__RunScrewdriver_SendGoal_Event__Sequence * array = (gearbox_sim__action__RunScrewdriver_SendGoal_Event__Sequence *)allocator.allocate(sizeof(gearbox_sim__action__RunScrewdriver_SendGoal_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = gearbox_sim__action__RunScrewdriver_SendGoal_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
gearbox_sim__action__RunScrewdriver_SendGoal_Event__Sequence__destroy(gearbox_sim__action__RunScrewdriver_SendGoal_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    gearbox_sim__action__RunScrewdriver_SendGoal_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
gearbox_sim__action__RunScrewdriver_SendGoal_Event__Sequence__are_equal(const gearbox_sim__action__RunScrewdriver_SendGoal_Event__Sequence * lhs, const gearbox_sim__action__RunScrewdriver_SendGoal_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!gearbox_sim__action__RunScrewdriver_SendGoal_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
gearbox_sim__action__RunScrewdriver_SendGoal_Event__Sequence__copy(
  const gearbox_sim__action__RunScrewdriver_SendGoal_Event__Sequence * input,
  gearbox_sim__action__RunScrewdriver_SendGoal_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(gearbox_sim__action__RunScrewdriver_SendGoal_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    gearbox_sim__action__RunScrewdriver_SendGoal_Event * data =
      (gearbox_sim__action__RunScrewdriver_SendGoal_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!gearbox_sim__action__RunScrewdriver_SendGoal_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          gearbox_sim__action__RunScrewdriver_SendGoal_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!gearbox_sim__action__RunScrewdriver_SendGoal_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__functions.h"

bool
gearbox_sim__action__RunScrewdriver_GetResult_Request__init(gearbox_sim__action__RunScrewdriver_GetResult_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    gearbox_sim__action__RunScrewdriver_GetResult_Request__fini(msg);
    return false;
  }
  return true;
}

void
gearbox_sim__action__RunScrewdriver_GetResult_Request__fini(gearbox_sim__action__RunScrewdriver_GetResult_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
}

bool
gearbox_sim__action__RunScrewdriver_GetResult_Request__are_equal(const gearbox_sim__action__RunScrewdriver_GetResult_Request * lhs, const gearbox_sim__action__RunScrewdriver_GetResult_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  return true;
}

bool
gearbox_sim__action__RunScrewdriver_GetResult_Request__copy(
  const gearbox_sim__action__RunScrewdriver_GetResult_Request * input,
  gearbox_sim__action__RunScrewdriver_GetResult_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  return true;
}

gearbox_sim__action__RunScrewdriver_GetResult_Request *
gearbox_sim__action__RunScrewdriver_GetResult_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__action__RunScrewdriver_GetResult_Request * msg = (gearbox_sim__action__RunScrewdriver_GetResult_Request *)allocator.allocate(sizeof(gearbox_sim__action__RunScrewdriver_GetResult_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(gearbox_sim__action__RunScrewdriver_GetResult_Request));
  bool success = gearbox_sim__action__RunScrewdriver_GetResult_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
gearbox_sim__action__RunScrewdriver_GetResult_Request__destroy(gearbox_sim__action__RunScrewdriver_GetResult_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    gearbox_sim__action__RunScrewdriver_GetResult_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
gearbox_sim__action__RunScrewdriver_GetResult_Request__Sequence__init(gearbox_sim__action__RunScrewdriver_GetResult_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__action__RunScrewdriver_GetResult_Request * data = NULL;

  if (size) {
    data = (gearbox_sim__action__RunScrewdriver_GetResult_Request *)allocator.zero_allocate(size, sizeof(gearbox_sim__action__RunScrewdriver_GetResult_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = gearbox_sim__action__RunScrewdriver_GetResult_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        gearbox_sim__action__RunScrewdriver_GetResult_Request__fini(&data[i - 1]);
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
gearbox_sim__action__RunScrewdriver_GetResult_Request__Sequence__fini(gearbox_sim__action__RunScrewdriver_GetResult_Request__Sequence * array)
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
      gearbox_sim__action__RunScrewdriver_GetResult_Request__fini(&array->data[i]);
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

gearbox_sim__action__RunScrewdriver_GetResult_Request__Sequence *
gearbox_sim__action__RunScrewdriver_GetResult_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__action__RunScrewdriver_GetResult_Request__Sequence * array = (gearbox_sim__action__RunScrewdriver_GetResult_Request__Sequence *)allocator.allocate(sizeof(gearbox_sim__action__RunScrewdriver_GetResult_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = gearbox_sim__action__RunScrewdriver_GetResult_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
gearbox_sim__action__RunScrewdriver_GetResult_Request__Sequence__destroy(gearbox_sim__action__RunScrewdriver_GetResult_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    gearbox_sim__action__RunScrewdriver_GetResult_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
gearbox_sim__action__RunScrewdriver_GetResult_Request__Sequence__are_equal(const gearbox_sim__action__RunScrewdriver_GetResult_Request__Sequence * lhs, const gearbox_sim__action__RunScrewdriver_GetResult_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!gearbox_sim__action__RunScrewdriver_GetResult_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
gearbox_sim__action__RunScrewdriver_GetResult_Request__Sequence__copy(
  const gearbox_sim__action__RunScrewdriver_GetResult_Request__Sequence * input,
  gearbox_sim__action__RunScrewdriver_GetResult_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(gearbox_sim__action__RunScrewdriver_GetResult_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    gearbox_sim__action__RunScrewdriver_GetResult_Request * data =
      (gearbox_sim__action__RunScrewdriver_GetResult_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!gearbox_sim__action__RunScrewdriver_GetResult_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          gearbox_sim__action__RunScrewdriver_GetResult_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!gearbox_sim__action__RunScrewdriver_GetResult_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `result`
// already included above
// #include "gearbox_sim/action/detail/run_screwdriver__functions.h"

bool
gearbox_sim__action__RunScrewdriver_GetResult_Response__init(gearbox_sim__action__RunScrewdriver_GetResult_Response * msg)
{
  if (!msg) {
    return false;
  }
  // status
  // result
  if (!gearbox_sim__action__RunScrewdriver_Result__init(&msg->result)) {
    gearbox_sim__action__RunScrewdriver_GetResult_Response__fini(msg);
    return false;
  }
  return true;
}

void
gearbox_sim__action__RunScrewdriver_GetResult_Response__fini(gearbox_sim__action__RunScrewdriver_GetResult_Response * msg)
{
  if (!msg) {
    return;
  }
  // status
  // result
  gearbox_sim__action__RunScrewdriver_Result__fini(&msg->result);
}

bool
gearbox_sim__action__RunScrewdriver_GetResult_Response__are_equal(const gearbox_sim__action__RunScrewdriver_GetResult_Response * lhs, const gearbox_sim__action__RunScrewdriver_GetResult_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // status
  if (lhs->status != rhs->status) {
    return false;
  }
  // result
  if (!gearbox_sim__action__RunScrewdriver_Result__are_equal(
      &(lhs->result), &(rhs->result)))
  {
    return false;
  }
  return true;
}

bool
gearbox_sim__action__RunScrewdriver_GetResult_Response__copy(
  const gearbox_sim__action__RunScrewdriver_GetResult_Response * input,
  gearbox_sim__action__RunScrewdriver_GetResult_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // status
  output->status = input->status;
  // result
  if (!gearbox_sim__action__RunScrewdriver_Result__copy(
      &(input->result), &(output->result)))
  {
    return false;
  }
  return true;
}

gearbox_sim__action__RunScrewdriver_GetResult_Response *
gearbox_sim__action__RunScrewdriver_GetResult_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__action__RunScrewdriver_GetResult_Response * msg = (gearbox_sim__action__RunScrewdriver_GetResult_Response *)allocator.allocate(sizeof(gearbox_sim__action__RunScrewdriver_GetResult_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(gearbox_sim__action__RunScrewdriver_GetResult_Response));
  bool success = gearbox_sim__action__RunScrewdriver_GetResult_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
gearbox_sim__action__RunScrewdriver_GetResult_Response__destroy(gearbox_sim__action__RunScrewdriver_GetResult_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    gearbox_sim__action__RunScrewdriver_GetResult_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
gearbox_sim__action__RunScrewdriver_GetResult_Response__Sequence__init(gearbox_sim__action__RunScrewdriver_GetResult_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__action__RunScrewdriver_GetResult_Response * data = NULL;

  if (size) {
    data = (gearbox_sim__action__RunScrewdriver_GetResult_Response *)allocator.zero_allocate(size, sizeof(gearbox_sim__action__RunScrewdriver_GetResult_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = gearbox_sim__action__RunScrewdriver_GetResult_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        gearbox_sim__action__RunScrewdriver_GetResult_Response__fini(&data[i - 1]);
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
gearbox_sim__action__RunScrewdriver_GetResult_Response__Sequence__fini(gearbox_sim__action__RunScrewdriver_GetResult_Response__Sequence * array)
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
      gearbox_sim__action__RunScrewdriver_GetResult_Response__fini(&array->data[i]);
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

gearbox_sim__action__RunScrewdriver_GetResult_Response__Sequence *
gearbox_sim__action__RunScrewdriver_GetResult_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__action__RunScrewdriver_GetResult_Response__Sequence * array = (gearbox_sim__action__RunScrewdriver_GetResult_Response__Sequence *)allocator.allocate(sizeof(gearbox_sim__action__RunScrewdriver_GetResult_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = gearbox_sim__action__RunScrewdriver_GetResult_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
gearbox_sim__action__RunScrewdriver_GetResult_Response__Sequence__destroy(gearbox_sim__action__RunScrewdriver_GetResult_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    gearbox_sim__action__RunScrewdriver_GetResult_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
gearbox_sim__action__RunScrewdriver_GetResult_Response__Sequence__are_equal(const gearbox_sim__action__RunScrewdriver_GetResult_Response__Sequence * lhs, const gearbox_sim__action__RunScrewdriver_GetResult_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!gearbox_sim__action__RunScrewdriver_GetResult_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
gearbox_sim__action__RunScrewdriver_GetResult_Response__Sequence__copy(
  const gearbox_sim__action__RunScrewdriver_GetResult_Response__Sequence * input,
  gearbox_sim__action__RunScrewdriver_GetResult_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(gearbox_sim__action__RunScrewdriver_GetResult_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    gearbox_sim__action__RunScrewdriver_GetResult_Response * data =
      (gearbox_sim__action__RunScrewdriver_GetResult_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!gearbox_sim__action__RunScrewdriver_GetResult_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          gearbox_sim__action__RunScrewdriver_GetResult_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!gearbox_sim__action__RunScrewdriver_GetResult_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `info`
// already included above
// #include "service_msgs/msg/detail/service_event_info__functions.h"
// Member `request`
// Member `response`
// already included above
// #include "gearbox_sim/action/detail/run_screwdriver__functions.h"

bool
gearbox_sim__action__RunScrewdriver_GetResult_Event__init(gearbox_sim__action__RunScrewdriver_GetResult_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    gearbox_sim__action__RunScrewdriver_GetResult_Event__fini(msg);
    return false;
  }
  // request
  if (!gearbox_sim__action__RunScrewdriver_GetResult_Request__Sequence__init(&msg->request, 0)) {
    gearbox_sim__action__RunScrewdriver_GetResult_Event__fini(msg);
    return false;
  }
  // response
  if (!gearbox_sim__action__RunScrewdriver_GetResult_Response__Sequence__init(&msg->response, 0)) {
    gearbox_sim__action__RunScrewdriver_GetResult_Event__fini(msg);
    return false;
  }
  return true;
}

void
gearbox_sim__action__RunScrewdriver_GetResult_Event__fini(gearbox_sim__action__RunScrewdriver_GetResult_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  gearbox_sim__action__RunScrewdriver_GetResult_Request__Sequence__fini(&msg->request);
  // response
  gearbox_sim__action__RunScrewdriver_GetResult_Response__Sequence__fini(&msg->response);
}

bool
gearbox_sim__action__RunScrewdriver_GetResult_Event__are_equal(const gearbox_sim__action__RunScrewdriver_GetResult_Event * lhs, const gearbox_sim__action__RunScrewdriver_GetResult_Event * rhs)
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
  if (!gearbox_sim__action__RunScrewdriver_GetResult_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!gearbox_sim__action__RunScrewdriver_GetResult_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
gearbox_sim__action__RunScrewdriver_GetResult_Event__copy(
  const gearbox_sim__action__RunScrewdriver_GetResult_Event * input,
  gearbox_sim__action__RunScrewdriver_GetResult_Event * output)
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
  if (!gearbox_sim__action__RunScrewdriver_GetResult_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!gearbox_sim__action__RunScrewdriver_GetResult_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

gearbox_sim__action__RunScrewdriver_GetResult_Event *
gearbox_sim__action__RunScrewdriver_GetResult_Event__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__action__RunScrewdriver_GetResult_Event * msg = (gearbox_sim__action__RunScrewdriver_GetResult_Event *)allocator.allocate(sizeof(gearbox_sim__action__RunScrewdriver_GetResult_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(gearbox_sim__action__RunScrewdriver_GetResult_Event));
  bool success = gearbox_sim__action__RunScrewdriver_GetResult_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
gearbox_sim__action__RunScrewdriver_GetResult_Event__destroy(gearbox_sim__action__RunScrewdriver_GetResult_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    gearbox_sim__action__RunScrewdriver_GetResult_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
gearbox_sim__action__RunScrewdriver_GetResult_Event__Sequence__init(gearbox_sim__action__RunScrewdriver_GetResult_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__action__RunScrewdriver_GetResult_Event * data = NULL;

  if (size) {
    data = (gearbox_sim__action__RunScrewdriver_GetResult_Event *)allocator.zero_allocate(size, sizeof(gearbox_sim__action__RunScrewdriver_GetResult_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = gearbox_sim__action__RunScrewdriver_GetResult_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        gearbox_sim__action__RunScrewdriver_GetResult_Event__fini(&data[i - 1]);
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
gearbox_sim__action__RunScrewdriver_GetResult_Event__Sequence__fini(gearbox_sim__action__RunScrewdriver_GetResult_Event__Sequence * array)
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
      gearbox_sim__action__RunScrewdriver_GetResult_Event__fini(&array->data[i]);
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

gearbox_sim__action__RunScrewdriver_GetResult_Event__Sequence *
gearbox_sim__action__RunScrewdriver_GetResult_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__action__RunScrewdriver_GetResult_Event__Sequence * array = (gearbox_sim__action__RunScrewdriver_GetResult_Event__Sequence *)allocator.allocate(sizeof(gearbox_sim__action__RunScrewdriver_GetResult_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = gearbox_sim__action__RunScrewdriver_GetResult_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
gearbox_sim__action__RunScrewdriver_GetResult_Event__Sequence__destroy(gearbox_sim__action__RunScrewdriver_GetResult_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    gearbox_sim__action__RunScrewdriver_GetResult_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
gearbox_sim__action__RunScrewdriver_GetResult_Event__Sequence__are_equal(const gearbox_sim__action__RunScrewdriver_GetResult_Event__Sequence * lhs, const gearbox_sim__action__RunScrewdriver_GetResult_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!gearbox_sim__action__RunScrewdriver_GetResult_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
gearbox_sim__action__RunScrewdriver_GetResult_Event__Sequence__copy(
  const gearbox_sim__action__RunScrewdriver_GetResult_Event__Sequence * input,
  gearbox_sim__action__RunScrewdriver_GetResult_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(gearbox_sim__action__RunScrewdriver_GetResult_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    gearbox_sim__action__RunScrewdriver_GetResult_Event * data =
      (gearbox_sim__action__RunScrewdriver_GetResult_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!gearbox_sim__action__RunScrewdriver_GetResult_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          gearbox_sim__action__RunScrewdriver_GetResult_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!gearbox_sim__action__RunScrewdriver_GetResult_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__functions.h"
// Member `feedback`
// already included above
// #include "gearbox_sim/action/detail/run_screwdriver__functions.h"

bool
gearbox_sim__action__RunScrewdriver_FeedbackMessage__init(gearbox_sim__action__RunScrewdriver_FeedbackMessage * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    gearbox_sim__action__RunScrewdriver_FeedbackMessage__fini(msg);
    return false;
  }
  // feedback
  if (!gearbox_sim__action__RunScrewdriver_Feedback__init(&msg->feedback)) {
    gearbox_sim__action__RunScrewdriver_FeedbackMessage__fini(msg);
    return false;
  }
  return true;
}

void
gearbox_sim__action__RunScrewdriver_FeedbackMessage__fini(gearbox_sim__action__RunScrewdriver_FeedbackMessage * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // feedback
  gearbox_sim__action__RunScrewdriver_Feedback__fini(&msg->feedback);
}

bool
gearbox_sim__action__RunScrewdriver_FeedbackMessage__are_equal(const gearbox_sim__action__RunScrewdriver_FeedbackMessage * lhs, const gearbox_sim__action__RunScrewdriver_FeedbackMessage * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  // feedback
  if (!gearbox_sim__action__RunScrewdriver_Feedback__are_equal(
      &(lhs->feedback), &(rhs->feedback)))
  {
    return false;
  }
  return true;
}

bool
gearbox_sim__action__RunScrewdriver_FeedbackMessage__copy(
  const gearbox_sim__action__RunScrewdriver_FeedbackMessage * input,
  gearbox_sim__action__RunScrewdriver_FeedbackMessage * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  // feedback
  if (!gearbox_sim__action__RunScrewdriver_Feedback__copy(
      &(input->feedback), &(output->feedback)))
  {
    return false;
  }
  return true;
}

gearbox_sim__action__RunScrewdriver_FeedbackMessage *
gearbox_sim__action__RunScrewdriver_FeedbackMessage__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__action__RunScrewdriver_FeedbackMessage * msg = (gearbox_sim__action__RunScrewdriver_FeedbackMessage *)allocator.allocate(sizeof(gearbox_sim__action__RunScrewdriver_FeedbackMessage), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(gearbox_sim__action__RunScrewdriver_FeedbackMessage));
  bool success = gearbox_sim__action__RunScrewdriver_FeedbackMessage__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
gearbox_sim__action__RunScrewdriver_FeedbackMessage__destroy(gearbox_sim__action__RunScrewdriver_FeedbackMessage * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    gearbox_sim__action__RunScrewdriver_FeedbackMessage__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
gearbox_sim__action__RunScrewdriver_FeedbackMessage__Sequence__init(gearbox_sim__action__RunScrewdriver_FeedbackMessage__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__action__RunScrewdriver_FeedbackMessage * data = NULL;

  if (size) {
    data = (gearbox_sim__action__RunScrewdriver_FeedbackMessage *)allocator.zero_allocate(size, sizeof(gearbox_sim__action__RunScrewdriver_FeedbackMessage), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = gearbox_sim__action__RunScrewdriver_FeedbackMessage__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        gearbox_sim__action__RunScrewdriver_FeedbackMessage__fini(&data[i - 1]);
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
gearbox_sim__action__RunScrewdriver_FeedbackMessage__Sequence__fini(gearbox_sim__action__RunScrewdriver_FeedbackMessage__Sequence * array)
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
      gearbox_sim__action__RunScrewdriver_FeedbackMessage__fini(&array->data[i]);
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

gearbox_sim__action__RunScrewdriver_FeedbackMessage__Sequence *
gearbox_sim__action__RunScrewdriver_FeedbackMessage__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  gearbox_sim__action__RunScrewdriver_FeedbackMessage__Sequence * array = (gearbox_sim__action__RunScrewdriver_FeedbackMessage__Sequence *)allocator.allocate(sizeof(gearbox_sim__action__RunScrewdriver_FeedbackMessage__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = gearbox_sim__action__RunScrewdriver_FeedbackMessage__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
gearbox_sim__action__RunScrewdriver_FeedbackMessage__Sequence__destroy(gearbox_sim__action__RunScrewdriver_FeedbackMessage__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    gearbox_sim__action__RunScrewdriver_FeedbackMessage__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
gearbox_sim__action__RunScrewdriver_FeedbackMessage__Sequence__are_equal(const gearbox_sim__action__RunScrewdriver_FeedbackMessage__Sequence * lhs, const gearbox_sim__action__RunScrewdriver_FeedbackMessage__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!gearbox_sim__action__RunScrewdriver_FeedbackMessage__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
gearbox_sim__action__RunScrewdriver_FeedbackMessage__Sequence__copy(
  const gearbox_sim__action__RunScrewdriver_FeedbackMessage__Sequence * input,
  gearbox_sim__action__RunScrewdriver_FeedbackMessage__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(gearbox_sim__action__RunScrewdriver_FeedbackMessage);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    gearbox_sim__action__RunScrewdriver_FeedbackMessage * data =
      (gearbox_sim__action__RunScrewdriver_FeedbackMessage *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!gearbox_sim__action__RunScrewdriver_FeedbackMessage__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          gearbox_sim__action__RunScrewdriver_FeedbackMessage__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!gearbox_sim__action__RunScrewdriver_FeedbackMessage__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
