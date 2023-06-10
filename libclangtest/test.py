import clang.cindex
import model
import out


c = []

extract = {"ISteamUtils"}

dependencies = set()

db = {}

def read_property(cursor) -> model.Property:
    property = model.Property(
        cursor.type.spelling, 
        cursor.spelling, 
        cursor.type.is_const_qualified(),
        cursor.type.get_array_size())
    
    if not property.name in dependencies:
        dependencies.add(property.name)
    
    return property

def read_return_type(cursor) -> model.Property:
    property = model.Property(
        cursor.result_type.spelling, 
        "", 
        cursor.result_type.is_const_qualified(),
        cursor.result_type.get_array_size())
    
    if not property.name in dependencies:
        dependencies.add(property.name)
    
    return property

def print_function_info(cursor):
    method = model.Method(cursor.spelling)
    method.return_type = read_return_type(cursor.result_type)

    for arg in cursor.get_arguments():
        property = read_property(arg)
        method.params.append(property)

    db[cursor.lexical_parent.spelling].methods.append(method)

def read_feild(cursor):
    if cursor.lexical_parent.spelling in db:
        db[cursor.lexical_parent.spelling].properties.append(read_property(cursor))

def visit(cursor):
    if cursor.kind == clang.cindex.CursorKind.CLASS_DECL or cursor.kind == clang.cindex.CursorKind.STRUCT_DECL:
        if 'unnamed' in cursor.spelling or 'anonymous' in cursor.spelling:
            return

        clazz = model.Class(read_type(cursor.spelling))
        db[cursor.spelling] = clazz

        c.append(cursor.spelling)
        for child in cursor.get_children():
            visit(child)
        c.pop()

    elif cursor.kind == clang.cindex.CursorKind.CXX_METHOD and bool(c):
        print_function_info(cursor)

    elif cursor.kind == clang.cindex.CursorKind.FIELD_DECL and bool(c):
        read_feild(cursor)

    else:
        for child in cursor.get_children():
            visit(child)

def main():
    index = clang.cindex.Index.create()
    translation_unit = index.parse('../lib/steam-sdk/public/steam/steam_api.h', ['-x', 'c++'])

    visit(translation_unit.cursor)

    out.log(dependencies)

    #print(db)

if __name__ == "__main__":
    main()

    to_out = {}
    for dependency in dependencies:
        if dependency in db:
            to_out[dependency] = db[dependency]   

    out.print_db(to_out)