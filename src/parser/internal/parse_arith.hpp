#pragma once

#include "token_list.hpp"
#include "ast/expressions/expr.hpp"

expr* parse_arith(token_list& Token_list);

expr* parse_multi_divis(token_list& Token_list);
