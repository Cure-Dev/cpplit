#include "parse_statement_block.hpp"
#include "parse_statement.hpp"
#include "exceptions/expect_symbol.hpp"
#include "check.hpp"

statement_block* parse_statements(token_list& Token_list, token_symbol::type terminator) {
	std::vector<statement*> statement_list;
	int begin = Token_list.this_()->BEGIN;

	while (!check::symbol::is(Token_list.this_(), terminator)) {

		if (check::symbol::is(Token_list.this_(), token_symbol::type::SEMICOLON) || check::symbol::is(Token_list.this_(), token_symbol::type::EOL_)) {
			Token_list.next();
		}

		else {
			statement_list.push_back(parse_statement(Token_list));

			if (!check::symbol::is(Token_list.this_(), token_symbol::type::SEMICOLON) &&
				!check::symbol::is(Token_list.this_(), token_symbol::type::EOL_)      &&
				!check::symbol::is(Token_list.this_(), terminator)) {

				throw new unexpect_token {2,1}; // expect semicolon, eol or }.
			}
			// check::symbol::require({A,B,C})
		}

	}
	statement_block* result = new statement_block { statement_list, begin, Token_list.this_()->END };
	Token_list.next();
	return result;
}

statement_block* parse_statement_block(token_list& Token_list) {
	return parse_statements(Token_list, token_symbol::type::BRACE_RIGHT);
}