#include "parse_namespace.hpp"
#include "check.hpp"
#include "parse_defination.hpp"

TYPE_namespace* parse_namespace(token_list& Token_list) {

	check::symbol::require(Token_list, token_symbol::type::BRACE_LEFT);

	defination_block* block = parse_defination_block(Token_list);

	return new TYPE_namespace { block, block->BEGIN, block->END };

}