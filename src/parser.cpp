#include "parser.h"
#include "tokens.h"
#include "errors.h"

#include <vector>

lipsem::ast parse(std::vector<lipsem::token> code)
{
    lipsem::ast ast{};
    std::vector<lipsem::token> node;

    std::string lb_name = "";
    bool name = false;
    bool in_func = false;

    for(int i = 0; i < (int) code.size(); i++)
    {
        lipsem::token tok = code.at(i);

        if (tok.value == "lb") {
            if (name != true and (int) node.size() == 0) name = true;
            else {
                ast.error = true;
                ast.msg = lipsem::parsing_error{tok, "Unexpected 'lb' token found while parsing."};
                return ast;
            }
            in_func = true;
        }
        
        else if (name == true) {
            if (tok.value.back() != ':' or tok.value == "endl" or (int) node.size() != 0)
            {
                ast.error = true;
                ast.msg = lipsem::parsing_error{tok, "Unexpected '" + tok.value + "' token found while parsing."};
                return ast;
            }
            lb_name = tok.value;
            name = false;
        }

        else if (tok.value == "endl")
        {
            ast.add_node(lb_name, node);
            node.clear();
            in_func = false;
        }

        else if (!in_func) {
            ast.error = true;
            ast.msg = lipsem::parsing_error{tok, "Unexpected '" + tok.value + "' token found while parsing."};
            return ast;
        }
        else node.push_back(tok);
    }
    if (in_func) {
        lipsem::token last = code.back();
        ast.error = true;
        ast.msg = lipsem::parsing_error{last, "No 'endl' token found while parsing."};
    }
    return ast;
}
