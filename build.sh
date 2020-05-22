#!/bin/bash

BUILD_DIR="$(pwd)/build/"
mkdir -p "${BUILD_DIR}"
cd "${BUILD_DIR}" || exit
cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
make all
./tests/seamcarving_tests
./src/seamcarving_run
