#include <map>
#include <string>

#include "semantic/class.hpp"

#ifndef _SEMANTIC_ENVIRONMENT_H_
#define _SEMANTIC_ENVIRONMENT_H_

class environment : public std::map<std::wstring, semantic_node*> {
public:

/*	semantic_node* operator[](std::wstring name) {
		return this[name];
	}
*/
};

#endif