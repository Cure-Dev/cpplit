#include <vector>
#include <map>

#include "lex/tokens.h"

#include "parse/nodes.hpp"
#include "parse/parser.hpp"

#include "exceptions/syntax_errors.h"

expr_entity* make_entity(token_entity* Token) {
	
	if (dynamic_cast<token_number*> (Token) != NULL) {
		return new expr_number { dynamic_cast<token_number*> (Token), Token->BEGIN, Token->END }; // number unit
	}

	else if (dynamic_cast<token_string*> (Token) != NULL) {
		return new expr_string { dynamic_cast<token_string*> (Token), Token->BEGIN, Token->END };
	}

	else if (dynamic_cast<token_boolean*> (Token) != NULL) {
		return new expr_boolean { dynamic_cast<token_boolean*> (Token), Token->BEGIN, Token->END };
	}

	else if (dynamic_cast<token_identifier*> (Token) != NULL) {
		return new expr_identifier { dynamic_cast<token_identifier*> (Token), Token->BEGIN, Token->END }; // id string
	}

	else {
		throw ""; //
	}

}

expr* parse_prefix(const token_list& Token_list, int& index) {
	static std::map<token_type, unary_expr::type> unary_map = {
		{ token_type::PLUS, unary_expr::type::positive },
		{ token_type::MINUS, unary_expr::type::negative },
	};

	token* first = Token_list[index];

	if (unary_map.find(first->TYPE) != unary_map.end()) {
		index += 1;
		auto val = parse_multi_divis(Token_list, index);
		return new unary_expr { unary_map[first->TYPE], val, first->BEGIN, val->END };
	}
	else {
		return parse_miditem(Token_list, index);
	}
}

expr* parse_miditem(const token_list& Token_list, int& index) {
	expr* result;

	token* first = Token_list[index++];
	if (dynamic_cast<token_entity*> (first) != NULL) {
		result = make_entity(dynamic_cast<token_entity*> (first));
	}

	else if (dynamic_cast<token_keyword*> (first) != NULL) {
		index -= 1;
		result = parse_expr_keywords(Token_list, index);
	}

	else if (first->TYPE == token_type::OPEN_PAREN) {
		result = parse_expression(Token_list, index);
		if (Token_list[index]->TYPE != token_type::CLOSE_PAREN) {
			throw "expect ')' || not closed";
		}
		else {
			index += 1;
		}
	}
	else {
		throw "";
	}

	result = parse_suffix(Token_list, index, result);

	return result;
}

expr* parse_expression(const token_list& Token_list, int& index) {
	return parse_comparation(Token_list, index);
}

statement* parse_statement(const token_list& Token_list, int& index) {
	if (dynamic_cast<token_identifier*> (Token_list[index]) != NULL && Token_list[index+1]->TYPE == token_type::EQUAL) {
		token_identifier* idn = dynamic_cast<token_identifier*> (Token_list[index]); // :=
		index += 2; // += -= ...
		expr* val = parse_expression(Token_list, index); // a = +1
		return new defination { idn, val, idn->BEGIN, val->END };
	}

	else if (dynamic_cast<token_keyword*> (Token_list[index]) != NULL && dynamic_cast<token_keyword*> (Token_list[index])->Type == token_keyword::type::IF) {
		index += 1;
		return parse_ifs(Token_list, index);
	}

	else if (dynamic_cast<token_keyword*> (Token_list[index]) != NULL && dynamic_cast<token_keyword*> (Token_list[index])->Type == token_keyword::type::ELSE_IF) { // Token_list[index] => token_keyword && (Token_list->token_keyword).TYPE == token_keyword.types.ELSE_IF
		throw L"'else if' without privious 'if'";
	}

	else if (dynamic_cast<token_keyword*> (Token_list[index]) != NULL && dynamic_cast<token_keyword*> (Token_list[index])->Type == token_keyword::type::ELSE) {
		throw L"'else' without privious 'if'";
	}

	else if (dynamic_cast<token_keyword*> (Token_list[index]) != NULL && dynamic_cast<token_keyword*> (Token_list[index])->Type == token_keyword::type::LOOP) {
		index += 1;
		return parse_loop(Token_list, index);
	}

	else { // 有点草率？
		expr* Expr = parse_expression(Token_list, index);
		return new expr_statement { Expr, Expr->BEGIN, Expr->END };
	}
}

execution_block* parse_executions(const token_list& Token_list, int& index, token_type terminator) {
	std::vector<statement*> statement_list;
	int begin = index;

	while (Token_list[index]->TYPE != terminator) {

		if (Token_list[index]->TYPE == token_type::SEMICOLON || Token_list[index]->TYPE == token_type::EOL_) {
			index += 1;
		}

		else {
			statement_list.push_back(parse_statement(Token_list, index));

			if (Token_list[index]->TYPE != token_type::SEMICOLON &&
				Token_list[index]->TYPE != token_type::EOL_       &&
				Token_list[index]->TYPE != terminator) {

				throw new unexpect_token(1,1);
			}
		}

	}
	execution_block* result = new execution_block { statement_list, begin, index };
	index += 1;
	return result;
}

execution_block* parse_execution_block(const token_list& Token_list, int& index) {
	return parse_executions(Token_list, index, token_type::CLOSE_BRACE);
}

execution_block* parse_exe(token_list Token_list) { // parse main program
	
	int index = 1; // pass BOF
	
	return parse_executions(Token_list, index, token_type::EOF_);
}

expr* parse_comparation(const token_list& Token_list, int& index) {

	static std::map<token_type, comparation::type> map = {
		{ token_type::EQUAL_EQUAL, comparation::EQUAL },
		{ token_type::GREATER, comparation::GREATER },
		{ token_type::LESS, comparation::LESS },
		{ token_type::NOT_EQUAL, comparation::NOT_EQUAL },
		{ token_type::GREATER_EQUAL, comparation::GREATER_EQUAL },
		{ token_type::LESS_EQUAL, comparation::LESS_EQUAL },
	};
	expr* result;
	expr* left;

	result = parse_arith(Token_list, index);

	if (map.find(Token_list[index]->TYPE) != map.end()) {
		auto sym = Token_list[index++];
		expr* right = parse_arith(Token_list, index);
		result = new comparation { map[sym->TYPE], result, right, result->BEGIN, right->END };
		left = right;
	}

	while (map.find(Token_list[index]->TYPE) != map.end()) { // ++?
		auto sym = Token_list[index++];
		expr* right = parse_arith(Token_list, index);
		result = new expr_logic { expr_logic::type::AND, result, new comparation { map[sym->TYPE], left, right, left->BEGIN, right->END }, result->BEGIN, right->END };
		left = right;
	}
	return result;
}

/*
语句：
定义，如a=1
过程：不可赋值的，如 loop, do{}, break, (async?)
记录：可被赋值的代码块，如func, class (call?) // 或函数返回值也可以赋值，a=a+1后面的运算也可以赋值
*/