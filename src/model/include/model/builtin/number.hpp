#pragma once

#include "model/class.hpp"
#include "model/object.hpp"
#include <gmpxx.h>

extern model_class* builtin_class_number;

class builtin_object_number : public model_object {
public:
	builtin_object_number(mpf_class val) : model_object(builtin_class_number, {}), val(val) {};
	mpz_class val;
};