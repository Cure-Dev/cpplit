/* data model */

#pragma once

#include <unordered_map>
#include <string>

class semantic_node {
public:
	semantic_node(std::unordered_map<std::wstring, semantic_node*> members = {}) : members(members) {};
	virtual semantic_node* get_member(std::wstring name) = 0;
	std::unordered_map<std::wstring, semantic_node*> members;
};