# Godot-Steam-API

> **Godot Steam integration without rebuilding Godot.** Supports 💰Windows, 🐧Linux & 🍏MacOS (x86_x64/arm64).

## Getting Started
1. Download this plugin through Godot's asset library https://godotengine.org/asset-library/asset/1020
2. There should now be a SteamAPI tab in your Project Settings, follow the instructions to configure the SteamAPI for your game *(Takes a few seconds)*.

Now you can use the following functions:
```gdscript
# acheivements
Steam.set_achievement("gator_god")
Steam.get_achievement("gator_god")
Steam.clear_achievement("gator_god")

# leaderboards
Steam.set_leaderboard_score("High Scores", 1000)
var scores = yield(Steam.get_leaderboard_scores("High Scores", 0, 10), "done")

# overlay
Steam.activate_game_overlay_to_web_page("https://steamcommunity.com/")
Steam.activate_game_overlay_to_store(1435470, Steam.OverlayToStoreFlag.AddToCart)
```

## Testing an exported build

Steam integration doesn't work with exported builds straight away. You'll have to either:
- Upload your build to Steam or
- Create a file in the same directory as your exported build named `steamapp_id.txt` with just your steam app id in it. Though do not upload this file as part of your build.
