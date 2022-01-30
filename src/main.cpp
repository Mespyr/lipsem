#include "../include/lexer.h"
#include "../include/tokens.h"
#include "../include/parser.h"
#include "../include/lipsem.h"

#include <iostream>
#include <fstream>
#include <vector>


std::string readfile(std::string filename) 
{
	std::fstream file;
	file.open(filename, std::ios::in);

    if (!file)
    {
        std::cout << "lipsem: Can't open file '" << filename << "'. No such file or directory." << std::endl;
        exit(1);
    }

    std::string code = "";

    std::string tp;
    while (getline(file, tp)) {
        code += tp + '\n';  
    }
    file.close();
    
    return code;
}


int evaluate(std::string code) {
    std::vector<lipsem::token> tokens = lipsem::tokenize(code);
    lipsem::ast ast = parse(tokens);
    if (ast.error) {
        ast.msg.raise();
        return 1;
    }
    lipsem::Reader reader;
    reader.ast = ast;
    reader.eval();
    if (reader.has_error)
    {
        reader.error.raise();
        return 1;
    }
    return 0;
}


int main(int argc, char const *argv[])
{
    if (argc == 1) return 1;
    int exit_status = evaluate(readfile(argv[1]));
    return exit_status;
}
