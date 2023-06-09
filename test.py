import re
import json
from dataclasses import dataclass
import copy
from enum import Enum

def camel_to_snake_case(camel_case_string):
    snake_case = re.sub(r'(?<!^)(?=[A-Z])', '_', camel_case_string)
    
    abbrvs = ["_I_D", "_U_G_C", "_E_U_L_", "_U_R_L", "_H_T_T_P", "_I_P", "_S_H_A", '_V_R', "_I_P_C", "_A_P_I", "_I_P"]
    for abbr in abbrvs:
        if abbr in snake_case:
           snake_case = snake_case.replace(abbr, '_' + re.sub(r'_', '', abbr))

    prefix_pattern = r'(^)([a-z]|[A-Z]|pch|cch|pvec|pfn|pfz|psz)_'

    for i in range(2):
        snake_case = re.sub(prefix_pattern, '', snake_case)

    return snake_case.lower()

def safe_name(str):
    res = str
    res = re.sub(r'unsigned ', '', res)
    res = re.sub(r'\s*const\s*', '', res)
    res = re.sub(r'\s*\*\s*', '', res)
    res = re.sub(r'::', '_', res)
    res = re.sub(r'&', '', res)
    res = re.sub(r'\s*', '', res)

    if 'unsigned' in str:
        res = 'unsigned_' + res

    if 'const' in str and not '&' in str:
        res += '_const'

    if '*' in str and 'const' in str:
        res += '_pointer'

    #if '&' in str:
    #    res += '_reference'

    if not '[' in res:
        res += '_box'

    return res

def log(str):
    print(f'/* {str} */')

def out(str):
    print(str)

class Type(Enum):
    VOID, POINTER, INTEGER, BOOL, REAL, STRING = range(0, 6)

@dataclass
class Class:
    data_type: str
    properties: list
    methods: list
    type: Type
    enum: dict
    interface: bool
    namespace: str

    def is_enum(self):
        return bool(self.enum)

    @property
    def name(self) -> str:
        return safe_name(self.data_type)

@dataclass
class Property:
    name: str
    type: str

    @property
    def safe_type(self) -> str:
        return safe_name(self.type)

@dataclass
class Method:
    _name: str
    return_type: str
    params: list
    overload_suffix: str

    @property
    def name(self) -> str:
        return self._name + self.overload_suffix
    
    @property
    def is_overload(self) -> bool:
        return bool(self.overload_suffix)

@dataclass
class Mappings:
    name: str
    properties: str
    property_name: str
    property_type: str
    methods: str
    method_name: str
    return_type: str
    params: str

default_mappings = Mappings(
    name="struct",
    properties="fields",
    property_name="fieldname",
    property_type="fieldtype",
    methods="methods",
    method_name="methodname",
    return_type="returntype",
    params="params"
)

typedef_mapping = copy.copy(default_mappings)
typedef_mapping.name = 'typedef'

interface_mapping = copy.copy(default_mappings)
interface_mapping.name = 'classname'

def overload(existing_method:Method, new_method:Method):
    for i in range(0, len(existing_method.params)):
        param_a = existing_method.params[i]
        param_b = new_method.params[i]

        if param_a.type != param_b.type:
            existing_method.overload_suffix = "_overload_" + param_a.type[0]
            new_method.overload_suffix = "_overload_" + param_b.type[0]
            return

def structs_to_class(struct:dict, m:Mappings = default_mappings) -> Class:
    clazz = Class(struct[m.name], [], [], Type.POINTER, {}, False, "::")

    for field in struct.get(m.properties, []):
        if 'private' in field:
            continue

        if is_ignored(struct[m.name], field[m.property_name]):
            log(f'ignoring property {struct[m.name]}::{field[m.property_name]}')
            continue

        clazz.properties.append(Property(
            name=field[m.property_name], 
            type=field[m.property_type]))

    for method in struct.get(m.methods, []):
        if 'private' in method:
            continue
        
        if is_ignored(struct[m.name], method[m.method_name]):
            log(f'ignoring method {struct[m.name]}::{method[m.method_name]}')
            continue

        new_method = Method(
            method[m.method_name], 
            return_type=method[m.return_type], 
            params=params_to_class(method.get(m.params, [])),
            overload_suffix="")


        for existing_method in clazz.methods:
            if existing_method.name == new_method.name:
                overload(existing_method, new_method)
                break

        clazz.methods.append(new_method)

    return clazz

def params_to_class(params:list) -> list:
    res = []
    for param in params:
        res.append(Property(name=param["paramname"], type=param["paramtype"]))
    return res

def out_property_decleration(property:Property, struct:Class):
    out(f"""auto get_{property.name}();""")

def out_property_defenition(property:Property, struct:Class):
        out(f"""
auto {struct.name}::get_{property.name}()
{{
    return cast<{property.safe_type}>(get_ptr()->{property.name});
}}
""")

def out_method_decleration(method:Method, struct:Class):
    out(f"""
        template <typename C = {struct.name}>
        auto {method.name}""")
    out_params(method.params)
    out(" -> typename std::enable_if<true>::type;")


mm = 0

def out_method_defenition(method:Method, struct:Class):
    out(f"""
        template <typename C>
        auto {struct.name}::{method.name}""")
    out_params(method.params)
    out(" -> typename std::enable_if<true>::type")
    out('{')

    global mm

    if mm < 110:
        mm += 1
        out(f"""
            
        call<{safe_name(method.return_type)}>([](auto* data, auto&& ...args)
        {{
            return data->{method._name}(args...);
        }}""")

        # pass paramters
        for param in method.params:
            out(f', {wrap2(param)}')

        out(");")
    out("}\n")

unknowns_types = set()

def wrap(type_str:str) -> str:
    const = 'const' in type_str
    pointer = '*' in type_str

    # output param
    if pointer and not const:
        type_str = re.sub(r'\*', '', type_str)

    return f'Ref<{safe_name(type_str)}>'


def wrap2(param:Property) -> str:
    if "**" in param.type:
        return param.name + "->get_array()"
    if "*" in param.type:
        return param.name + "->get_ptr()"
    else:
        return param.name + "->get()"

def out_params(params:list):
    out('(')
    for param in params:
        out(f'{wrap(param.type)} {param.name} {"," if param != params[-1] else ""}')
    out(')')

def out_register(struct:Class):
    out(f"""
void {struct.name}::_register_methods()
{{""")
    
    for property in struct.properties:
        out(f'register_method("get_{property.name}", &{struct.name}::get_{property.name});')

    for method in struct.methods:
        out(f'register_method("{method.name}", &{struct.name}::{method.name});')
    
    out("""}\n""")

def out_pre_class(struct:Class):
    out(f'#define {struct.name}_IS_DEFINED 1')
    out(f'class {struct.name};')


def out_class(struct:Class):
    # header
    out(f"""
class {struct.name} : public Steam{'Interface' if struct.interface else ''}Base<{struct.data_type}, {struct.name}>
{{
GODOT_CLASS({struct.name}, Reference)
public:
    static void _register_methods();
    void _init() {{}}
""")

    # properties
    for property in struct.properties:
        out_property_decleration(property, struct)

    # methods
    for method in struct.methods:
        out_method_decleration(method, struct)

    #end
    out('};')
    
def out_class_methods(struct:Class):
    for property in struct.properties:
        out_property_defenition(property, struct)

    for method in struct.methods:
        out_method_defenition(method, struct)
    
    out_register(struct)

def is_ignored(classname, fieldname):
    if 'operator' in fieldname:
        return True
    if '&' in fieldname:
        return True
    if '::' in fieldname:
        return True
    if 'Construct' in fieldname:
        return True
    if not classname in missing_fields:
        return False
    if not fieldname in missing_fields[classname]:
        return False
    return True

# write register

def write_register():
    res = """
        extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) 
        {
            godot::Godot::gdnative_init(o);
        }

        extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) 
        {
            godot::Godot::gdnative_terminate(o);
        }

        extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) 
        {
            godot::Godot::nativescript_init(handle);
            godot::register_class<godot::SteamAPI>();
    """

    
def read_json_file_as_text(file_path):
    with open(file_path, 'r') as file:
        return file.read()

def read_json_file(file_path):
    with open(file_path, 'r') as file:
        json_content = file.read()
        json_dict = json.loads(json_content)
        return json_dict

missing = set()

missing_fields = {
    'SteamInputActionEvent_t': {
        'analogAction_actionHandle', 
        'analogAction_analogActionData'
    },
    'SteamNetConnectionInfo_t': { 
        'm_nFlags' 
    },
    'SteamNetworkingConfigValue_t': {
        'm_int64'
    },
    'SteamDatagramHostedAddress': {
        'm_cbSize',
        'm_data'
    },
    'SteamDatagramGameCoordinatorServerLogin': {
        'm_identity',
        'm_routing',
        'm_rtime',
        'm_cbAppData',
        'm_appData',
        'm_nAppID'
    },
    'FriendGameInfo_t': {
        'm_rgubIPv6'
    },
    'RequestPlayersForGameResultCallback_t': {
        'm_ePlayerAcceptState'
    },
    'SteamParamStringArray_t': {
        'm_ppStrings'
    },
    'SteamNetworkingMessage_t': {
        'm_pfnFreeData',
        'm_pfnRelease'
    },
    'SteamNetworkingIdentity': {
        'SetXboxPairwiseID',
        'GetXboxPairwiseID',
        'SetPSNID',
        'GetPSNID',
        'SetStadiaID',
        'GetStadiaID'
    },
    'SteamNetworkingIdentity': {
        'SetIPv4Addr',
        'SetXboxPairwiseID',
        'GetXboxPairwiseID',
        'SetPSNID',
        'GetPSNID',
        'SetStadiaID',
        'GetStadiaID',
        'GetIPv4',
    },
    'SteamDatagramHostedAddress': {
        'Clear',
        'GetPopID',
        'm_cbSize',
        'm_data',
        'SetDevAddress'
    },
    'ISteamUtils': {
        'ShowModalGamepadTextInput'
    },
    'ISteamNetworkingSockets': {
        'SendMessages',
        'GetCertificateRequest',
        'SetCertificate',
        'ResetIdentity'
    },
    'ISteamNetworkingUtils': {
        'IterateGenericEditableConfigValues',
        'GetConfigValueInfo'
    }
}

simple_type_map = {
  'char',
  'SteamDatagramRelayAuthTicket',
  'ISteamHTMLSurface::EHTMLMouseButton',
  'ISteamHTMLSurface::EHTMLKeyModifiers',
  'ISteamNetworkingConnectionSignaling',
  'ISteamNetworkingSignalingRecvContext',
  'CSteamID',
  'intptr_t',
  'size_t',
  'void', 
  'bool', 
  'int32_t', 
  'int64_t', 
  'float', 
  #'const char*',
  #'const void*', 
  #'int&', 
  'unsigned int',
  'CGameID',
  'int',
  'double',
  'SteamAPIWarningMessageHook_t',
  'unsigned short',
}


type_map = {}

text = read_json_file_as_text("../src/srcs/steam_api.json")

api = read_json_file("../src/srcs/steam_api.json")

print('#include "SteamGodot.cpp"')
print("namespace godot {")

for key in simple_type_map:
    type_map[key] = Class(key, [], [], Type.POINTER, {}, False, "")

#type_map["CSteamID"] = Class("CSteamID", [], [], Type.POINTER, {}, False, "::")

for enum in api["enums"]:
    clazz = Class(enum["enumname"], [], [], Type.POINTER, {}, False, "::")

    for key in enum["values"]:
        clazz.enum[key["name"]] = key["value"]

    type_map[enum["enumname"]] = clazz

for typedef in api["typedefs"]:
    if not typedef["typedef"] in type_map:
        clazz = structs_to_class(typedef, typedef_mapping)
        type_map[clazz.data_type] = clazz

for struct in api["structs"]:
    clazz = structs_to_class(struct)   
    type_map[clazz.data_type] = clazz

for struct in api["callback_structs"]:
    clazz = structs_to_class(struct)   
    type_map[clazz.data_type] = clazz

ll = 0
for struct in api["interfaces"]:
    clazz = structs_to_class(struct, interface_mapping)   
    #clazz.interface = True
    type_map[clazz.data_type] = clazz
    ll += 1

    if ll > 0:
        break

    #out_class(res)

types_tmp = copy.copy(type_map)

for type in types_tmp:
    const = copy.copy(type_map[type])
    const.data_type = const.data_type + ' const*'
    type_map[const.data_type] = const

for type in type_map:
    if type_map[type].data_type != "void":
        out_pre_class(type_map[type])

for type in type_map:
    if type_map[type].data_type != "void":
        out_class(type_map[type])

for type in type_map:
    if type_map[type].data_type != "void":
        out_class_methods(type_map[type])

out("}")

#if bool(unknowns_types):
#    print(unknowns_types)
