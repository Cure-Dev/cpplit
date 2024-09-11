#pragma once

#include "ast/node.hpp"
#include "model/identifier_table.hpp"

class statement : public node {
public:
	statement(int begin, int end) : node(begin, end) {};

	std::wstring statement_view(std::wstring s) {
		return s + L";\n";
	}

	virtual void exec(identifier_table env) {}; //!

};