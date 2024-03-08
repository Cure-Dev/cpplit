#include <string>
#include <map>

#ifndef _SEM_NODE_HPP_
#define _SEM_NODE_HPP_

class sem_node {
public:
	std::map<std::wstring, sem_node*> members;
};


// ======

class sem_class : public sem_node {
public:
	sem_class(std::vector<sem_class*> inherit_list, lit_func* constractor, std::vector<lit_method*> methods) {
		this->inherit_list = inherit_list;
		this->members[L"call"] = constractor;

		for (auto super : inherit_list) {
			this->methods.merge(super->methods);
		}
		this->methods.merge(methods);
	}

	std::vector<sem_class*> inherit_list;
	std::vector<lit_method*> methods;
};

class sem_object : public sem_node {
public:
	sem_object()
};
#endif