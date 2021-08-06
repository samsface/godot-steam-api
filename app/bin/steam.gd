extends Node

export(int) var steam_app_id := 1435470

var api_
var user_stats_

func write_steam_app_id_file_to_exe_dir_() -> void:
	# for debug builds, steam requires this file next to exe.
	var exe_dir := OS.get_executable_path().get_base_dir()
	var f := File.new()
	var res := f.open(exe_dir + "/steam_appid.txt", File.WRITE)
	if res == OK:
		f.store_string(str(steam_app_id))
		f.close()

func copy_libsteam_to_exe_dir_() -> void:
	# for linux, we need libsteam.so to be in a known location relative
	# to the exe.
	var exe_dir := OS.get_executable_path().get_base_dir()
	var dir := Directory.new()
	dir.copy("res://bin/libsteam.so", exe_dir + "/libsteam.so")

func _ready():
	if OS.is_debug_build():
		write_steam_app_id_file_to_exe_dir_()
		
		if OS.get_name() == "X11":
			copy_libsteam_to_exe_dir_()
			
	api_ = SteamAPI.new()
	if not api_.init(steam_app_id):
		push_error("failed to init steam api")
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
