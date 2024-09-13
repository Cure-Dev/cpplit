#pragma once

#include "device_position.hpp"
#include "input_device.hpp"
#include "number_convert.hpp"

class file_position : public device_position {};

class file_point : public file_position {
public:
	file_device_point(int position) : position(position) {};
	int position;
};