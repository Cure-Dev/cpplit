#include "exceptions/lex.hpp"
#include "language/language.hpp"

std::map<language, std::wstring> invalid_character::NAME = std::map<language, std::wstring> {
	{ language::en_us, L"Invalid character" },
	{ language::zh_cn, L"无效字符" },
};