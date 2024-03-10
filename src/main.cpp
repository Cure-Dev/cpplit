#include <iostream>
#include <string>
#include <vector>

#include <stdexcept>

#include <locale>

#include "ansi.hpp"

#include "exceptions/exception.hpp"


#include "lex/lexer.hpp"
#include "exceptions/lex_errors.hpp"
#include "lex/tokens.hpp"

#include "parse/parser.hpp"
#include "parse/nodes.hpp"

#include "semantic/class.hpp"
#include "semantic/environment.hpp"

#include "utils/ranges.hpp"

int main(int argc, char** args) {

    std::locale::global(std::locale(""));

    // losh

    std::string command = args[1];

    if (command == "lex") {

        if (args[2] == NULL) {
            throw;
        }
        else {

            std::string filepath = args[2];
            // bool color;
            try {
                std::wstring o = lex(filepath).view();
                std::wcout << rmansi(o) << std::endl;
            }
            catch (exception* e) {
                std::wcerr << e->msg(language::en_us) << std::endl;
                return 1;
            }
        }
        
    }

    else if (command == "parse") {
        std::string filepath = args[2];

        try {
            node* ast = parse_exe(filepath);
            std::wstring o = ast->view();
            std::wcout << rmansi(o);
        }
        catch (const char* e) {
            std::cerr << e << std::endl;
            return 1;
        }
        catch (exception* e) {
            std::wcerr << e->msg(language::en_us) << std::endl;
            return 1;
        }
    }

    else if (command == "run") {
        std::string filepath = args[2];

        try {
            execution_block* ast = parse_exe(filepath);

            auto env = environment {};
            ast->exec(env);
        }
        catch (exception* e) {
            std::wcerr << e->msg(language::en_us) << std::endl;
            return 1;
        }
        catch (const char* e) {
            std::cerr << e << std::endl;
            return 1;
        }
        catch (std::wstring e) {
            std::wcerr << e << std::endl;
            return 1;
        }
    }

    else if (command == "test") {
/*        auto ofunc = new lit_io_output {};
        ofunc->call({ new semantic_object_builtin_string { L"hello, world!" } });

        auto var_list = environment {};
        var_list.insert({ L"val", new semantic_object_builtin_string { L"hello, world!" }});*/
        ranges range = { {10, 100}};
        std::cout << range.include(3) << range.include(50);
    }

    else {
        std::wcout << "no command or unknown command.\n";
    }

    return 0;
}