#include "semantic/fm.hpp"
#include "semantic/builtin/number.hpp"

class _number_init : public semantic_function {
public:
	_number_init() : semantic_function(builtin_class_number) {};

	semantic_object* call(_builtin_object_tuple* arglist) {
		auto arg = arglist->items[0];
		return (dynamic_cast<semantic_method*> (arg->get_member(L"number"))) -> call(arg, {});
	}
} *number_init = new _number_init {};

class _number_number : public semantic_method {
public:
	_number_number() : semantic_method(builtin_class_number) {};

	semantic_object* call(semantic_object* obj, std::vector<semantic_object*> arglist) {
		return obj;
	}
};
auto number_number = new _number_number {};

#include <sstream>
#include "codec.hpp"
#include "semantic/builtin/string.hpp"
class _number_output : public semantic_method {
public:
	_number_output() : semantic_method(builtin_class_number) {};

	semantic_object* call(semantic_object* obj, std::vector<semantic_object*> arglist) {
		std::stringstream s;
		s << dynamic_cast<builtin_object_number*> (obj) -> val;
		return new builtin_object_string { decode(s.str())};
	}
};
auto number_output = new _number_output {};

class _number_add : public semantic_method {
public:
	_number_add() : semantic_method(builtin_class_number) {}; //!

	// overload (for example: 1+'string'?)
	semantic_object* call(semantic_object* obj, std::vector<semantic_object*> arglist) {
		auto left = dynamic_cast<builtin_object_number*> (obj) -> val;
		auto right = dynamic_cast<builtin_object_number*> (arglist[0]) -> val;
		return new builtin_object_number { left + right };
	}
};
auto number_add = new _number_add {};

semantic_class* builtin_class_number = new semantic_class { {}, 
	{{L"call", number_init}}, 
	{
		{ L"number", number_number },
		{ L"output", number_output },
		{ L"add", number_add },
	}
};