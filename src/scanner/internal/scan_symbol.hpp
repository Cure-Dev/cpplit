#pragma once

#include "tokens/symbol.hpp"
#include "char_stream.hpp"

bool symbol_matched(wchar_t);
token_symbol* scan_symbol(char_stream*);