#pragma once

#include "./expr_entity.hpp"

class expr_boolean : public expr_entity {
public:
	expr_boolean(token_boolean* val, int begin, int end) : expr_entity(begin, end), VALUE(val) {};

	token_boolean* VALUE;

	std::wstring view() {
		return this->VALUE->view();
	}

	model_node* eval(identifier_table env);
};