// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from gearbox_sim:srv/SetAttachment.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "gearbox_sim/srv/set_attachment.h"


#ifndef GEARBOX_SIM__SRV__DETAIL__SET_ATTACHMENT__FUNCTIONS_H_
#define GEARBOX_SIM__SRV__DETAIL__SET_ATTACHMENT__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/action_type_support_struct.h"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/type_description/type_description__struct.h"
#include "rosidl_runtime_c/type_description/type_source__struct.h"
#include "rosidl_runtime_c/type_hash.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "gearbox_sim/msg/rosidl_generator_c__visibility_control.h"

#include "gearbox_sim/srv/detail/set_attachment__struct.h"

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
const rosidl_type_hash_t *
gearbox_sim__srv__SetAttachment__get_type_hash(
  const rosidl_service_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
const rosidl_runtime_c__type_description__TypeDescription *
gearbox_sim__srv__SetAttachment__get_type_description(
  const rosidl_service_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
const rosidl_runtime_c__type_description__TypeSource *
gearbox_sim__srv__SetAttachment__get_individual_type_description_source(
  const rosidl_service_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
const rosidl_runtime_c__type_description__TypeSource__Sequence *
gearbox_sim__srv__SetAttachment__get_type_description_sources(
  const rosidl_service_type_support_t * type_support);

/// Initialize srv/SetAttachment message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * gearbox_sim__srv__SetAttachment_Request
 * )) before or use
 * gearbox_sim__srv__SetAttachment_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
bool
gearbox_sim__srv__SetAttachment_Request__init(gearbox_sim__srv__SetAttachment_Request * msg);

/// Finalize srv/SetAttachment message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
void
gearbox_sim__srv__SetAttachment_Request__fini(gearbox_sim__srv__SetAttachment_Request * msg);

/// Create srv/SetAttachment message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * gearbox_sim__srv__SetAttachment_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
gearbox_sim__srv__SetAttachment_Request *
gearbox_sim__srv__SetAttachment_Request__create(void);

/// Destroy srv/SetAttachment message.
/**
 * It calls
 * gearbox_sim__srv__SetAttachment_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
void
gearbox_sim__srv__SetAttachment_Request__destroy(gearbox_sim__srv__SetAttachment_Request * msg);

/// Check for srv/SetAttachment message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
bool
gearbox_sim__srv__SetAttachment_Request__are_equal(const gearbox_sim__srv__SetAttachment_Request * lhs, const gearbox_sim__srv__SetAttachment_Request * rhs);

/// Copy a srv/SetAttachment message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
bool
gearbox_sim__srv__SetAttachment_Request__copy(
  const gearbox_sim__srv__SetAttachment_Request * input,
  gearbox_sim__srv__SetAttachment_Request * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
const rosidl_type_hash_t *
gearbox_sim__srv__SetAttachment_Request__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
const rosidl_runtime_c__type_description__TypeDescription *
gearbox_sim__srv__SetAttachment_Request__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
const rosidl_runtime_c__type_description__TypeSource *
gearbox_sim__srv__SetAttachment_Request__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
const rosidl_runtime_c__type_description__TypeSource__Sequence *
gearbox_sim__srv__SetAttachment_Request__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of srv/SetAttachment messages.
/**
 * It allocates the memory for the number of elements and calls
 * gearbox_sim__srv__SetAttachment_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
bool
gearbox_sim__srv__SetAttachment_Request__Sequence__init(gearbox_sim__srv__SetAttachment_Request__Sequence * array, size_t size);

/// Finalize array of srv/SetAttachment messages.
/**
 * It calls
 * gearbox_sim__srv__SetAttachment_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
void
gearbox_sim__srv__SetAttachment_Request__Sequence__fini(gearbox_sim__srv__SetAttachment_Request__Sequence * array);

/// Create array of srv/SetAttachment messages.
/**
 * It allocates the memory for the array and calls
 * gearbox_sim__srv__SetAttachment_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
gearbox_sim__srv__SetAttachment_Request__Sequence *
gearbox_sim__srv__SetAttachment_Request__Sequence__create(size_t size);

/// Destroy array of srv/SetAttachment messages.
/**
 * It calls
 * gearbox_sim__srv__SetAttachment_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
void
gearbox_sim__srv__SetAttachment_Request__Sequence__destroy(gearbox_sim__srv__SetAttachment_Request__Sequence * array);

/// Check for srv/SetAttachment message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
bool
gearbox_sim__srv__SetAttachment_Request__Sequence__are_equal(const gearbox_sim__srv__SetAttachment_Request__Sequence * lhs, const gearbox_sim__srv__SetAttachment_Request__Sequence * rhs);

/// Copy an array of srv/SetAttachment messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
bool
gearbox_sim__srv__SetAttachment_Request__Sequence__copy(
  const gearbox_sim__srv__SetAttachment_Request__Sequence * input,
  gearbox_sim__srv__SetAttachment_Request__Sequence * output);

/// Initialize srv/SetAttachment message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * gearbox_sim__srv__SetAttachment_Response
 * )) before or use
 * gearbox_sim__srv__SetAttachment_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
bool
gearbox_sim__srv__SetAttachment_Response__init(gearbox_sim__srv__SetAttachment_Response * msg);

/// Finalize srv/SetAttachment message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
void
gearbox_sim__srv__SetAttachment_Response__fini(gearbox_sim__srv__SetAttachment_Response * msg);

/// Create srv/SetAttachment message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * gearbox_sim__srv__SetAttachment_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
gearbox_sim__srv__SetAttachment_Response *
gearbox_sim__srv__SetAttachment_Response__create(void);

/// Destroy srv/SetAttachment message.
/**
 * It calls
 * gearbox_sim__srv__SetAttachment_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
void
gearbox_sim__srv__SetAttachment_Response__destroy(gearbox_sim__srv__SetAttachment_Response * msg);

/// Check for srv/SetAttachment message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
bool
gearbox_sim__srv__SetAttachment_Response__are_equal(const gearbox_sim__srv__SetAttachment_Response * lhs, const gearbox_sim__srv__SetAttachment_Response * rhs);

/// Copy a srv/SetAttachment message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
bool
gearbox_sim__srv__SetAttachment_Response__copy(
  const gearbox_sim__srv__SetAttachment_Response * input,
  gearbox_sim__srv__SetAttachment_Response * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
const rosidl_type_hash_t *
gearbox_sim__srv__SetAttachment_Response__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
const rosidl_runtime_c__type_description__TypeDescription *
gearbox_sim__srv__SetAttachment_Response__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
const rosidl_runtime_c__type_description__TypeSource *
gearbox_sim__srv__SetAttachment_Response__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
const rosidl_runtime_c__type_description__TypeSource__Sequence *
gearbox_sim__srv__SetAttachment_Response__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of srv/SetAttachment messages.
/**
 * It allocates the memory for the number of elements and calls
 * gearbox_sim__srv__SetAttachment_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
bool
gearbox_sim__srv__SetAttachment_Response__Sequence__init(gearbox_sim__srv__SetAttachment_Response__Sequence * array, size_t size);

/// Finalize array of srv/SetAttachment messages.
/**
 * It calls
 * gearbox_sim__srv__SetAttachment_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
void
gearbox_sim__srv__SetAttachment_Response__Sequence__fini(gearbox_sim__srv__SetAttachment_Response__Sequence * array);

/// Create array of srv/SetAttachment messages.
/**
 * It allocates the memory for the array and calls
 * gearbox_sim__srv__SetAttachment_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
gearbox_sim__srv__SetAttachment_Response__Sequence *
gearbox_sim__srv__SetAttachment_Response__Sequence__create(size_t size);

/// Destroy array of srv/SetAttachment messages.
/**
 * It calls
 * gearbox_sim__srv__SetAttachment_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
void
gearbox_sim__srv__SetAttachment_Response__Sequence__destroy(gearbox_sim__srv__SetAttachment_Response__Sequence * array);

/// Check for srv/SetAttachment message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
bool
gearbox_sim__srv__SetAttachment_Response__Sequence__are_equal(const gearbox_sim__srv__SetAttachment_Response__Sequence * lhs, const gearbox_sim__srv__SetAttachment_Response__Sequence * rhs);

/// Copy an array of srv/SetAttachment messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
bool
gearbox_sim__srv__SetAttachment_Response__Sequence__copy(
  const gearbox_sim__srv__SetAttachment_Response__Sequence * input,
  gearbox_sim__srv__SetAttachment_Response__Sequence * output);

/// Initialize srv/SetAttachment message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * gearbox_sim__srv__SetAttachment_Event
 * )) before or use
 * gearbox_sim__srv__SetAttachment_Event__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
bool
gearbox_sim__srv__SetAttachment_Event__init(gearbox_sim__srv__SetAttachment_Event * msg);

/// Finalize srv/SetAttachment message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
void
gearbox_sim__srv__SetAttachment_Event__fini(gearbox_sim__srv__SetAttachment_Event * msg);

/// Create srv/SetAttachment message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * gearbox_sim__srv__SetAttachment_Event__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
gearbox_sim__srv__SetAttachment_Event *
gearbox_sim__srv__SetAttachment_Event__create(void);

/// Destroy srv/SetAttachment message.
/**
 * It calls
 * gearbox_sim__srv__SetAttachment_Event__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
void
gearbox_sim__srv__SetAttachment_Event__destroy(gearbox_sim__srv__SetAttachment_Event * msg);

/// Check for srv/SetAttachment message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
bool
gearbox_sim__srv__SetAttachment_Event__are_equal(const gearbox_sim__srv__SetAttachment_Event * lhs, const gearbox_sim__srv__SetAttachment_Event * rhs);

/// Copy a srv/SetAttachment message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
bool
gearbox_sim__srv__SetAttachment_Event__copy(
  const gearbox_sim__srv__SetAttachment_Event * input,
  gearbox_sim__srv__SetAttachment_Event * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
const rosidl_type_hash_t *
gearbox_sim__srv__SetAttachment_Event__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
const rosidl_runtime_c__type_description__TypeDescription *
gearbox_sim__srv__SetAttachment_Event__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
const rosidl_runtime_c__type_description__TypeSource *
gearbox_sim__srv__SetAttachment_Event__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
const rosidl_runtime_c__type_description__TypeSource__Sequence *
gearbox_sim__srv__SetAttachment_Event__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of srv/SetAttachment messages.
/**
 * It allocates the memory for the number of elements and calls
 * gearbox_sim__srv__SetAttachment_Event__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
bool
gearbox_sim__srv__SetAttachment_Event__Sequence__init(gearbox_sim__srv__SetAttachment_Event__Sequence * array, size_t size);

/// Finalize array of srv/SetAttachment messages.
/**
 * It calls
 * gearbox_sim__srv__SetAttachment_Event__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
void
gearbox_sim__srv__SetAttachment_Event__Sequence__fini(gearbox_sim__srv__SetAttachment_Event__Sequence * array);

/// Create array of srv/SetAttachment messages.
/**
 * It allocates the memory for the array and calls
 * gearbox_sim__srv__SetAttachment_Event__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
gearbox_sim__srv__SetAttachment_Event__Sequence *
gearbox_sim__srv__SetAttachment_Event__Sequence__create(size_t size);

/// Destroy array of srv/SetAttachment messages.
/**
 * It calls
 * gearbox_sim__srv__SetAttachment_Event__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
void
gearbox_sim__srv__SetAttachment_Event__Sequence__destroy(gearbox_sim__srv__SetAttachment_Event__Sequence * array);

/// Check for srv/SetAttachment message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
bool
gearbox_sim__srv__SetAttachment_Event__Sequence__are_equal(const gearbox_sim__srv__SetAttachment_Event__Sequence * lhs, const gearbox_sim__srv__SetAttachment_Event__Sequence * rhs);

/// Copy an array of srv/SetAttachment messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_gearbox_sim
bool
gearbox_sim__srv__SetAttachment_Event__Sequence__copy(
  const gearbox_sim__srv__SetAttachment_Event__Sequence * input,
  gearbox_sim__srv__SetAttachment_Event__Sequence * output);
#ifdef __cplusplus
}
#endif

#endif  // GEARBOX_SIM__SRV__DETAIL__SET_ATTACHMENT__FUNCTIONS_H_
