extends Node2D

func _ready():
	Steam.clear_achievement("gator_god")
	Steam.set_achievement("gator_god")

	Steam.set_leaderboard_score("High Score", 1000)

	var scores = yield(Steam.get_leaderboard_scores("High Score", 0, 10), "done")
	print(scores)
