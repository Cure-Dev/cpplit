#include <iostream>
#include "language/language.hpp"
#include "exceptions/lex.h"

#include "ansi.h"

#ifndef _HANDLER_LEX_H_
#define _HANDLER_LEX_H_

int* count_line_and_column(std::wstring src, int index) {
    int line = 1;
    int column = 1;

    for (int i = 0; i < index; i += 1) {
        if (src[i] == L'\n') { //! NEL, CRLF?
            line += 1;
            column = 1;
        }
        else {
            column += 1;
        }
    }

    return new int[2] {line, column};
}

void make_output_header(std::wstring filepath, std::wstring src, lexical_error* e, language L) {
    int* _ = count_line_and_column(src, e->BEGIN);
    int line = _[0], column = _[1];
    delete _;

    switch (L) {
    case language::zh_cn:
        break; //
    default:
        std::wcerr << "In file \"" << filepath << "\", at line " << line << ", column " << column << L"\n";
    }
}

void handle_lexical_error(lexical_error* e, language L) {

/*	catch (invalid_character e) {
		int* line_and_column = count_line_and_column(src, e.BEGIN);
		std::wcerr << "[Lit] Invalid character '" << src[e.BEGIN] << "' (U+" << std::hex << int(src[e.BEGIN]) << std::dec << ") "
					<< "at line " << line_and_column[0] << ", column " << line_and_column[1] << ".\n";
		throw e;
	}*/


    std::wstring info;
    if (err_is_redired) {
        info = rmansi(e->msg(L));
    }
    else {
        info = e->msg(L);
    }

    std::wcerr << info << std::endl;


/*    catch (exception* e) {
        // std::wcerr << "Err not catched" << std::endl;
        // throw e;
    }*/

/*	catch (std::exception e) {
        std::wcerr << "Internal Error" << std::endl;
        throw e;
    }*/

}

#endif