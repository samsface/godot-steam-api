import re
import json
from dataclasses import dataclass, field
import copy
from enum import Enum

class Type(Enum):
    VOID, OBJECT, POINTER, INTEGER, BOOL, REAL, STRING, ENUM, FUNCTION = range(0, 9)

class DupeProtector:
    def __init__(self):
        self.d = {}

    def get(self, name) -> str:
        if name in self.d:
            self.d[name] += 1
            return name + ("_" * self.d[name])
        else:
            self.d[name] = 0
            return name
    
    def clear(self):
        self.d = {}

class Comma:
    def __init__(self) -> None:
        self.needed = False
    
    def comma(self) -> str:
        if self.needed:
            return ", "
        else:
            self.needed = True
            return ""

    def clear(self):
        self.needed = False

def safe_name(str):
    res = str
    res = re.sub(r'unsigned ', '', res)
    res = re.sub(r'\s*const\s*', '', res)
    res = re.sub(r'\s*\*\s*', '', res)
    res = re.sub(r'::', '_', res)
    res = re.sub(r'&', '', res)
    res = re.sub(r'\s*', '', res)
    res = re.sub(r'[\[\]\(\),]', '_', res)

    if 'unsigned' in str:
        res = 'unsigned_' + res

    if 'const' in str:
        res += '_const'

    if '(' in str:
        res += '_func'

    if '**' in str:
        res += '_pointer_pointer'
    elif '*' in str:
        res += '_pointer'

    if '&' in str:
        res += '_reference'


    res += '_box'

    res = re.sub(r'_+', '_', res)

    return res

def is_prefix_allowed(string) -> bool:
    if 'progress' in string:
        print(string)

    allowed_prefixes = ['get', 'is', 'set', 'mod', 'app', 'max', 'cur']
    for allowed_prefix in allowed_prefixes:
        if string.startswith(allowed_prefix):
            return True
    return False

def snake_case(string):
    # Convert camel case to snake case
    string = re.sub(r'(.)([A-Z][a-z]+)', r'\1_\2', string)
    string = re.sub(r'([a-z0-9])([A-Z])', r'\1_\2', string).lower()

    # Remove Hungarian prefixes
    for i in range(2):
        if not is_prefix_allowed(string):
            string = re.sub(r'^[a-z]{0,3}_', '', string)
    
    string = re.sub(r'^_+', '', string) 

    if string == 'len':
        string = 'length'
    if string == 'str':
        string = 'string'
    if string == 'set':
        string = 'set_'
    if string == 'max':
        string = 'max_'

    return string

def camel_case(string):
    string = re.sub(r'_box', '', string)
    string = re.sub(r'(?:^|_)(.)', lambda match: match.group(1).upper(), string)

    return string

def wrap_with_out(string ,property) -> str:
    if property.is_pointer and not property.const:
        return 'Out' + string[0].upper() + string[1:]
    return string

def godot_type(property):
    if property.is_buffer:
        if property.kind == Type.VOID:
            return 'PoolByteArray'
        if property.kind == Type.INTEGER:
            return 'PoolIntArray'

    if property.kind == Type.VOID:
        return 'void'
    if property.kind == Type.STRING:
        return 'String'
    if property.kind == Type.INTEGER:
        return 'int'
    if property.kind == Type.BOOL:
        return 'bool'
    if property.kind == Type.REAL:
        return 'float'
    if property.kind == Type.ENUM:
        return 'int'
    
    return camel_case(property.inter_type)

@dataclass
class Object:
    cpp_type: str = field(default_factory=str) 
    name: str = field(default_factory=str)
    const: bool = field(default_factory=bool)
    array_size : int = field(default_factory=int)
    kind: Type = field(default=Type.OBJECT)
    is_pointer: bool = field(default_factory=bool)
    handwritten: bool = field(default_factory=bool)
    enums: list = field(default_factory=list) 
    properties: list = field(default_factory=list) 
    methods: list = field(default_factory=list)

    size_for: object = field(default=None)
    buffer_size: object = field(default=None)
    is_buffer: bool = field(default_factory=bool)

    @property
    def inter_type(self) -> str:
        return safe_name(self.cpp_type)
    
    @property
    def is_enum(self) -> bool:
        return self.kind == Type.ENUM

    @property
    def is_integer(self) -> bool:
        return self.kind == Type.INTEGER
    
    @property
    def is_void(self) -> bool:
        return self.kind == Type.VOID

    @property
    def godot_type(self) -> str:
        return godot_type(self)
    
    @property
    def godot_type_name(self) -> str:
        return camel_case(self.inter_type)
    
    @property
    def godot_type_hint(self) -> str:
        if self.godot_type == 'void':
            return ""
        else:
            return ":" + self.godot_type

    @property
    def godot_name(self) -> str:
        return snake_case(self.name)
    
    @property
    def is_output_param(self) -> bool:
        return self.is_pointer and self.const == False

    @property
    def is_primitive(self) -> bool:
        return self.kind in [
            Type.VOID,
            Type.INTEGER,
            Type.REAL,
            Type.BOOL,
        ]

@dataclass
class Method:
    _name: str
    return_type: Object = field(default_factory=Object) 
    params: list = field(default_factory=list) 
    overload_suffix: str = field(default_factory=str) 

    @property
    def name(self) -> str:
        return self._name + self.overload_suffix
    
    @property
    def is_overload(self) -> bool:
        return bool(self.overload_suffix)
    
    @property
    def godot_name(self) -> str:
        return snake_case(self.name)
     
    @property
    def godot_return_type(self) -> str:
        if bool(self.output_params):
            return self.name + "Result"
        else:
            return self.return_type.godot_type

    @property
    def output_params(self) -> list:
        res = []
        for param in self.params:
            if param.is_output_param:
                res.append(param)

        return res

def correct_overloads(method:Method, methods:list):
    for existing_method in methods:
        if existing_method._name == method._name:
            for param1, param2 in list(zip(existing_method.params, method.params)):
                if param1.cpp_type != param2.cpp_type:
                    existing_method.overload_suffix = param1.cpp_type[0] 
                    method.overload_suffix = param2.cpp_type[0] 
                    break