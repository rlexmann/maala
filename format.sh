#!/usr/bin/sh

# format source code
DIRS_TO_PROCESS=("core" "tests" "exercises")
FILELIST=""
for DIR in "${DIRS_TO_PROCESS[@]}"
do
	FILELIST="$FILELIST $DIR/*/*.cpp $DIR/*/*.hpp"
done
(set -x; clang-format --style=file -i $FILELIST)

# read -n 1 -s -r -p "Press any key to continue..."