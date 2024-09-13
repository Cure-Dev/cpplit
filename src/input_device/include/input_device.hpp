#pragma once

#include <string>
#include "language.hpp"
// #include "device_position.hpp"

class device_position;
class input_device {
public:
	virtual std::wstring getinfo(language) = 0;
	virtual std::wstring get_segment_info(int begin, int end, language lang) = 0;
	virtual std::wstring get_point_info(int point, language lang) = 0;
};