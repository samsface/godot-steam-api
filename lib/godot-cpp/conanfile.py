import glob
import os

from conans import ConanFile, tools, CMake
from conans.errors import ConanInvalidConfiguration

class GodotCppConan(ConanFile):
    version = "3.3"
    name = "godot-cpp"
    description = "C++ bindings for the Godot script API"
    license = "MIT"
    url = "https://github.com/conan-io/conan-center-index"
    homepage = "https://github.com/godotengine/godot-cpp"
    topics = ("game-engine", "game-development", "c++")
    settings = "os", "arch", "compiler", "build_type"
    generators = "cmake"

    @property
    def _source_subfolder(self):
        return "source_subfolder"

    def source(self):
        tools.get(**self.conan_data["sources"][self.version], strip_root=True)

        os.rmdir("godot-headers")
        tools.get(**self.conan_data["sources"]["headers"])
        tools.rename(glob.glob("godot-headers-*")[0], "godot-headers")

        scrub = [
            'set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${BUILD_PATH}")',
            'set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BUILD_PATH}")',
            'set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BUILD_PATH}")',
            'SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BUILD_PATH}")',
            'SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BUILD_PATH}")',
            'SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BUILD_PATH}")',
            'SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BUILD_PATH}")',
            'SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BUILD_PATH}")',
            'SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BUILD_PATH}")'
            ]

        for line in scrub:
            tools.replace_in_file("CMakeLists.txt", line, "")

        with open("CMakeLists.txt", "a") as myfile:
            myfile.write("install(DIRECTORY godot-headers/ DESTINATION include)\n")
            myfile.write("install(DIRECTORY include/core DESTINATION include)\n")
            myfile.write("install(DIRECTORY include/core/ DESTINATION include)\n")
            myfile.write("install(DIRECTORY include/gen/ DESTINATION include)\n")
            myfile.write("install(TARGETS godot-cpp)\n")
 

    def _configure_cmake(self):
        cmake = CMake(self)

        if self.settings.os == "Macos":
            cmake.definitions["CMAKE_OSX_ARCHITECTURES"] = "arm64;x86_64"

        cmake.configure()
        return cmake

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()

    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)
    