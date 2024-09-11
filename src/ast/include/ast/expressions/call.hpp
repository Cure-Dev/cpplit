#pragma once

#include "model/builtin/tuple.hpp" //
#include "model/fm.hpp" //

class arg_list : public paren_list {
public:
	arg_list(std::vector<expr*> items, int begin, int end) : paren_list(items, begin, end) {};

	_builtin_object_tuple* eval(identifier_table env) {
		std::vector<model_object*> result;
		for (auto item : this->ITEMS) {
			result.push_back(dynamic_cast<model_object*> ((item)->eval(env)));
		}
		return new _builtin_object_tuple { result };
	}
};

class expr_callation : public expr {
public:
	expr_callation(expr* callee, arg_list* caller, int begin, int end) : expr(begin, end), CALLEE(callee), CALLER(caller) {};
	expr* CALLEE;
	arg_list* CALLER; // expr_iter: use abs class?

	std::wstring view() {
		return this->CALLEE->view() + this->CALLER->view();
	}

	model_node* eval(identifier_table env) {
		auto callee = this->CALLEE->eval(env);

		if (dynamic_cast<model_function*> (callee) != NULL) { //
			return (dynamic_cast<model_function*> (callee)) -> call(this->CALLER->eval(env));
		}
		else if (auto call = dynamic_cast<model_class*> (callee); call != NULL) {//!
			return dynamic_cast<model_function*> (call->members[L"call"]) -> call(this->CALLER->eval(env));
		}
		else {
			throw "cannot call";
		}
	}
};