extends Node
class_name SteamDependencyLibraries


static func get_plugin_base_dir() -> String:
	return "res://addons/steam_api"


static func get_gdnlib_backup_dir() -> String:
	return "res://addons/steam_api/.gdnlib_backup"


static func get_gdns_backup_dir() -> String:
	return "res://addons/steam_api/.gdns_backup"


static func disable() -> void:
	disable_gdnlib()
	disable_gdns()


static func enable() -> void:
	enable_gdnlib()
	enable_gdns()


static func disable_gdnlib() -> void:
	var dir = Directory.new()

	dir.make_dir(get_gdnlib_backup_dir())

	dir.copy(
		get_plugin_base_dir().plus_file("steam_api.gdnlib"),
		get_gdnlib_backup_dir().plus_file("steam_api.gdnlib")
	)

	var gdnlib = load(get_plugin_base_dir().plus_file("steam_api.gdnlib")).config_file

	for entry in gdnlib.get_section_keys("entry"):
		gdnlib.set_value("entry", entry, "")

	for dependency in gdnlib.get_section_keys("dependencies"):
		gdnlib.set_value("dependencies", dependency, [])

	gdnlib.save(get_plugin_base_dir().plus_file("steam_api.gdnlib"))


static func enable_gdnlib() -> void:
	var dir = Directory.new()

	if not dir.dir_exists(get_gdnlib_backup_dir()):
		return

	dir.copy(
		get_gdnlib_backup_dir().plus_file("steam_api.gdnlib"),
		get_plugin_base_dir().plus_file("steam_api.gdnlib")
	)

	if dir.open(get_gdnlib_backup_dir()) == OK:
		dir.list_dir_begin()

		var file_name = dir.get_next()

		while file_name != "":
			if not dir.current_is_dir():
				dir.remove(get_gdnlib_backup_dir().plus_file(file_name))

			file_name = dir.get_next()

		dir.list_dir_end()
	else:
		print("An error occurred when trying to access the path.")

	dir.remove(get_gdnlib_backup_dir())


static func disable_gdns() -> void:
	var dir = Directory.new()

	dir.make_dir(get_gdns_backup_dir())

	if dir.open(get_plugin_base_dir()) == OK:
		dir.list_dir_begin()

		var file_name = dir.get_next()

		while file_name != "":
			if not dir.current_is_dir():
				if file_name.get_extension() == "gdns":
					var file := get_plugin_base_dir().plus_file(file_name)
					var gdns_backup_file := get_gdns_backup_dir().plus_file(file_name)

					dir.copy(file, gdns_backup_file)

					var lines := []
					var output_string := ""

					var f = File.new()

					f.open(file, File.READ)
					while not f.eof_reached():
						lines.append(f.get_line())
					f.close()

					var line_index := 0
					for _i in lines.size():
						if line_index >= lines.size():
							break

						var line = lines[line_index]

						if "gd_resource" in line:
							line = line.replace("load_steps=2", "load_steps=1")

						if "ext_resource" in line or "library" in line:
							line_index += 1
							if lines[line_index - 2] == "":
								line_index += 1
							continue

						output_string += line

						if line_index != lines.size() - 1:
							output_string += "\n"

						line_index += 1

					f.open(file, File.WRITE)
					f.store_string(output_string)
					f.close()

			file_name = dir.get_next()

		dir.list_dir_end()
	else:
		print("An error occurred when trying to access the path.")


static func enable_gdns() -> void:
	var dir = Directory.new()

	if not dir.dir_exists(get_gdns_backup_dir()):
		return

	if dir.open(get_gdns_backup_dir()) == OK:
		dir.list_dir_begin()

		var file_name = dir.get_next()

		while file_name != "":
			if not dir.current_is_dir():
				var file := get_plugin_base_dir().plus_file(file_name)
				var gdns_backup_file := get_gdns_backup_dir().plus_file(file_name)

				dir.copy(gdns_backup_file, file)
				dir.remove(gdns_backup_file)

			file_name = dir.get_next()

		dir.list_dir_end()
	else:
		print("An error occurred when trying to access the path.")

	dir.remove(get_gdns_backup_dir())
