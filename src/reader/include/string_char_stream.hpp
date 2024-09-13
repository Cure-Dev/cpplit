#pragma once

#include "char_stream.hpp"
#include "number_convert.hpp"

static std::pair<int, int> count_pos(const std::wstring& src, const int& index) { //
	int line = 1;
    int column = 1;

    for (int i = 0; i < index; i += 1) {
        if (src[i] == L'\n') { //! NEL, CRLF?
            line += 1;
            column = 1;
        }
        else {
            column += 1;
        }
    }

    return { line, column };
}

class string_char_stream : public char_stream {
public:
	string_char_stream(std::wstring filepath, std::wstring data) : filepath(filepath), data(data), length(data.length()) {};

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

	std::wstring getinfo(language lang) {
		switch (lang) {
		case language::zh_cn:
			return L"在文件 \"" + filepath + L"\" 中";
		default:
			return L"In file \"" + filepath + L"\"";
		}
	}

	std::wstring get_point_info(int point, language lang) {
		auto pos = count_pos(data, point);
		int line = pos.first;
		int column = pos.second;
		return getinfo(lang) + L", at line " + number_convert::to_dec(line) + L", column " + number_convert::to_dec(column);
	}

	std::wstring get_segment_info(int begin, int end, language lang) {
		return getinfo(lang) + L", from " + number_convert::to_dec(begin) + L", to " + number_convert::to_dec(end);
	}


private:
	std::wstring filepath;
	std::wstring data;
	int length;
	int index = 0;
};