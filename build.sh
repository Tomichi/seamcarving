#!/bin/bash

mkdir -p "$(pwd)/build/"
cd build
cmake ..
make all
./tests/Necklace_tests
./src/Necklace_run