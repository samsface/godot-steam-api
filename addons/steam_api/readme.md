# 🚂 Godot-Steam-API

> **Godot Steam integration without rebuilding Godot.** Supports 💰Windows, 🐧Linux & 🍏MacOS (x86_x64/arm64).

## 🏁 Getting Started
1. Download this plugin through Godot's asset library https://godotengine.org/asset-library/asset/1020
2. There should now be a SteamAPI tab in your Project Settings, follow the instructions to configure the SteamAPI for your game *(Takes a few seconds)*.

Now you can use the following functions:
```gdscript
# check steam integration is working and enabled, useful if you publish to multiple stores
Steam.is_init()

# achievements
# check if player already unlocked this achievement
var has_alredy_unlocked_achievement:bool = Steam.get_achievement("gator_god")
# give the player this achievement, benign if they already have it
Steam.set_achievement("gator_god")
# clear this achievement (only for debugging)
Steam.clear_achievement("gator_god")

# leaderboards
Steam.set_leaderboard_score("High Scores", 1000)
# Get the first 10 global high scores
var top_10_global_scores = yield(Steam.get_leaderboard_scores("High Scores", 0, 10), "done")
# Get just the current user's high score
var players_score = yield(Steam.get_leaderboard_scores("High Scores", 0, 0, Steam.LeaderboardDataRequest.GlobalAroundUser), "done")
# Get the current user's high score and the two scores infront and behind
var player_rivals_score = yield(Steam.get_leaderboard_scores("High Scores", -1, 1, Steam.LeaderboardDataRequest.GlobalAroundUser), "done")

# rich presence
# Read the docs: https://partner.steamgames.com/doc/features/enhancedrichpresence as this call has lots of hidden magic
# and use this tool to test: https://steamcommunity.com/dev/testrichpresence
Steam.friends.set_rich_presence("status", "cactus")
Steam.friends.clear_rich_presence()

# overlay
Steam.friends.connect("game_overlay_activated", self, "_on_game_overlay_activated")
Steam.friends.activate_game_overlay_to_web_page("https://steamcommunity.com/")
Steam.friends.activate_game_overlay_to_store(1435470, Steam.OverlayToStoreFlag.AddToCart)
```

## 📄 Documentation

This plugin follows the structure and naming of the offical C++ SteamSDK almost verbatim.
The only major difference is I use snake_case to better integrate with Godot.
That is to say, you can just rely on the offical docs: https://partner.steamgames.com/doc/api.

## 🧪 Testing an exported build

Steam integration doesn't work with exported builds straight away. You'll have to either:
- Upload your build to Steam or
- Create a file in the same directory as your exported build named `steam_appid.txt` with just your steam app id in it. Though do not upload this file as part of your build.

## 😶‍🌫️ Can I publish to Itch.io still?

Yes. There's a switch in `Project Settings > Steam API` that disables the integration, i.e. all calls on the API just do nothing and return/yield null. However it is up to the caller to then safely deal with the null values returned by the API in disabled mode.


## 🤔 Troubleshooting

- Did you follow the instruction in the project settings Steam tab?
- Is Steam running?
- Have you published your acheivments in the SteamWorks console? *Publishing isn't releasing the game, I mean the button that publishes your Store page.*
- Tried uninstalling and reinstalling the plugin 😅?
