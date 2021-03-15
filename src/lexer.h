#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <string>
#include "tokens.h"

namespace lipsem
{
    std::vector<lipsem::token> tokenize(std::string code);
}

#endif