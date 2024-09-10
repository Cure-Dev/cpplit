#include "ast/statements/loops/condition_loop.hpp"
#include "call_method.hpp"

void condition_loop::exec(identifier_table env, const runtime& Runtime) {
	while (dynamic_cast<builtin_object_bool*> (call_method(dynamic_cast<model_object*> (this->CONDITION->eval(env, Runtime)), L"bool")) -> data) {
		this->BODY->exec(env, Runtime);
	}
};