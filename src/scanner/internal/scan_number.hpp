#pragma once

#include "tokens/entity.hpp" //!!
#include "char_stream.hpp"

bool number_matched(wchar_t);

token_number* scan_number(char_stream*);