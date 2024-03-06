#ifndef _SEMANTIC_BUILTIN_STRING_H_
#define _SEMANTIC_BUILTIN_STRING_H_

class _semantic_builtin_class_string : public semantic_class {
public:
	_semantic_builtin_class_string() {};

	semantic_node* get_member(std::wstring name) {
		throw "no member in string";
	}
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

#endif