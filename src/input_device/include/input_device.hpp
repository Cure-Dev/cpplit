#pragma once

#include <string>
#include "language.hpp"

class input_device {
public:
	virtual std::wstring getinfo(language) = 0;
};