cmake_minimum_required(VERSION 3.10)
project(steamsdk-godot)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "../app/addons/steam_api" CACHE PATH "..." FORCE)
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

add_definitions("-std=c++11")

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake"
                EXPECTED_HASH SHA256=396e16d0f5eabdc6a14afddbcfff62a54a7ee75c6da23f32f7a31bc85db23484
                TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_configure(REQUIRES godot-cpp/cci.3.2-20200130
                      GENERATORS cmake_find_package)

conan_cmake_autodetect(settings)

conan_cmake_install(PATH_OR_REFERENCE .
                    BUILD missing
                    REMOTE conan-center
                    SETTINGS ${settings})

find_package(godot-cpp)

set(CMAKE_INSTALL_RPATH "$ORIGIN")

add_library(steamsdk-godot SHARED src/Godot.cpp)

set_target_properties(
  steamsdk-godot
  PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
)

target_include_directories(steamsdk-godot PUBLIC lib/steam-sdk/public)

if(APPLE)
  set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
  
  find_library(
    STEAM_API 
    NAMES libsteam_api steam_api
    REQUIRED 
    PATHS lib/steam-sdk/redistributable_bin/osx
  )
else()
  find_library(
    STEAM_API 
    NAMES libsteam_api steam_api64 steam_api
    REQUIRED 
    PATHS lib/steam-sdk/redistributable_bin/win64 lib/steam-sdk/redistributable_bin/linux64
  )
endif()

target_link_libraries(
  steamsdk-godot
  PRIVATE
    godot-cpp::godot-cpp
    ${STEAM_API}
)

install(TARGETS steamsdk-godot DESTINATION .)

