#!/bin/bash

SSF_DIR=`pwd`
BUILD_DIR=$SSF_DIR/build

function build()
{
  mkdir $BUILD_DIR && cd $BUILD_DIR
  cmake -DBUILD_TESTS=OFF $SSF_DIR
  make -j2
}

function test()
{
  mkdir $BUILD_DIR && cd $BUILD_DIR
  cmake -DBUILD_TESTS=ON $SSF_DIR
  make 
  make test
  cd ..
  gcov build/components/core/CMakeFiles/ssf_core.dir/src/*.cpp*
  bash <(curl -s https://codecov.io/bash)
}

case $TASK in
  build ) build;;
  test ) test;;
esac
