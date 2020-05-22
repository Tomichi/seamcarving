#!/bin/bash

CURRENT_DIR=$(pwd)
GOOGLE_TEST_LIB_PATH="${CURRENT_DIR}libs/googletest"

if [ ! -d  $GOOGLE_TEST_LIB_PATH ] ; then
  mkdir -p libs
  cd "${CURRENT_DIR}/libs" || exit
  git clone https://github.com/google/googletest/
fi

echo 'Project seamcarving was setup'
