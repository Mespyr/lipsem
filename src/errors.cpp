#include "../include/errors.h"

void lipsem::parsing_error::raise()
{
    std::cout << "Parsing Error on line " << tok.line << "." << std::endl;
    std::cout << msg << std::endl;
}

void lipsem::unknown_error::raise()
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
