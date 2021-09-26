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

        void add_key(std::string name, int value)
        {
            keys.push_back(name);
            values.push_back(value);
        }

        int has_key(std::string key)
        {
            for (int i = 0; i < (int) values.size(); i++)
            {
                std::string name = keys.at(i);
                if (name == key) return 1;
            }
            return 0;
        }
        
        int get_keyvalue(std::string key)
        {
            int tok;
            for (int i = 0; i < (int) values.size(); i++)
            {
                std::string name = keys.at(i);
                if (name == key) tok = values.at(i);
            }
            return tok;
        }
        void clear()
        {
            keys.clear(); values.clear();
        }
    };
    
} // namespace Dictionary


#endif