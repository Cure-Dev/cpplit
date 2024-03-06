#ifndef _SEMANTIC_BUILTIN_NULL_HPP_
#define _SEMANTIC_BUILTIN_NULL_HPP_

class _semantic_builtin_class_null : public semantic_class {
public:
	_semantic_builtin_class_null() {};

	semantic_node* get_member(std::wstring name) {
		throw "no member in null";
	}
};

static auto semantic_builtin_class_null = new _semantic_builtin_class_null {};
static auto semantic_builtin_object_null = new semantic_object { { semantic_builtin_class_null }, {} };

#endif