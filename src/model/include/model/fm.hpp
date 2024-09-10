#pragma once

#include "./node.hpp"
#include "./object.hpp"
#include "model/builtin/tuple.hpp"
class model_function : public model_node {
public:
	model_function(model_class* type) : return_type(type) {};
	model_class* return_type;

	virtual model_object* call(_builtin_object_tuple* arglist) {
		return this->call(arglist);
	}

	model_node* get_member(std::wstring name) {
	/*	if (name == L"call") {

		}*/
		return NULL;
	}
};

class model_method : public model_node {
public:
	model_method(model_class* type) : return_type(type) {};
	model_class* return_type;
	virtual model_object* call(model_object* obj, std::vector<model_object*> arglist) {
		throw "no call";
	};

	model_node* get_member(std::wstring name) {
		throw L"no member named " + name;
	}
};

// null == null