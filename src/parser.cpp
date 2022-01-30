#include "../include/parser.h"
#include "../include/tokens.h"
#include "../include/errors.h"

#include <vector>

void lipsem::ast::add_node(std::string name, std::vector<lipsem::token> value)
{
    keys.push_back(name);
    values.push_back(value);
}

void lipsem::ast::print()
{
    for (int i = 0; i < (int) values.size(); i++)
    {
        std::vector<lipsem::token> node = values.at(i);
        std::string name = keys.at(i);
        std::cout << name << std::endl;
        for (int a = 0; a < (int) node.size(); a++)
        {
            lipsem::token tok = node.at(a);
            std::cout << "    ";
            tok.print();
        }
    }
}

int lipsem::ast::has_key(std::string key)
{
    for (int i = 0; i < (int) values.size(); i++)
    {
        std::string name = keys.at(i);
        if (name == key) return 1;
    }
    return 0;
}

std::vector<lipsem::token> lipsem::ast::get_keyvalue(std::string key)
{
    std::vector<lipsem::token> tok;
    for (int i = 0; i < (int) values.size(); i++)
    {
        std::string name = keys.at(i);
        if (name == key) tok = values.at(i);
    }
    return tok;
}


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
