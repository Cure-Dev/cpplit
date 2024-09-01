#include "exceptions/syntax_errors.hpp"

#include "parse_suffix.hpp"
#include "parse_expression.hpp"
#include "check.hpp"

#include "ast/expressions/member_access.hpp"
#include "ast/expressions/call.hpp"

arg_list* parse_callation(token_list& Token_list) {
	std::vector<expr*> result;

	int begin = Token_list.this_()->BEGIN;
	while (!check::symbol::is(Token_list.this_(), token_symbol::type::PAREN_RIGHT)) {
		result.push_back(parse_expression(Token_list));

		if (check::symbol::is(Token_list.this_(), token_symbol::type::COMMA)) {
			Token_list.next();
		}
		else if (check::symbol::is(Token_list.this_(), token_symbol::type::PAREN_RIGHT)) {
			// pass
		}
		else {
			throw new unexpect_token {1,1};
		}
	}
	int end = Token_list.this_()->END;
	Token_list.next();
	return new arg_list { result, begin, end };
}

expr* parse_suffix(token_list& Token_list, expr* item) {

	while (true) {

		if (check::symbol::is(Token_list.this_(), token_symbol::type::PAREN_LEFT)) {
			Token_list.next();
			auto caller = parse_callation(Token_list); // @index+1
			item = new expr_callation { item, caller, item->BEGIN, caller->END };
		}

		else if (check::symbol::is(Token_list.this_(), token_symbol::type::DOT)) {
			Token_list.next();
			if (dynamic_cast<token_identifier*> (Token_list.this_()) != NULL) {
				item = new member_access { item, dynamic_cast<token_identifier*> (Token_list.this_()), item->BEGIN, Token_list.this_()->END };
				Token_list.next();
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