#!/bin/bash

git submodule update --init --recursive

mkdir -p work
cd work
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build . --target install
cd ../app/addons/steam_api
pwd
cp -fr ../../../work/install/lib/* .
