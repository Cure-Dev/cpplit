#pragma once

class char_stream {
public:
	virtual wchar_t peek() = 0;
	virtual wchar_t get() = 0;
	virtual bool is_end() = 0;
	virtual void next() = 0;
	virtual int get_pos() = 0; // temp
};