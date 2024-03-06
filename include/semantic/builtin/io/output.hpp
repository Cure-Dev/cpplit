#include "semantic/class.hpp"
#include "semantic/builtins.hpp"

#include <iostream>

#ifndef _SEMANTIC_BUILTIN_IO_OUTPUT_H_
#define _SEMANTIC_BUILTIN_IO_OUTPUT_H_

class lit_io_output : public semantic_function {
public:
	lit_io_output() : semantic_function(lit_null_base) {};

	semantic_object* call(_builtin_object_tuple* arglist) {
		auto arg = arglist->items[0];
		std::wcout << (dynamic_cast <semantic_object_builtin_string*> (arg->get_member(L"output"))) -> val;
		return lit_null;
	}
};

static auto _builtin_lit_io_output = new lit_io_output {};

#endif