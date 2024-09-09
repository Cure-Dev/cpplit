#pragma once

#include "./expr_entity.hpp"

class expr_number : public expr_entity {
public:
	expr_number(token_number* val, int begin, int end) : expr_entity(begin, end), VALUE(val) {};

	token_number* VALUE;

	std::wstring view() {
		return this->VALUE->view();
	}

	semantic_node* eval(identifier_table env, const runtime& Runtime);
};