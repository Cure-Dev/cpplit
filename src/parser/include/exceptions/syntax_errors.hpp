#pragma once

#include <string>

#include "exception.hpp"
#include "position.hpp"

#include "tokens/symbol.hpp"

class syntax_error : public exception {

};

class expect_symbol : public syntax_error {
public:
	expect_symbol(position pos, token_symbol::type sym) : pos(pos), sym(sym) {};
	position pos;
	token_symbol::type sym;

	std::wstring msg(language L) {
		static std::map<token_symbol::type, std::wstring> map = {
			{ token_symbol::type::EOF_, L"EOF" },
			{ token_symbol::type::EOL_, L"EOL" },

			{ token_symbol::type::PLUS, L"plus" },
			{ token_symbol::type::MINUS, L"minus" },
			{ token_symbol::type::ASTERISK, L"asterisk" },
			{ token_symbol::type::SLASH, L"slash" },
			{ token_symbol::type::CARET, L"caret" },
			{ token_symbol::type::CARET_SLASH, L"caret_slash" },
			{ token_symbol::type::PERCENT, L"percent" },

			{ token_symbol::type::AT, L"at" },
			{ token_symbol::type::QUESTION, L"question" },
			{ token_symbol::type::NOT, L"not" },
			{ token_symbol::type::AND, L"and" },
			{ token_symbol::type::OR, L"or" },
			{ token_symbol::type::XOR, L"xor" },


			{ token_symbol::type::DOT, L"dot" },
			{ token_symbol::type::COMMA, L"comma" },
			{ token_symbol::type::COLON, L"colon" },
			{ token_symbol::type::SEMICOLON, L"semicolon" },
			{ token_symbol::type::PAREN_LEFT, L"left_paren" },
			{ token_symbol::type::PAREN_RIGHT, L"right_paren" },
			{ token_symbol::type::BRACKET_LEFT, L"left_bracket" },
			{ token_symbol::type::BRACKET_RIGHT, L"right_bracket" },
			{ token_symbol::type::BRACE_LEFT, L"left_brace" },
			{ token_symbol::type::BRACE_RIGHT, L"right_brace" },
			{ token_symbol::type::ANGLE_BRACKET_LEFT, L"left_angle_bracket" },
			{ token_symbol::type::ANGLE_BRACKET_RIGHT, L"right_angle_bracket" },

			{ token_symbol::type::GREATER, L"greater" },
			{ token_symbol::type::LESS, L"less" },
			{ token_symbol::type::GREATER_EQUAL, L"greater_equal" },
			{ token_symbol::type::LESS_EQUAL, L"less_equal" },
			{ token_symbol::type::EQUAL_EQUAL, L"equal_equal" },
			{ token_symbol::type::NOT_EQUAL, L"not_equal" },

			{ token_symbol::type::SINGLE_ARROW, L"single_arrow" },
			{ token_symbol::type::DOUBLE_ARROW, L"double_arrow" },


			{ token_symbol::type::EQUAL, L"equal" },
			{ token_symbol::type::PLUS_EQUAL, L"plus_equal" },
			{ token_symbol::type::MINUS_EQUAL, L"minus_equal" },
			{ token_symbol::type::ASTERISK_EQUAL, L"asterisk_equal" },
			{ token_symbol::type::SLASH_EQUAL, L"slash_equal" },
			{ token_symbol::type::CARET_EQUAL, L"caret_equal" },
			{ token_symbol::type::CARET_SLASH_EQUAL, L"caret_slash_equal" },
			{ token_symbol::type::PERCENT_EQUAL, L"percent_equal" },

		};
		return L"error: except symbol " + map[this->sym];
	}
};

class unexpect_token : public syntax_error {
public:
	unexpect_token(int begin, int end) : BEGIN(begin), END(end) {};
	int BEGIN, END;

	std::wstring msg(language L) {
		return L"unexpect_token" + std::to_wstring(this->BEGIN);
	}
};

class expect_identifier : public syntax_error {};

/*

error usage of kw

保留kw

*/