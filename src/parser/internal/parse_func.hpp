#pragma once

#include "token_list.hpp"
#include "ast/expressions/expr.hpp"

expr* parse_func(token_list& token_list);