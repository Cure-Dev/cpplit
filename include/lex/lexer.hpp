#include "lex/tokens.hpp"
#include <vector>

#ifndef _LEXER_H_
#define _LEXER_H_

token_list lex(std::string filepath);

static std::map<std::wstring, token_type> symbol_map = {

// 通用
	{ L"\n", token_type::EOL_ }, // lf
	// { L"\n", token_types::SEP_EOL }, cr
	// { L"\n", token_types::SEP_EOL }, nel

	{ L"@", token_type::AT },
	{ L"?", token_type::QUESTION },
	{ L"!", token_type::NOT },
	{ L"&", token_type::AND },
	{ L"|", token_type::OR },
	{ L"\\", token_type::XOR },

	{ L"+", token_type::PLUS },
	{ L"-", token_type::MINUS },
	{ L"*", token_type::ASTERISK },
	{ L"/", token_type::SLASH },
	{ L"^", token_type::CARET },
	{ L"^/", token_type::CARET_SLASH },
	{ L"%", token_type::PERCENT },


	{ L".", token_type::DOT },
	{ L",", token_type::COMMA },
	{ L":", token_type::COLON },
	{ L";", token_type::SEMICOLON },
	{ L"(", token_type::OPEN_PAREN },
	{ L")", token_type::CLOSE_PAREN },
	{ L"[", token_type::OPEN_BRACKET },
	{ L"]", token_type::CLOSE_BRACKET },
	{ L"{", token_type::OPEN_BRACE },
	{ L"}", token_type::CLOSE_BRACE },
	{ L"<<", token_type::DOUBLE_ANGLE_BRACKET_LEFT },
	{ L">>", token_type::DOUBLE_ANGLE_BRACKET_RIGHT },

	{ L">", token_type::GREATER },
	{ L"<", token_type::LESS },
	{ L">=", token_type::GREATER_EQUAL },
	{ L"<=", token_type::LESS_EQUAL },
	{ L"==", token_type::EQUAL_EQUAL },
	{ L"!=", token_type::NOT_EQUAL },

	{ L"->", token_type::BELONG },
	{ L"=>", token_type::SUB },
	{ L"!->", token_type::NOT_BELONG },
	{ L"!=>", token_type::NOT_SUB },

	{ L"=", token_type::EQUAL },
	{ L"+=", token_type::PLUS_EQUAL },
	{ L"-=", token_type::MINUS_EQUAL },
	{ L"*=", token_type::ASTERISK_EQUAL },
	{ L"/=", token_type::SLASH_EQUAL },
	{ L"^=", token_type::CARET_EQUAL },
	{ L"^/=", token_type::CARET_SLASH_EQUAL },
	{ L"%=", token_type::PERCENT_EQUAL },

// zh-cn
	{ L"？", token_type::QUESTION },
	{ L"！", token_type::NOT },

	{ L"，", token_type::COMMA },
	{ L"：", token_type::COLON },
	{ L"；", token_type::SEMICOLON },
	{ L"（", token_type::OPEN_PAREN },
	{ L"）", token_type::CLOSE_PAREN },
	{ L"【", token_type::OPEN_BRACKET },
	{ L"】", token_type::CLOSE_BRACKET },
	{ L"｛", token_type::OPEN_BRACE },
	{ L"｝", token_type::CLOSE_BRACE },
	{ L"《", token_type::DOUBLE_ANGLE_BRACKET_LEFT },
	{ L"》", token_type::DOUBLE_ANGLE_BRACKET_RIGHT },

	{ L"！->", token_type::NOT_BELONG },
	{ L"！=>", token_type::NOT_SUB },

};

static std::map<std::wstring, token_keyword::type> keyword_map = {

// en-us
	{ L"import", token_keyword::type::IMPORT },
	{ L"if", token_keyword::type::IF },
	{ L"else if", token_keyword::type::ELSE_IF },
	{ L"else", token_keyword::type::ELSE },
	{ L"loop", token_keyword::type::LOOP },
	{ L"func", token_keyword::type::FUNC },
	{ L"class", token_keyword::type::CLASS },
	{ L"namespace", token_keyword::type::NAMESPACE },
	{ L"enum", token_keyword::type::ENUM },
	{ L"try", token_keyword::type::TRY },
	{ L"catch", token_keyword::type::CATCH },

// zh-cn
	{ L"导入", token_keyword::type::IMPORT },
	{ L"如果", token_keyword::type::IF },
	{ L"若", token_keyword::type::IF },
	{ L"又如果", token_keyword::type::ELSE_IF },
	{ L"否则", token_keyword::type::ELSE },
	{ L"循环", token_keyword::type::LOOP },
	{ L"函数", token_keyword::type::FUNC },
	{ L"类", token_keyword::type::CLASS },
	{ L"命名空间", token_keyword::type::NAMESPACE },
	{ L"枚举", token_keyword::type::ENUM },
	{ L"尝试", token_keyword::type::TRY },
	{ L"捕获", token_keyword::type::CATCH },

};

static std::map<std::wstring, bool> literal_bool_map = {

// en-us
	{ L"true", true },
	{ L"true", false },

// zh-cn
	{ L"真", true },
	{ L"假", false },

};


static std::map<std::wstring, token_symbol::type> new_symbol_map = {

	{ L"\n", token_symbol::type::EOL_ }, // lf

	{ L"@", token_symbol::type::AT },
	{ L"?", token_symbol::type::QUESTION },
	{ L"!", token_symbol::type::NOT },
	{ L"&", token_symbol::type::AND },
	{ L"|", token_symbol::type::OR },
	{ L"\\", token_symbol::type::XOR },

	{ L"+", token_symbol::type::PLUS },
	{ L"-", token_symbol::type::MINUS },
	{ L"*", token_symbol::type::ASTERISK },
	{ L"/", token_symbol::type::SLASH },
	{ L"^", token_symbol::type::CARET },
	{ L"^/", token_symbol::type::CARET_SLASH },
	{ L"%", token_symbol::type::PERCENT },


	{ L".", token_symbol::type::DOT },
	{ L",", token_symbol::type::COMMA },
	{ L":", token_symbol::type::COLON },
	{ L";", token_symbol::type::SEMICOLON },
	{ L"(", token_symbol::type::PAREN_LEFT },
	{ L")", token_symbol::type::PAREN_RIGHT },
	{ L"[", token_symbol::type::BRACKET_LEFT },
	{ L"]", token_symbol::type::BRACKET_RIGHT },
	{ L"{", token_symbol::type::BRACE_LEFT },
	{ L"}", token_symbol::type::BRACE_RIGHT },
	{ L"<<", token_symbol::type::ANGLE_BRACKET_LEFT },
	{ L">>", token_symbol::type::ANGLE_BRACKET_RIGHT },

	{ L">", token_symbol::type::GREATER },
	{ L"<", token_symbol::type::LESS },
	{ L">=", token_symbol::type::GREATER_EQUAL },
	{ L"<=", token_symbol::type::LESS_EQUAL },
	{ L"==", token_symbol::type::EQUAL_EQUAL },
	{ L"!=", token_symbol::type::NOT_EQUAL },

	{ L"->", token_symbol::type::SINGLE_ARROW },
	{ L"=>", token_symbol::type::DOUBLE_ARROW },
	// { L"!=>", token_symbol::type::NOT_SUB },

	{ L"=", token_symbol::type::EQUAL },
	{ L"+=", token_symbol::type::PLUS_EQUAL },
	{ L"-=", token_symbol::type::MINUS_EQUAL },
	{ L"*=", token_symbol::type::ASTERISK_EQUAL },
	{ L"/=", token_symbol::type::SLASH_EQUAL },
	{ L"^=", token_symbol::type::CARET_EQUAL },
	{ L"^/=", token_symbol::type::CARET_SLASH_EQUAL },
	{ L"%=", token_symbol::type::PERCENT_EQUAL },
};

#endif