# 🚂 Godot-Steam-API

> **Godot Steam integration without rebuilding Godot.** Supports 💰Windows(x86_x64), 🐧Linux(x86_x64) & 🍏MacOS (x86_x64/arm64).

## 🏁 Getting Started
1. Ensure your game is in your Steam library.
2. Download this plugin through Godot's asset library https://godotengine.org/asset-library/asset/1020
3. There should now be a SteamAPI tab in your Project Settings, follow the instructions to configure the SteamAPI for your game *(Takes a few seconds)*.

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

# stats
# set an integer stat
Steam.user_stats.set_stat("kills", 5)
var kills_stat:int = Steam.user_stats.get_stat("kills")
# set a float stat
Steam.user_stats.set_stat("time", 10.3)
var time_stat:float = Steam.user_stats.get_stat("time")
# show the progress of a stat towards some achievement
Steam.user_stats.indicate_achievement_progress("gator_god", 1, 4)

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

# Check if the game runs on the Steam Deck
Steam.utils.is_running_on_steam_deck()
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

Yes. There's a flag that disables the integration, i.e. all calls on the API just do nothing and return/yield null. However it is up to the caller to then safely deal with the null values returned by the API in disabled mode. You can set the flag in two ways:

A. Set `Project Settings > Steam API > Disable Steam Integration [x]`.  
B. Or add `disable_steam_integration` to your export's feature flags.

## ☁️ Does this support cloud saves?

No and intentionally. You can configure automatic cloud saves in the SteamWorks settings. Just give it a filesystem path and it magically syncs it. We've found this automatic support is, for most use cases, safer than rolling your own.

## 🤔 Who uses this?

A ton of projects on Steam use this plugin. Here's just a few of my favourite:

[👾 Beat Invaders](https://store.steampowered.com/app/1863080/Beat_Invaders/),
[🚀 Space Bandit](https://store.steampowered.com/app/1435470/Space_Bandit),
[🚗 Franz Fury](https://store.steampowered.com/app/1513960/FRANZ_FURY),
[🏌️ The Ballad of Bonky](https://store.steampowered.com/app/1619870/The_Ballad_of_Bonky),
[🔲 Hack Grid](https://store.steampowered.com/app/1543290/Hack_Grid),
[💀 Dark Crypt](https://store.steampowered.com/app/1706170/Dark_Crypt),
[🏔️ Red Nivis](https://store.steampowered.com/app/1928130/Red_Nivis),
[🏰 Sokobos](https://store.steampowered.com/app/1655890/Sokobos),
[🐑 Dark Sheep](https://store.steampowered.com/app/1576490/Dark_Sheep),
[🪞 Mirrorama](https://store.steampowered.com/app/1845050/Mirrorama),
[🌑 Letters from the Moon](https://store.steampowered.com/app/1805720/Letters_From_the_Moon/),
[👩🏾‍🦰 ROTA](https://store.steampowered.com/app/1993830/ROTA/),
[🍩 Donut Dodo](https://store.steampowered.com/app/1779560/Donut_Dodo/).

## 👻 Missing feature?

This plugin doesn't implement the entirety of the Steam API. But if there's a Steam API feature you need, leave a github issue stating why you need the feature and I'll try add support when I can.

## ⁉️ Troubleshooting

- Did you follow the instruction in the project settings Steam tab?
- Is Steam running?
- Have you published your acheivments in the SteamWorks console? *Publishing isn't releasing the game, I mean the button that publishes your Store page chnages.*
- Tried uninstalling and reinstalling the plugin 😅?
