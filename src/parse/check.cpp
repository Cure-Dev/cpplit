#include "parse/parser.hpp"
#include "exceptions/syntax_errors.hpp"

void check_symbol(const token_list& Token_list, int& index, token_symbol::type Type) {
	if (dynamic_cast<token_symbol*> (Token_list[index]) != NULL && (dynamic_cast<token_symbol*> (Token_list[index])) -> Type == Type) {
		index += 1;
	}
	else {
		throw new expect_symbol { {index, index}, Type };
	}
}

bool check_symbol_if(token* Token, token_symbol::type Type) {
	if (dynamic_cast<token_symbol*> (Token) != NULL && (dynamic_cast<token_symbol*> (Token))->Type == Type) {
		return true;
	}
	else {
		return false;
	}
}