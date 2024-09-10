#include "model/fm.hpp"
#include "model/builtin/string.hpp"

class _string_init : public model_function {
public:
	_string_init() : model_function(builtin_class_string) {};

	model_object* call(_builtin_object_tuple* arglist) {
		auto arg = arglist->items[0];
		return (dynamic_cast<model_method*> (arg->get_member(L"string"))) -> call(arg, {});
	}
} *string_init = new _string_init {};
/*不写new _string_init 无法初始化？*/

class _string_string : public model_method {
public:
	_string_string() : model_method(builtin_class_string) {};

	model_object* call(model_object* obj, std::vector<model_object*> arglist) {
		return obj;
	}
};
auto string_string = new _string_string {};

class _string_output : public model_method {
public:
	_string_output() : model_method(builtin_class_string) {};

	model_object* call(model_object* obj, std::vector<model_object*> arglist) {
		return obj;
	}
};
auto string_output = new _string_output {};

class _string_add : public model_method {
public:
	_string_add() : model_method(builtin_class_string) {}; //!

	model_object* call(model_object* obj, std::vector<model_object*> arglist) {
		auto left = dynamic_cast<builtin_object_string*> (obj);
		auto _right = arglist[0];
		auto right = dynamic_cast<builtin_object_string*> (dynamic_cast<model_method*> (_right->get_member(L"string")) -> call(_right, {}));
		return new builtin_object_string { left->val + right->val };
	}
};
auto string_add = new _string_add {};

model_class* builtin_class_string = new model_class { {}, 
	{{L"call", string_init}}, 
	{
		{ L"string", string_string },
		{ L"output", string_output },
		{ L"add", string_add },
	}
};