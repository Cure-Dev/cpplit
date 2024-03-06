#ifndef _SEMANTIC_BUILTIN_NUMBER_H_
#define _SEMANTIC_BUILTIN_NUMBER_H_

class _semantic_builtin_class_integer : public semantic_class {
public:
	_semantic_builtin_class_integer() {};
	semantic_node* get_member(std::wstring name) {
		throw "no member in null";
	}
};

static auto semantic_builtin_class_integer = new _semantic_builtin_class_integer {};

class semantic_builtin_object_integer : public semantic_object {
public:
	semantic_builtin_object_integer(int val) : semantic_object(semantic_builtin_class_integer, {}), val(val) {};
	int val;
	std::wstring view_temp;

	semantic_object* get_member(std::wstring name) {
		if (name == L"output") {
			return new semantic_object_builtin_string { std::to_wstring(this->val) };
		}
		else if (name == L"string") {
			throw "not support";
		}
		else {
			throw "member not exists.";
		}
	}
};

#endif