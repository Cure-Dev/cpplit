#include "lex/tokens.hpp"
#include "parse/nodes.hpp"

#include "semantic/class.hpp"
#include "semantic/environment.hpp"

#ifndef _STATEMENT_H_
#define _STATEMENT_H_

class statement : public node {
public:
	statement(int begin, int end) : node(begin, end) {};

	std::wstring statement_view(std::wstring s) {
		return s + L";\n";
	}

	virtual void exec(environment env) {};

};

class expr_statement : public statement {
public:
	expr_statement(expr* Expr, int begin, int end) : statement(begin, end), EXPR(Expr) {};
	expr* EXPR;

	std::wstring view() {
		return statement::statement_view(this->EXPR->view());
	}

	void exec(environment env) {
		this->EXPR->eval(env);
	}
};

class statement_block : public node {
public:
	statement_block(std::vector<statement*> block, int begin, int end) : node(begin, end), BLOCK(block) {};
	std::vector<statement*> BLOCK;

	std::wstring view() {
		std::wstring result;
		for (auto Statement : this->BLOCK) {
			result += Statement->view();
		}
		return result;
	}
};

class defination : public statement {
public:
	defination(token_identifier* Identifier, expr* Val, int begin, int end) : statement(begin, end), IDENTIFIER(Identifier), VALUE(Val) {}; // 'id' to 'ref'
	token_identifier* IDENTIFIER;
	expr* VALUE;

	std::wstring view() {
		return statement::statement_view(this->IDENTIFIER->view() + L" = " + this->VALUE->view());
	}

	void exec(environment& env) {
		env.insert({ this->IDENTIFIER->VALUE, this->VALUE->eval(env) });
	}
};


class defination_block : public statement { // inhret node?
public:
	defination_block(std::vector<defination*> block, int begin, int end) : statement(begin, end), BLOCK(block) {};

	std::vector<defination*> BLOCK;

	std::wstring view() {
		std::wstring result;

		for (auto Defination : this->BLOCK) {
			result += Defination->view();
		}
		return result;
	}
};

class TYPE_namespace : public expr {
public:
	TYPE_namespace(defination_block* block, int begin, int end) : expr(begin, end), BLOCK(block) {};
	defination_block* BLOCK;

	std::wstring view() {
		return L"namespace {\n" + block_indent(this->BLOCK->view()) + L"}";
	}
};

/*class defination_block : public statement_block {
public:
	defination_block(std::vector<defination*> block, int begin, int end) : statement_block(block, begin, end) {};
};*/

class execution_block : public statement_block {
public:
	execution_block(std::vector<statement*> block, int begin, int end) : statement_block(block, begin, end) {}; // execution?

	void exec(environment env) {
		for (auto execution : this->BLOCK) {
			if (dynamic_cast<defination*> (execution) != NULL) {
				(dynamic_cast<defination*> (execution))->exec(env);
			}
			else {
				execution->exec(env);
			}
		}
	}
};


/*class program_definations : public defination_block {
public:
	std::wstring view() {
		std::wstring result = L":";
		for (auto Statement : this->BLOCK) {
			result += Statement->view() + L"\n";
		}
		return result;
	}
};
*/

#endif