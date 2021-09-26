#ifndef LEXER_H
#define LEXER_H

#include "tokens.h"

#include <vector>
#include <string>

namespace lipsem
{
    std::vector<lipsem::token> tokenize(std::string code);
}

#endif
