#include "exceptions/lexical_errors.hpp"
#include "number_convert.hpp"
#include <sstream>

lexical_errors::invalid_character::invalid_character(int pos, wchar_t ch) : lexical_point_error(pos), ch(ch) {};

std::wstring lexical_errors::invalid_character::info(language lang) {
	std::wstringstream result;

	if (lang == language::zh_cn) {
		result << L"错误：无效字符 ‘" << this->ch << L"’（U+" << number_convert::to_hex(this->ch) << L"）";
	}
	else {
		result << "lexical error: invalid character '" << this->ch << "' (U+" << number_convert::to_hex(this->ch) << L")";
	}

	return result.str();
}