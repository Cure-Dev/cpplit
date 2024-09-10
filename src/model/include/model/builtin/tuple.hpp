#pragma once

#include "model/class.hpp"
#include "model/object.hpp"

class _model_builtin_class_tuple : public model_class {
public:
	_model_builtin_class_tuple() {};
	model_node* get_member(std::wstring name) {
		throw "no member in tuple"; // init
	}
};

static auto model_builtin_class_tuple = new _model_builtin_class_tuple {};

class _builtin_object_tuple : public model_object {
public:
	_builtin_object_tuple(std::vector<model_object*> items) : model_object(model_builtin_class_tuple, {}), items(items) {};
	std::vector<model_object*> items;
};