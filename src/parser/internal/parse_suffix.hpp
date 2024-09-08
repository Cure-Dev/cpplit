#pragma once

#include "token_list.hpp"
#include "ast/expressions/expr.hpp"

expr* parse_suffix(token_list& Token_list, expr* item);