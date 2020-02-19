#!/bin/bash

GOOGLE_TEST_LIB_PATH="libs/googletest"

if [ ! -d  $GOOGLE_TEST_LIB_PATH ] ; then
  mkdir -p libs
  cd libs
  git clone https://github.com/google/googletest/
fi

echo 'Project Neclase was setup'
