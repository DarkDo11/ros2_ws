// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from gearbox_sim:srv/SetAttachment.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "gearbox_sim/srv/set_attachment.hpp"


#ifndef GEARBOX_SIM__SRV__DETAIL__SET_ATTACHMENT__STRUCT_HPP_
#define GEARBOX_SIM__SRV__DETAIL__SET_ATTACHMENT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__gearbox_sim__srv__SetAttachment_Request __attribute__((deprecated))
#else
# define DEPRECATED__gearbox_sim__srv__SetAttachment_Request __declspec(deprecated)
#endif

namespace gearbox_sim
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetAttachment_Request_
{
  using Type = SetAttachment_Request_<ContainerAllocator>;

  explicit SetAttachment_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->robot_name = "";
      this->tool_frame = "";
      this->part_name = "";
      this->part_frame = "";
      this->part_link = "";
      this->attach = false;
    }
  }

  explicit SetAttachment_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : robot_name(_alloc),
    tool_frame(_alloc),
    part_name(_alloc),
    part_frame(_alloc),
    part_link(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->robot_name = "";
      this->tool_frame = "";
      this->part_name = "";
      this->part_frame = "";
      this->part_link = "";
      this->attach = false;
    }
  }

  // field types and members
  using _robot_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _robot_name_type robot_name;
  using _tool_frame_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _tool_frame_type tool_frame;
  using _part_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _part_name_type part_name;
  using _part_frame_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _part_frame_type part_frame;
  using _part_link_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _part_link_type part_link;
  using _attach_type =
    bool;
  _attach_type attach;

  // setters for named parameter idiom
  Type & set__robot_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->robot_name = _arg;
    return *this;
  }
  Type & set__tool_frame(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->tool_frame = _arg;
    return *this;
  }
  Type & set__part_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->part_name = _arg;
    return *this;
  }
  Type & set__part_frame(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->part_frame = _arg;
    return *this;
  }
  Type & set__part_link(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->part_link = _arg;
    return *this;
  }
  Type & set__attach(
    const bool & _arg)
  {
    this->attach = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    gearbox_sim::srv::SetAttachment_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const gearbox_sim::srv::SetAttachment_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<gearbox_sim::srv::SetAttachment_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<gearbox_sim::srv::SetAttachment_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      gearbox_sim::srv::SetAttachment_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<gearbox_sim::srv::SetAttachment_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      gearbox_sim::srv::SetAttachment_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<gearbox_sim::srv::SetAttachment_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<gearbox_sim::srv::SetAttachment_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<gearbox_sim::srv::SetAttachment_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__gearbox_sim__srv__SetAttachment_Request
    std::shared_ptr<gearbox_sim::srv::SetAttachment_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__gearbox_sim__srv__SetAttachment_Request
    std::shared_ptr<gearbox_sim::srv::SetAttachment_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetAttachment_Request_ & other) const
  {
    if (this->robot_name != other.robot_name) {
      return false;
    }
    if (this->tool_frame != other.tool_frame) {
      return false;
    }
    if (this->part_name != other.part_name) {
      return false;
    }
    if (this->part_frame != other.part_frame) {
      return false;
    }
    if (this->part_link != other.part_link) {
      return false;
    }
    if (this->attach != other.attach) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetAttachment_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetAttachment_Request_

// alias to use template instance with default allocator
using SetAttachment_Request =
  gearbox_sim::srv::SetAttachment_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace gearbox_sim


#ifndef _WIN32
# define DEPRECATED__gearbox_sim__srv__SetAttachment_Response __attribute__((deprecated))
#else
# define DEPRECATED__gearbox_sim__srv__SetAttachment_Response __declspec(deprecated)
#endif

namespace gearbox_sim
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetAttachment_Response_
{
  using Type = SetAttachment_Response_<ContainerAllocator>;

  explicit SetAttachment_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  explicit SetAttachment_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    gearbox_sim::srv::SetAttachment_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const gearbox_sim::srv::SetAttachment_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<gearbox_sim::srv::SetAttachment_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<gearbox_sim::srv::SetAttachment_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      gearbox_sim::srv::SetAttachment_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<gearbox_sim::srv::SetAttachment_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      gearbox_sim::srv::SetAttachment_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<gearbox_sim::srv::SetAttachment_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<gearbox_sim::srv::SetAttachment_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<gearbox_sim::srv::SetAttachment_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__gearbox_sim__srv__SetAttachment_Response
    std::shared_ptr<gearbox_sim::srv::SetAttachment_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__gearbox_sim__srv__SetAttachment_Response
    std::shared_ptr<gearbox_sim::srv::SetAttachment_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetAttachment_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetAttachment_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetAttachment_Response_

// alias to use template instance with default allocator
using SetAttachment_Response =
  gearbox_sim::srv::SetAttachment_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace gearbox_sim


// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__gearbox_sim__srv__SetAttachment_Event __attribute__((deprecated))
#else
# define DEPRECATED__gearbox_sim__srv__SetAttachment_Event __declspec(deprecated)
#endif

namespace gearbox_sim
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetAttachment_Event_
{
  using Type = SetAttachment_Event_<ContainerAllocator>;

  explicit SetAttachment_Event_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_init)
  {
    (void)_init;
  }

  explicit SetAttachment_Event_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _info_type =
    service_msgs::msg::ServiceEventInfo_<ContainerAllocator>;
  _info_type info;
  using _request_type =
    rosidl_runtime_cpp::BoundedVector<gearbox_sim::srv::SetAttachment_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<gearbox_sim::srv::SetAttachment_Request_<ContainerAllocator>>>;
  _request_type request;
  using _response_type =
    rosidl_runtime_cpp::BoundedVector<gearbox_sim::srv::SetAttachment_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<gearbox_sim::srv::SetAttachment_Response_<ContainerAllocator>>>;
  _response_type response;

  // setters for named parameter idiom
  Type & set__info(
    const service_msgs::msg::ServiceEventInfo_<ContainerAllocator> & _arg)
  {
    this->info = _arg;
    return *this;
  }
  Type & set__request(
    const rosidl_runtime_cpp::BoundedVector<gearbox_sim::srv::SetAttachment_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<gearbox_sim::srv::SetAttachment_Request_<ContainerAllocator>>> & _arg)
  {
    this->request = _arg;
    return *this;
  }
  Type & set__response(
    const rosidl_runtime_cpp::BoundedVector<gearbox_sim::srv::SetAttachment_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<gearbox_sim::srv::SetAttachment_Response_<ContainerAllocator>>> & _arg)
  {
    this->response = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    gearbox_sim::srv::SetAttachment_Event_<ContainerAllocator> *;
  using ConstRawPtr =
    const gearbox_sim::srv::SetAttachment_Event_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<gearbox_sim::srv::SetAttachment_Event_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<gearbox_sim::srv::SetAttachment_Event_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      gearbox_sim::srv::SetAttachment_Event_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<gearbox_sim::srv::SetAttachment_Event_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      gearbox_sim::srv::SetAttachment_Event_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<gearbox_sim::srv::SetAttachment_Event_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<gearbox_sim::srv::SetAttachment_Event_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<gearbox_sim::srv::SetAttachment_Event_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__gearbox_sim__srv__SetAttachment_Event
    std::shared_ptr<gearbox_sim::srv::SetAttachment_Event_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__gearbox_sim__srv__SetAttachment_Event
    std::shared_ptr<gearbox_sim::srv::SetAttachment_Event_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetAttachment_Event_ & other) const
  {
    if (this->info != other.info) {
      return false;
    }
    if (this->request != other.request) {
      return false;
    }
    if (this->response != other.response) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetAttachment_Event_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetAttachment_Event_

// alias to use template instance with default allocator
using SetAttachment_Event =
  gearbox_sim::srv::SetAttachment_Event_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace gearbox_sim

namespace gearbox_sim
{

namespace srv
{

struct SetAttachment
{
  using Request = gearbox_sim::srv::SetAttachment_Request;
  using Response = gearbox_sim::srv::SetAttachment_Response;
  using Event = gearbox_sim::srv::SetAttachment_Event;
};

}  // namespace srv

}  // namespace gearbox_sim

#endif  // GEARBOX_SIM__SRV__DETAIL__SET_ATTACHMENT__STRUCT_HPP_
