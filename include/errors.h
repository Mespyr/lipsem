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
        void raise();
    };
    struct unknown_error
    {
        int is_runtime;

        std::string name;
        std::string msg;
        lipsem::token tok;
        void raise();
    };
} // namespace lipsem


#endif
