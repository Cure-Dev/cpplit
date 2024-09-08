#include "scan_number.hpp"
#include "ranges.hpp"

ranges digit_charset = {
	{ 48, 57 },
};

bool number_matched(wchar_t c) {
	return digit_charset.include(c) ? true : false;
}

token_number* scan_number(char_stream* src) {
	int begin = src->get_pos();

	std::wstring val;
	do {
		val += src->get();
	} while (digit_charset.include(src->peek()));
	return new token_number { encode(val), begin, src->get_pos() }; //!
}