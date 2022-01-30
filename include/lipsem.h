#ifndef LIPSEM_H
#define LIPSEM_H


#include "errors.h"
#include "parser.h"
#include "dict.h"

#include <string>

namespace lipsem
{
    // saves last index and function name for faster recursion.
    // When current node is at the EOF, the reader will restore the top screenshot.
    struct Screenshot {
        int idx;
        std::string name;
        Dictionary::dict labels;
    };


    // Will use `next` function to move forward in code and evaluate cell
    // exits when passes eof
    class Reader {
        public:
            lipsem::ast ast;
            int eof = 0;

            // position in code
            int idx = -1;
            std::string name;

            // all stacks
            std::vector<Screenshot> screenstack;
            std::vector<int> stack;

            // tags
            Dictionary::dict labels{};

            // error
            lipsem::unknown_error error;
            bool has_error = false;

            void next();
            void eval();
            int is_int(const std::string& s);
    };
} // namespace lipsem

#endif
