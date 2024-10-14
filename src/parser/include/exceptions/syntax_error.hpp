#pragma once

#include <string>
#include "language.hpp"

class syntax_error {
public:
	virtual std::wstring info(language lang) = 0;
};

class syntax_point_error : public syntax_error {
public:
	syntax_point_error(int pos) : pos(pos) {};
	int get_pos() {
		return pos;
	}

private:
	int pos;
};