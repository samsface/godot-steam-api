tool
extends Control

signal disable

var settings
var settings_path = "res://addons/steam_api/settings.tres"

func _ready():
	settings = load(settings_path)
	$panel/container/app_id/input.text = settings.app_id
	$panel/container/sdk_dir/input.text = settings.sdk_dir
	$panel/container/disable/input.pressed = settings.disable

func copy_file_from_steam_sdk_(base_path:String, file_name:String) -> void:
	print(settings.sdk_dir + base_path + file_name)
	if not File.new().file_exists("res://addons/steam_api/%s" % file_name):
		var res := Directory.new().copy(settings.sdk_dir + base_path + file_name, "res://addons/steam_api/%s" % file_name)
		if res != OK:
			popup_error("Failed to copy %s. Steam integration will not work. Did you set the 'SDK Directory' correctly?" % file_name)

static func exe_path_() -> String:
	return OS.get_executable_path().get_base_dir()

func write_steam_app_id_file_() -> void:
	var f := File.new()
	var res := f.open(exe_path_() + "/steam_appid.txt", File.WRITE)
	if res == OK:
		f.store_string(str(settings.app_id))
		f.close()
	else:
		popup_error("Failed to write steamapp_id.txt to \"{exe_path}\". Steam integration will not work. For debug builds, steam needs a text file with just your steam_app_id named 'steam_appid.txt' next to your exe in '{exe_path}'. Try write the file manually.".format({"exe_path": exe_path_()}))

func steam_appid_file_has_correct_id_() -> bool:
	var file := File.new()
	var res := file.open(exe_path_() + "/steam_appid.txt", File.READ)
	if res == OK:
		return str(settings.app_id) == file.get_line()
	else:
		return false

func debug_setup_() -> void:
	copy_file_from_steam_sdk_("/redistributable_bin/linux64/", "libsteam_api.so")
	copy_file_from_steam_sdk_("/redistributable_bin/win64/", "steam_api64.dll")
	copy_file_from_steam_sdk_("/redistributable_bin/osx/", "libsteam_api.dylib")
	
	if not steam_appid_file_has_correct_id_():
		write_steam_app_id_file_()

func _on_SDK_instructions_meta_clicked(meta):
	if meta == "open_sdk_page":
		OS.shell_open("https://partner.steamgames.com/downloads/steamworks_sdk.zip")

func popup_error(message):
	$panel/warning.popup_centered_clamped(Vector2(400, 100))
	$panel/warning/container/error_text.text = message
	push_error(message)

func _on_FindSDK_pressed():
	_ready()
	debug_setup_()
	check_status()

func _on_SteamAPI_visibility_changed():
	check_status()

func check_status():
	var file = File.new()
	var status = "[color=green]Done![/color]"
	var missing = []
	if not file.file_exists("res://addons/steam_api/libsteam_api.so"): missing.push_back("linux")
	if not file.file_exists("res://addons/steam_api/steam_api64.dll"): missing.push_back("windows")
	if not file.file_exists("res://addons/steam_api/libsteam_api.dylib"): missing.push_back("osx")
	if missing.size() > 0:
		if missing.size() == 3:
			status = "[color=red]No files imported[/color]"
		else:
			status = "[color=#ffa500]Partially complete, missing: %s[/color]" % String(missing)
	status = "[center]%s[/center]" % status
	$panel/container/sdk_status/status.bbcode_text = status

func _on_app_id_focus_exited():
	save_settings()

func _on_sdk_dir_focus_exited():
	save_settings()

func save_settings():
	settings.app_id = $panel/container/app_id/input.text
	settings.sdk_dir = $panel/container/sdk_dir/input.text
	ResourceSaver.save(settings_path, settings)

func _on_disable_pressed():
	settings.disable = $panel/container/disable/input.pressed
	save_settings()
	emit_signal("disable", settings.disable)
