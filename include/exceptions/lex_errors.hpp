
#include <string>
#include <map>
#include <sstream>

#include "exceptions/exception.hpp"

#include "language/language.hpp"

#ifndef _EXCEPTIONS_LEX_ERRORS_HPP_
#define _EXCEPTIONS_LEX_ERRORS_HPP_

class lexerr /*: public exception */{
public:
	lexerr(int begin, int end) : BEGIN(begin), END(end) {};
	int BEGIN, END;
};

/*static std::wstring an(std::wstring name, std::wstring msg) {
	return L"\033[1;31m" + name + L"\033[0m: " + msg;
}*/

class lexical_error : public exception {
public:

	virtual std::wstring name(language L) { // static?
		return this->name(L);
	}

};

class character_error : public lexical_error {
public:
	character_error(int pos, wchar_t ch) : POS(pos), CH(ch) {};
	int POS;
	wchar_t CH;
};

class invalid_character : public character_error {
public:
	invalid_character(std::wstring filepath, int line, int column, int ch) : character_error(1, ch), filepath(filepath), line(line), column(column) {};
	std::wstring filepath;
	int line, column;

	std::wstring msg(language L) {
		std::wstringstream result;

		switch (L) {
		default:
			result << "In file " << this->filepath << ", at line " << this->line << ", column " << this->column << "\n";
			result << "error: invalid character '" << this->CH << "' (U+" << std::hex << int(this->CH) << std::dec << L")";
		}

		return result.str();
	}
};

/*class non_existent_operator : public lexerr {
public:
	non_existent_operator(wchar_t op) : lexerr(std::wstring(L"Symbol '") + op + L"' not exists"){};

};*/


class unterminated_comments : public lexical_error {
public:
	unterminated_comments(std::wstring filepath, int line, int column) : filepath(filepath), line(line), column(column) {};
	std::wstring filepath;
	int line;
	int column;

	std::wstring msg(language L) {
		std::wstringstream result;
		switch (L) {
		default:
			result << "In file " << this->filepath << ", at line " << this->line << ", column " << this->column << "\n";
			result << "error: unterminated comments";
		}
		return result.str();
	}
};

class invalid_escape : public lexerr { // 无效转义
public:
	invalid_escape(int begin, int end) : lexerr(begin, end) {}; /*lexerr(L"invalid escape '...' from .. to ..") {};*/
};

class unclosed_string : public lexical_error {
public:
	unclosed_string(int begin, int end) {};

	std::wstring msg(language L) {
		return L"";
	}
};

#endif