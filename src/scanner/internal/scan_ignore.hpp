#pragma once

#include "tokens/token.hpp"
#include "char_stream.hpp"

bool ignore_matched(wchar_t c);

token* scan_ignore(char_stream* src);