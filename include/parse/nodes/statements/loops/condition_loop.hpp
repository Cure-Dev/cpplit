#ifndef _CONDITION_LOOP_
#define _CONDITION_LOOP_

class condition_loop : public loop_statement {
public:
	condition_loop(expr* Condition, statement_block* Block, int begin, int end) : loop_statement(begin, end), CONDITION(Condition), BODY(Block) {};
	expr* CONDITION;
	statement_block* BODY;

	std::wstring view() {
		return L"loop (" + this->CONDITION->view() + L") {\n" + block_indent(this->BODY->view()) + L"}\n";
	}
};

#endif