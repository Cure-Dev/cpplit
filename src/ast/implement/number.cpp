#include "ast/expressions/number.hpp"
#include "model/builtin/number.hpp"

model_node* expr_number::eval(identifier_table env) {
	mpz_class data;
	data = this->VALUE->val;
	return new builtin_object_number { data };
}