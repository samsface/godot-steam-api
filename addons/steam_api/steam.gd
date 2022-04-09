extends SteamI

func _ready() -> void:
	var settings = load("res://addons/steam_api/settings.tres")
	api_ = SteamAPI.new()
	if not api_ or not api_.init():
		api_ = null
		push_error("Failed to init steam api. Is Steam running? Is the plugin activated? Did you do the setup in ProjectSettings > SteamAPI")
		if OS.has_feature("standalone"):
			push_error("You're running an exported build. Steam integration will only work if the game is launched by Steam. Either upload this build to Steam or create a file in the same directory as your exported build named 'steamapp_id.txt' with just your steam app id in it.")

		return

	user = User.new(SteamUser.new())
	user_stats = UserStats.new(SteamUserStats.new())
	user_stats.request_current_stats()
	friends = Friends.new(SteamFriends.new())

#warning-ignore:unused_argument
func _process(delta:float) -> void:
	if api_:
		api_.run_callbacks()
