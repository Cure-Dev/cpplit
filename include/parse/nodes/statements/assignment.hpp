#ifndef _ASSIGNMENT_H_
#define _ASSIGNMENT_H_

class assignment : public statement {
public:
	assignment(token_identifier* Identifier, expr* Val, int begin, int end) : statement(begin, end), IDENTIFIER(Identifier), VALUE(Val) {};
	token_identifier* IDENTIFIER;
	expr* VALUE;

	std::wstring view() {
		return statement::statement_view(this->IDENTIFIER->view() + L" = " + this->VALUE->view());
	}
};

#endif