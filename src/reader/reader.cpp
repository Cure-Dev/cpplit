#include <iostream>
#include <fstream>
#include <string>
#include <codecvt>
#include <locale>

#include "exceptions/fserrs.hpp"
#include "reader/encoding.hpp"
#include "reader/reader.hpp"

std::wstring utf8ToWstring(std::string utf8) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    return converter.from_bytes(utf8);
}

std::wstring read(std::string filepath, encoding Encoding) {

	std::string source;

	std::ifstream file;
	file.open(filepath, std::ios::in);

	if (! file.is_open()) {
		throw file_not_exists(filepath);
	}

	char c;
	while ((c = file.get()) != EOF) {
		source += c;
	}

	file.close();

	std::wstring result;
	if (Encoding == encoding::UTF_8) {
		result = utf8ToWstring(source);
	}
	else if (Encoding == encoding::ASCII) {
		// result = source;
	}
	else {
		throw "unknown encoding";
	}
	return result;
}