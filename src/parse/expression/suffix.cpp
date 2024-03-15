#include "exceptions/syntax_errors.hpp"

#include "parse/parser.hpp"

arg_list* parse_callation(const token_list& Token_list, int& index) {
	std::vector<expr*> result;

	int begin = Token_list[index]->BEGIN;
	while (!check_symbol_if(Token_list[index], token_symbol::type::PAREN_RIGHT)) {
		result.push_back(parse_expression(Token_list, index));

		if (check_symbol_if(Token_list[index], token_symbol::type::COMMA)) {
			index += 1;
		}
		else if (check_symbol_if(Token_list[index], token_symbol::type::PAREN_RIGHT)) {
			// pass
		}
		else {
			throw new unexpect_token {1,1};
		}
	}
	int end = Token_list[index]->END;
	index += 1;
	return new arg_list { result, begin, end };
}

expr* parse_suffix(const token_list& Token_list, int& index, expr* item) {

	while (true) {

		if (check_symbol_if(Token_list[index], token_symbol::type::PAREN_LEFT)) {
			index += 1;
			auto caller = parse_callation(Token_list, index); // @index+1
			item = new expr_callation { item, caller, item->BEGIN, caller->END };
		}

		else if (check_symbol_if(Token_list[index], token_symbol::type::DOT)) {
			index += 1;
			if (dynamic_cast<token_identifier*> (Token_list[index]) != NULL) {
				item = new member_access { item, dynamic_cast<token_identifier*> (Token_list[index]), item->BEGIN, Token_list[index]->END };
				index += 1;
			}
			else {
				throw "expect identifier";
			}
		}

		else {
			break;
		}
	}

	return item;

}