#pragma once

#include <string>
#include "language.hpp"
#include "input_device.hpp"

class input_device;

class device_position {
public:
	device_position(input_device* device) : device(device) {};
	virtual std::wstring msg(language lang) = 0;

protected:
	input_device* device;
};