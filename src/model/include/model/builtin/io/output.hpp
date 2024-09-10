#pragma once

#include "model/class.hpp"
#include "model/fm.hpp"
#include "model/builtin/null.hpp"
#include "model/builtin/string.hpp"

#include <iostream>


class _lit_io_output : public model_function {
public:
	_lit_io_output() : model_function(model_builtin_class_null) {};

	model_object* call(_builtin_object_tuple* arglist) {
		auto arg = arglist->items[0];
		auto _out = arg->get_member(L"output");
		if (auto out = dynamic_cast <builtin_object_string*> (_out); out != NULL) {//!
			std::wcout << out -> val;
		}
		else if (auto out = dynamic_cast <model_method*> (_out); out != NULL) {
			std::wcout << dynamic_cast <builtin_object_string*> (out->call(arg, {})) -> val;
		}
		return model_builtin_object_null;
	}
};

static _lit_io_output* lit_io_output = new _lit_io_output {};