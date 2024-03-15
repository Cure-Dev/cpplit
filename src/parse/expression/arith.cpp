#include "parse/parser.hpp"
#include "parse/nodes.hpp"
#include "lex/tokens.hpp"

expr* parse_multi_divis(const token_list& Token_list, int& index) {
	static std::map<token_symbol::type, binary_expr::type> map = {
		{ token_symbol::type::ASTERISK, binary_expr::type::multiplication },
		{ token_symbol::type::SLASH, binary_expr::type::division },
	};

	expr* left = parse_prefix(Token_list, index);
	while (dynamic_cast<token_symbol*> (Token_list[index]) != NULL && map.find((dynamic_cast<token_symbol*> (Token_list[index]))->Type) != map.end()) {
		auto sym = dynamic_cast<token_symbol*> (Token_list[index++]);
		expr* right = parse_prefix(Token_list, index);
		left = new binary_expr { map[sym->Type], left, right, left->BEGIN, right->END };
	}
	return left;
}

expr* parse_plus_minus(const token_list& Token_list, int& index) {
	static std::map<token_symbol::type, binary_expr::type> map = {
		{ token_symbol::type::PLUS, binary_expr::type::addition },
		{ token_symbol::type::MINUS, binary_expr::type::subtraction },
	};

	expr* left = parse_multi_divis(Token_list, index);
	while (dynamic_cast<token_symbol*> (Token_list[index]) != NULL && map.find((dynamic_cast<token_symbol*> (Token_list[index]))->Type) != map.end()) {
		auto sym = dynamic_cast<token_symbol*> (Token_list[index++]);
		expr* right = parse_multi_divis(Token_list, index);
		left = new binary_expr { map[sym->Type], left, right, left->BEGIN, right->END };
	}
	return left;
}

expr* parse_arith(const token_list& Token_list, int& index) {
	return parse_plus_minus(Token_list, index);
}