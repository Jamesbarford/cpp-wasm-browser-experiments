#include <string>
#include <map>
#include <iostream>
#include "TypeDefs.hpp"

class TypeMapping
{
public:
    static void insert_into_type_mapping(TypeMapping *t_map, std::string &key, std::string &value)
    {
        t_map->insert(key, value);
    }

    void insert(std::string &key, std::string &value)
    {
        if (raw_type_to_json.count(value) == 0)
            throw std::invalid_argument("Invalid type valid type : '" + value + "' valid types: " + valid_types);

        current_type_mapping.insert({key, raw_type_to_json.at(value)});
    }

    static void bound_insert(TypeMapping *self, std::string key, std::string value)
    {
        self->insert(key, value);
    }

    bool has(std::string &key)
    {
        if (current_type_mapping.find(key) != current_type_mapping.end())
            return true;
        return false;
    }

    JSON_TYPES get(std::string &key)
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
    std::map<std::string, JSON_TYPES> current_type_mapping;
    std::map<std::string, JSON_TYPES> raw_type_to_json = {
        {"string", JSON_TYPES::STRING},
        {"number", JSON_TYPES::NUMBER}};
    std::map<JSON_TYPES, std::string> json_type_to_raw = {
        {JSON_TYPES::STRING, "string"},
        {JSON_TYPES::NUMBER, "number"}};
};