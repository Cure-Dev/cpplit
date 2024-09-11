#pragma once

#include "tokens/token.hpp"
#include "char_stream.hpp"

bool block_comments_matched(wchar_t);
void scan_block_comments(char_stream*);
// void scan_line_comments(char_stream*);