#include "parse/nodes.hpp"
#include "parse/parser.hpp"

#include "exceptions/syntax_errors.hpp"

expr* parse_expr_keywords(const token_list& Token_list, int& index) {
	token_keyword* kw = dynamic_cast<token_keyword*> (Token_list[index]);
	index += 1;

	if (kw->Type == token_keyword::type::IMPORT) {
		int begin = Token_list[index]->BEGIN;

		check_symbol(Token_list, index, token_symbol::type::PAREN_LEFT);

		expr* path = parse_expression(Token_list, index);

		import* result;
		// check if path formally valid
		if (dynamic_cast<expr_string*> (path) != NULL) {
			result = new import { dynamic_cast<expr_string*> (path), begin, index };
		}
		else {
			throw "import path must be literal_string";
		}// import()

		check_symbol(Token_list, index, token_symbol::type::PAREN_RIGHT);

		return result;

	}

	else if (kw->Type == token_keyword::type::NAMESPACE) {
		return parse_namespace(Token_list, index);
	}

	else {
		throw L"保留kw";
	}
}

/*

error usage of kw

保留kw

if not

*/