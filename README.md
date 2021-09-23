# Godot-Steam-API 💨

> **Godot Steam integration using GDNative.** Supports 💰Windows, 🐧Linux & 🍏MacOS (x86_x64/arm64).

# Getting Started
1. Enable the plugin in the Project Settings
2. There will now be a SteamAPI tab in the Project Settings, follow the instructions to import the Steam SDK files
3. Make sure Steam is running

Now you can use the following functions:
```gdscript
Steam.set_achievement("gator_god")
Steam.get_achievement("gator_god")
Steam.clear_achievement("gator_god")
Steam.set_leaderboard_score("High Scores", 1000)
var scores = yield(Steam.get_leaderboard_scores("High Scores", 0, 10), "done")
```

## Buildling localy on Windows

1. Clone this repo.
  ``` sh
  git clone git@github.com:samsface/godot-steam-api.git
  ```

2. Download and install:
    - https://cmake.org/download
    - https://visualstudio.microsoft.com/downloads (community edition is fine)
    - https://www.python.org/downloads (download Python3 if you just have 2.7)

3. Install Conan, a C++ package manager.
    ``` sh
    # in root directory of this project
    pip3 install conan
    ```

4. Download the steam sdk and extract it into the lib directory of this project.
    > If your files are now laid out like this: `godot-steam-api/lib/steam-sdk/redistributable_bin/win64/steam_api64.dll`; you've done it correctly. 

5. Generate the Visual Studio project.
    ```sh
    # in root directory of this project
    mkdir work && cd work && cmake .. && start .
    ```

6. Open `steamsdk-godot.sln` and build. CMake will install the built dlls into the example project for you every time you build. Just open the example project and your good. The library is also reloadable so no need to restart Godot every build.
