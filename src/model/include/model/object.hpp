#pragma once

#include <unordered_map>
#include <string>

#include "./node.hpp"
#include "./class.hpp"

class model_object : public model_node {
public:
	model_object(model_class* type, std::unordered_map<std::wstring, model_object*> members) : type(type), members(members) {};
	model_class* type;
	model_node* get_member(std::wstring name);

private:
	std::unordered_map<std::wstring, model_object*> members;
};