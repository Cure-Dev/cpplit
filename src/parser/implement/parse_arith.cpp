#include "parse_arith.hpp"
#include "ast/expressions/arith.hpp"
#include "tokens/symbol.hpp"

#include "parse_prefix.hpp"

expr* parse_multi_divis(token_list& Token_list) {

	expr* left = parse_prefix(Token_list); // 复制过来的 parse_multi_divis 忘改了 -> （编译期间）如果标识符在整个生命周期未使用，则警告。

	while (true) {
		if (token_symbol* sym = dynamic_cast<token_symbol*> (Token_list.this_()); sym != NULL) {
			if (sym->Type == token_symbol::type::ASTERISK) {
				Token_list.next();
				expr* right = parse_multi_divis(Token_list);
				left = new expr_multiplication { left, right, left->BEGIN, right->END };
			}
			else if (sym->Type == token_symbol::type::SLASH) {
				Token_list.next();
				expr* right = parse_multi_divis(Token_list);
				left = new expr_division { left, right, left->BEGIN, right->END };
			}
			else {
				break;
			}
		}
		else {
			break;
		}
	}

	return left;
}

expr* parse_plus_minus(token_list& Token_list) {
	
	expr* left = parse_multi_divis(Token_list);

	while (true) {
		if (token_symbol* sym = dynamic_cast<token_symbol*> (Token_list.this_()); sym != NULL) {
			if (sym->Type == token_symbol::type::PLUS) {
				Token_list.next();
				expr* right = parse_multi_divis(Token_list);
				left = new expr_addition { left, right, left->BEGIN, right->END };
			}
			else if (sym->Type == token_symbol::type::MINUS) {
				Token_list.next();
				expr* right = parse_multi_divis(Token_list);
				left = new expr_subtraction { left, right, left->BEGIN, right->END };
			}
			else {
				break;
			}
		}
		else {
			break;
		}
	}

	return left;
}

expr* parse_arith(token_list& Token_list) {
	return parse_plus_minus(Token_list);
}