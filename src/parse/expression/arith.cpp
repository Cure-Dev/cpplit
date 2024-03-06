#include "parse/parser.hpp"
#include "parse/nodes.hpp"
#include "lex/tokens.h"

expr* parse_multi_divis(const token_list& Token_list, int& index) {

	static std::map<token_type, binary_expr::type> map = {
		{ token_type::ASTERISK, binary_expr::type::multiplication },
		{ token_type::SLASH, binary_expr::type::division },
	};
	expr* left;

	left = parse_prefix(Token_list, index);

	while (map.find(Token_list[index]->TYPE) != map.end()) {
		auto sym = Token_list[index++];
		expr* right = parse_prefix(Token_list, index);
		left = new binary_expr { map[sym->TYPE], left, right, left->BEGIN, right->END };
	}
	return left;
}

expr* parse_plus_minus(const token_list& Token_list, int& index) {
	static std::map<token_type, binary_expr::type> map = {
		{ token_type::PLUS, binary_expr::type::addition },
		{ token_type::MINUS, binary_expr::type::subtraction },
	};

	expr* left = parse_multi_divis(Token_list, index);
	while (map.find(Token_list[index]->TYPE) != map.end()) { // ++?
		auto sym = Token_list[index++]; // auto* ?
		expr* right = parse_multi_divis(Token_list, index);
		left = new binary_expr { map[sym->TYPE], left, right, left->BEGIN, right->END };
	}
	return left;
}

expr* parse_arith(const token_list& Token_list, int& index) {
	return parse_plus_minus(Token_list, index);
}