#pragma once

#include <string>
#include <vector>

#include "tokens/entity.hpp"

#include "ast/node.hpp"

#include "semantic/class.hpp"
#include "semantic/identifier_table.hpp"

#include "runtime.hpp"

class expr : public node {
public:
	expr(int begin, int end) : node(begin, end) {};

	virtual semantic_node* eval(environment env, const runtime& Runtime) {
		throw "pure virtual method";
	};

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