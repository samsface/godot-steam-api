# Godot Steam API

## Project Vision

- This project plans to expose the Steam API in GDScript as a small few mb GDNative project.
- The API will be exposed verbatim to the C++ interface.
- A simple Godot opionated interface will also be developed to support the most common cases.

## Project Roadmap

The Steam API is pretty huge. The plan is to start with easy common used stuff and work through to bigger stuff.

## Buildling localy on Windows

1. Download and install:
    - https://cmake.org/download
    - https://visualstudio.microsoft.com/downloads (community edition is fine)
    - https://www.python.org/downloads (download Python3 if you just have 2.7)

2. Install Conan, a C++ package manager.
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

7. Open `steamsdk-godot.sln` and build. CMake will install the built dlls into the example project for you every time you build. Just open the example project and your good. The library is also reloadable so no need to restart Godot every build.
