cmake_minimum_required(VERSION 3.10)
project(steamsdk-godot)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "install" CACHE PATH "..." FORCE)
endif()

add_subdirectory(lib/godot-cpp)

set(CMAKE_INSTALL_RPATH "$ORIGIN")

add_library(steamsdk-godot SHARED src/Godot.cpp)

set_target_properties(
  steamsdk-godot
  PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
)

target_include_directories(steamsdk-godot PUBLIC lib/steam-sdk/public)

find_library(STEAM_API NAMES steam_api libsteam_api REQUIRED PATHS lib/steam-sdk/redistributable_bin/linux64)

target_link_libraries(
  steamsdk-godot
  PRIVATE
    godot-cpp
    ${STEAM_API}
)

install(FILES ${STEAM_API} DESTINATION lib)
install(TARGETS steamsdk-godot DESTINATION lib)
