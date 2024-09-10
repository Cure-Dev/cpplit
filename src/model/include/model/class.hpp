#pragma once

#include <vector>
#include <unordered_map>
#include <string>

#include "./node.hpp"

class model_method;

class model_class : public model_node {
public:
	model_class(std::vector<model_class*> supers = {}, std::unordered_map<std::wstring, model_node*> members = {}, std::unordered_map<std::wstring, model_method*> methods = {}) : model_node(members), supers(supers), methods(methods) {};
	std::vector<model_class*> supers;
	std::unordered_map<std::wstring, model_method*> methods;

	model_node* get_member(std::wstring name);
};