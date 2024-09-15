#pragma once

#include "char_stream.hpp"

class string_char_stream : public char_stream {
public:
	string_char_stream(std::wstring data) : data(data), length(data.length()) {};

	wchar_t peek() {
		return this->data[this->index]; // throw exception if reach eof?
	}

	wchar_t get() {
		wchar_t result = this->peek();
		this->next();
		return result;
	}

	bool is_end() { // has_next
		if (this->index == this->length) { //!
			return true;
		}
		else {
			return false;
		}
	}

	void next() {
		this->index += 1;
		if (this->index > length) {
			throw "error: index out of range";
		}
	}

	int get_pos() { // temp
		return this->index;
	}

private:
	std::wstring data;
	int length;
	int index = 0;
};