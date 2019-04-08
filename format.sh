#!/usr/bin/sh

# format source code
# clang-format --style=LLVM -i src/*.cpp include/*.hpp
clang-format --style=file -i core/*/*.cpp core/*/*.hpp exercises/*/*.cpp exercises/*/*.hpp