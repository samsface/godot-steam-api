import re

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

def to_godot_class_name(str):
    if str[:6] == "ISteam":
        str = str[6:]

    if str.endswith('_t'):
        str = str[:-2]
    
    if str[:5] != "Steam":
        str = "Steam" + str
    
    return str

def map_type_from_steam_to_godot(steam_type):
    if '&' in steam_type:
        return "VOID"

    search = type_map.get(steam_type)
    if search:
        return search
    
    if "*" in steam_type:
        return "Array"

    regex_to_remove_array = r"\s*\[\d+\]"
    without_array = re.sub(regex_to_remove_array, "", steam_type)
    return type_map[without_array]

def remove_ref(str):
    class_name_sans_ref = re.sub(r'Ref<', "", str)
    class_name_sans_ref = re.sub(r'>', "", class_name_sans_ref)
    return class_name_sans_ref

# interfaces

def write_interface_param(param):
    res = camel_to_snake_case(param["paramname"])

    type = map_type_from_steam_to_godot(param["paramtype"])

    if type == "String":
        res += ".utf8().get_data()"
    elif type[:3] == "Ref":
        res += ".get()"

    return res

def write_interface_method(method):
    res = map_type_from_steam_to_godot(method["returntype"])
    res += " " + camel_to_snake_case(method["methodname"])
    res += "("

    if bool(method["params"]):
        for param in method["params"]:
            res += map_type_from_steam_to_godot(param["paramtype"])
            res += " " + camel_to_snake_case(param["paramname"])
            res += ", "
        res = res[:-2]
    res += ")\n"
    res += "{\n"

    if method["returntype"] == "void":
        pass
    elif method["returntype"] == "SteamAPICall_t":
        res += "auto call = "
    else:
        res += "return "

    res += "interface_->" + method["methodname"]
    res += "("

    if bool(method["params"]):
        for param in method["params"]:
            res += write_interface_param(param)
            res += ", "
        res = res[:-2]
    res += ");\n"

    if method["returntype"] == "SteamAPICall_t":
        res += "return SteamCallback::make<" + method["callresult"] + ", Steam" + method["callresult"][:-2] + ">(call);\n"

    res += "}"

    return res

def write_interface_register_methods_function(interface):
    class_name = remove_ref(map_type_from_steam_to_godot(interface["classname"]))

    res = "static void _register_methods()\n"
    res += "{\n"

    for method in interface["methods"]:
        function_name = camel_to_snake_case(method["methodname"])
        res += f'register_method("{function_name}", &{class_name}::{function_name});\n'

    res += "}\n"

    return res

def write_interface(interface):
    class_name = remove_ref(map_type_from_steam_to_godot(interface["classname"]))

    res = f'class {class_name} : public Reference\n'
    res += "{\n"
    res += f'GODOT_CLASS({class_name}, Reference)\n\n'
    res += f'{interface["classname"]}* interface_{{}};\n\n'

    for method in interface["methods"]:
        res += write_interface_method(method)
        res += "\n\n"

    res += "public:\n"

    res += write_interface_register_methods_function(interface)

    res += "};\n"
    
    return res

# callbacks

def write_callback_field(field):
    class_name = map_type_from_steam_to_godot(field["fieldtype"])
  
    res = class_name
    res += " get_" + camel_to_snake_case(field["fieldname"])
    res += "()\n"
    res += "{\n"

    if field["fieldtype"] in simple_type_map:
        res += f'return data.{field["fieldname"]};\n' 
    else:
        res += f'return {remove_ref(class_name)}::make(data.{field["fieldname"]});\n' 

    res += "}\n"

    return res

def write_callback_register_methods_function(callback):
    if not "struct" in callback:
        return ""

    class_name = remove_ref(map_type_from_steam_to_godot(callback["struct"]))

    res = "static void _register_methods()\n"
    res += "{\n"

    for method in callback["fields"]:
        function_name = camel_to_snake_case(method["fieldname"])
        res += f'register_method("get_{function_name}", &{class_name}::get_{function_name});\n'

    res += "}\n"

    return res

def write_callback(callback):
    class_name = remove_ref(map_type_from_steam_to_godot(callback["struct"]))

    res = f'class {class_name} : public SteamBase<{callback["struct"]}, {class_name}>\n'
    res += "{\n"
    res += f'GODOT_CLASS({class_name}, Reference)\n\n'

    for field in callback["fields"]:
        res += write_callback_field(field)
        res += "\n"

    res += "public:\n"

    res += write_callback_register_methods_function(callback)

    res += "};\n"
    
    return res

# typedefs

simple_type_map = {
    "unsigned short": "int",
    "unsigned int": "int",
    "void *": "void *",
    "void": "void",
    "int": "int",
    "float": "float",
    "double": "double",
    "bool": "bool",
    "uint8":"int",
    "int8":"int", 
    "int16":"int",
    "uint16":"int", 
    "int32":"int", 
    "uint32":"int", 
    "int64":"int", 
    "uint64":"int",
    "char":"String",
    "char*":"String",
    "char *":"String",
    "const char *": "String",
    "CSteamID": "Ref<SteamID>",
    "CGameID": "CGameID",
    "PublishedFileId_t": "String",
    "RequestPlayersForGameResultCallback_t::PlayerAcceptState_t": "int",
    "HSteamPipe *":"",
    "SteamAPIWarningMessageHook_t": "int", # this is missing from api json
    "ISteamHTMLSurface::EHTMLMouseButton": "int",
    "ISteamHTMLSurface::EHTMLKeyModifiers": "int",
    "intptr_t": "int",
    "SteamAPICall_t": "Ref<SteamCallback>"
}

type_map = simple_type_map.copy()

def write_typedef(typedef):
    if typedef["typedef"] in simple_type_map:
        return ""
    
    class_name = to_godot_class_name(typedef["typedef"])

    res = f'class {class_name} : public SteamBase<{typedef["type"]}, {class_name}>\n'
    res += "{\n"
    res += f'GODOT_CLASS({class_name}, Reference)\n'

    res += "public:\n"

    res += write_callback_register_methods_function({"fields": []})

    res += "};\n"
    
    return res

import json

def read_json_file(file_path):
    with open(file_path, 'r') as file:
        json_content = file.read()
        json_dict = json.loads(json_content)
        return json_dict

api = read_json_file("src/srcs/steam_api.json")

print('#include "SteamGodot.cpp"')
print("namespace godot {")

for enum in api["enums"]:
    type_map[enum["enumname"]] = "int"

for typedef in api["typedefs"]:
    if not typedef["typedef"] in type_map:
        type_map[typedef["typedef"]] = f'Ref<{to_godot_class_name(typedef["typedef"])}>'

for struct in api["structs"]:
    type_map[struct["struct"]] = f'Ref<{to_godot_class_name(struct["struct"])}>'

for callback_struct in api["callback_structs"]:
    type_map[callback_struct["struct"]] = f'Ref<{to_godot_class_name(callback_struct["struct"])}>'

for interface in api["interfaces"]:
    type_map[interface["classname"]] = f'Ref<{to_godot_class_name(interface["classname"])}>'
    type_map[interface["classname"] + " *"] = f'Ref<{to_godot_class_name(interface["classname"])}>'

#print(json.dumps(type_map, indent=3))

for t in api["typedefs"]:
    print(write_typedef(t))

for c in api["callback_structs"]:
    print(write_callback(c))

for i in api["interfaces"]:
    print(write_interface(i))

print("}\n")
