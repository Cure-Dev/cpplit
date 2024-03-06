#include "semantic/class.hpp"
#include "semantic/builtins.hpp"

#ifndef _IMPORT_H_
#define _IMPORT_H_

class import : public expr {
public:
	import(expr_string* path, int begin, int end) : expr(begin, end), PATH(path) {};

	expr_string* PATH;

	std::wstring view() {
		return L"import (" + this->PATH->view() + L")";
	}

	semantic_node* eval(environment env) {

		if (this->PATH->VALUE->VALUE == L"lit/io/output") {
			return _builtin_lit_io_output;
		}
		else {
			throw "waiting to add method for real import... meow~";
		}
	}
};

#endif