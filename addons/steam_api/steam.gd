extends SteamI

func test_running_godot_from_steam() -> bool:
	var godot_steam_app_id := 404790
	if Steam.utils.get_app_id() == godot_steam_app_id:
		push_error("You are running the Godot editor from Steam. You must launch the Godot editor outside of Steam for Steam integration to work properly. Steam can only run one application at a time.")
		return true
	return false

func test_steam_api_missing() -> bool:
	var file := File.new()
	for f in ["steam_api64.dll", "libsteam_api.so", "libsteam_api.dylib"]:
		if not file.file_exists("res://addons/steam_api/%s" % f):
			push_error("You are missing the steamsdk libraries. You must download the steamsdk from steamworks and copy 'steam_api64.dll', 'libsteam_api.so' and 'libsteam_api.dylib' into 'res://addons/steam_api'. See the Steam API tab in project settings for full instructions.")
			return true
	
	return false

func _ready() -> void:
	if not OS.has_feature("standalone"):
		if test_steam_api_missing():
			return

	api_ = SteamAPI.new()
	if not api_ or not api_.init():
		api_ = null
		push_error("Failed to init steam api. Is Steam running? Is the plugin activated? Did you do the setup in ProjectSettings > SteamAPI")
		if OS.has_feature("standalone"):
			push_error("You're running an exported build. Steam integration will only work if the game is launched by Steam. Either upload this build to Steam or create a file in the same directory as your exported build named 'steam_appid.txt' with just your steam app id in it.")

		return

	user = User.new(SteamUser.new())
	user_stats = UserStats.new(SteamUserStats.new())
	user_stats.request_current_stats()
	friends = Friends.new(SteamFriends.new())
	utils = Utils.new(SteamUtils.new())

	pause_mode = PAUSE_MODE_PROCESS
	
	if not OS.has_feature("standalone"):
		test_running_godot_from_steam()

#warning-ignore:unused_argument
func _process(delta:float) -> void:
	if api_:
		api_.run_callbacks()
