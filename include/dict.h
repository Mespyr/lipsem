#ifndef DICT_H
#define DICT_H

#include <string>
#include <vector>

namespace Dictionary
{
    struct dict
    {
        std::vector<std::string> keys;
        std::vector<int> values;

        void add_key(std::string name, int value);
        int has_key(std::string key);
        int get_keyvalue(std::string key);
        void clear();
    };
    
} // namespace Dictionary


#endif
