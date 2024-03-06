#include "exceptions/syntax_errors.hpp"

#include "parse/parser.hpp"

arg_list* parse_callation(const token_list& Token_list, int& index) {
	std::vector<expr*> result;

	int begin = Token_list[index]->BEGIN;
	while (Token_list[index]->TYPE != token_type::CLOSE_PAREN) {
		result.push_back(parse_expression(Token_list, index));
		if (Token_list[index]->TYPE == token_type::COMMA) {
			index += 1;
		}
		else if (Token_list[index]->TYPE == token_type::CLOSE_PAREN) { /* pass */ }
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

		if (Token_list[index]->TYPE == token_type::OPEN_PAREN) {
			index += 1;
			auto caller = parse_callation(Token_list, index); // @index+1
			item = new expr_callation { item, caller, item->BEGIN, caller->END };
		}

		else if (Token_list[index]->TYPE == token_type::DOT) {
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