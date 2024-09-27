#include "scan_symbol.hpp"
#include "trie.hpp"

trie<token_symbol::type> symbol_map = {

// 通用

	{ L"@", token_symbol::type::AT },
	{ L"?", token_symbol::type::QUESTION },
	{ L"!", token_symbol::type::NOT },
	{ L"&", token_symbol::type::AND },
	{ L"|", token_symbol::type::OR },
	{ L"\\", token_symbol::type::XOR },
	{ L"&&", token_symbol::type::AND_AND },
	{ L"||", token_symbol::type::OR_OR },
	{ L"\\\\", token_symbol::type::XOR_XOR },

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
	// { L";", token_symbol::type::SEMICOLON },
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
	{ L"≥", token_symbol::type::GREATER_EQUAL },
	{ L"<=", token_symbol::type::LESS_EQUAL },
	{ L"≤", token_symbol::type::LESS_EQUAL },
	{ L"==", token_symbol::type::EQUAL_EQUAL },
	{ L"!=", token_symbol::type::NOT_EQUAL },
	{ L"≠", token_symbol::type::NOT_EQUAL },

	{ L"->", token_symbol::type::SINGLE_ARROW },
	{ L"=>", token_symbol::type::DOUBLE_ARROW },
/*	{ L"!->", token_symbol::type::NOT_BELONG },
	{ L"!=>", token_symbol::type::NOT_SUB },*/

	{ L"=", token_symbol::type::EQUAL },
	{ L"+=", token_symbol::type::PLUS_EQUAL },
	{ L"-=", token_symbol::type::MINUS_EQUAL },
	{ L"*=", token_symbol::type::ASTERISK_EQUAL },
	{ L"/=", token_symbol::type::SLASH_EQUAL },
	{ L"^=", token_symbol::type::CARET_EQUAL },
	{ L"^/=", token_symbol::type::CARET_SLASH_EQUAL },
	{ L"%=", token_symbol::type::PERCENT_EQUAL },

// zh-cn
	{ L"？", token_symbol::type::QUESTION },
	{ L"！", token_symbol::type::NOT },

	{ L"，", token_symbol::type::COMMA },
	{ L"：", token_symbol::type::COLON },
	// { L"；", token_symbol::type::SEMICOLON },
	{ L"（", token_symbol::type::PAREN_LEFT },
	{ L"）", token_symbol::type::PAREN_RIGHT },
	{ L"【", token_symbol::type::BRACKET_LEFT },
	{ L"】", token_symbol::type::BRACKET_RIGHT },
	{ L"｛", token_symbol::type::BRACE_LEFT },
	{ L"｝", token_symbol::type::BRACE_RIGHT },
	{ L"《", token_symbol::type::ANGLE_BRACKET_LEFT },
	{ L"》", token_symbol::type::ANGLE_BRACKET_RIGHT },

/*	{ L"！->", token_symbol::type::NOT_BELONG },
	{ L"！=>", token_symbol::type::NOT_SUB }, // replace_list*/

};


bool symbol_matched(wchar_t c) {
	return symbol_map.has(c);
}

token_symbol* scan_symbol(char_stream* src) {
	int begin = src->get_pos();

	wchar_t c = src->get();
	auto t = symbol_map.get(c);

	while (!src->is_end() && t->has(src->peek())) { //! after is_end no peek?
		c = src->get();
		t = t->get(c);
	}
	return new token_symbol { *t->val, begin, src->get_pos() };
}