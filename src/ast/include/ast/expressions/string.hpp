#pragma once

#include "./expr_entity.hpp"

class expr_string : public expr_entity {
public:
	expr_string(token_string* val, int begin, int end) : expr_entity(begin, end), VALUE(val) {};

	token_string* VALUE;

	std::wstring view() {
		return this->VALUE->view();
	}

	model_node* eval(identifier_table env, const runtime& Runtime) {
		return new builtin_object_string { this->VALUE->VALUE };
	}
};