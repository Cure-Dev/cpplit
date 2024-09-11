#pragma once

#include "ast/expressions/expr.hpp"
#include "ast/statements/statement.hpp"
#include "ast/statements/statement_block.hpp"

class condition_loop : public statement {
public:
	condition_loop(expr* Condition, statement_block* Block, int begin, int end) : statement(begin, end), CONDITION(Condition), BODY(Block) {};
	expr* CONDITION;
	statement_block* BODY;

	std::wstring view() {
		return L"loop (" + this->CONDITION->view() + L") {\n" + block_indent(this->BODY->view()) + L"}\n";
	}

	void exec(identifier_table env);
};