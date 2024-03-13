#include <codecvt>
#include <locale>

#ifndef _CODING_HPP_
#define _CODING_HPP_

enum class coding {

	ASCII,
	UTF_8,

};

static std::wstring to_wstring(coding Coding, const std::string& src) {
	std::wstring result;

	if (Coding == coding::ASCII || Coding == coding::UTF_8) {
		std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter; // std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    	result = converter.from_bytes(src);
	}
	return result;
}

static std::string to_string(coding Coding, const std::wstring& src) {
	std::string result;

	if (Coding == coding::UTF_8) {
		std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
		result = converter.to_bytes(src);
	}
	else {
		throw "unsupport coding";
	}
	return result;
}

#endif