extends Node2D

func _ready():
	Steam.clear_achievement("gator_god")
	Steam.set_achievement("gator_god")

	Steam.set_leaderboard_score("High Score", 1000)

	var scores = yield(Steam.get_leaderboard_scores("High Score", 0, 10), "done")
	print(scores)
	
	Steam.active_game_overlay_to_web_page("https://steamcommunity.com/")
	Steam.activate_game_overlay_to_store(1435470, Steam.OverlayToStoreFlag.AddToCart)
