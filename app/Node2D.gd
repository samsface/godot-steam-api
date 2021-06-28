extends Node2D

func _ready():
	var steam_api := SteamAPI.new()
	if not steam_api.init(123):
		return
	
	var steam_user_stats := SteamUserStats.new()

	steam_user_stats.request_current_stats();
	
	if not steam_user_stats.clear_achievement("gator_god"):
		print("oh no")
		
	var v = steam_user_stats.get_achievement("asdasd")
	if not v:
		steam_user_stats.set_achievement("gator_god")
		steam_user_stats.store_stats();
