#!/bin/bash

git submodule update --init --recursive

python3 generation/test.py
clang-format -i src/generated.cpp

#mkdir -p work
#cd work


#cmake .. -DCMAKE_BUILD_TYPE=Debug && cmake --build . --target install ../app/addons/steam_api/
