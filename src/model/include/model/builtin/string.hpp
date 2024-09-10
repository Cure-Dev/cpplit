#pragma once

#include "model/class.hpp"
#include "model/object.hpp"

extern model_class* builtin_class_string;

class builtin_object_string : public model_object {
public:
	builtin_object_string(std::wstring data) : model_object(builtin_class_string, {}), val(data) {};
	std::wstring val;
};