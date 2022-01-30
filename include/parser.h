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

        void add_node(std::string name, std::vector<lipsem::token> value);
        void print();
        int has_key(std::string key);
        std::vector<lipsem::token> get_keyvalue(std::string key);
    };
} // namespace lipsem

lipsem::ast parse(std::vector<lipsem::token> code);

#endif
