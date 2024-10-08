#pragma once

#include <string>
#include <unordered_map>
#include <sstream>

#include "exception.hpp"

#include "language.hpp"

#include "position.hpp"
#include "number_convert.hpp"


class lex_error : public exception {
public:

	lex_error(std::wstring filepath, position pos) : filepath(filepath), pos(pos) {};
	position pos; // character error
	std::wstring filepath;

	std::wstring msg(language L) {
		return this->head(L) + L"\n" + this->body(L) + L"\n";
	}

protected:
	virtual std::wstring body(language L) = 0;

private:
	std::wstring head(language L) { // character error
		std::wstringstream result;

		if (L == language::zh_cn) {
			result << L"在文件 " << this->filepath << L" 的第 " << this->pos.line << L" 行第 " << this->pos.column << L" 列";
			// 如果是segament error: 从文件...的第...行到第...列
		}

		else {
			result << "In file " << this->filepath << ", at line " << this->pos.line << ", column " << this->pos.column;
		}
		return result.str();
	}

};

// undefined symbol

class unterminated_comments : public lex_error {
public:
	unterminated_comments(std::wstring filepath, position pos) : lex_error(filepath, pos) {};

	std::wstring body(language L) {
		std::wstringstream result;
		
		if (L == language::zh_cn) {
			result << L"错误：未终结的注释";
		}
		else {
			result << "error: unterminated comments";
		}
		return result.str();
	}
};

class invalid_escape : public lex_error {
public:
	invalid_escape(std::wstring filepath, position pos) : lex_error(filepath, pos) {};

	std::wstring body(language L) {
		std::wstringstream result;

		if (L == language::zh_cn) {
			result << L"错误：无效转义(...)";
		}
		else {
			result << "error: invalid escape (..)";
		}
		return result.str();
	}
};

class invalid_string_escape : public lex_error {
public:
	invalid_string_escape(std::wstring filepath, position pos) : lex_error(filepath, pos) {};

	std::wstring body(language L) {
		std::wstringstream result;
		if (L == language::zh_cn) {
			result << L"错误：无效字符串转义";
		}
		else {
			result << "error: invalid string escape";
		}
		return result.str();
	}
};

class unclosed_string : public lex_error {
public:
	unclosed_string(int begin, int end) : lex_error(L"", {-1,-1}) {};

	std::wstring body(language L) {
		return L"unclosed_string";
	}
};