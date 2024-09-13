#pragma once

#include "language.hpp"

class char_stream {
public:
	virtual wchar_t peek() = 0;
	virtual wchar_t get() = 0;
	virtual bool is_end() = 0;
	virtual void next() = 0;
	virtual int get_pos() = 0; // temp

	// features from input_device
	virtual std::wstring getinfo(language) = 0;
	virtual std::wstring get_segment_info(int begin, int end, language lang) = 0;
	virtual std::wstring get_point_info(int point, language lang) = 0;
};