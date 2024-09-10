#include "ast/expressions/bool.hpp"
#include "model/builtin/bool.hpp"

semantic_node* expr_boolean::eval(identifier_table env, const runtime& Runtime) {
	return new builtin_object_bool { this->VALUE->VALUE };
}