#pragma once

#include <unordered_map>
#include <string>

#include "./node.hpp"
#include "./class.hpp"

class semantic_object : public semantic_node {
public:
	semantic_object(semantic_class* type, std::unordered_map<std::wstring, semantic_object*> members) : type(type), members(members) {};
	semantic_class* type;
	semantic_node* get_member(std::wstring name);

private:
	std::unordered_map<std::wstring, semantic_object*> members;
};