#ifndef TOKENS_H
#define TOKENS_H

#include <string>
#include <iostream>

namespace lipsem
{
    struct token {
        unsigned int line;
        std::string value;

        void print();
    };
} // namespace lipsem


#endif
