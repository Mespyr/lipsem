#ifndef TOKENS_H
#define TOKENS_H

#include <string>
#include <iostream>

namespace lipsem
{
    struct token {
        unsigned int line;
        std::string value;

        void print()
        {
            std::cout << "Line: " << line << ", Value: " << value << std::endl;
        }
    };
} // namespace lipsem


#endif