extends Node
class_name SteamI

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

class Proxy_:
	signal keep_alive_hack_
	
	var object_to_proxy_

	func _init(object_to_proxy) -> void:
		object_to_proxy_ = object_to_proxy

	func call_(func_name, args := []):
		if not object_to_proxy_:
			return
		
		return object_to_proxy_.callv(func_name, args)
		
	func callback_(func_name, args := []):
		if not object_to_proxy_:
			var result = Callback.new()
			result.call_deferred("emit_signal", "done", null)
			call_deferred("emit_signal", "keep_alive_hack_", result)
			return result

		return object_to_proxy_.callv(func_name, args)

class UserStats extends Proxy_:
	func _init(o).(o) -> void:
		pass

	func set_achievement(achievement_api_name:String) -> bool:
		return call_("set_achievement", [achievement_api_name])
		
	func clear_achievement(achievement_api_name:String) -> bool:
		return call_("clear_achievement", [achievement_api_name])

	func get_achievement(achievement_api_name:String) -> bool:
		return call_("get_achievement", [achievement_api_name])

	func request_current_stats() -> bool:
		return call_("request_current_stats")

	func store_stats() -> bool:
		return call_("store_stats")
		
	func find_leaderboard(leaderboard_name:String):
		return callback_("find_leaderboard", [leaderboard_name])

	func upload_leaderboard_score(leaderboard, method:int, score:int):
		return callback_("upload_leaderboard_score", [leaderboard, method, score])

	func download_leaderboard_entries(leaderboard, data_request:int, begin:int, end:int):
		return callback_("download_leaderboard_entries", [leaderboard, data_request, begin, end])

	func get_downloaded_leaderboard_entry(leaderboard, index:int):
		return callback_("get_downloaded_leaderboard_entry", [leaderboard, index])

class Friends extends Proxy_:
	signal game_overlay_activated

	func _init(o).(o) -> void:
		if o:
			o.connect("game_overlay_activated", self, "_on_game_overlay_activated")

	func _on_game_overlay_activated(active:bool) -> void:
		emit_signal("game_overlay_activated", active)

	func request_user_information(steam_user_id, require_name_only:bool) -> bool:
		return call_("request_user_information", [steam_user_id, require_name_only])
	
	func get_friend_persona_name(steam_user_id) -> String:
		return call_("get_friend_persona_name", [steam_user_id])

	func active_game_overlay_to_web_page(url:String) -> String:
		return call_("active_game_overlay_to_web_page", [url])
		
	func activate_game_overlay_to_store(app_id:int, where:int) -> void:
		call_("activate_game_overlay_to_store", [app_id, where])

var api_
var user_stats:UserStats = UserStats.new(null)
var friends:Friends = Friends.new(null)

func is_init() -> bool:
	if api_:
		return api_.is_init()
	return false

func set_achievement(name:String) -> void:
	user_stats.set_achievement(name)
	user_stats.store_stats()
	
func get_achievement(name:String) -> bool:
	return user_stats.get_achievement(name)

func clear_achievement(name:String) -> void:
	user_stats.clear_achievement(name)
	user_stats.store_stats()

func set_leaderboard_score(leaderboard_name:String, score:int, method:int = LeaderboardUploadScoreMethod.KeepBest) -> void:
	var find_leaderboard_result = yield(user_stats.find_leaderboard(leaderboard_name), "done")
	if not find_leaderboard_result:
		return

	if not find_leaderboard_result.get_leaderboard_found():
		return
		
	var leaderboard = find_leaderboard_result.get_leaderboard()
	if not leaderboard:
		return

	yield(user_stats.upload_leaderboard_score(leaderboard, method, score), "done")

func get_leaderboard_scores(leaderboard_name:String, begin:int, end:int, method:int = LeaderboardDataRequest.Global):
	var callback := Callback.new()
	get_leaderboard_scores_(leaderboard_name, begin, end, method, callback)
	return callback

func get_leaderboard_scores_(leaderboard_name:String, begin:int, end:int, method:int, callback:Callback) -> Callback:
	var res := []
	
	var user_stats_ = user_stats.object_to_proxy_
	var friends_ = friends.object_to_proxy_

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
	friends.active_game_overlay_to_web_page(url)

func activate_game_overlay_to_store(app_id:int, where:int = 0) -> void:
	friends.activate_game_overlay_to_store(app_id, where)
