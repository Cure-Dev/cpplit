#pragma once

#include <string>

#include "model/class.hpp"
#include "model/exceptions/runtime_errors.hpp"


class identifier_table {
public:
	identifier_table() {};

/*	model_node* operator[](std::wstring name) {
		return this[name];
	}
*/
	// declare define assign
	// insert
	void add(std::wstring name, model_node* val) {
		this->map[name] = val;
	}

	// find / get
	model_node* get(std::wstring name) {
		if (this->map.find(name) != this->map.end()) {
			return this->map[name];
		}
		else {
			throw new undefined_identifier { name };
		}
	}

private:
	std::unordered_map<std::wstring, model_node*> map;
};