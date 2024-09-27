#pragma once

#include "tokens/token.hpp"
#include "char_stream.hpp"

bool block_comments_matched(wchar_t);
token* scan_block_comments(char_stream*);

bool line_comments_matched(wchar_t);
token* scan_line_comments(char_stream*); // scan_semicolon