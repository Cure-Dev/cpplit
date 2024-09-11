#include "model/builtin/wd.hpp"
#include "model/builtin/null.hpp"
#include <iostream>

#include "model/runtime/env.hpp"

class _ : public model_function {
public:
	_() : model_function(model_builtin_class_null) {};

	model_object* call(_builtin_object_tuple* arglist) {
		std::wcout << env::working_directory;
		return model_builtin_object_null;
	}
};

model_function* builtin_function_getwd = new _ {};