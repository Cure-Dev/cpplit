#include <map>
#include <string>

#include "lex/tokens.h"

#ifndef _NODE_H_
#define _NODE_H_

class node {

public:
	int BEGIN;
	int END;
	virtual std::wstring view() {
		return this->view();
	}

	node(int begin, int end) : BEGIN(begin), END(end) {};

};

#include <regex>
static std::wstring block_indent(std::wstring ori) {
	std::wregex pat (L"\n");
	std::wstring result = L"\t" + std::regex_replace(ori, pat, L"\n\t");
	result = result.substr(0, result.length()-1); // rm the last \t
	return result;
}

#endif