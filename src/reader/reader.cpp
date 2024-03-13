#include <iostream>
#include <fstream>
#include <string>

#include "exceptions/fserrs.hpp"
#include "utils/coding.hpp"
#include "reader/reader.hpp"

std::wstring read(std::wstring filepath, coding Coding) {

	std::string source;

	std::ifstream file;
	file.open(to_string(coding::UTF_8, filepath), std::ios::in);

	if (! file.is_open()) {
		throw new file_not_exists { filepath };
	}

	char c;
	while ((c = file.get()) != EOF) {
		source += c;
	}

	file.close();

	return to_wstring(Coding, source);
}