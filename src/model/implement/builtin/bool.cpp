#include "model/builtin/bool.hpp"
#include "model/builtin/string.hpp"
#include "model/builtin/tuple.hpp"
#include "model/class.hpp"
#include "model/fm.hpp"

#include <vector>
#include <unordered_map>
#include <string>

class _bool_init : public model_function {
public:
	_bool_init() : model_function(builtin_class_bool) {};

	model_object* call(_builtin_object_tuple* arglist) {
		auto arg = arglist->items[0];
		return (dynamic_cast<model_method*> (arg->get_member(L"bool"))) -> call(arg, {});
	}
};
auto bool_init = new _bool_init {};

class _bool_bool : public model_method {
public:
	_bool_bool() : model_method(builtin_class_bool) {};

	model_object* call(model_object* obj, std::vector<model_object*> arglist) {
		return obj;
	}
};
auto bool_bool = new _bool_bool {};

class _bool_output : public model_method {
public:
	_bool_output() : model_method(builtin_class_bool) {};

	model_object* call(model_object* obj, std::vector<model_object*> arglist) {
		return new builtin_object_string { dynamic_cast<builtin_object_bool*> (obj)->data ? L"true" : L"false" };
	}
};
auto bool_output = new _bool_output {};

model_class* builtin_class_bool = new model_class { {}, 
	{{L"call", bool_init}}, 
	{
		{ L"bool", bool_bool },
		{ L"output", bool_output },
	}
};