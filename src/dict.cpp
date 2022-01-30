#include "../include/dict.h"

void Dictionary::dict::add_key(std::string name, int value)
{
    keys.push_back(name);
    values.push_back(value);
}

int Dictionary::dict::has_key(std::string key)
{
    for (int i = 0; i < (int) values.size(); i++)
    {
        std::string name = keys.at(i);
        if (name == key) return 1;
    }
    return 0;
}

int Dictionary::dict::get_keyvalue(std::string key)
{
    int tok;
    for (int i = 0; i < (int) values.size(); i++)
    {
        std::string name = keys.at(i);
        if (name == key) tok = values.at(i);
    }
    return tok;
}

void Dictionary::dict::clear()
{
    keys.clear();
    values.clear();
}
