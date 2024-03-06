
#include <string>
#include <map>
#include <sstream>

#include "exceptions/exception.hpp"

#include "language/language.hpp"

#ifndef LEXERRS_H
#define LEXERRS_H

class lexerr /*: public exception */{
public:
	lexerr(int begin, int end) : BEGIN(begin), END(end) {};
	int BEGIN, END;
};

static std::wstring an(std::wstring name, std::wstring msg) {
	return L"\033[1;31m" + name + L"\033[0m: " + msg;
}

class lexical_error : public exception {
public:
	int BEGIN; //
	lexical_error(int begin) : BEGIN(begin) {};

	virtual std::wstring name(language L) { // static?
		return this->name(L);
	}

	virtual std::wstring msg(language L) {
		return L"";
	}
};

class character_error : public lexical_error {
public:
	character_error(int pos, wchar_t ch) : lexical_error(pos), POS(pos), CH(ch) {};
	int POS;
	wchar_t CH;
};

class invalid_character : public character_error {
public:
	invalid_character(int pos, int ch) : character_error(pos, ch) {};

	static std::map<language, std::wstring> NAME;

	std::wstring name(language L) {
		return NAME[L];
	}

	std::wstring msg(language L) {

		std::wstringstream result_stream;

		switch (L) {
			default:
				result_stream << L"'" << this->CH << L"' (U+" << std::hex << int(this->CH) << std::dec << L")";
		}

		std::wstring result = an(NAME[L], result_stream.str());

		return result;
	}
};

/*class non_existent_operator : public lexerr {
public:
	non_existent_operator(wchar_t op) : lexerr(std::wstring(L"Symbol '") + op + L"' not exists"){};

};*/

class unterminated : public lexerr {
public:
	unterminated(std::wstring type, int begin, int end) : lexerr(begin, end) {}; /*lexerr(std::wstring(L"Unterminated ") + type + L" from " + std::to_wstring(start) + L" to " + std::to_wstring(end)) {};*/
};

class unterminated_comments : public unterminated {
public:
	unterminated_comments(int begin, int end) : unterminated(L"Comments(missing #)", begin, end) {};
};

class invalid_escape : public lexerr { // 无效转义
public:
	invalid_escape(int begin, int end) : lexerr(begin, end) {}; /*lexerr(L"invalid escape '...' from .. to ..") {};*/
};

class unclosed_string : public unterminated {
public:
	unclosed_string(int begin, int end) : unterminated(L"string", begin, end) {};
};

#endif