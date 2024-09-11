#include "ast/statements/conditional_branch.hpp"
#include "call_method.hpp"
#include "model/builtin/bool.hpp"

void conditional_branches::exec(identifier_table env) {
	for (auto branch : this->BRANCHES) {
		model_object* condition = dynamic_cast<model_object*> (branch->CONDITION->eval(env));
		model_object* interface;

		try {
			interface = call_method(condition, L"bool");
		}
		catch (const char*) {
			throw "no impl: bool()";
		}

		bool result = dynamic_cast<builtin_object_bool*> (interface) -> data;

		if (result) {
			branch->BLOCK->exec(env);
			break;
		}
	}
};