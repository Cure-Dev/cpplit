#pragma once

#include "model/class.hpp"
#include "model/object.hpp"

extern model_class* builtin_class_bool;

class builtin_object_bool : public model_object {
public:
	builtin_object_bool(bool data) : model_object(builtin_class_bool, {}), data(data) {};
	bool data;
};