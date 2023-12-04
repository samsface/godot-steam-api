import model

file = None

def out(str):
    file.write(str)

def log(s):
    file.write("# " + str(s))

def out_proxy():
    out("""extends Node
class_name SteamI

class Callback:
    signal done

class Proxy_:
    signal keep_alive_hack_
    
    var object_to_proxy_

    func _init(object_to_proxy) -> void:
        object_to_proxy_ = object_to_proxy

    func call_(func_name, args := []):
        if not object_to_proxy_:
            return
        
        return object_to_proxy_.callv(func_name, args)
        
    func callback_(func_name, args := []):
        if not object_to_proxy_:
            var result = Callback.new()
            result.call_deferred("emit_signal", "done", null)
            call_deferred("emit_signal", "keep_alive_hack_", result)
            return result

        return object_to_proxy_.callv(func_name, args)

""")
        
def enum_name(object:model.Object, e:str) -> str:
    e = e.replace(object.cpp_type, '')
    return model.snake_case(e)

def out_enum_type(object:model.Object) -> None:
    out(f"""enum {object.godot_type_name} {{\n""")

    for e in object.enums:
        out(f"""    {enum_name(object, e[0])} = {e[1]},\n""")

    out("}\n\n")

def out_return_class(method:model.Method):
    out(f'    class {method.godot_return_type}:\n')

    dupe_protector = model.DupeProtector()

    if method.return_type:
        out(f'        {dupe_protector.get("error")}{method.return_type.godot_type_hint}\n')

    for param in method.output_params:
        out(f'        {dupe_protector.get(param.godot_name)}{param.godot_type_hint}\n')

    out('\n')

def out_class(clazz:model.Object):
    out(f"""class {clazz.godot_type_name} extends Proxy_:
    func _init(o).(o) -> void:
        pass

""")

    for method in clazz.methods:
        
        # Check if we have output params and print a result class if so
        if bool(method.output_params):
            out_return_class(method)

        out(f'    func {method.godot_name}(')
        
        # Print the function's params
        comma = model.Comma()
        dupe_protector = model.DupeProtector()
        for param in method.params:
            if param.size_for:
                continue

            if param.is_output_param:
                continue

            out(f'{comma.comma()}{dupe_protector.get(param.godot_name)}{param.godot_type_hint}')

        out(f') -> {method.godot_return_type}:\n')
    
        out(f'        {"" if method.return_type.is_void else "return "}call_("{method.name}", [')

        comma.clear()
        dupe_protector.clear()
        for param in method.params:
            if param.size_for:
                continue

            if param.is_output_param:
                continue

            out(f'{comma.comma()}{dupe_protector.get(param.godot_name)}')
    
        if bool(method.output_params):
            out(f'{comma.comma()}{method.godot_return_type}.new()')

        out('])\n\n')

def print_db(db:dict):
    global file

    file = open('src/steam_i.gd', 'w')

    out_proxy()

    for clazz in db:
        if db[clazz].is_enum:
            out_enum_type(db[clazz])

    for clazz in db:
        if not db[clazz].is_enum:
            out_class(db[clazz])
