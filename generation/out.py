import model
import re
import subprocess

file = None

def out(str):
    file.write(str + "\n")

def log(s):
    file.write("/* " + str(s) + " */\n")

def run_clang_format(file_path):
    try:
        # Run clang-format command
        subprocess.run(['clang-format', '-i', file_path], check=False)
        print(f"clang-format successfully applied to {file_path}")
    except subprocess.CalledProcessError as e:
        print(f"An error occurred while running clang-format on {file_path}: {e}")

def out_class_predecleration(struct:model.Object):
    if struct.handwritten:
        log(f'ignore handwritten: {struct.cpp_type}')
        return

    out(f'class {struct.inter_type};')

def wrap(param:model.Object) -> str:
    if param.is_output_param:
        return f'Ref<Reference> /* {param.cpp_type} */'

    if param.kind == model.Type.STRING:
        return f'String /* {param.cpp_type} */'

    if param.is_buffer:
        return f'PoolByteArray /* {param.cpp_type} */'

    if param.kind == model.Type.INTEGER:
        return f'int /* {param.cpp_type} {param.kind} */'
    
    if param.kind == model.Type.ENUM:
        return f'int /* {param.cpp_type} {param.kind} */'

    if param.kind == model.Type.BOOL:
        return f'bool /* {param.cpp_type} {param.kind} */'

    return f'Ref<{param.inter_type}> /* {param.cpp_type} {param.kind} */'

def wrap2(param:model.Object) -> str:
    if param.is_buffer:
        if param.const:
            return f'reinterpret_cast<{param.cpp_type}>({param.name}.read().ptr())'
        else:
            return f'reinterpret_cast<{param.cpp_type}>({param.name}.write().ptr())'

    if param.is_output_param:
        return f'&{param.name}'

    if param.size_for:
        return f'{param.size_for.name}.size()'

    if param.kind == model.Type.STRING:
        return param.name + '.utf8().get_data()'


    if param.kind == model.Type.INTEGER:
        return param.name
    
    if param.kind == model.Type.BOOL:
        return param.name

    if param.kind == model.Type.ENUM:
        return f'static_cast<{param.cpp_type}>({param.name})'

    if "**" in param.cpp_type:
        return param.name + "->get_array()"
    if "*" in param.cpp_type:
        return param.name + "->get_ptr()"
    else:
        return param.name + "->get()"

def out_params(params:list):
    out('(')

    comma_needed = False
    for param in params:
        if param.size_for and not param.size_for.is_output_param:
            continue
        if param.is_output_param:
            continue

        out(f'{", " if comma_needed else ""}{wrap(param)} {param.name}')
        comma_needed = True

    out(')')

def out_class_method_decleration(method:model.Method, struct:model.Object):
    out(f"""auto /*{method.return_type.cpp_type}*/ {method.name}""")
    out_params(method.params)
    out(";")

def out_class_method_defenition(method:model.Method, struct:model.Object):
    out(f"""
        auto /* {method.return_type.cpp_type}, {method.return_type.kind} */ {struct.inter_type}::{method.name}""")
    out_params(method.params)
    out('{')

    for param in method.params:
        if param.is_output_param:
            t = param.cpp_type

            if param.is_buffer:
                t = "PoolByteArray"

            elif param.kind == model.Type.INTEGER or param.kind == model.Type.REAL or param.kind == model.Type.BOOL or param.kind == model.Type.ENUM or param.kind == model.Type.OBJECT:
                if not 'void' in param.cpp_type:
                    t = t.replace('*', "")

            out(f'{t} /* {param.cpp_type}, {param.kind} */ {param.name}{{}};')

            if param.is_buffer:
                out(f'{param.name}.resize({param.buffer_size.name});')

    out(f'return call<{method.return_type.inter_type}>([&](auto data__){{')

    out(f'return data__->{method._name}(')

    # pass paramters
    comma_needed = False
    for param in method.params:
        out(f'{", " if comma_needed else ""}{wrap2(param)}')
        comma_needed = True

    out(");});")

    out("}\n")

def out_class_property_decleration(property:model.Object, struct:model.Object):
    out(f"""auto /*{property.cpp_type} */ get_{property.name}();""")

def out_class_property_defenition(property:model.Object, struct:model.Object):
        out(f"""
auto {struct.inter_type}::get_{property.name}()
{{
    return cast<{property.inter_type} /* {property.cpp_type} */>(get_ptr()->{property.name});
}}
""")

def out_class_register_methods_defenition(struct:model.Object):
    out(f"""
        void {struct.inter_type}::_register_methods()""")
    out('{')

    for property in struct.properties:
        out(f'register_method("get_{property.name}", &{struct.inter_type}::get_{property.name});')

    for method in struct.methods:
        out(f'register_method("{method.name}", &{struct.inter_type}::{method.name});')

    out('}')

def out_class_decleration(struct:model.Object):
    if struct.handwritten:
        return

    out(f"""
class {struct.inter_type} : public SteamBase<{struct.cpp_type}, {struct.inter_type}>
{{
GODOT_CLASS({struct.inter_type}, Reference)
public:
    static void _register_methods();
    void _init() {{}}
""")

    log("fields")
    for property in struct.properties:
        out_class_property_decleration(property, struct)

    for method in struct.methods:
        out_class_method_decleration(method, struct)

    out('};')

def print_db(db:dict):
    global file

    file = open('src/generated.cpp', 'w')

    if "void" in db:
        del db["void"]

    out('#include "pre.cpp"')

    out('namespace godot {')

    for clazz in db:
        out_class_predecleration(db[clazz])

    for clazz in db:
        out_class_decleration(db[clazz])

    for clazz in db:
        if db[clazz].handwritten:
            continue

        for property in db[clazz].properties:
            out_class_property_defenition(property, db[clazz])

        for method in db[clazz].methods:
            out_class_method_defenition(method, db[clazz])
        
        out_class_register_methods_defenition(db[clazz])
    
    out('}')
    out('#include "post.cpp"')

    out('namespace godot {')
    out_footer(db)
    out('}')

    file.close()

    run_clang_format('src/generated.cpp')

    for clazz in db:
        out_gdns_file(db[clazz].inter_type)

    out_gdnlib_file('steam_api', 'steamsdk')

def out_footer(db):
    out("""
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
""")
    
    for clazz in db:
        out(f'godot::register_class<godot::{db[clazz].inter_type}>();')
       
    out("}\n")

def out_gdns_file(name:str):
    global file

    with open(f'src/gdns/{name}.gdns', 'w') as file:
 
        out(f"""[gd_resource type="NativeScript" load_steps=2 format=2]

[ext_resource path="res://addons/steam_api/gdns/steam_api.gdnlib" type="GDNativeLibrary" id=1]

[resource]
resource_name = "{name}"
class_name = "{name}"
library = ExtResource( 1 )
script_class_name = "{name}"
""")

def out_gdnlib_file(name, libname):
    global file

    with open(f'src/gdns/{name}.gdnlib', 'w') as file:
        out(f"""[general]

singleton=false
load_once=true
symbol_prefix="godot_"
reloadable=true

[entry]

OSX.64="res://addons/{name}/lib{libname}-godot.dylib"
Windows.64="res://addons/{name}/{libname}-godot.dll"
X11.64="res://addons/{name}/lib{libname}-godot.so"
Server="res://addons/{name}/lib{libname}-godot.so"

[dependencies]

OSX.64=[ "res://addons/steam_api/libsteam_api.dylib" ]
Windows.64=[ "res://addons/steam_api/steam_api64.dll" ]
X11.64=[ "res://addons/steam_api/libsteam_api.so" ]
Server=[ "res://addons/steam_api/libsteam_api.so" ]
""")
