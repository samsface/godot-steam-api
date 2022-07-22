extends Node2D

func _ready():
	print(Steam.is_init())

	print(Steam.utils.get_app_id())

	Steam.clear_achievement("test")
	Steam.set_achievement("test")
	
	var num_achievements = Steam.user_stats.get_num_achievements()
	if num_achievements:
		for i in Steam.user_stats.get_num_achievements():
			print(Steam.user_stats.get_achievement_name(i))

	yield(Steam.set_leaderboard_score("High Score", 1001, Steam.LeaderboardUploadScoreMethod.KeepBest, PoolIntArray([1, 2, 3]), Steam.LeaderboardSortMethod.Descending), "done")

	var scores = yield(Steam.get_leaderboard_scores("High Score", 0, 10, Steam.LeaderboardDataRequest.Global, 3), "done")
	print(scores)

	Steam.friends.connect("game_overlay_activated", self, "_on_game_overlay_activated")
	Steam.friends.activate_game_overlay_to_web_page("https://steamcommunity.com/")
	Steam.friends.activate_game_overlay_to_store(1435470, Steam.OverlayToStoreFlag.AddToCart)

	Steam.friends.set_rich_presence("steam_display", "cactus")

	print(Steam.friends.get_persona_name())
	
	prints("appid", Steam.utils.get_app_id())
	
	Steam.set_stat("kills", 123)
	print(Steam.get_stat("kills"))

func _on_game_overlay_activated(active:bool) -> void:
	$game_overlay_activated.text = str(active)
