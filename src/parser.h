#ifndef PARSER_H
#define PARSER_H

#include "tokens.h"
#include "errors.h"

#include <vector>
#include <string>
#include <iostream>

namespace lipsem
{
    struct ast
    {
        std::vector<std::string> keys;
        std::vector<std::vector<lipsem::token>> values;
        bool error = false;
        lipsem::parsing_error msg;

        void add_node(std::string name, std::vector<lipsem::token> value)
        {
            keys.push_back(name);
            values.push_back(value);
        }
        void print()
        {
            for (int i = 0; i < (int) values.size(); i++)
            {
                std::vector<lipsem::token> node = values.at(i);
                std::string name = keys.at(i);
                std::cout << name << std::endl;
                for (int a = 0; a < (int) node.size(); a++)
                {
                    lipsem::token tok = node.at(a);
                    std::cout << "    ";
                    tok.print();
                }
            }
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
        
        std::vector<lipsem::token> get_keyvalue(std::string key)
        {
            std::vector<lipsem::token> tok;
            for (int i = 0; i < (int) values.size(); i++)
            {
                std::string name = keys.at(i);
                if (name == key) tok = values.at(i);
            }
            return tok;
        }
    };
} // namespace lipsem

lipsem::ast parse(std::vector<lipsem::token> code);

#endif