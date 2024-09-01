#pragma once

#include "device_position.hpp"
#include "input_device.hpp"
#include "number_convert.hpp"

class file_device_position : public device_position {
public:
	file_device_position(input_device* device) : device_position(device) {}; //!! file_input_device?
};

class file_device_point : public file_device_position {
public:
	file_device_point(input_device* device, int line, int column) : file_device_position(device), line(line), column(column) {};

	std::wstring msg(language lang) {
		return device->getinfo(lang) + L", at line " + number_convert::to_dec(line) + L", column " + number_convert::to_dec(column);
	}
private:
	int line;
	int column;
};