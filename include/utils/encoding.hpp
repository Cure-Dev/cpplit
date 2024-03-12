#include <codecvt>
#include <locale>

#ifndef _CODING_HPP_
#define _CODING_HPP_

enum class encoding {

	ASCII,
	UTF_8,

};

static std::wstring to_wstring(encoding Coding, const std::string& src) {
	std::wstring result;

	if (Coding == encoding::UTF_8) {
		std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    	result = converter.from_bytes(src);
	}
	// else if ascii
	return result;
}

/*std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

std::wstring to_wstring(const std::string& str) {
    return converter.from_bytes(str);
}*/

#endif