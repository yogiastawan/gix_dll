#!/bin/sh

# $1 is buld type: Debug or Release

CC=/usr/bin/clang
CXX=/usr/bin/clang++
BUILD_TYPE=Debug

SOURCE=.

BUILD_OUTPUT=./build

if [[ ! -z "$1" ]]; then
  BUILD_TYPE=$1
fi

rm -rf ./build
mkdir -p ./build

cmake -DCMAKE_BUILD_TYPE:STRING=${BUILD_TYPE} -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER:FILEPATH=${CC} -DCMAKE_CXX_COMPILER:FILEPATH=${CXX} --no-warn-unused-cli -S${SOURCE} -B${BUILD_OUTPUT}
