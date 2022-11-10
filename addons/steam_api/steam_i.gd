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
	AddToCartAndShow = 2
}

enum LeaderboardSortMethod {
	None = 0,
	Ascending = 1,
	Descending = 2
}

enum LeaderboardDisplayType {
	None = 0, 
	Numeric = 1,
	TimeSeconds = 2,
	TimeMilliSeconds = 3
}

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

class SteamUserProxy_ extends Proxy_:
	func _init(o).(o) -> void:
		pass
		
	func get_steam_id() -> SteamId:
		return call_("get_steam_id")

class SteamUserStatsProxy_ extends Proxy_:
	func _init(o).(o) -> void:
		pass

	func set_stat(name:String, value, store := true) -> bool:
		var res := false

		if value is float:
			res = set_statf(name, value)
			if not res:
				res = set_stati(name, value)
			
		elif value is int:
			res = set_stati(name, value)
			if not res:
				res = set_statf(name, value)

		if res and store:
			store_stats()
			
		return res

	func get_stat(name:String):
		var try = get_statf(name)
		if not try:
			return
		
		if try[0]:
			return try[1]
		
		try = get_stati(name)
		if try[0]:
			return try[1]

	func set_statf(name:String, value:float) -> bool:
		return call_("set_statf", [name, value])

	func get_statf(name:String) -> Array:
		return call_("get_statf", [name])

	func set_stati(name:String, value:int) -> bool:
		return call_("set_stati", [name, value])

	func get_stati(name:String) -> Array:
		return call_("get_stati", [name])

	func set_achievement(achievement_api_name:String) -> bool:
		return call_("set_achievement", [achievement_api_name])
		
	func clear_achievement(achievement_api_name:String) -> bool:
		return call_("clear_achievement", [achievement_api_name])

	func reset_all_stats(achievements_too:bool) -> bool:
		return call_("reset_all_stats", [achievements_too])

	func get_achievement(achievement_api_name:String) -> bool:
		return call_("get_achievement", [achievement_api_name])
	
	func get_num_achievements() -> int:
		return call_("get_num_achievements")
	
	func indicate_achievement_progress(achievement_api_name:String, current_progress:int, max_progress:int) -> bool:
		return call_("indicate_achievement_progress", [achievement_api_name, current_progress, max_progress])
	
	func get_achievement_name(idx:int) -> String:
		return call_("get_achievement_name", [idx])
	
	func request_current_stats() -> bool:
		return call_("request_current_stats")

	func store_stats() -> bool:
		return call_("store_stats")
		
	func find_leaderboard(leaderboard_name:String):
		return callback_("find_leaderboard", [leaderboard_name])

	func find_or_create_leaderboard(leaderboard_name:String, sort_method:int, display_type:int):
		return callback_("find_or_create_leaderboard", [leaderboard_name, sort_method, display_type])

	func upload_leaderboard_score(leaderboard, method:int, score:int, details:PoolIntArray):
		return callback_("upload_leaderboard_score", [leaderboard, method, score, details])

	func download_leaderboard_entries(leaderboard, data_request:int, begin:int, end:int):
		return callback_("download_leaderboard_entries", [leaderboard, data_request, begin, end])

	func get_downloaded_leaderboard_entry(leaderboard, index:int, max_details:int):
		return callback_("get_downloaded_leaderboard_entry", [leaderboard, index, max_details])

class SteamFriendsProxy_ extends Proxy_:
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

	func get_persona_name() -> String:
		return call_("get_persona_name")
		
	func activate_game_overlay(dialog:String) -> void:
		call_("activate_game_overlay", [dialog])

	func activate_game_overlay_to_web_page(url:String) -> void:
		call_("activate_game_overlay_to_web_page", [url])

	func activate_game_overlay_to_store(app_id:int, where:int) -> void:
		call_("activate_game_overlay_to_store", [app_id, where])

	func set_rich_presence(key:String, value:String) -> bool:
		return call_("set_rich_presence", [key, value])

	func clear_rich_presence() -> void:
		call_("clear_rich_presence")

class SteamUtilsProxy_ extends Proxy_:
	func _init(o).(o) -> void:
		pass

	func get_app_id() -> int:
		return call_("get_app_id")

	func is_running_on_steam_deck() -> bool:
		return call_("is_running_on_steam_deck")

class SteamAppsProxy_ extends Proxy_:
	func _init(o).(o) -> void:
		pass

	func get_current_game_language() -> String:
		return call_("get_current_game_language")
		
	# Returns a comma separated list of languages.
	func get_available_game_languages() -> String:
		return call_("get_available_game_languages")
	
	func is_subscribed_app(app_id:int) -> bool:
		return call_("is_subscribed_app", [app_id])

var api_
var user:SteamUserProxy_ = SteamUserProxy_.new(null)
var user_stats:SteamUserStatsProxy_ = SteamUserStatsProxy_.new(null)
var friends:SteamFriendsProxy_ = SteamFriendsProxy_.new(null)
var utils:SteamUtilsProxy_ = SteamUtilsProxy_.new(null)
var apps:SteamAppsProxy_ = SteamAppsProxy_.new(null)

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

func set_leaderboard_score(leaderboard_name:String, score:int, method:int = LeaderboardUploadScoreMethod.KeepBest, details:PoolIntArray = PoolIntArray(), sort_method:int = -1, display_type:int = LeaderboardDisplayType.Numeric):
	var callback := Callback.new()
	set_leaderboard_score_(leaderboard_name, score, method, details, sort_method, display_type, callback)
	return callback

func set_leaderboard_score_(leaderboard_name:String, score:int, method:int, details:PoolIntArray, sort_method:int, display_type:int, callback) -> void:
	var find_leaderboard_result
	
	if sort_method > 0:
		find_leaderboard_result = yield(user_stats.find_or_create_leaderboard(leaderboard_name, sort_method, display_type), "done")
	else:
		find_leaderboard_result = yield(user_stats.find_leaderboard(leaderboard_name), "done")
	
	if not find_leaderboard_result:
		return callback.emit_signal("done", null)

	if not find_leaderboard_result.get_leaderboard_found():
		return callback.emit_signal("done", null)
		
	var leaderboard = find_leaderboard_result.get_leaderboard()
	if not leaderboard:
		return callback.emit_signal("done", null)

	yield(user_stats.upload_leaderboard_score(leaderboard, method, score, details), "done")

	return callback.emit_signal("done", null)

func get_leaderboard_scores(leaderboard_name:String, begin:int, end:int, method:int = LeaderboardDataRequest.Global, max_details:int = 0):
	var callback := Callback.new()
	get_leaderboard_scores_(leaderboard_name, begin, end, method, max_details, callback)
	return callback

func get_leaderboard_scores_(leaderboard_name:String, begin:int, end:int, method:int, max_details, callback:Callback) -> Callback:
	var res := []

	var find_leaderboard_result = yield(user_stats.find_leaderboard(leaderboard_name), "done")
	if not find_leaderboard_result:
		return callback.emit_signal("done", res)
	
	if not find_leaderboard_result.get_leaderboard_found():
		return callback.emit_signal("done", res)
	
	var leaderboard = find_leaderboard_result.get_leaderboard()
	if not leaderboard:
		return callback.emit_signal("done", res)

	var download = yield(user_stats.download_leaderboard_entries(leaderboard, method, begin, end), "done")
	if not download:
		return callback.emit_signal("done", res)

	var entries = download.get_entries()
	if not entries:
		return callback.emit_signal("done", res)
	
	for i in download.get_entry_count():
		var entry = user_stats.get_downloaded_leaderboard_entry(entries, i, max_details)
		if not entry:
			continue

		var score := {}
		score["global_rank"] = entry.get_global_rank()
		score["score"] = entry.get_score()
		score["details"] = entry.get_details()

		if entry.get_steam_id_user() and user.get_steam_id():
			score["id"] = entry.get_steam_id_user().get_account_id()
			score["is_player"] = user.get_steam_id().get_account_id() == entry.get_steam_id_user().get_account_id()
		else:
			score["id"] = 0
			score["is_player"] = false

		if not friends.request_user_information(entry.get_steam_id_user(), true):
			score["persona_name"] = friends.get_friend_persona_name(entry.get_steam_id_user())
		else:
			score["persona_name"] = "Frank"
			
		res.push_back(score)
	
	return callback.emit_signal("done", res)

func activate_game_overlay_to_web_page(url:String) -> void:
	friends.activate_game_overlay_to_web_page(url)

func activate_game_overlay_to_store(app_id:int, where:int = 0) -> void:
	friends.activate_game_overlay_to_store(app_id, where)
