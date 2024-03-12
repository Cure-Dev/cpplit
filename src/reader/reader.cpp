#include <iostream>
#include <fstream>
#include <string>

#include "exceptions/fserrs.hpp"
#include "utils/coding.hpp"
#include "reader/reader.hpp"

std::wstring read(std::string filepath, coding Coding) {

	std::string source;

	std::ifstream file;
	file.open(filepath, std::ios::in);

	if (! file.is_open()) {
		throw new file_not_exists { to_wstring(coding::UTF_8, filepath) };
	}

	char c;
	while ((c = file.get()) != EOF) {
		source += c;
	}

	file.close();

	return to_wstring(Coding, source);
}