import model

file = None

def out(str):
    file.write(str)

def log(s):
    file.write("# " + str(s))

def out_proxy():
    out("""extends Node
class_name SteamI

class OutBool:
	var value:bool

class OutInt:
	var value:int
	
class OutFloat:
	var value:float

class OutString:
	var value:String

class OutPoolByteArray:
	var value:PoolByteArray

class OutPoolIntArray:
	var value:PoolIntArray

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

def out_class(clazz:model.Object):
    out(f"""class {clazz.godot_type_name} extends Proxy_:
    func _init(o).(o) -> void:
        pass

""")

    for method in clazz.methods:
        out(f'    func {method.godot_name}(')
        
        comma = model.Comma()
        dupe_protector = model.DupeProtector()
        for param in method.params:
            if param.size_for:
                continue

            out(f'{comma.comma()}{dupe_protector.get(param.godot_name)}{param.godot_type_hint}')

        out(f') -> {method.return_type.godot_type}:\n')
    
        out(f'        {"" if method.return_type.is_void else "return "}call_("{method.name}", [')

        comma.clear()
        dupe_protector.clear()
        for param in method.params:
            if param.size_for:
                continue

            out(f'{comma.comma()}{dupe_protector.get(param.godot_name)}')
    
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
