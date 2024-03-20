#include "exceptions/exception.hpp"

#ifndef _EXCEPTIONS_RUNTIME_ERRORS_HPP_
#define _EXCEPTIONS_RUNTIME_ERRORS_HPP_

class runtime_error : public exception {};

// symbol table error

class undefined_identifier : public exception {
public:
	undefined_identifier(std::wstring name) : name(name) {};
	std::wstring name;

	std::wstring msg(language L) {
		return L"undefined identifier " + this->name;
	}
};

#endif