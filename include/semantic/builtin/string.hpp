#include <string>

#include "semantic/class.hpp"

#ifndef _SEMANTIC_BUILTIN_STRING_H_
#define _SEMANTIC_BUILTIN_STRING_H_

class _semantic_builtin_class_string : public semantic_class {
public:
	_semantic_builtin_class_string() {};

	semantic_node* get_member(std::wstring name);
};

static auto semantic_builtin_class_string = new _semantic_builtin_class_string {};

class semantic_object_builtin_string : public semantic_object {
public:
	semantic_object_builtin_string(std::wstring val) : semantic_object(semantic_builtin_class_string, {}), val(val) {};
	std::wstring val;

	semantic_object* get_member(std::wstring name) {
		if (name == L"output") {
			return this;
		}
		else if (name == L"string") {
			return this;
		}
		else {
			throw "member not exists.";
		}
	}
};

class _semantic_builtin_method_string_init : public semantic_method {
public:
	_semantic_builtin_method_string_init() : semantic_method(semantic_builtin_class_tuple)/*...*/ {};
	semantic_object* call(semantic_object* obj, std::vector<semantic_object*> arglist) {
	/*	auto val = (dynamic_cast<semantic_object_builtin_string*> (obj->get_member(L"string")))->val;
		return new semantic_object_builtin_string { val };*/

		auto object = dynamic_cast<semantic_object_builtin_string*> (arglist[0]->get_member(L"string"));
		auto val = object->val;
		return new semantic_object_builtin_string {val};
	}

	semantic_node* get_member(std::wstring name) {
		return NULL;
	}
};

#endif