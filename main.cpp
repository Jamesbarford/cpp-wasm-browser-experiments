/**
 * File is a public api for the web assembly module
 */

#include <emscripten/bind.h>
#include "util.cpp"

void cast_func(uintptr_t bufferAddress, unsigned int size)
{
    double_arr(reinterpret_cast<unsigned int *>(bufferAddress), size);
}

EMSCRIPTEN_BINDINGS(my_module)
{
    emscripten::function("echo", &echo);
    emscripten::function("double_arr", &cast_func);
    emscripten::function("json_tokenizer", &json_tokenizer);
}