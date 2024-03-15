#include "lex/tokens.hpp"

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
	token_symbol(token_type type_, type Type, int begin, int end) : token(type_, begin, end), Type(Type) {};

	std::wstring view() {
		static std::map<token_symbol::type, std::wstring> token_to_view = {
			{ token_symbol::type::BOF_, L"<BOF>" },
			{ token_symbol::type::EOF_, L"<EOF>" },
			{ token_symbol::type::EOL_, L"<EOL>" },

			{ token_symbol::type::PLUS, L"+" },
			{ token_symbol::type::MINUS, L"-" },
			{ token_symbol::type::ASTERISK, L"*" },
			{ token_symbol::type::SLASH, L"/" },
			{ token_symbol::type::CARET, L"^" },
			{ token_symbol::type::CARET_SLASH, L"^/" },
			{ token_symbol::type::PERCENT, L"%" },

			{ token_symbol::type::AT, L"@" },
			{ token_symbol::type::QUESTION, L"?" },
			{ token_symbol::type::NOT, L"!" },
			{ token_symbol::type::AND, L"&" },
			{ token_symbol::type::OR, L"|" },
			{ token_symbol::type::XOR, L"\\" },


			{ token_symbol::type::DOT, L"." },
			{ token_symbol::type::COMMA, L"," },
			{ token_symbol::type::COLON, L":" },
			{ token_symbol::type::SEMICOLON, L";" },
			{ token_symbol::type::PAREN_LEFT, L"(" },
			{ token_symbol::type::PAREN_RIGHT, L")" },
			{ token_symbol::type::BRACKET_LEFT, L"[" },
			{ token_symbol::type::BRACKET_RIGHT, L"]" },
			{ token_symbol::type::BRACE_LEFT, L"{" },
			{ token_symbol::type::BRACE_RIGHT, L"}" },
			{ token_symbol::type::ANGLE_BRACKET_LEFT, L"<<" },
			{ token_symbol::type::ANGLE_BRACKET_RIGHT, L">>" },

			{ token_symbol::type::GREATER, L">" },
			{ token_symbol::type::LESS, L"<" },
			{ token_symbol::type::GREATER_EQUAL, L">=" },
			{ token_symbol::type::LESS_EQUAL, L"<=" },
			{ token_symbol::type::EQUAL_EQUAL, L"==" },
			{ token_symbol::type::NOT_EQUAL, L"!=" },

			{ token_symbol::type::SINGLE_ARROW, L"->" },
			{ token_symbol::type::DOUBLE_ARROW, L"=>" },


			{ token_symbol::type::EQUAL, L"=" },
			{ token_symbol::type::PLUS_EQUAL, L"+=" },
			{ token_symbol::type::MINUS_EQUAL, L"-=" },
			{ token_symbol::type::ASTERISK_EQUAL, L"*=" },
			{ token_symbol::type::SLASH_EQUAL, L"/=" },
			{ token_symbol::type::CARET_EQUAL, L"^=" },
			{ token_symbol::type::CARET_SLASH_EQUAL, L"^/=" },
			{ token_symbol::type::PERCENT_EQUAL, L"%=" },

		};
		return token_to_view[this->Type];
	};

};

#endif