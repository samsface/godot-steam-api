extends Node2D

func _ready():
	print(Steam.is_init())

	print(Steam.utils.get_app_id())
	
	print(Steam.user.get_steam_id().convert_to_uint64())

	prints("owns", Steam.apps.is_subscribed_app(80))

	Steam.set_achievement("gator_god")
	Steam.user_stats.reset_all_stats(true)
	print(Steam.get_achievement("gator_god"))

	Steam.clear_achievement("gator_god")
	Steam.set_achievement("gator_god")
	
	var num_achievements = Steam.user_stats.get_num_achievements()
	if num_achievements:
		for i in Steam.user_stats.get_num_achievements():
			print(Steam.user_stats.get_achievement_name(i))

	Steam.clear_achievement("gator_god")

	var res = Steam.user_stats.indicate_achievement_progress("gator_god", 1, 4)

	yield(Steam.set_leaderboard_score("High Score", 1001, Steam.LeaderboardUploadScoreMethod.KeepBest, PoolIntArray([1, 2, 3]), Steam.LeaderboardSortMethod.Descending), "done")

	var scores = yield(Steam.get_leaderboard_scores("High Score", 0, 10, Steam.LeaderboardDataRequest.Global, 3), "done")
	print(scores)
	
	print(Steam.apps.get_current_game_language())
	print(Steam.apps.get_available_game_languages())

	Steam.friends.connect("game_overlay_activated", self, "_on_game_overlay_activated")
	Steam.friends.activate_game_overlay_to_web_page("https://steamcommunity.com/")
	Steam.friends.activate_game_overlay_to_store(1435470, Steam.OverlayToStoreFlag.AddToCart)

	Steam.friends.set_rich_presence("steam_display", "cactus")

	print(Steam.friends.get_persona_name())
	
	print(Steam.utils.is_running_on_steam_deck())
	prints("appid", Steam.utils.get_app_id())
	
	Steam.user_stats.set_stat("total_kills", 556)
	print(Steam.user_stats.get_stat("total_kills"))

func _on_game_overlay_activated(active:bool) -> void:
	$game_overlay_activated.text = str(active)
