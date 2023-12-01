import clang.cindex
from clang.cindex import TypeKind
import model
import proc
import out
import out_gdscript

c = []

extract = {"ISteamUtils"}

db = {}

db["SteamAPI"] = model.Object("SteamAPI", handwritten=True)
db["SteamAPICall_t"] = model.Object("SteamAPICall_t", handwritten=True)
db["void"] = model.Object("void", handwritten=True)

always_box = {
   'SteamAPICall_t'
}

undefined_symbols = [
    # private symbols
    'BValidExternalSteamID',
    'Render',
    'SetFromString',
    'SetFromSteam',
    'SetFromStringStrict',
    'ValidExternalSteamID',

    # undocumented
    'GetAchievementProgressLimits',

    # unsupported
    'GetGlobalStatHistory',
    'SetIPAddr',
    'operator',
    'GetAPICallResult'
]

def is_void_type(type_kind):
    return type_kind == TypeKind.VOID

def is_bool_type(type_kind):
    return type_kind == TypeKind.BOOL

def is_enum_type(type_kind):
    return type_kind == TypeKind.ENUM

def is_int_type(type_kind):
    return type_kind in [
        TypeKind.CHAR_U,
        TypeKind.UCHAR,
        TypeKind.CHAR16,
        TypeKind.CHAR32,
        TypeKind.USHORT,
        TypeKind.UINT,
        TypeKind.ULONG,
        TypeKind.ULONGLONG,
        TypeKind.CHAR_S,
        TypeKind.SCHAR,
        TypeKind.WCHAR,
        TypeKind.SHORT,
        TypeKind.INT,
        TypeKind.LONG,
        TypeKind.LONGLONG
    ]

def is_function_pointer(pointee):
    return pointee.kind == TypeKind.FUNCTIONPROTO

def is_float_type(type_kind):
    return type_kind in [TypeKind.FLOAT, TypeKind.DOUBLE]

def is_pointer_type(type_kind):
    return type_kind == TypeKind.POINTER

def get_type(cursor, result=False):
    if not result:
        type_kind = cursor.type.get_canonical().kind
        type_spelling = cursor.type.get_canonical().spelling
        pointee = cursor.type.get_canonical().get_pointee()
    else:
        type_kind = cursor.result_type.get_canonical().kind
        pointee = cursor.result_type.get_canonical().get_pointee()
        type_spelling = cursor.result_type.spelling

    if is_function_pointer(pointee):
        raise Exception("no support for function pointers atm")
        return model.Type.FUNCTION

    if type_spelling in always_box:        
        return model.Type.OBJECT

    if is_pointer_type(type_kind):
        type_kind = pointee.kind
        if type_kind == TypeKind.CHAR_S and pointee.is_const_qualified():
            return model.Type.STRING

    if is_float_type(type_kind):
        return model.Type.REAL

    if is_bool_type(type_kind):
        return model.Type.BOOL

    if is_int_type(type_kind):
        return model.Type.INTEGER

    if is_enum_type(type_kind):
        return model.Type.ENUM
    
    if is_void_type(type_kind):
        return model.Type.VOID

    return model.Type.OBJECT

def read_property(cursor) -> model.Object:
    property = model.Object(
        cursor.type.get_canonical().spelling, 
        cursor.spelling, 
        cursor.type.get_canonical().get_pointee().is_const_qualified(),
        cursor.type.get_array_size(),
        kind=get_type(cursor),
        is_pointer=is_pointer_type(cursor.type.get_canonical().kind))

    if "union CSteamID::SteamID_t" in property.cpp_type:
        property = model.Object("CSteamID")

    add_dependancy(property)
    
    return property

def read_return_type(cursor) -> model.Object:
    property = model.Object(
        cursor.result_type.spelling, 
        "", 
        cursor.type.get_canonical().get_pointee().is_const_qualified(),
        cursor.result_type.get_array_size(),
        kind=get_type(cursor, True),
        is_pointer=is_pointer_type(cursor.result_type.get_canonical().kind))
   
    add_dependancy(property)
    
    return property

def add_dependancy(property):
    if 'unnamed' in property.cpp_type:
        raise Exception("cannot bind unamed stuff")

    if 'locale' in property.cpp_type:
        raise Exception("cannot bind _locale_t stuff")

    if property.cpp_type in db:
        return db[property.cpp_type]
    else:
        db[property.cpp_type] = property
        return property

def read_function(cursor):
    if cursor.storage_class == clang.cindex.StorageClass.STATIC:
        return

    for symbol in undefined_symbols:
        if symbol in cursor.spelling:
            return

    method = model.Method(cursor.spelling)
    method.return_type = read_return_type(cursor)

    for arg in cursor.get_arguments():
        method.params.append(read_property(arg))

    model.correct_overloads(method, db[cursor.lexical_parent.spelling].methods)

    db[cursor.lexical_parent.spelling].methods.append(method)

def read_feild(cursor):
    if cursor.lexical_parent.spelling in db:
        db[cursor.lexical_parent.spelling].properties.append(read_property(cursor))

def read_typedef(cursor):
    add_dependancy(model.Object(cursor.type.spelling))

def read_enum(cursor):
    object = add_dependancy(model.Object(cpp_type=cursor.type.spelling, name=cursor.type.spelling, kind=model.Type.ENUM))

    for child in cursor.get_children():
        if child.kind == clang.cindex.CursorKind.ENUM_CONSTANT_DECL:
            object.enums.append((child.spelling, child.enum_value))

def visit(cursor):
    if cursor.access_specifier == clang.cindex.AccessSpecifier.PRIVATE:
          return
    if cursor.access_specifier == clang.cindex.AccessSpecifier.PROTECTED:
          return
     
    if cursor.kind == clang.cindex.CursorKind.CLASS_DECL or cursor.kind == clang.cindex.CursorKind.STRUCT_DECL:
        try:
            clazz = model.Object(cursor.type.spelling)
            add_dependancy(clazz)

            if db[clazz.cpp_type].handwritten:
                return

            c.append(cursor.type.spelling)
            for child in cursor.get_children():
                visit(child)
            c.pop()
        except Exception as e:
            print(e)

    elif cursor.kind == clang.cindex.CursorKind.ENUM_DECL:
        try:
            read_enum(cursor)
        except Exception as e:
            print(e)

    elif cursor.kind == clang.cindex.CursorKind.CXX_METHOD and bool(c):
        try:
            read_function(cursor)
        except Exception as e:
            print(e)

    elif cursor.kind == clang.cindex.CursorKind.FIELD_DECL and bool(c):
        try:
            read_feild(cursor)
        except Exception as e:
            print(e)

    elif cursor.kind == clang.cindex.CursorKind.TYPEDEF_DECL:
        try:
            read_typedef(cursor)
        except Exception as e:
            print(e)
    else:
        for child in cursor.get_children():
            visit(child)


def get_dependancies(type) -> set:
    res = set()
    res.add(type)

    struct = db[type]

    if hasattr(struct, 'properties'):
        for property in struct.properties:
            res = res | get_dependancies(property.cpp_type)

    if hasattr(struct, 'methods'):
        for method in struct.methods:
            res = res | get_dependancies(method.return_type.cpp_type)

            for param in method.params:
                res = res | get_dependancies(param.cpp_type)

    return res

def main():
    index = clang.cindex.Index.create()
    translation_unit = index.parse('lib/steam-sdk/public/steam/steam_api.h', ['-x', 'c++'])

    visit(translation_unit.cursor)

    db2 = { "SteamAPI": db["SteamAPI"] }
    for d in (get_dependancies('ISteamUtils') | get_dependancies('ISteamUserStats')):
        db2[d] = db[d]

    proc.optimize(db2)

    out.print_db(db2)
    out_gdscript.print_db(db2)

if __name__ == "__main__":
    main()
