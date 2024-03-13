#include <map>
#include <string>

#include "utils/numcvt.hpp"

unsigned int cvt(std::map<wchar_t, int> cvt_map, int base, std::wstring src, int& i) {

	int result;

	if (cvt_map.find(src[i]) == cvt_map.end()) {
		throw "no digits";
	}
	else {
		result = cvt_map[src[i]];
		i += 1;
	}

	while (cvt_map.find(src[i]) != cvt_map.end()) {
		result *= base;
		result += cvt_map[src[i]];
		i += 1;
	}
	return result;
}

unsigned int cvt_bin(std::wstring src, int& i) {
	static std::map<wchar_t, int> cvt_map = {
		{ L'0', 0 },
		{ L'1', 1 },
	};
	return cvt(cvt_map, 2, src, i);
}

unsigned int cvt_oct(std::wstring src, int& i) {
	static std::map<wchar_t, int> cvt_map = {
		{ L'0', 0 },
		{ L'1', 1 },
		{ L'2', 2 },
		{ L'3', 3 },
		{ L'4', 4 },
		{ L'5', 5 },
		{ L'6', 6 },
		{ L'7', 7 },
	};
	return cvt(cvt_map, 8, src, i);
}

unsigned int cvt_dec(std::wstring src, int& i) {
	static std::map<wchar_t, int> cvt_map = {
		{ L'0', 0 },
		{ L'1', 1 },
		{ L'2', 2 },
		{ L'3', 3 },
		{ L'4', 4 },
		{ L'5', 5 },
		{ L'6', 6 },
		{ L'7', 7 },
		{ L'8', 8 },
		{ L'9', 9 },
	};
	return cvt(cvt_map, 10, src, i);
}

unsigned int cvt_hex(std::wstring src, int& i) {
	static std::map<wchar_t, int> cvt_map = {
		{ L'0', 0 },
		{ L'1', 1 },
		{ L'2', 2 },
		{ L'3', 3 },
		{ L'4', 4 },
		{ L'5', 5 },
		{ L'6', 6 },
		{ L'7', 7 },
		{ L'8', 8 },
		{ L'9', 9 },

		{ L'a', 10 },
		{ L'A', 10 },
		{ L'b', 11 },
		{ L'B', 11 },
		{ L'c', 12 },
		{ L'C', 12 },
		{ L'd', 13 },
		{ L'D', 13 },
		{ L'e', 14 },
		{ L'E', 14 },
		{ L'f', 15 },
		{ L'F', 15 },
	};
	return cvt(cvt_map, 16, src, i);
}

std::wstring to_hex(int num) {
	static std::map<int, wchar_t> map = {
		{ 0, L'0' },
		{ 1, L'1' },
		{ 2, L'2' },
		{ 3, L'3' },
		{ 4, L'4' },
		{ 5, L'5' },
		{ 6, L'6' },
		{ 7, L'7' },
		{ 8, L'8' },
		{ 9, L'9' },
		{ 10, L'A' },
		{ 11, L'B' },
		{ 12, L'C' },
		{ 13, L'D' },
		{ 14, L'E' },
		{ 15, L'F' },
	};

	std::wstring result;

	do {
		wchar_t bit = map[num % 16];
		num /= 16;
		result.insert(0, 1, bit);
		// result = bit + result; // ???
	} while (num != 0);

	return result;
}