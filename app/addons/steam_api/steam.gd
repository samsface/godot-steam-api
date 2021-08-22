extends Node

var api_:SteamAPI
var user_stats_:SteamUserStats

func _ready():
	var settings = load("res://addons/steam_api/settings.tres")
	api_ = SteamAPI.new()
	if not api_ or not api_.init():
		api_ = null
		push_error("Failed to init steam api. Is Steam running? Is the plugin activated? Did you do the setup in ProjectSettings > SteamAPI")
		return
	
	user_stats_ = SteamUserStats.new()
	user_stats_.request_current_stats()

#warning-ignore:unused_argument
func _process(delta:float) -> void:
	if api_:
		api_.run_callbacks()

func set_achievement(name:String) -> void:
	if user_stats_:
		user_stats_.set_achievement(name)
		user_stats_.store_stats();
	
func get_achievement(name:String) -> bool:
	if user_stats_:
		return user_stats_.get(name)

	return false

func clear_achievement(name:String) -> void:
	if user_stats_:
		user_stats_.clear_achievement(name)
		user_stats_.store_stats()
