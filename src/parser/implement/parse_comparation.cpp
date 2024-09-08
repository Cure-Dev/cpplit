#include "parse_comparation.hpp"
#include "parse_arith.hpp"

#include "tokens/symbol.hpp"
#include "ast/expressions/comparation.hpp"

std::unordered_map<token_symbol::type, comparation::type> comp_symbol_map = {
	{ token_symbol::type::EQUAL_EQUAL, comparation::EQUAL },
	{ token_symbol::type::GREATER, comparation::GREATER },
	{ token_symbol::type::LESS, comparation::LESS },
	{ token_symbol::type::NOT_EQUAL, comparation::NOT_EQUAL },
	{ token_symbol::type::GREATER_EQUAL, comparation::GREATER_EQUAL },
	{ token_symbol::type::LESS_EQUAL, comparation::LESS_EQUAL },
};

bool is_comp_symbol(token* Token) {
	bool result = false;
	if (dynamic_cast<token_symbol*> (Token) != NULL) {
		token_symbol* _Token = dynamic_cast<token_symbol*> (Token); //！
		if (comp_symbol_map.find(_Token->Type) != comp_symbol_map.end()) {
			result = true;
		}
	}
	return result;
}

expr* parse_comparation(token_list& Token_list) {
	expr* result;
	expr* left;

	result = parse_arith(Token_list);

	// token_symbol::type
	if (is_comp_symbol(Token_list.this_())) {
		expr* left = result;
		std::vector<std::pair<comparation::type, expr*>> right;

		do {
			comparation::type comp_type = comp_symbol_map[dynamic_cast<token_symbol*> (Token_list.fetch()) -> Type];

			expr* comp_item = parse_arith(Token_list);
			right.push_back({ comp_type, comp_item });
		} while (is_comp_symbol(Token_list.this_()));

		result = new comparation { left, right, left->BEGIN, right.back().second->END };
	}

	return result;
}