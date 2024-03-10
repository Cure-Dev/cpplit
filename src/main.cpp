#include <iostream>
#include <string>
#include <vector>

#include <stdexcept>

#include <locale>

#include "exceptions/exception.hpp"
#include "exceptions/fserrs.hpp"

#include "exceptions/handler/lex.hpp"

#include "lex/lexer.hpp"
#include "exceptions/lex_errors.hpp"
#include "lex/tokens.hpp"

#include "parse/parser.hpp"
#include "parse/nodes.hpp"

#include "ansi.hpp"

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

            // lexing...
            try {
                std::wstring o = lex(filepath).view();
                if (out_is_redired) {
                    o = rmansi(o);
                }
                std::wcout << o << std::endl;
            }
            catch (lexical_error* e) {
                // make_output_header(std::wstring (filepath.begin(), filepath.end()), source, e, language::en_us);
                handle_lexical_error(e, language::en_us);
                return 1;
            }
        }
        
    }

    else if (command == "parse") {
        std::string filepath = args[2];

        try {
            node* ast = parse_exe(filepath);
            std::wstring o = ast->view();
            if (out_is_redired) {
                o = rmansi(o);
            }
            std::wcout << o;
        }
        catch (const char* e) {
            std::cout << e << std::endl;
            return 1;
        }
        catch (exception* e) {
            std::wcout << e->msg(language::en_us) << std::endl;
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
        catch (lexical_error* e) {
            handle_lexical_error(e, language::zh_cn);
            return 1;
        }
        catch (const char* e) {
            std::cout << e << std::endl;
            return 1;
        }
        catch (std::wstring e) {
            std::wcout << e << std::endl;
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