#pragma once

#include "input_device.hpp"
#include "language.hpp"

class file_input_device : public input_device {
public:
	file_input_device(std::wstring filepath, std::wstring src) : filepath(filepath), src(src) {};

	std::wstring get_point_info(int point, language lang);

	std::wstring get_segment_info(int begin, int end, language lang);

private:
	std::wstring filepath;
	std::wstring src;

	std::wstring getinfo(language lang);

};