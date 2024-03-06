#include <vector>
#include <map>
#include <string>

#ifndef _SEMANTIC_TYPE_H_
#define _SEMANTIC_TYPE_H_

class semantic_node {
public:
	virtual semantic_node* get_member(std::wstring name) = 0;
};

class semantic_method;

class semantic_class : public semantic_node {
public:
	// semantic_class(std::vector<semantic_class*> supers, std::map<std::wstring, semantic_method*> members) : supers(supers), methods(members) {};
	std::vector<semantic_class*> supers;

/*	semantic_node* get_member(std::wstring name) {
		if (this->members.find(name) != this->members.end()) {
			return this->members[name];
		}
		else {
			throw "member not exists.";
		}
	}*/

	// virtual semantic_method* get_method(std::wstring name) = 0;

	std::map<std::wstring, semantic_method*> methods;
};

class semantic_object : public semantic_node {
public:
	semantic_object(semantic_class* type, std::map<std::wstring, semantic_object*> members) : type(type), members(members) {};
	semantic_class* type;
	virtual semantic_node* get_member(std::wstring name) {
		return members[name];
	}

private:
	std::map<std::wstring, semantic_object*> members;
};



class _semantic_builtin_class_tuple : public semantic_class {
public:
	_semantic_builtin_class_tuple() {};
	semantic_node* get_member(std::wstring name) {
		throw "no member in tuple"; // init
	}
};

static auto semantic_builtin_class_tuple = new _semantic_builtin_class_tuple {};

class _builtin_object_tuple : public semantic_object {
public:
	_builtin_object_tuple(std::vector<semantic_object*> items) : semantic_object(semantic_builtin_class_tuple, {}), items(items) {};
	std::vector<semantic_object*> items;
};



class semantic_function : public semantic_node {
public:
	semantic_function(semantic_class* type) : return_type(type) {};
	semantic_class* return_type;

	virtual semantic_object* call(_builtin_object_tuple* arglist) {
		return this->call(arglist);
	}

	semantic_node* get_member(std::wstring name) {
	/*	if (name == L"call") {

		}*/
		return NULL;
	}
};



/*class semantic_builtin_func : public semantic_function {
public:
	semantic_builtin_func(semantic_class* type) : semantic_function(type) {};

	semantic_object* call(std::vector<semantic_object*> arglist);
};*/

/*class test_builtin_add : public semantic_builtin_func {
public:
	semantic_object* call(std::vector<semantic_object*> arglist) {
		auto first = dynamic_cast<builtin_object_integer*> (arglist[0]);
		auto second = dynamic_cast<builtin_object_integer*> (arglist[1]);
		return first->val + second->val;
	}
};*/

class semantic_method : public semantic_function {
public:
	semantic_object* call(semantic_object* obj, std::vector<semantic_object*> arglist);
};

/*class semantic_builtin_method_string : public semantic_method {
public:
	semantic_object* call(semantic_object* obj, std::vector<semantic_object*> arglist) {
		return obj;
	}
};
*/
/*// ...
auto lit_null = semantic_type { {}, {} };
// auto lit_integer = semantic_type { {}, {} };
auto lit_string = semantic_type {
	{},

	{
		{ L"string", semantic_function { lit_null } },
	},
};*/

/*auto lit_integer = new semantic_class { {} };

class builtin_object_integer : public semantic_object {
public:
	builtin_object_integer(int val) : semantic_object(lit_integer, {}), val(val) {};
	int val;
};
*/

#endif

// null == null