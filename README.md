# Godot Steam API

## Project Vision

- This project plans to expose the Steam API in GDScript as a small few mb GDNative project.
- The API will be exposed verbatim to the C++ interface.
- A simple Godot opionated interface will also be developed to support the most common cases.

## Project Roadmap

The Steam API is pretty huge. The plan is to start with most commonly requested 
parts of the API and work through.

[] Achievements
[] Leaderboards
[] ??


## Buildling localy on Windows

1. Download and install:
    - https://cmake.org/download
    - https://visualstudio.microsoft.com/downloads
    - https://www.python.org/downloads
2. In a cmd.exe window run `pip3 install conan`
3. In a cmd.exe window run `mkdir work && cd work && cmake .. && start .`
4. Open `steamsdk-godot.sln` and write some bugs.
