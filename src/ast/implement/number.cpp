#include "ast/expressions/number.hpp"
#include "semantic/builtin/number.hpp"

semantic_node* expr_number::eval(identifier_table env, const runtime& Runtime) {
	mpz_class data;
	data = this->VALUE->val;
	return new builtin_object_number { data };
}