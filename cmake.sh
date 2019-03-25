#!/usr/bin/sh
BUILD_DIR=build

# prepare for build
mkdir -p $BUILD_DIR;

# run cmake - generate platform specific build files
cmake ./ -B $BUILD_DIR;

if [ "$(uname -s | grep -i 'linux')" ]
then
	# run make
	make -C $BUILD_DIR;

	# copy build result (for convenience)
	cp $BUILD_DIR/Demo.exe ./;

elif [ "$(uname -s | grep -i 'mingw')" ]
then
	# do something Windows specific
	echo "Manual build required.";

else
	echo "Manual build required.";

fi
