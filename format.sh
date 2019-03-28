#!/usr/bin/sh

# format source code
# clang-format --style=Mozilla -i src/*.cpp include/*.hpp
clang-format --style=Mozilla -i core/*/*.cpp core/*/*.hpp exercises/*/*.cpp exercises/*/*.hpp