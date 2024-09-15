#include "file_input_device.hpp"
#include "number_convert.hpp"

std::pair<int, int> count_pos(const std::wstring& src, const int& index) {
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

std::wstring file_input_device::getinfo(language lang) {
	switch (lang) {
	case language::zh_cn:
		return L"在文件 \"" + filepath + L"\" 中";
	default:
		return L"In file \"" + filepath + L"\"";
	}
}

std::wstring file_input_device::get_point_info(int point, language lang) {
	auto pos = count_pos(src, point);
	int line = pos.first;
	int column = pos.second;
	return getinfo(lang) + L", at line " + number_convert::to_dec(line) + L", column " + number_convert::to_dec(column);
}

std::wstring file_input_device::get_segment_info(int begin, int end, language lang) {
	return getinfo(lang) + L", from " + number_convert::to_dec(begin) + L", to " + number_convert::to_dec(end);
}
