#pragma once

#include "model/object.hpp"

static class : public model_class {
public:
	model_node* get_member(std::wstring name) {
		throw "no member in null";
	}
} *model_builtin_class_null = {};

static auto model_builtin_object_null = new model_object { model_builtin_class_null, {} };