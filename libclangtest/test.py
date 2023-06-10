import clang.cindex

c = []

extract = {"ISteamUtils"}

dependencies = {}

def print_function_info(cursor):
    if not cursor.result_type.spelling in dependencies:
        dependencies[cursor.spelling] = False

    print("{}::{} (Return Type: {})".format(c[-1], cursor.spelling, cursor.result_type.spelling))
    for arg in cursor.get_arguments():
        dependencies[arg.type.spelling] = False
        print("  Parameter: {} (Type: {})".format(arg.spelling, arg.type.spelling))

def visit(cursor):
    if cursor.kind == clang.cindex.CursorKind.CLASS_DECL or cursor.kind == clang.cindex.CursorKind.STRUCT_DECL:
        if (cursor.spelling in extract) or bool(c):
            c.append(cursor.spelling)
            for child in cursor.get_children():
                visit(child)
            c.pop()
    elif bool(c) and cursor.kind == clang.cindex.CursorKind.CXX_METHOD:
        print_function_info(cursor)
    else:
        for child in cursor.get_children():
                visit(child)

def main():
    index = clang.cindex.Index.create()
    translation_unit = index.parse('C:/work/godot-steam-api/lib/steam-sdk/public/steam/isteamutils.h', ['-x', 'c++'])

    visit(translation_unit.cursor)

    print(dependencies)

if __name__ == "__main__":
    main()