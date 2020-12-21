#include <emscripten/bind.h>
#include <string>

std::string echo(std::string word)
{
    return word.substr(0, 3);
}

void double_arr(unsigned int arr[], int size)
{
    for (int i = 0; i < size; i++)
        arr[i] = arr[i] * 2;
}

void cast_func(uintptr_t bufferAddress, unsigned int size)
{
    double_arr(reinterpret_cast<unsigned int *>(bufferAddress), size);
}

EMSCRIPTEN_BINDINGS(my_module)
{
    emscripten::function("echo", &echo);
    emscripten::function("double_arr", &cast_func);
}