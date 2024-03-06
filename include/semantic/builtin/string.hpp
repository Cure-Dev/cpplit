#ifndef _SEMANTIC_BUILTIN_STRING_H_
#define _SEMANTIC_BUILTIN_STRING_H_

static auto lit_string = new semantic_class { {}, {} };

class semantic_object_builtin_string : public semantic_object {
public:
	semantic_object_builtin_string(std::wstring val) : semantic_object(lit_string, {}), val(val) {};
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