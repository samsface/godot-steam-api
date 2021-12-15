## Building yourself

You don't need to compile/build anything for this addon. These instructions are only for people that wish to contribute.

### Buildling Windows

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
    pip3 install conan
    ```

4. Download the [Steam SDK](https://partner.steamgames.com/downloads/steamworks_sdk_152.zip) and extract it into the lib directory were you cloned this project.
    > If your files are now laid out like this: `godot-steam-api/lib/steam-sdk/redistributable_bin/win64/steam_api64.dll`; you've done it correctly. 

5. Generate the Visual Studio project.
    ```sh
    # in root directory were you cloned this project to, e.g. C:/work/godot-steam-api
    mkdir work && cd work && cmake .. && start .
    ```

6. Open `steamsdk-godot.sln` and build. CMake will install the built dlls into the example project for you every time you build. Just open the example project and your good. The library is also reloadable so no need to restart Godot every build.
