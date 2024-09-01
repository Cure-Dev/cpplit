#pragma once

#include <string>
#include "language.hpp"
#include "device_position.hpp"

class device_position;
class input_device {
public:
	virtual std::wstring getinfo(language) = 0;
	virtual device_position* get_point() = 0;
};