#pragma once

#include "token_list.hpp"
#include "ast/expressions/expr.hpp"

expr* parse_logical_and(token_list& Token_list);
expr* parse_logical_or(token_list& Token_list);