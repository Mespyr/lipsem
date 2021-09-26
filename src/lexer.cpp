#include "../include/lexer.h"
#include "../include/tokens.h"

#include <vector>
#include <string>

std::vector<lipsem::token> lipsem::tokenize(std::string code)
{
    std::vector<lipsem::token> tokens;

    int len = code.length();
    std::string word;
    unsigned int linenum = 1;

    for(int i = 0; i < len; i++)
    {
        std::string cc;
        char c = code.at(i);
        
        if(isspace(c)) {
            if (word != "") {
                lipsem::token tok{ linenum, word };
                tokens.push_back(tok);
            }
            if (c=='\n')
            {
                linenum++;
            }

            word = "";
        }

        else word.push_back(c);
    }

    return tokens;
}
