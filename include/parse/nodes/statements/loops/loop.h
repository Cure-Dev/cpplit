#ifndef _LOOP_H_
#define _LOOP_H_

class loop_statement : public statement {
public:
	loop_statement(int begin, int end) : statement(begin, end) {};
};

#endif