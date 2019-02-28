#!/usr/bin/sh
BUILD_DIR=build

# prepare for build
mkdir -p $BUILD_DIR;

# run cmake - generate platform specific build files
cmake ./ -B $BUILD_DIR;

# run make - Linux specific build tool
make -C $BUILD_DIR; 

# copy build result (for convenience)
cp $BUILD_DIR/Demo ./
