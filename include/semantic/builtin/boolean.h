#include "semantic/class.h"

#ifndef _SEMANTIC_BUILTIN_BOOLEAN_H_
#define _SEMANTIC_BUILTIN_BOOLEAN_H_

static auto semantic_builtin_class_boolean = new semantic_class { {}, {} };

class semantic_builtin_object_boolean : public semantic_object {
public:
	semantic_builtin_object_boolean(bool state) : semantic_object(semantic_builtin_class_boolean, {}), state(state) {};
	bool state;

	semantic_object* get_member(std::wstring name) {
		if (name == L"bool") {
			return this;
		}
		else if (name == L"output") {
			return new semantic_object_builtin_string { this->state ? L"true" : L"false" };
		}
		else {
			throw "member not exists";
		}
	}
};

#endif