cmake_minimum_required(VERSION 3.10)
project(steamsdk-godot)

option(BUILD_SHARED_LIBS "Build shared libs" ON)

# build universal binaries on macos
if(APPLE)
  set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64" CACHE STRING "" FORCE)
endif()

set(STEAM_SDK_PATH "lib/steam-sdk" CACHE STRING "Steam SDK path")

# install build into example project by default
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(
    CMAKE_INSTALL_PREFIX "../app/addons/steam_api" 
    CACHE PATH "..." 
    FORCE)
endif()

add_subdirectory(lib/godot-cpp)

# let's us link relative to process on linux
set(CMAKE_INSTALL_RPATH "$ORIGIN")

add_library(steamsdk-godot src/Godot.cpp)

set_target_properties(
  steamsdk-godot
  PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON)

target_include_directories(
  steamsdk-godot 
  PUBLIC 
  ${STEAM_SDK_PATH}/public)

if(APPLE)
  find_library(
    STEAM_API 
    NAMES libsteam_api steam_api
    REQUIRED 
    PATHS ${STEAM_SDK_PATH}/redistributable_bin/osx)
else()
  find_library(
    STEAM_API 
    NAMES libsteam_api steam_api64 steam_api
    REQUIRED 
    PATHS ${STEAM_SDK_PATH}/redistributable_bin/win64 ${STEAM_SDK_PATH}/redistributable_bin/linux64)
endif()

target_link_libraries(
  steamsdk-godot
  PRIVATE
    godot-cpp
    ${STEAM_API})

install(TARGETS steamsdk-godot DESTINATION .)
