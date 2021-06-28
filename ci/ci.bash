#!/bin/bash

PLATFORM=$1
ARCH=$2

mkdir -p work
cd work

if [[ $PLATFORM == "linux" ]]; then
  cmake .. -DCMAKE_BUILD_TYPE=Release
fi


cmake --build . --config Release --target install
