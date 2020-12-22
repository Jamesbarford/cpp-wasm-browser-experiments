#include <string>
#include <iostream>

#include "TypeMapping.cpp"
#include "TypeDefs.hpp"

std::string echo(std::string word)
{
    return word;
}

void double_arr(unsigned int arr[], int size)
{
    for (int i = 0; i < size; i++)
        arr[i] = arr[i] * 2;
}

/**
 * @param instructions a json string i.e `"{'foo':'int','bar':'string'}"`
*/
template <typename T>
void _json_tokenizer(std::string json_tokens, void (*iteratee)(T *, std::string, std::string), T *context)
{
    std::string key_value_delimiter = ":";
    std::string pair_delimiter = ",";
    size_t pos = 0;

    // split by pair then by K V
    json_tokens.erase(0, 1);
    json_tokens.erase(json_tokens.size() - 1, json_tokens.size());
    json_tokens.append(pair_delimiter);

    while ((pos = json_tokens.find(pair_delimiter)) != std::string::npos)
    {
        int key_value_position = json_tokens.find(key_value_delimiter);

        if (key_value_position == std::string::npos)
            throw std::invalid_argument("Invalid key value pairing expected a ':' delimiter");

        std::string key = json_tokens.substr(1, key_value_position - 2);
        std::string value = json_tokens.substr(key_value_position + 2, pos - key_value_position - 3);

        iteratee(context, key, value);
        json_tokens.erase(0, pos + pair_delimiter.length());
    }
}

void forwarder(int *c, std::string key, std::string value)
{
    std::cout << key << ":" << value << '\n';
}

void json_tokenizer(std::string instructions)
{
    int y = 1;
    _json_tokenizer(instructions, &forwarder, &y);
}

int main(void)
{
    TypeMapping t_map;
    _json_tokenizer("{'foo':'number','bar':'string'}", &TypeMapping::bound_insert, &t_map);
}
