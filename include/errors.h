#ifndef ERRORS_H
#define ERRORS_H

#include "tokens.h"

#include <string>
#include <iostream>

namespace lipsem
{
    struct parsing_error
    {
        lipsem::token tok;
        std::string msg;
        void raise()
        {
            std::cout << "Parsing Error on line " << tok.line << "." << std::endl;
            std::cout << msg << std::endl;
        }
    };
    struct unknown_error
    {
        int is_runtime;

        std::string name;
        std::string msg;
        lipsem::token tok;
        void raise()
        {
            if (is_runtime)
            {
                std::cout << name << " found." << std::endl;
                std::cout << msg << std::endl;
            } else {
                std::cout << name << " on line " << tok.line << "." << std::endl;
                std::cout << msg << std::endl;
            }
        }
    };
} // namespace lipsem


#endif