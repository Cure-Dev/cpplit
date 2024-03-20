#include <string>
#include <vector>

#include "lex/tokens.hpp"

#include "parse/nodes/node.hpp"

#include "semantic/class.hpp"
#include "semantic/environment.hpp"
#include "semantic/builtins.hpp"

#ifndef _EXPR_H_
#define _EXPR_H_

class expr : public node {
public:
	expr(int begin, int end) : node(begin, end) {};

	std::wstring expr_view(std::wstring s) {
		return L"(" + s + L")";
	}

	virtual semantic_node* eval(environment env) { // 忘写virtual
		throw "";
		// return this->eval(env); //
	};

};

// --- entity --- //
class expr_entity : public expr {
public:
	expr_entity(int begin, int end) : expr(begin, end) {};
};

class unary_expr : public expr {
public:
	enum class type {
		positive,
		negative,
	};

	expr* OPERAND;
	type Type;

	unary_expr(type Type, expr* operand, int begin, int end) : expr(begin, end), Type(Type), OPERAND(operand) {};
	std::wstring view() {
		static std::map<type, std::wstring> view_map = {
			{ type::positive, L"+" },
			{ type::negative, L"-" },
		};

		std::wstring op;
		if (dynamic_cast<expr_entity*> (this->OPERAND) != NULL) {
			op = this->OPERAND->view();
		}
		else {
			op = L"(" + this->OPERAND->view() + L")";
		}

		return view_map[this->Type] + op;
	}
};

class binary_expr : public expr {
public:

	enum class type {
		addition,
		subtraction,
		multiplication,
		division,
	};

	type Type;
	expr* OPERAND_LEFT, * OPERAND_RIGHT;
	binary_expr(type Type, expr* operand1, expr* operand2, int begin, int end) : expr(begin, end), Type(Type), OPERAND_LEFT(operand1), OPERAND_RIGHT(operand2) {};

	std::wstring view() {

		static std::map<type, std::wstring> view_map = {
			{ type::addition, L"+" },
			{ type::subtraction, L"-" },
			{ type::multiplication, L"*" },
			{ type::division, L"/" },
		};

		std::wstring left, right;
		if (dynamic_cast<expr_entity*> (this->OPERAND_LEFT) != NULL) {
			left = this->OPERAND_LEFT->view();
		}
		else {
			left = L"(" + this->OPERAND_LEFT->view() + L")";
		}

		if (dynamic_cast<expr_entity*> (this->OPERAND_RIGHT) != NULL) {
			right = this->OPERAND_RIGHT->view();
		}
		else {
			right = L"(" + this->OPERAND_RIGHT->view() + L")";
		}
		return left + view_map[this->Type] + right;
	}
};


class expr_number : public expr_entity {
public:
	expr_number(token_number* val, int begin, int end) : expr_entity(begin, end), VALUE(val) {};

	token_number* VALUE;

	std::wstring view() {
		return this->VALUE->view();
	}

	semantic_node* eval(environment env) {
		return new semantic_builtin_object_integer { this->VALUE->val };
	}
};

class expr_string : public expr_entity {
public:
	expr_string(token_string* val, int begin, int end) : expr_entity(begin, end), VALUE(val) {};

	token_string* VALUE;

	std::wstring view() {
		return this->VALUE->view();
	}

	semantic_node* eval(environment env) {
		return new semantic_object_builtin_string { this->VALUE->VALUE };
	}
};

class expr_boolean : public expr_entity {
public:
	expr_boolean(token_boolean* val, int begin, int end) : expr_entity(begin, end), VALUE(val) {};

	token_boolean* VALUE;

	std::wstring view() {
		return this->VALUE->view();
	}

	semantic_node* eval(environment env) {
		return new semantic_builtin_object_boolean { this->VALUE->VALUE };
	}
};

class expr_identity : public expr_entity {
public:
	expr_identity(int begin, int end) : expr_entity(begin, end) {};
};

class expr_identifier : public expr_identity {
public:
	expr_identifier(token_identifier* val, int begin, int end) : expr_identity(begin, end), VALUE(val) {};

	token_identifier* VALUE; // name?

	std::wstring view() {
		return this->VALUE->view();
	}

	semantic_node* eval(environment env) {
		return env.get(this->VALUE->VALUE);
	}
};

class expr_iter : public expr { // node
public:
	std::vector<expr*> ITEMS;
	expr_iter(std::vector<expr*> items, int begin, int end) : expr(begin, end), ITEMS(items) {};
};

class paren_list : public expr_iter {
public:
	paren_list(std::vector<expr*> items, int begin, int end) : expr_iter(items, begin, end) {};

	std::wstring view() {
		std::wstring result = L"(";
		for (expr* item : this->ITEMS) {
			result += item->view() + L", ";
		}
		result += L")";
		return result;
	}

};

#endif