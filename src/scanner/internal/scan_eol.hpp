#pragma once

#include "tokens/token.hpp"
#include "char_stream.hpp"

bool eol_matched(wchar_t c);

token* scan_eol(char_stream* src);