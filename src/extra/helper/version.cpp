#include <iostream>
#include <string>

#include "utils/losh.hpp"

std::wstring version = L"0.0.5";

void help_version(losh command) {
	std::wcout << L"CppLit v" << version << std::endl;
}