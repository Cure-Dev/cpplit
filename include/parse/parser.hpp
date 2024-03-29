#include "parse/nodes.hpp"
#include "lex/tokens.hpp"


#ifndef _PARSER_H_
#define _PARSER_H_
;
// statement* parse_dec(token_list Token_list); // declaration
execution_block* parse_exe(std::wstring filepath); // imperative

expr* parse_expression(const token_list& Token_list, int& index);
expr* parse_comparation(const token_list& Token_list, int& index);

expr* parse_arith(const token_list& Token_list, int& index);

expr* parse_multi_divis(const token_list& Token_list, int& index);

expr* parse_miditem(const token_list& Token_list, int& index);
expr* parse_prefix(const token_list& Token_list, int& index);
expr* parse_suffix(const token_list& Token_list, int& index, expr* item);

expr* parse_expr_keywords(const token_list& Token_list, int& index);

expr* parse_expression(const token_list& Token_list, int& index);

defination_block* parse_defination_block(const token_list& Token_list, int& index);
TYPE_namespace* parse_namespace(const token_list& Token_list, int& index);

execution_block* parse_execution_block(const token_list& Token_list, int& index);
conditional_branch* parse_if(const token_list& Token_list, int& index);
conditional_branches* parse_ifs(const token_list& Token_list, int& index);

loop_statement* parse_loop(const token_list& Token_list, int& index);


void check_symbol(const token_list& Token_list, int& index, token_symbol::type Type);
bool check_symbol_if(token* Token, token_symbol::type Type);

#endif