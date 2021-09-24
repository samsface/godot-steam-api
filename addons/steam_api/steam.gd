extends Node

signal leaderboard_scores

enum LeaderboardUploadScoreMethod {
	None = 0,
	KeepBest = 1,
	ForceUpdate = 2,
}

enum LeaderboardDataRequest {
	Global = 0,
	GlobalAroundUser = 1,
	Friends = 2,
	Users = 3
}

enum OverlayToStoreFlag {
	None = 0,
	AddToCart = 1,
	AddToCartAndShow = 2,
};

class Callback:
	signal done

var api_:SteamAPI
var user_stats_:SteamUserStats
var friends_:SteamFriends

func _ready():
	var settings = load("res://addons/steam_api/settings.tres")
	api_ = SteamAPI.new()
	if not api_ or not api_.init():
		api_ = null
		push_error("Failed to init steam api. Is Steam running? Is the plugin activated? Did you do the setup in ProjectSettings > SteamAPI")
		return

	user_stats_ = SteamUserStats.new()
	friends_    = SteamFriends.new()
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
		return user_stats_.get_achievement(name)

	return false

func clear_achievement(name:String) -> void:
	if user_stats_:
		user_stats_.clear_achievement(name)
		user_stats_.store_stats()

func set_leaderboard_score(leaderboard_name:String, score:int, method:int = LeaderboardUploadScoreMethod.KeepBest) -> void:
	if not user_stats_:
		return

	var find_leaderboard_result = yield(user_stats_.find_leaderboard(leaderboard_name), "done")
	if not find_leaderboard_result:
		return

	if not find_leaderboard_result.get_leaderboard_found():
		return
		
	var leaderboard = find_leaderboard_result.get_leaderboard()
	if not leaderboard:
		return

	yield(user_stats_.upload_leaderboard_score(leaderboard, method, score), "done")

func get_leaderboard_scores(leaderboard_name:String, begin:int, end:int, method:int = LeaderboardDataRequest.Global):
	var callback := Callback.new()
	get_leaderboard_scores_(leaderboard_name, begin, end, method, callback)
	return callback

func get_leaderboard_scores_(leaderboard_name:String, begin:int, end:int, method:int, callback:Callback) -> Callback:
	var res := []
	
	if not user_stats_:
		return callback.emit_signal("done", res)

	if not friends_:
		return callback.emit_signal("done", res)

	var find_leaderboard_result = yield(user_stats_.find_leaderboard(leaderboard_name), "done")
	if not find_leaderboard_result.get_leaderboard_found():
		return callback.emit_signal("done", res)
	
	var leaderboard = find_leaderboard_result.get_leaderboard()
	if not leaderboard:
		return callback.emit_signal("done", res)

	var download = yield(user_stats_.download_leaderboard_entries(leaderboard, method, begin, end), "done")
	if not download:
		return callback.emit_signal("done", res)

	var entries = download.get_entries()
	if not entries:
		return callback.emit_signal("done", res)
	
	for i in download.get_entry_count():
		var entry = user_stats_.get_downloaded_leaderboard_entry(entries, i)
		if not entry:
			continue

		var score := {}
		score["global_rank"] = entry.get_global_rank()
		score["score"] = entry.get_score()

		if not friends_.request_user_information(entry.get_steam_id_user(), true):
			score["persona_name"] = friends_.get_friend_persona_name(entry.get_steam_id_user())
		else:
			score["persona_name"] = "Frank"
			
		res.push_back(score)
	
	return callback.emit_signal("done", res)

func active_game_overlay_to_web_page(url:String) -> void:
	if not friends_:
		return
		
	friends_.active_game_overlay_to_web_page(url)
	
func activate_game_overlay_to_store(app_id:int, where:int = 0) -> void:
	if not friends_:
		return
		
	friends_.activate_game_overlay_to_store(app_id, where)
