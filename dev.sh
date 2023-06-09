#!/bin/bash

git submodule update --init --recursive

mkdir -p work
cd work

python3 ../test.py &> ../src/file.cpp
clang-format -i ../src/file.cpp

cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build . --target install ../app/addons/steam_api/
