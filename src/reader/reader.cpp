#include <fstream>
#include <string>
#include <map>

#include "exceptions/fserrs.hpp"
#include "utils/coding.hpp"
#include "reader/reader.hpp"

std::map<std::wstring, std::wstring> content_map;


std::wstring read(std::wstring filepath, coding Coding) {

	std::string source;

	std::ifstream file;
	file.open(to_string(coding::UTF_8, filepath), std::ios::in);

	if (! file.is_open()) {
		throw new file_not_exists { filepath }; // perm access
	}

	char c;
	while ((c = file.get()) != EOF) {
		source += c;
	}

	file.close();
	std::wstring result = to_wstring(Coding, source);

	content_map[filepath] = result;
	return result;
}

std::wstring get_content(std::wstring filepath) {
	return content_map[filepath];
}