#!/bin/bash

mkdir -p work
cd work
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build . --target install
mkdir -p ../app/bin/
cd ../app/bin
pwd
cp -fr ../../work/install/lib/* .
