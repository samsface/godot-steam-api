extends Node2D

func _ready() -> void:
	var s = SteamAPI_box.new()
	s.init()
	
	var user_stats := SteamI.ISteamUserStats.new(s.SteamUserStats())

	var utils := SteamI.ISteamUtils.new(s.SteamUtils())
	var id = utils.get_app_id()
	print(id)


	var battery := utils.get_current_battery_power()
	print(battery)
	
	var language := utils.get_steam_ui_language()
	print(language)

	for i in user_stats.get_num_achievements():
		print(user_stats.get_achievement_name(i))

		
	var request = user_stats.get_achievement("gator_god")
