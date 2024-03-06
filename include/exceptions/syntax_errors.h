#include "exceptions/exception.hpp"

#ifndef _SYNTAX_ERRORS_H_
#define _SYNTAX_ERRORS_H_

class syntex_error : public exception {
public:
	syntex_error(int begin, int end) : BEGIN(begin), END(end) {};
	int BEGIN, END;
};

class expect_punc : public syntex_error {
public:
	expect_punc(int begin, int end) : syntex_error(begin, end) {};
};

class unexpect_token : public syntex_error {
public:
	unexpect_token(int begin, int end) : syntex_error(begin, end) {};
};

class expect_identifier : public syntex_error {};

#endif