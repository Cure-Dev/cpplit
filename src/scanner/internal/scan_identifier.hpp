#pragma once

#include "tokens/token.hpp"
#include "char_stream.hpp"

bool identifier_matched(wchar_t);
token* scan_identifier(char_stream*);