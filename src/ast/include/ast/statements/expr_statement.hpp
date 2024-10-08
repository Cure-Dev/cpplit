#pragma once

#include "ast/expressions/expr.hpp"
#include "./statement.hpp"

class expr_statement : public statement {
public:
	expr_statement(expr* Expr, int begin, int end) : statement(begin, end), EXPR(Expr) {};
	expr* EXPR;

	std::wstring view() {
		return statement::statement_view(this->EXPR->view());
	}

	void exec(identifier_table env) {
		this->EXPR->eval(env);
	}
};