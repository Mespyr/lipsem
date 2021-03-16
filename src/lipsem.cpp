#include "lipsem.h"
#include "parser.h"
#include "errors.h"
#include "tokens.h"

#include <vector>
#include <algorithm>
#include <iostream>

void lipsem::Reader::eval()
{
    if (!ast.has_key("main:"))
    {
        has_error = true;
        eof = 1;
        error = unknown_error{1, "Runtime Error", "No 'main' function found."};
    }
    else {
        name = "main:";
        while (!eof)
        {
            next();
        }
    }
}

void lipsem::Reader::next()
{
    idx++;
    std::vector<lipsem::token> node = ast.get_keyvalue(name);
    int size = node.size();
    if (idx >= size) {
        int screenshots_size = screenstack.size();
        if (screenshots_size == 0) {
            eof = 1;
        } else {
            lipsem::Screenshot lastshot = screenstack.back();
            screenstack.pop_back();
            name = lastshot.name;
            idx = lastshot.idx;
            labels = lastshot.labels;
        }
        return;
    }
    lipsem::token tok = node.at(idx);
    // tok.print();
    
    
    // Keywords
    if (tok.value == "pop") {
        if ((int) stack.size() == 0) {
            has_error = true;
            eof = 1;
            error = unknown_error{0, "Stack Error", "Can't pop from empty stack.", tok};
        } else {
            stack.pop_back();
        }
    }
    else if (is_int(tok.value)) stack.push_back(atoi(tok.value.c_str()));
    else if (tok.value == "pchar") {
        if ((int) stack.size() == 0) {
            has_error = true;
            eof = 1;
            error = unknown_error{0, "Stack Error", "Can't get last value from empty stack.", tok};
        } else {
            putchar(stack.back());
        }
    }
    else if (tok.value == "add") {
        if ((int) stack.size() == 1 or (int) stack.size() == 0) {
            has_error = true;
            eof = 1;
            error = unknown_error{0, "Stack Error", "Can't pop from stack with size of " + std::to_string(stack.size()) + ".", tok};
        } else {
            int i = stack.back();
            stack.pop_back();
            int o = stack.back();
            stack.pop_back();
            stack.push_back(i+o);
        }
    }    
    else if (tok.value == "sub") {
        if ((int) stack.size() == 1 or (int) stack.size() == 0) {
            has_error = true;
            eof = 1;
            error = unknown_error{0, "Stack Error", "Can't pop from stack with size of " + std::to_string(stack.size()) + ".", tok};
        } else {
            int i = stack.back();
            stack.pop_back();
            int o = stack.back();
            stack.pop_back();
            stack.push_back(i-o);
        }
    }
    else if (tok.value == "flip") {
        std::reverse(stack.begin(), stack.end());
    }
    else if (tok.value == "dupe") {
        if ((int) stack.size() == 0) {
            has_error = true;
            eof = 1;
            error = unknown_error{0, "Stack Error", "Can't get last value from empty stack.", tok};
        } else {
            stack.push_back(stack.back());
        }
    }
    else if (tok.value == "print") {
        if ((int) stack.size() == 0) {
            has_error = true;
            eof = 1;
            error = unknown_error{0, "Stack Error", "Can't get last value from empty stack.", tok};
        } else {
            std::cout << stack.back();
        }
    }
    else if (tok.value == "jmp") {
        if (idx+1==size) {
            has_error = true;
            eof = 1;
            error = unknown_error{0, "EOF Error", "Unexpected EOF while parsing.", tok};
        } else {
            idx++;
            lipsem::token skip_size = node.at(idx);
            if (is_int(skip_size.value)) {
                int skip = atoi(skip_size.value.c_str());

                if (idx+1==size) {
                    has_error = true;
                    eof = 1;
                    error = unknown_error{0, "EOF Error", "Unexpected EOF while parsing.", tok};
                } else {
                    idx++;
                    lipsem::token wanted_size = node.at(idx);
                    
                    if (is_int(wanted_size.value)) {
                        int w_size = atoi(wanted_size.value.c_str());
                        if (w_size == (int) stack.size()) idx+=skip;
                    } else {
                        has_error = true;
                        eof = 1;
                        error = unknown_error{0, "Type Error", "Stack size can't be a non-integer.", tok};
                    }

                }
            } else {
                has_error = true;
                eof = 1;
                error = unknown_error{0, "Type Error", "Can't set skip size for `jmp` to a non-integer.", tok};
            }
        }
    }
    else if (tok.value == "gchar") stack.push_back(getchar());
    else if (tok.value == "gline") {
        std::string line;
        std::getline (std::cin, line);
        for (int i = 0; i < (int) line.length(); i++)
        {
            char n = line.at(i);
            stack.push_back(n);
        }
    }
    else if (tok.value == "bk") {
        stack.insert(stack.begin(), stack.back());
        stack.pop_back();
    }
    else if (tok.value == "tv") {
        if (idx+1==size) {
            has_error = true;
            eof = 1;
            error = unknown_error{0, "EOF Error", "Unexpected EOF while parsing.", tok};
        } else {
            idx++;
            lipsem::token skip_size = node.at(idx);
            if (is_int(skip_size.value)) {
                int skip = atoi(skip_size.value.c_str());

                if (idx+1==size) {
                    has_error = true;
                    eof = 1;
                    error = unknown_error{0, "EOF Error", "Unexpected EOF while parsing.", tok};
                } else {
                    idx++;
                    lipsem::token wanted_size = node.at(idx);
                    
                    if (is_int(wanted_size.value)) {
                        int w_size = atoi(wanted_size.value.c_str());
                        if (w_size == stack.back()) idx+=skip;
                    } else {
                        has_error = true;
                        eof = 1;
                        error = unknown_error{0, "Type Error", "Stack size can't be a non-integer.", tok};
                    }

                }
            } else {
                has_error = true;
                eof = 1;
                error = unknown_error{0, "Type Error", "Can't set skip size for `tv` to a non-integer.", tok};
            }
        }
    }
    // custom
    else if (tok.value.front() == '.')
    {
        if ((int) tok.value.length() == 1) {
            has_error = true;
            eof = 1;
            error = unknown_error{0, "Illegal Char Error", "Unexpected '.' found while parsing.\nIf this is a function call, remember to have the function name after the period.", tok};
        } else {
            std::string key = tok.value.substr(1) + ":";
            if (ast.has_key(key)) {
                lipsem::Screenshot shot{idx, name, labels};
                screenstack.push_back(shot);
                name = key;
                idx = -1;
                labels.clear();
            } else {
                has_error = true;
                eof = 1;
                error = unknown_error{0, "Name Error", "Undefine function " + tok.value + ".", tok};
            }
        }
    }
    else if (tok.value.front() == '`')
    {
        if ((int) tok.value.length() == 1) {
            has_error = true;
            eof = 1;
            error = unknown_error{0, "Illegal Char Error", "Unexpected '`' found while parsing.", tok};
        } else {
            std::string key = tok.value.substr(1);
            for (int i = 0; i < (int) key.size(); i++)
            {
                char c = key.at(i);
                stack.push_back(c);
            }
        }
    }
    else if (tok.value.front() == ':')
    {
        if ((int) tok.value.length() == 1) {
            has_error = true;
            eof = 1;
            error = unknown_error{0, "Illegal Char Error", "Unexpected ':' found while parsing.", tok};
        } else {
            std::string key = tok.value.substr(1);
            labels.add_key(key, idx);
        }
    }
    else if (tok.value.front() == '-')
    {
        if ((int) tok.value.length() == 1) {
            has_error = true;
            eof = 1;
            error = unknown_error{0, "Illegal Char Error", "Unexpected '-' found while parsing.", tok};
        } else {
            std::string key = tok.value.substr(1);
            if (labels.has_key(key)) idx = labels.get_keyvalue(key);
            else {
                has_error = true;
                eof = 1;
                error = unknown_error{0, "Name Error", "No label called '"+key+"'.", tok};
            }
        }
    }
    else if (tok.value.front() == '~')
    {
        if ((int) tok.value.length() == 1) {
            has_error = true;
            eof = 1;
            error = unknown_error{0, "Illegal Char Error", "Unexpected '~' found while parsing.", tok};
        } else {
            std::string key = tok.value.substr(1);
            if (labels.has_key(key)) {
                int size = stack.size();
                if (size) {
                    idx = labels.get_keyvalue(key);
                }
            }
            else {
                has_error = true;
                eof = 1;
                error = unknown_error{0, "Name Error", "No label called '"+key+"'.", tok};
            }
        }
    }
}