#!/usr/bin/sh

# try to identify platform
PLATFORM="generic"

if [ "$(uname -s | grep -i 'linux')" ]
then
	PLATFORM="linux"

elif [ "$(uname -s | grep -i 'mingw')" ]
then
	PLATFORM="windows"

fi

# prepare build directory
BUILD_DIR="build-"$PLATFORM
mkdir -p $BUILD_DIR;

# run cmake - generate platform specific build files
cmake ./ -B $BUILD_DIR;

# try to build
if [ "$PLATFORM" = "linux" ]
then
	# run make
	make -C $BUILD_DIR;
	# copy build result (for convenience)
	cp $BUILD_DIR/demo.exe ./;

else
	echo "Manual build required.";

fi
