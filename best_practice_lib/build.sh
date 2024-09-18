#!/bin/bash

rm -rf build
cmake -S . -B build -DCMAKE_INSTALL_PREFIX=./build/install -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build
cmake --install build