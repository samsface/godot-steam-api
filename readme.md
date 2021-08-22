# Godot-Steam-API 💨
**Godot Steam integration using GDNative.**

# Getting Started
1. Enable the plugin in the Project Settings
2. There will now be a SteamAPI tab in the Project Settings, follow the instructions to import the Steam SDK files
3. Make sure Steam is running

Now you can use the following functions to manage Steam Achievements:
``` python
Steam.set_achievement(name:String)
Steam.get_achievement(name:String)
Steam.clear_achievement(name:String)
```
