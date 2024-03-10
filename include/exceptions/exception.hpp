#include <string>

#include "language/language.hpp"

#ifndef EXCEPTION_H
#define EXCEPTION_H

class exception {
public:
	virtual std::wstring msg(language L) = 0;
};

#endif