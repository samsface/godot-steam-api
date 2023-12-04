import clang.cindex
from clang.cindex import TypeKind
import model
import re

extract = {"ISteamUtils"}

class ILBuilder:
    db = {}

    c = []

    always_box = {
        'SteamAPICall_t'
    }

    def seed(self):
        self.db["SteamAPI"] = model.Object("SteamAPI", handwritten=True)
        self.db["SteamAPICall_t"] = model.Object("SteamAPICall_t", handwritten=True)
        self.db["void"] = model.Object("void", handwritten=True)

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

    def is_void_type(self, type_kind):
        return type_kind == TypeKind.VOID

    def is_bool_type(self, type_kind):
        return type_kind == TypeKind.BOOL

    def is_enum_type(self, type_kind):
        return type_kind == TypeKind.ENUM

    def is_int_type(self, type_kind):
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

    def is_function_pointer(self, pointee):
        return pointee.kind == TypeKind.FUNCTIONPROTO

    def is_float_type(self, type_kind):
        return type_kind in [TypeKind.FLOAT, TypeKind.DOUBLE]

    def is_pointer_type(self, type_kind):
        return type_kind == TypeKind.POINTER

    def get_type(self, cursor, result=False):
        if not result:
            type_kind = cursor.type.get_canonical().kind
            type_spelling = cursor.type.get_canonical().spelling
            pointee = cursor.type.get_canonical().get_pointee()
        else:
            type_kind = cursor.result_type.get_canonical().kind
            pointee = cursor.result_type.get_canonical().get_pointee()
            type_spelling = cursor.result_type.spelling

        if self.is_function_pointer(pointee):
            raise Exception("no support for function pointers atm")
            return model.Type.FUNCTION

        if type_spelling in self.always_box:        
            return model.Type.OBJECT

        if self.is_pointer_type(type_kind):
            type_kind = pointee.kind
            if type_kind == TypeKind.CHAR_S:# and pointee.is_const_qualified():
                return model.Type.STRING

        if self.is_float_type(type_kind):
            return model.Type.REAL

        if self.is_bool_type(type_kind):
            return model.Type.BOOL

        if self.is_int_type(type_kind):
            return model.Type.INTEGER

        if self.is_enum_type(type_kind):
            return model.Type.ENUM
        
        if self.is_void_type(type_kind):
            return model.Type.VOID

        return model.Type.OBJECT

    def read_property(self, cursor) -> model.Object:
        property = model.Object(
            cursor.type.get_canonical().spelling, 
            cursor.spelling, 
            cursor.type.get_canonical().get_pointee().is_const_qualified(),
            cursor.type.get_array_size(),
            kind=self.get_type(cursor),
            is_pointer=self.is_pointer_type(cursor.type.get_canonical().kind))

        if "union CSteamID::SteamID_t" in property.cpp_type:
            property = model.Object("CSteamID")

        self.add_to_db(property)
        
        return property

    def read_return_type(self, cursor) -> model.Object:
        property = model.Object(
            cursor.result_type.spelling, 
            "", 
            cursor.type.get_canonical().get_pointee().is_const_qualified(),
            cursor.result_type.get_array_size(),
            kind=self.get_type(cursor, True),
            is_pointer=self.is_pointer_type(cursor.result_type.get_canonical().kind))
    
        self.add_to_db(property)
        
        return property

    # Check if this object is known in the db and add it if not.
    def add_to_db(self, property:model.Object) -> model.Object:
        if 'unnamed' in property.cpp_type:
            raise Exception("cannot bind unamed stuff")

        if 'locale' in property.cpp_type:
            raise Exception("cannot bind _locale_t stuff")

        if property.cpp_type in self.db:
            return self.db[property.cpp_type]
        else:
            self.db[property.cpp_type] = property
            return property

    def read_function(self, cursor):
        if cursor.storage_class == clang.cindex.StorageClass.STATIC:
            return

        for symbol in self.undefined_symbols:
            if symbol in cursor.spelling:
                return

        method = model.Method(cursor.spelling)
        method.return_type = self.read_return_type(cursor)

        for arg in cursor.get_arguments():
            method.params.append(self.read_property(arg))

        model.correct_overloads(method, self.db[cursor.lexical_parent.spelling].methods)

        self.db[cursor.lexical_parent.spelling].methods.append(method)

    def read_feild(self, cursor):
        if cursor.lexical_parent.spelling in self.db:
            self.db[cursor.lexical_parent.spelling].properties.append(self.read_property(cursor))

    def read_typedef(self, cursor):
        self.add_to_db(model.Object(cursor.type.spelling))

    def read_enum(self, cursor):
        object = self.add_to_db(model.Object(cpp_type=cursor.type.spelling, name=cursor.type.spelling, kind=model.Type.ENUM))

        for child in cursor.get_children():
            if child.kind == clang.cindex.CursorKind.ENUM_CONSTANT_DECL:
                object.enums.append((child.spelling, child.enum_value))

    # recursively build a database of everything in the translation unit
    def visit(self, cursor):
        if cursor.access_specifier == clang.cindex.AccessSpecifier.PRIVATE:
            return
        if cursor.access_specifier == clang.cindex.AccessSpecifier.PROTECTED:
            return
        
        if cursor.kind == clang.cindex.CursorKind.CLASS_DECL or cursor.kind == clang.cindex.CursorKind.STRUCT_DECL:
            try:
                clazz = model.Object(cursor.type.spelling)
                self.add_to_db(clazz)

                if self.db[clazz.cpp_type].handwritten:
                    return

                self.c.append(cursor.type.spelling)
                for child in cursor.get_children():
                    self.visit(child)
                self.c.pop()
            except Exception as e:
                print(e)

        elif cursor.kind == clang.cindex.CursorKind.ENUM_DECL:
            try:
                self.read_enum(cursor)
            except Exception as e:
                print(e)

        elif cursor.kind == clang.cindex.CursorKind.CXX_METHOD and bool(self.c):
            try:
                self.read_function(cursor)
            except Exception as e:
                print(e)

        elif cursor.kind == clang.cindex.CursorKind.FIELD_DECL and bool(self.c):
            try:
                self.read_feild(cursor)
            except Exception as e:
                print(e)

        elif cursor.kind == clang.cindex.CursorKind.TYPEDEF_DECL:
            try:
                self.read_typedef(cursor)
            except Exception as e:
                print(e)
        else:
            for child in cursor.get_children():
                self.visit(child)

    # Get all needed types for this type
    def get_dependencies(self, type:str) -> set:
        res = set()
        res.add(type)

        struct = self.db[type]

        if hasattr(struct, 'properties'):
            for property in struct.properties:
                res = res | self.get_dependencies(property.cpp_type)

        if hasattr(struct, 'methods'):
            for method in struct.methods:
                res = res | self.get_dependencies(method.return_type.cpp_type)

                for param in method.params:
                    res = res | self.get_dependencies(param.cpp_type)

        return res

    def build(self, header_path:str) -> dict:
        index = clang.cindex.Index.create()
        translation_unit = index.parse(header_path, ['-x', 'c++'])

        # Get all types into a db
        self.visit(translation_unit.cursor)

        optimize(self.db)

        return self.db

def find_len_param(param:model.Object, method:model.Method):
    for i in range(len(method.params)):
        param = method.params[i]
        if param.size_for:
            continue
        if param.is_integer and re.findall(r"(len|size|count|max|cch)", param.name, re.IGNORECASE):
            return i

    return -1

def optimize_buffer(method:model.Method):
    for param in method.params:
        if param.is_pointer and param.is_primitive:
            len_param = find_len_param(param, method)
           
            if len_param != -1:
                param.is_buffer = True
                param.buffer_size = method.params[len_param]
                method.params[len_param].size_for = param

def optimize(db:dict):
    for key in db:
        object = db[key]

        for method in object.methods:
            optimize_buffer(method)
