#include "scan_escape.hpp"

bool escape_head_matched(wchar_t c) {
	return c == L'`';
}

token* scan_escape(char_stream* src) {
	src->next();
	if (src->peek() == L'\n') {
		src->next();
	}
	// else if '`x837' 汉字标识符
	else {
		// throw new invalid_escape { filepath, position_format(src, i) };
		throw "invalid_escape";
	}
	return nullptr;
}