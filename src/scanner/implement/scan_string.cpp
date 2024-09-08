#include <unordered_set>

#include "exceptions/lex_errors.hpp"

#include "scan_string.hpp"
#include "numcvt.hpp"

#include "position.hpp"

std::unordered_set<wchar_t> head_set = {

// global
	L'\'',
	L'"',

// zh-cn
	L'‘',
	L'“',
};

wchar_t string_escape(std::wstring src, int& i, const std::wstring& filepath) {

	int begin = i;
	wchar_t result;

	if (src[i] == L'"') {
		i += 1;
		result = L'"';
	}
	else if (src[i] == L'`') {
		i += 1;
		result = L'`';
	}

	// unicode escape
	else if (src[i] == L'u' || src[i] == L'U') {
		i += 1;
		if (src[i] == L'x' || src[i] == L'X' || src[i] == L'+') {
			i += 1;
			unsigned int val = cvt_hex(src, i);
			if (src[i] != L'`') {
				throw "unicode escape must ended at `";
			}
			else if (val > 0x10ffff) {
				throw "unicode out of range";
			}
			else {
				i += 1;
				result = val;
			}
		}
		else {
			throw "unsupported / expect 0x, 0d, 0o...";
		}
		
	}

	else {
		throw new invalid_string_escape { filepath, position_format(src, i) };
	}
	return result;

}

bool string_head_matched(wchar_t ch) {
	if (head_set.find(ch) != head_set.end()) {
		return true;
	}
	else {
		return false;
	}
}


std::wstring lex_glob_line_string(std::wstring src, int& i) {
	int begin = i;
	int length = src.length();

	while (true) {

		if (i >= length || src[i] == L'\n') {
			throw unclosed_string(begin, i);
		}
		else if (src[i] == L'\'') {
			i += 1;
			break;
		}
		else {
			i += 1;
		}
	}

	return src.substr(begin, i - begin - 1);
};

std::wstring lex_glob_block_string(std::wstring src, int& i) {
	int begin = i;
	int length = src.length();

	while (true) {
		if (i + 2 >= length) {
			throw unclosed_string(begin, i);
		}
		else if (src.substr(i, 3) == L"'''") {
			i += 3;
			break;
		}
		else {
			i += 1;
		}
	}

	return src.substr(begin, i - begin - 3);
}

std::wstring lex_glob_string(std::wstring src, int& i) {
	std::wstring val;
	if (src.substr(i, 2) == L"''") {
		i += 2;
		return lex_glob_block_string(src, i);
	}
	else {
		val = lex_glob_line_string(src, i);
	}
	return val;
}

std::wstring lex_glob_line_escapable_string(std::wstring src, int& i, const std::wstring& filepath) {
	int begin = i;
	int length = src.length();
	std::wstring val;

	while (true) {

		if (i >= length || src[i] == L'\n') {
			throw unclosed_string(begin, i);
		}
		else if (src[i] == L'"') {
			i += 1;
			break;
		}
		else if (src[i] == L'`') {
			i += 1;
			val += string_escape(src, i, filepath);
		}
		else {
			val += src[i++];
		}
	}

	return val;
};

std::wstring lex_glob_block_escapable_string(std::wstring src, int& i, const std::wstring& filepath) {
	int begin = i;
	int length = src.length();
	std::wstring val;

	while (true) {
		if (i + 2 >= length) {
			throw unclosed_string(begin, i);
		}
		else if (src.substr(i, 3) == L"\"\"\"") {
			i += 3;
			break;
		}
		else if (src[i] == L'`') {
			i += 1;
			val += string_escape(src, i, filepath);
		}
		else {
			val += src[i++];
		}
	}

	return val;
}


std::wstring lex_glob_escapable_string(std::wstring src, int& i, const std::wstring& filepath) {
	std::wstring val;
	if (src.substr(i, 2) == L"\"\"") {
		i += 2;
		return lex_glob_block_escapable_string(src, i, filepath);
	}
	else {
		val = lex_glob_line_escapable_string(src, i, filepath);
	}
	return val;
}


token_string* lex_string(std::wstring src, int& i, const std::wstring& filepath) {
	int begin = i;
	wchar_t bs = src[i++]; // begin symbol
	std::wstring val;

	if (bs == L'\'') {
		val = lex_glob_string(src, i);
	}

	else if (bs == L'"') {
		val = lex_glob_escapable_string(src, i, filepath);
	}

	return new token_string {val, begin, i};
}

token_string* scan_string(char_stream* src) {
	int pos_begin = src->get_pos();
	wchar_t begin = src->get();

	std::wstring data;
	while (src->peek() != begin) {
		data += src->get();
	}
	src->next();
	return new token_string { data, pos_begin, src->get_pos() };
}