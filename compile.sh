#!/bin/bash

COMPILE_TYPE=$1
FILE=$2

if [[ $COMPILE_TYPE == 'cpp' ]]; then
    OUTPUT=${FILE%.*}.out

    clang++ --std=c++17 $FILE -o $OUTPUT && ./$OUTPUT
    exit 0
fi

if [[ $COMPILE_TYPE == 'emcc' ]]; then
    # https://github.com/emscripten-core/emscripten/wiki/WebAssembly-Standalone
    emcc --bind -o ./main.js ./main.cpp -s ALLOW_MEMORY_GROWTH=1
    exit 0
fi