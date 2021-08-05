#!/bin/bash

mkdir -p work
cd work

cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release --target install
