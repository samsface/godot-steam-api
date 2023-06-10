import re
import json
from dataclasses import dataclass, field
import copy
from enum import Enum

class Type(Enum):
    VOID, POINTER, INTEGER, BOOL, REAL, STRING = range(0, 6)

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

@dataclass
class Class:
    data_type: str
    properties: list = field(default_factory=list) 
    methods: list = field(default_factory=list) 
    #type: Type = field(default_factory=list) 
    enum: dict = field(default_factory=dict) 
    interface: bool = field(default_factory=bool) 
    namespace: str = field(default_factory=str)

    def is_enum(self):
        return bool(self.enum)

    @property
    def name(self) -> str:
        return safe_name(self.data_type)

@dataclass
class Property:
    type: str = field(default_factory=str) 
    name: str = field(default_factory=str) 
    const: bool = field(default_factory=bool) 
    array_size : int = field(default_factory=int) 

    @property
    def safe_type(self) -> str:
        return safe_name(self.type)

@dataclass
class Method:
    _name: str
    return_type: Property = field(default_factory=Property) 
    params: list = field(default_factory=list) 
    overload_suffix: str = field(default_factory=str) 

    @property
    def name(self) -> str:
        return self._name + self.overload_suffix
    
    @property
    def is_overload(self) -> bool:
        return bool(self.overload_suffix)
