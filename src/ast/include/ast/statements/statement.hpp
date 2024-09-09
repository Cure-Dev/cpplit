#pragma once

#include "ast/node.hpp"
#include "semantic/identifier_table.hpp"
#include "runtime.hpp"

class statement : public node {
public:
	statement(int begin, int end) : node(begin, end) {};

	std::wstring statement_view(std::wstring s) {
		return s + L";\n";
	}

	virtual void exec(identifier_table env, const runtime& Runtime) {}; //!

};