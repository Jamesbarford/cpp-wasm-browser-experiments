#!/bin/bash

# https://github.com/emscripten-core/emscripten/wiki/WebAssembly-Standalone
emcc --bind -o ./main.js ./main.cpp -s ALLOW_MEMORY_GROWTH=1