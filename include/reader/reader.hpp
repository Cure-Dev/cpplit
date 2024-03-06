#include "reader/encoding.hpp"

#ifndef _READER_H_
#define _READER_H_

std::wstring read(std::string filepath, encoding Encoding = encoding::UTF_8);

#endif