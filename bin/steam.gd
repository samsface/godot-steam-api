extends Node

export(int) var steam_app_id := 1435470

var api_
var user_stats_

func write_steam_app_id_file_to_exe_dir_(path:String) -> int:
	var f := File.new()
	var res := f.open(path + "/steam_appid.txt", File.WRITE)
	if res == OK:
		f.store_string(str(steam_app_id))
		f.close()
	
	return res

func setup_() -> void:
	var exe_path := OS.get_executable_path().get_base_dir()
	var file := File.new()
	
	var write_steam_appid_file := false

	if not file.file_exists(exe_path + "/steam_appid.txt"):
		print("steam_appid.txt not found path")
		write_steam_appid_file = true
	else:
		file.open(exe_path + "/steam_appid.txt", File.READ)
		if str(steam_app_id) != file.get_line():
			print("steam_appid.txt exists but not our app id")
			write_steam_appid_file = true
	
	if write_steam_appid_file:
		var res := write_steam_app_id_file_to_exe_dir_(exe_path)
		if res != OK:
			push_error("Failed to write steamapp_id.txt to \"{exe_path}\". Steam integration will not work. For debug builds, steam needs a file named 'steam_appid.txt' next to your exe in '{exe_path}'. Try write the file manually.".format({"exe_path": exe_path, "steam_app_id": str(steam_app_id)}))

func _ready():
	if OS.is_debug_build():
		setup_()

	api_ = SteamAPI.new()
	if not api_.init(steam_app_id):
		push_error("Failed to init steam api. Is Steam running?")
		return
	
	user_stats_ = SteamUserStats.new()
	user_stats_.request_current_stats();

#warning-ignore:unused_argument
func _process(delta:float) -> void:
	api_.run_callbacks()

func set_achievement(name:String) -> void:
	user_stats_.set_achievement(name)
	user_stats_.store_stats();
	
func get_achievement(name:String) -> bool:
	return user_stats_.get(name)

func clear_achievement(name:String) -> void:
	user_stats_.clear_achievement(name)
	user_stats_.store_stats()
