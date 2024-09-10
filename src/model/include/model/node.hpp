/* data model */

#pragma once

#include <unordered_map>
#include <string>

class model_node {
public:
	model_node(std::unordered_map<std::wstring, model_node*> members = {}) : members(members) {};
	virtual model_node* get_member(std::wstring name) = 0;
	std::unordered_map<std::wstring, model_node*> members;
};