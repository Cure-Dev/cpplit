#pragma once

#include "./expr_entity.hpp"

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

	semantic_node* eval(identifier_table env, const runtime& Runtime) {
		return env.get(this->VALUE->VALUE);
	}
};