#!/bin/bash

mkdir -p work
cd work

cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=install/lib
cmake --build . --config Release --target install

unameOut="$(uname -s)"
case "${unameOut}" in
    Linux*)     machine=linux;;
    Darwin*)    machine=macos;;
    CYGWIN*)    machine=windows;;
    MINGW*)     machine=windows;;
    *)          machine="${unameOut}"
esac
echo ${machine}

if [ "${machine}" = "linux" ]; then
  strip install/lib/*
fi
