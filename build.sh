#!/bin/bash

mkdir -p "$(pwd)/build/"
cd build
cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
make all
./tests/Necklace_tests
./src/Necklace_run