#include <string>
#include <map>
#include <iostream>
#include "TypeDefs.hpp"

class TypeMapping
{
public:
    static void bound_insert(TypeMapping *self, std::string key, std::string value)
    {
        self->insert(key, value);
    }

    void insert(std::string &key, std::string &value)
    {
        if (raw_type_to_json.count(value) == 0)
            throw std::invalid_argument("Invalid type valid type : '" + value + "' valid types: " + valid_types);

        current_type_mapping.insert({key, raw_type_to_json.at(value)});
    }

    bool has(std::string &key)
    {
        if (current_type_mapping.find(key) != current_type_mapping.end())
            return true;
        return false;
    }

    JSON_TYPE get(std::string &key)
    {
        if (!has(key))
            throw std::invalid_argument("No mapping for key : " + key);
        return current_type_mapping.at(key);
    }

    void print_mapping(void (*iteratee)(std::string key_value))
    {
        for (auto &entry : current_type_mapping)
            iteratee(entry.first + ":" + json_type_to_raw.at(entry.second));
    }

private:
    std::string valid_types = "string, number";
    std::map<std::string, JSON_TYPE> current_type_mapping;
    std::map<std::string, JSON_TYPE> raw_type_to_json = {
        {"string", JSON_TYPE::STRING},
        {"number", JSON_TYPE::NUMBER}};
    std::map<JSON_TYPE, std::string> json_type_to_raw = {
        {JSON_TYPE::STRING, "string"},
        {JSON_TYPE::NUMBER, "number"}};
};