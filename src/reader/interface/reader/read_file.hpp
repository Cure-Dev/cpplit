#pragma once

#include "codec.hpp"
#include "string_char_stream.hpp"

string_char_stream* read_file(std::wstring filepath, codec_type Codec_type = codec_type::UTF_8);
// std::wstring get_content(std::wstring filepath);