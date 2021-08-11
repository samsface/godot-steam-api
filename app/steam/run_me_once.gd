tool
extends EditorScript

# Run this script with: File > Run

export(int) var steam_app_id  := 1435470
export(String) var steam_sdk_dir := "/home/sam/work/spacebandit/steam/steamworks_sdk/sdk"

func copy_file_from_steam_sdk_(base_path:String, file_name:String) -> void:
	if not File.new().file_exists("res://steam/%s" % file_name):
		var res := Directory.new().copy(steam_sdk_dir + base_path + file_name, "res://steam/%s" % file_name)
		if res != OK:
			push_error("Failed to copy %s. Steam integration will not work. Did you set the steam_sdk_dir correctly?" % file_name)

static func exe_path_() -> String:
	return OS.get_executable_path().get_base_dir()

func write_steam_app_id_file_() -> void:
	var f := File.new()
	var res := f.open(exe_path_() + "/steam_appid.txt", File.WRITE)
	if res == OK:
		f.store_string(str(steam_app_id))
		f.close()
	else:
		push_error("Failed to write steamapp_id.txt to \"{exe_path}\". Steam integration will not work. For debug builds, steam needs a text file with just your steam_app_id named 'steam_appid.txt' next to your exe in '{exe_path}'. Try write the file manually.".format({"exe_path": exe_path_()}))

func steam_appid_file_has_correct_id_() -> bool:
	var file := File.new()
	var res := file.open(exe_path_() + "/steam_appid.txt", File.READ)
	if res == OK:
		return str(steam_app_id) != file.get_line()
	else:
		return false

func debug_setup_() -> void:
	copy_file_from_steam_sdk_("/redistributable_bin/linux64/", "libsteam_api.so")
	copy_file_from_steam_sdk_("/redistributable_bin/win64/", "steam_api64.dll")
	copy_file_from_steam_sdk_("/redistributable_bin/osx/", "libsteam_api.dylib")

	if not steam_appid_file_has_correct_id_():
		write_steam_app_id_file_()

func _run() -> void:
	debug_setup_()
