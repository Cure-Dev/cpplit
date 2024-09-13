#pragma once

#include "input_device.hpp"
#include "language.hpp"
#include "file_device_position.hpp"
#include "number_convert.hpp"

class file_input_device : public input_device {
public:
	file_input_device(std::wstring filepath) : filepath(filepath) {};

	std::wstring getinfo(language lang) {
		switch (lang) {
		case language::zh_cn:
			return L"在文件 \"" + filepath + L"\" 中";
		default:
			return L"In file \"" + filepath + L"\"";
		}
	}

	file_device_point* get_point() { //
		return new file_device_point {this, 2, 2};
	}

	std::wstring get_point_info(int point, language lang) {
		return getinfo(lang) + L", at " + number_convert::to_dec(point);
	}

	std::wstring get_segment_info(int begin, int end, language lang) {
		return getinfo(lang) + L", from " + number_convert::to_dec(begin) + L", to " + number_convert::to_dec(end);
	}

private:
	std::wstring filepath;
	char_stream* Char_stream;
};