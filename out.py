import model
import re

def out(str):
    print(str)

def log(s):
    print("/* " + str(s) + " */")

def out_class_predecleration(struct:model.Class):
    out(f'class {struct.name};')

def wrap(type_str:str) -> str:
    const = 'const' in type_str
    pointer = '*' in type_str

    # output param
    if pointer and not const:
        type_str = re.sub(r'\*', '', type_str)

    return f'Ref<{model.safe_name(type_str)}> /* {type_str} */'

def wrap2(param:model.Property) -> str:
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

def out_class_method_decleration(method:model.Method, struct:model.Class):
    out(f"""auto /*{method.return_type.type}*/ {method.name}""")
    out_params(method.params)
    out(";")


def out_class_method_defenition(method:model.Method, struct:model.Class):
    out(f"""
        auto /* {method.return_type.type} */ {struct.name}::{method.name}""")
    out_params(method.params)
    out('{')

    if True:
        out(f"""
            
        return call<{method.return_type.safe_type}>([](auto* data, auto&& ...args)
        {{
            return data->{method._name}(args...);
        }}""")

        # pass paramters
        for param in method.params:
            out(f', {wrap2(param)}')

        out(");")

    out("}\n")

def out_class_property_decleration(property:model.Property, struct:model.Class):
    out(f"""auto /*{property.type} */ get_{property.name}();""")

def out_class_property_defenition(property:model.Property, struct:model.Class):
        out(f"""
auto {struct.name}::get_{property.name}()
{{
    return cast<{property.safe_type} /* {property.type} */>(get_ptr()->{property.name});
}}
""")

def out_class_decleration(struct:model.Class):
    out(f"""
class {struct.name} : public SteamBase<{struct.data_type}, {struct.name}>
{{
GODOT_CLASS({struct.name}, Reference)
public:
    static void _register_methods();
    void _init() {{}}
""")

    log("fields")
    for property in struct.properties:
        out_class_property_decleration(property, struct)

    log("methods")
    for method in struct.methods:
        out_class_method_decleration(method, struct)

    out('};')

def print_db(db:dict):
    if "void" in db:
        del db["void"]

    out('#include "SteamGodot.cpp"')

    out('namespace godot {')

    for clazz in db:
        out_class_predecleration(db[clazz])

    for clazz in db:
        out_class_decleration(db[clazz])

    for clazz in db:
        for property in db[clazz].properties:
            out_class_property_defenition(property, db[clazz])
        for method in db[clazz].methods:
            out_class_method_defenition(method, db[clazz])
    
    out('}')