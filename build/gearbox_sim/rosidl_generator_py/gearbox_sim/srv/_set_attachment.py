# generated from rosidl_generator_py/resource/_idl.py.em
# with input from gearbox_sim:srv/SetAttachment.idl
# generated code does not contain a copyright notice

# This is being done at the module level and not on the instance level to avoid looking
# for the same variable multiple times on each instance. This variable is not supposed to
# change during runtime so it makes sense to only look for it once.
from os import getenv

ros_python_check_fields = getenv('ROS_PYTHON_CHECK_FIELDS', default='')


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SetAttachment_Request(type):
    """Metaclass of message 'SetAttachment_Request'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('gearbox_sim')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'gearbox_sim.srv.SetAttachment_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__set_attachment__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__set_attachment__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__set_attachment__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__set_attachment__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__set_attachment__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SetAttachment_Request(metaclass=Metaclass_SetAttachment_Request):
    """Message class 'SetAttachment_Request'."""

    __slots__ = [
        '_robot_name',
        '_tool_frame',
        '_part_name',
        '_part_frame',
        '_part_link',
        '_attach',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'robot_name': 'string',
        'tool_frame': 'string',
        'part_name': 'string',
        'part_frame': 'string',
        'part_link': 'string',
        'attach': 'boolean',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        if 'check_fields' in kwargs:
            self._check_fields = kwargs['check_fields']
        else:
            self._check_fields = ros_python_check_fields == '1'
        if self._check_fields:
            assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
                'Invalid arguments passed to constructor: %s' % \
                ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.robot_name = kwargs.get('robot_name', str())
        self.tool_frame = kwargs.get('tool_frame', str())
        self.part_name = kwargs.get('part_name', str())
        self.part_frame = kwargs.get('part_frame', str())
        self.part_link = kwargs.get('part_link', str())
        self.attach = kwargs.get('attach', bool())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.get_fields_and_field_types().keys(), self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    if self._check_fields:
                        assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.robot_name != other.robot_name:
            return False
        if self.tool_frame != other.tool_frame:
            return False
        if self.part_name != other.part_name:
            return False
        if self.part_frame != other.part_frame:
            return False
        if self.part_link != other.part_link:
            return False
        if self.attach != other.attach:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def robot_name(self):
        """Message field 'robot_name'."""
        return self._robot_name

    @robot_name.setter
    def robot_name(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'robot_name' field must be of type 'str'"
        self._robot_name = value

    @builtins.property
    def tool_frame(self):
        """Message field 'tool_frame'."""
        return self._tool_frame

    @tool_frame.setter
    def tool_frame(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'tool_frame' field must be of type 'str'"
        self._tool_frame = value

    @builtins.property
    def part_name(self):
        """Message field 'part_name'."""
        return self._part_name

    @part_name.setter
    def part_name(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'part_name' field must be of type 'str'"
        self._part_name = value

    @builtins.property
    def part_frame(self):
        """Message field 'part_frame'."""
        return self._part_frame

    @part_frame.setter
    def part_frame(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'part_frame' field must be of type 'str'"
        self._part_frame = value

    @builtins.property
    def part_link(self):
        """Message field 'part_link'."""
        return self._part_link

    @part_link.setter
    def part_link(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'part_link' field must be of type 'str'"
        self._part_link = value

    @builtins.property
    def attach(self):
        """Message field 'attach'."""
        return self._attach

    @attach.setter
    def attach(self, value):
        if self._check_fields:
            assert \
                isinstance(value, bool), \
                "The 'attach' field must be of type 'bool'"
        self._attach = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_SetAttachment_Response(type):
    """Metaclass of message 'SetAttachment_Response'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('gearbox_sim')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'gearbox_sim.srv.SetAttachment_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__set_attachment__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__set_attachment__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__set_attachment__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__set_attachment__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__set_attachment__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SetAttachment_Response(metaclass=Metaclass_SetAttachment_Response):
    """Message class 'SetAttachment_Response'."""

    __slots__ = [
        '_success',
        '_message',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'success': 'boolean',
        'message': 'string',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        if 'check_fields' in kwargs:
            self._check_fields = kwargs['check_fields']
        else:
            self._check_fields = ros_python_check_fields == '1'
        if self._check_fields:
            assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
                'Invalid arguments passed to constructor: %s' % \
                ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.success = kwargs.get('success', bool())
        self.message = kwargs.get('message', str())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.get_fields_and_field_types().keys(), self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    if self._check_fields:
                        assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.success != other.success:
            return False
        if self.message != other.message:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def success(self):
        """Message field 'success'."""
        return self._success

    @success.setter
    def success(self, value):
        if self._check_fields:
            assert \
                isinstance(value, bool), \
                "The 'success' field must be of type 'bool'"
        self._success = value

    @builtins.property
    def message(self):
        """Message field 'message'."""
        return self._message

    @message.setter
    def message(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'message' field must be of type 'str'"
        self._message = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_SetAttachment_Event(type):
    """Metaclass of message 'SetAttachment_Event'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('gearbox_sim')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'gearbox_sim.srv.SetAttachment_Event')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__set_attachment__event
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__set_attachment__event
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__set_attachment__event
            cls._TYPE_SUPPORT = module.type_support_msg__srv__set_attachment__event
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__set_attachment__event

            from service_msgs.msg import ServiceEventInfo
            if ServiceEventInfo.__class__._TYPE_SUPPORT is None:
                ServiceEventInfo.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SetAttachment_Event(metaclass=Metaclass_SetAttachment_Event):
    """Message class 'SetAttachment_Event'."""

    __slots__ = [
        '_info',
        '_request',
        '_response',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'info': 'service_msgs/ServiceEventInfo',
        'request': 'sequence<gearbox_sim/SetAttachment_Request, 1>',
        'response': 'sequence<gearbox_sim/SetAttachment_Response, 1>',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['service_msgs', 'msg'], 'ServiceEventInfo'),  # noqa: E501
        rosidl_parser.definition.BoundedSequence(rosidl_parser.definition.NamespacedType(['gearbox_sim', 'srv'], 'SetAttachment_Request'), 1),  # noqa: E501
        rosidl_parser.definition.BoundedSequence(rosidl_parser.definition.NamespacedType(['gearbox_sim', 'srv'], 'SetAttachment_Response'), 1),  # noqa: E501
    )

    def __init__(self, **kwargs):
        if 'check_fields' in kwargs:
            self._check_fields = kwargs['check_fields']
        else:
            self._check_fields = ros_python_check_fields == '1'
        if self._check_fields:
            assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
                'Invalid arguments passed to constructor: %s' % \
                ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from service_msgs.msg import ServiceEventInfo
        self.info = kwargs.get('info', ServiceEventInfo())
        self.request = kwargs.get('request', [])
        self.response = kwargs.get('response', [])

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.get_fields_and_field_types().keys(), self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    if self._check_fields:
                        assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.info != other.info:
            return False
        if self.request != other.request:
            return False
        if self.response != other.response:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def info(self):
        """Message field 'info'."""
        return self._info

    @info.setter
    def info(self, value):
        if self._check_fields:
            from service_msgs.msg import ServiceEventInfo
            assert \
                isinstance(value, ServiceEventInfo), \
                "The 'info' field must be a sub message of type 'ServiceEventInfo'"
        self._info = value

    @builtins.property
    def request(self):
        """Message field 'request'."""
        return self._request

    @request.setter
    def request(self, value):
        if self._check_fields:
            from gearbox_sim.srv import SetAttachment_Request
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) <= 1 and
                 all(isinstance(v, SetAttachment_Request) for v in value) and
                 True), \
                "The 'request' field must be a set or sequence with length <= 1 and each value of type 'SetAttachment_Request'"
        self._request = value

    @builtins.property
    def response(self):
        """Message field 'response'."""
        return self._response

    @response.setter
    def response(self, value):
        if self._check_fields:
            from gearbox_sim.srv import SetAttachment_Response
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) <= 1 and
                 all(isinstance(v, SetAttachment_Response) for v in value) and
                 True), \
                "The 'response' field must be a set or sequence with length <= 1 and each value of type 'SetAttachment_Response'"
        self._response = value


class Metaclass_SetAttachment(type):
    """Metaclass of service 'SetAttachment'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('gearbox_sim')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'gearbox_sim.srv.SetAttachment')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__set_attachment

            from gearbox_sim.srv import _set_attachment
            if _set_attachment.Metaclass_SetAttachment_Request._TYPE_SUPPORT is None:
                _set_attachment.Metaclass_SetAttachment_Request.__import_type_support__()
            if _set_attachment.Metaclass_SetAttachment_Response._TYPE_SUPPORT is None:
                _set_attachment.Metaclass_SetAttachment_Response.__import_type_support__()
            if _set_attachment.Metaclass_SetAttachment_Event._TYPE_SUPPORT is None:
                _set_attachment.Metaclass_SetAttachment_Event.__import_type_support__()


class SetAttachment(metaclass=Metaclass_SetAttachment):
    from gearbox_sim.srv._set_attachment import SetAttachment_Request as Request
    from gearbox_sim.srv._set_attachment import SetAttachment_Response as Response
    from gearbox_sim.srv._set_attachment import SetAttachment_Event as Event

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
