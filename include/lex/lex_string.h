#include "lex/tokens.hpp"

#ifndef _LEX_STRING_
#define _LEX_STRING_

bool string_head_matched(wchar_t ch);

token_string* lex_string(std::wstring src, int& i);

#endif