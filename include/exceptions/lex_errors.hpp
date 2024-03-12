
#include <string>
#include <map>
#include <sstream>

#include "exceptions/exception.hpp"

#include "language/language.hpp"

#include "utils/position.hpp"

#ifndef _EXCEPTIONS_LEX_ERRORS_HPP_
#define _EXCEPTIONS_LEX_ERRORS_HPP_

class lexical_error : public exception {
public:

/*	virtual std::wstring name(language L) { // static?
		return this->name(L);
	}*/

};

/*class character_error : public lexical_error {
public:
	character_error(int pos, wchar_t ch) : POS(pos), CH(ch) {};
	int POS;
	wchar_t CH;
};*/

class invalid_character : public lexical_error {
public:
	invalid_character(std::wstring filepath, position pos, wchar_t ch) : filepath(filepath), pos(pos), Char(ch) {};
	std::wstring filepath;
	position pos;
	wchar_t Char;

	std::wstring msg(language L) {
		std::wstringstream result;

		if (L == language::zh_cn) {
			result << L"在文件 " << this->filepath << L" 的第 " << this->pos.line << L" 行第 " << this->pos.column << L" 列\n";
			result << L"错误：无效字符 ‘" << this->Char << L"’（U+" << std::hex << int(this->Char) << std::dec << L"）";
		}

		else {
			result << "In file " << this->filepath << ", at line " << this->pos.line << ", column " << this->pos.column << "\n";
			result << "error: invalid character '" << this->Char << "' (U+" << std::hex << int(this->Char) << std::dec << L")";
		}

		return result.str();
	}
};

// undefined symbol

class unterminated_comments : public lexical_error {
public:
	unterminated_comments(std::wstring filepath, position pos) : filepath(filepath), pos(pos) {};
	std::wstring filepath;
	position pos;

	std::wstring msg(language L) {
		std::wstringstream result;
		switch (L) {
		default:
			result << "In file " << this->filepath << ", at line " << this->pos.line << ", column " << this->pos.column << "\n";
			result << "error: unterminated comments";
		}
		return result.str();
	}
};

class invalid_escape : public lexical_error { // 无效转义
public:
	invalid_escape(std::wstring file, position pos) : file(file), pos(pos) {};
	std::wstring file;
	position pos;

	std::wstring msg(language L) {
		std::wstringstream result;

		if (L == language::en_us) {
			result << "In file " << this->file << ", at line " << this->pos.line << ", column " << this->pos.column << "\n";
			result << "error: invalid escape (..)";
		}
		// else
		return result.str();
	}
};

class invalid_string_escape : public lexical_error {
public:
	invalid_string_escape(std::wstring filepath, position pos) : filepath(filepath), pos(pos) {};
	std::wstring filepath;
	position pos;

	std::wstring msg(language L) {
		std::wstringstream result;
		if (L == language::zh_cn) {
			result << L"在文件 " << this->filepath << L" 的第 " << this->pos.line << L" 行第 " << this->pos.column << L" 列\n";
			result << L"错误：无效字符串转义";
		}
		else {
			result << "In file " << this->filepath << ", at line " << this->pos.line << ", column " << this->pos.column << "\n";
			result << "error: invalid string escape";
		}
		return result.str();
	}
};

class unclosed_string : public lexical_error {
public:
	unclosed_string(int begin, int end) {};

	std::wstring msg(language L) {
		return L"";
	}
};

#endif