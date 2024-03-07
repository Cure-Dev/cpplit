#include "semantic/builtins.hpp"

semantic_node* _semantic_builtin_class_string::get_member(std::wstring name) {
	static auto semantic_builtin_method_string_init = new _semantic_builtin_method_string_init {};

	if (name == L"init") {
		return semantic_builtin_method_string_init;
	}
	else {
		throw "non-exists member in string";
	}
}