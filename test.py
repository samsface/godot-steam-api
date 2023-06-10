import clang.cindex
import model
import out


c = []

extract = {"ISteamUtils"}

dependencies = {}

db = {}

def read_property(cursor) -> model.Property:
    property = model.Property(
        cursor.type.get_canonical().spelling, 
        cursor.spelling, 
        cursor.type.is_const_qualified(),
        cursor.type.get_array_size())
    
    if "union CSteamID::SteamID_t" in property.type:
        return model.Property("CSteamID")

    if not property.name in dependencies:
        add_dependancy(property)
    
    return property

def read_return_type(cursor) -> model.Property:
    property = model.Property(
        cursor.result_type.spelling, 
        "", 
        cursor.result_type.is_const_qualified(),
        cursor.result_type.get_array_size())
   
    if not property.name in dependencies:
        add_dependancy(property)
    
    return property

def add_dependancy(property):
    if 'unnamed' in property.type:
        return
    
    #if '&' in property.type and 'const' in property.type:
    #    return

    dependencies[property.type] = property

def print_function_info(cursor):
    if 'operator' in cursor.spelling:
        return

    method = model.Method(cursor.spelling)
    method.return_type = read_return_type(cursor)

    for arg in cursor.get_arguments():
        method.params.append(read_property(arg))

    db[cursor.lexical_parent.spelling].methods.append(method)

def read_feild(cursor):
    if cursor.lexical_parent.spelling in db:
        db[cursor.lexical_parent.spelling].properties.append(read_property(cursor))

def read_typedef(cursor):
    db[cursor.spelling] = model.Class(cursor.type.spelling)

def visit(cursor):
    if cursor.access_specifier == clang.cindex.AccessSpecifier.PRIVATE:
          return
     
    if cursor.kind == clang.cindex.CursorKind.CLASS_DECL or cursor.kind == clang.cindex.CursorKind.STRUCT_DECL:
        clazz = model.Class(cursor.type.spelling)
        db[cursor.type.spelling] = clazz

        c.append(cursor.type.spelling)
        for child in cursor.get_children():
            visit(child)
        c.pop()

    elif cursor.kind == clang.cindex.CursorKind.CXX_METHOD and bool(c):
        print_function_info(cursor)

    elif cursor.kind == clang.cindex.CursorKind.FIELD_DECL and bool(c):
        read_feild(cursor)

    elif cursor.kind == clang.cindex.CursorKind.TYPEDEF_DECL:
        read_typedef(cursor)

    else:
        for child in cursor.get_children():
            visit(child)

def main():
    index = clang.cindex.Index.create()
    translation_unit = index.parse('../lib/steam-sdk/public/steam/steam_api.h', ['-x', 'c++'])

    visit(translation_unit.cursor)

    for dependency in dependencies:
         if not dependency in db:
            db[dependency] = model.Class(dependency)

    #out.log(dependencies)

    #print(db)

if __name__ == "__main__":
    main()

    to_out = {}
    for dependency in dependencies:
        if dependency in db:
            to_out[dependency] = db[dependency]   

    out.print_db(to_out)