#pragma once

#include "tokens/token.hpp"
#include "char_stream.hpp"

bool escape_head_matched(wchar_t c);

token* scan_escape(char_stream* src);