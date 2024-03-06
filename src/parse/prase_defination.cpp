#include "parse/parser.hpp"

defination* parse_defination(const token_list& Token_list, int& index) {
	if (dynamic_cast<token_identifier*> (Token_list[index]) != NULL) {
		token_identifier* id = dynamic_cast<token_identifier*> (Token_list[index]);
		index += 1;

		if (Token_list[index]->TYPE == token_type::EQUAL) {
			index += 1;

			auto val = parse_expression(Token_list, index);
			return new defination { id, val, id->BEGIN, val->END };
		}
		else {
			throw "暂不支持泛型";
		}
	}
	else {
		throw "expect identifier";
	}
}

defination_block* parse_defination_block(const token_list& Token_list, int& index) {
	int begin = index;

	std::vector<defination*> result;

	while (Token_list[index]->TYPE != token_type::CLOSE_BRACE) {
		if (Token_list[index]->TYPE == token_type::SEMICOLON || Token_list[index]->TYPE == token_type::EOL_) {
			index += 1;
		}
		else {
			result.push_back(parse_defination(Token_list, index));
			if (Token_list[index]->TYPE != token_type::CLOSE_BRACE && Token_list[index]->TYPE != token_type::SEMICOLON && Token_list[index]->TYPE != token_type::EOL_) {
				throw "unexpect token";
			}
		}
	}

	return new defination_block { result, begin, index };
}