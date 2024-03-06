#include "lex/tokens.h"

#ifndef _TOKENS_SYMBOL_H_
#define _TOKENS_SYMBOL_H_

class token_symbol : public token {
public:

	enum class type {
		// operators

		AT,
		QUESTION,
		NOT, // !
		XOR,
		AND, // AMPERSAND &
		OR, // BAR |

		PLUS,         // + 
		MINUS,        // -
		ASTERISK,     // *
		SLASH,        // /
		CARET,        // ^
		CARET_SLASH,  // ^/
		PERCENT,      // %

		/// comparision operators
		GREATER,          // >
		LESS,             // <
		GREATER_EQUAL,    // >=
		LESS_EQUAL,       // <=
		EQUAL_EQUAL,      // ==
		NOT_EQUAL,        // !=

		// !> !< !>= ...

		/// logical operators
		NOT_NOT, // !!
		AND_AND, // &&
		XOR_XOR,
		OR_OR,   // ||

		/// assign ops
		EQUAL,             // =
		PLUS_EQUAL,        // +=
		MINUS_EQUAL,       // -=
		ASTERISK_EQUAL,    // *=
		SLASH_EQUAL,       // /=
		CARET_EQUAL,       // ^=
		CARET_SLASH_EQUAL, // ^/=
		PERCENT_EQUAL,     // %=


		// seperators
		BOF_,
		EOL_,
		EOF_,

		COMMA,     // ,
		DOT,       // .
		COLON,     // :
		SEMICOLON, // ;

		PAREN_LEFT,    // (
		PAREN_RIGHT,   // )
		BRACKET_LEFT,  // [
		BRACKET_RIGHT, // ]
		BRACE_LEFT,    // {
		BRACE_RIGHT,   // }

		ANGLE_BRACKET_LEFT,  // <<
		ANGLE_BRACKET_RIGHT, // >>

		SINGLE_ARROW, // ->
		DOUBLE_ARROW, // =>
	};

	type Type;
	
	token_symbol(token_type type_,/* type Type, */int begin, int end) : token(type_, begin, end)/*, Type(Type)*/ {};

	std::wstring view() {
		static std::map<token_type, std::wstring> token_to_view = {
			{ token_type::BOF_, L"<BOF>" },
			{ token_type::EOF_, L"<EOF>" },
			{ token_type::EOL_, L"<EOL>" },

			{ token_type::PLUS, L"+" },
			{ token_type::MINUS, L"-" },
			{ token_type::ASTERISK, L"*" },
			{ token_type::SLASH, L"/" },
			{ token_type::CARET, L"^" },
			{ token_type::CARET_SLASH, L"^/" },
			{ token_type::PERCENT, L"%" },

			{ token_type::AT, L"@" },
			{ token_type::QUESTION, L"?" },
			{ token_type::NOT, L"!" },
			{ token_type::AND, L"&" },
			{ token_type::OR, L"|" },
			{ token_type::XOR, L"\\" },


			{ token_type::DOT, L"." },
			{ token_type::COMMA, L"," },
			{ token_type::COLON, L":" },
			{ token_type::SEMICOLON, L";" },
			{ token_type::OPEN_PAREN, L"(" },
			{ token_type::CLOSE_PAREN, L")" },
			{ token_type::OPEN_BRACKET, L"[" },
			{ token_type::CLOSE_BRACKET, L"]" },
			{ token_type::OPEN_BRACE, L"{" },
			{ token_type::CLOSE_BRACE, L"}" },
			{ token_type::DOUBLE_ANGLE_BRACKET_LEFT, L"<<" },
			{ token_type::DOUBLE_ANGLE_BRACKET_RIGHT, L">>" },

			{ token_type::GREATER, L">" },
			{ token_type::LESS, L"<" },
			{ token_type::GREATER_EQUAL, L">=" },
			{ token_type::LESS_EQUAL, L"<=" },
			{ token_type::EQUAL_EQUAL, L"==" },
			{ token_type::NOT_EQUAL, L"!==" },
			{ token_type::IDENTICAL, L"===" },
			{ token_type::NOT_IDENTICAL, L"!===" },

			{ token_type::BELONG, L"->" },
			{ token_type::SUB, L"=>" },
			{ token_type::NOT_BELONG, L"!->" },
			{ token_type::NOT_SUB, L"!=>" },

			{ token_type::EQUAL, L"=" },
			{ token_type::PLUS_EQUAL, L"+=" },
			{ token_type::MINUS_EQUAL, L"-=" },
			{ token_type::ASTERISK_EQUAL, L"*=" },
			{ token_type::SLASH_EQUAL, L"/=" },
			{ token_type::CARET_EQUAL, L"^=" },
			{ token_type::CARET_SLASH_EQUAL, L"^/=" },
			{ token_type::PERCENT_EQUAL, L"%=" },

		};
		return token_to_view[this->TYPE];
	};

};

#endif