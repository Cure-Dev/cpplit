#include "parse/parser.hpp"

TYPE_namespace* parse_namespace(const token_list& Token_list, int& index) {

	if (Token_list[index]->TYPE == token_type::OPEN_BRACE) {
		index += 1;
		defination_block* block = parse_defination_block(Token_list, index);

		if (Token_list[index]->TYPE == token_type::CLOSE_BRACE) {
			index += 1;
		}
		else {
			throw "expect close brace";
		}

		return new TYPE_namespace { block, block->BEGIN, block->END };
	}
	else {
		throw "expect open brace";
	}

}

conditional_branch* parse_if(const token_list& Token_list, int& index) {
	if (Token_list[index]->TYPE == token_type::OPEN_PAREN) {
		index += 1;
	}
	else {
		throw "expect open paren";
	}

	expr* Condition = parse_expression(Token_list, index);

	if (Token_list[index]->TYPE == token_type::CLOSE_PAREN) {
		index += 1;
	}
	else {
		throw "expect close paren";
	}

	if (Token_list[index]->TYPE == token_type::OPEN_BRACE) {
		index += 1;
	}
	else {
		throw "expect open brace";
	}

	execution_block* block = parse_execution_block(Token_list, index);

	return new conditional_branch { Condition, block, Condition->BEGIN, block->END };
}

conditional_branch* parse_else(const token_list& Token_list, int& index) {

	if (Token_list[index]->TYPE == token_type::OPEN_BRACE) {
		index += 1;
	}
	else {
		throw "expect open brace";
	}

	execution_block* block = parse_execution_block(Token_list, index);

	return new conditional_branch { new expr_boolean { new token_boolean { true, 1, 1 }, 1, 1 }, block, 1, block->END };
}

conditional_branches* parse_ifs(const token_list& Token_list, int& index) {

	std::vector<conditional_branch*> result;
	result.push_back(parse_if(Token_list, index));

	while (true) {
		if (Token_list[index]->TYPE == token_type::EOL_) {
			index += 1;
		}
		else if (dynamic_cast<token_keyword*> (Token_list[index]) != NULL && dynamic_cast<token_keyword*> (Token_list[index])->Type == token_keyword::type::ELSE_IF) {
			index += 1;
			result.push_back(parse_if(Token_list, index));
		}
		else {
			break;
		}
	}

	if (dynamic_cast<token_keyword*> (Token_list[index]) != NULL && dynamic_cast<token_keyword*> (Token_list[index])->Type == token_keyword::type::ELSE) {
		index += 1;
		result.push_back(parse_else(Token_list, index));
	}

	return new conditional_branches { result, 1, 1 };
}


condition_loop* parse_condition_loop(const token_list& Token_list, int& index) {

	if (Token_list[index]->TYPE == token_type::OPEN_PAREN) {
		index += 1;
	}
	else {
		throw "expect open paren";
	}

	expr* Condition = parse_expression(Token_list, index);

	if (Token_list[index]->TYPE == token_type::CLOSE_PAREN) {
		index += 1;
	}
	else {
		throw "expect close paren";
	}

	if (Token_list[index]->TYPE == token_type::OPEN_BRACE) {
		index += 1;
	}
	else {
		throw "expect open brace";
	}

	execution_block* block = parse_execution_block(Token_list, index);

	return new condition_loop { Condition, block, Condition->BEGIN, block->END };
}

loop_statement* parse_loop(const token_list& Token_list, int& index) {
	return parse_condition_loop(Token_list, index);
}