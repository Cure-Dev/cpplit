#ifndef _TOKENS_KEYWORD_H_
#define _TOKENS_KEYWORD_H_

class token_keyword : public token {
public:

	enum class type {
		IMPORT,

		IF,
		ELSE_IF,
		ELSE,

		LOOP,

		FUNC,
		CLASS,
		ENUM,
		NAMESPACE,
		// STRUCTURE

		TRY,
		CATCH,

	};

	type Type;
	token_keyword(type Type, int begin, int end) : token(token_type::temp, begin, end), Type(Type) {};

	std::wstring view() {

		static std::map<type, std::wstring> keyword_view = {

			{ type::IMPORT, L"import" },
			{ type::IF, L"if" },
			{ type::ELSE_IF, L"else if" },
			{ type::ELSE, L"else" },
			{ type::LOOP, L"loop" },
			{ type::FUNC, L"func" },
			{ type::CLASS, L"class"},
			{ type::NAMESPACE, L"namespace" },
			{ type::ENUM, L"enum" },
			{ type::TRY, L"try" },
			{ type::CATCH, L"catch" },

		};
		return L"\033[1m" + keyword_view[this->Type] + L"\033[0m";
	}
};

#endif