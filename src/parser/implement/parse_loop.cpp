#include "parse_loop.hpp"

#include "parse_expression.hpp"
#include "parse_statement_block.hpp"
#include "check.hpp"

#include "ast/expressions/expr.hpp"

condition_loop* parse_condition_loop(token_list& Token_list) {

	check::symbol::require(Token_list, token_symbol::type::PAREN_LEFT);
	expr* Condition = parse_expression(Token_list);
	check::symbol::require(Token_list, token_symbol::type::PAREN_RIGHT);

	check::symbol::require(Token_list, token_symbol::type::BRACE_LEFT);

	statement_block* block = parse_statement_block(Token_list);

	return new condition_loop { Condition, block, Condition->BEGIN, block->END };
}

condition_loop* parse_loop(token_list& Token_list) {
	return parse_condition_loop(Token_list);
}