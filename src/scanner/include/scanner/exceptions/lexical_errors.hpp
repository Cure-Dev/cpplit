#pragma once

#include "language.hpp"
#include <string>

class lexical_error {
public:
	virtual std::wstring info(language) = 0;
};

class lexical_point_error : public lexical_error {
public:
	lexical_point_error(int position) : position(position) {};
	int get_pos() {
		return position;
	}

private:
	int position;
};

class lexical_segment_error : public lexical_error {
public:
	lexical_segment_error(std::pair<int, int> position) : position(position) {};
	std::pair<int, int> get_pos() {
		return position;
	}

private:
	std::pair<int, int> position;
};

namespace lexical_errors {
	class unterminated_comments : public lexical_point_error { //
	public:
		unterminated_comments(int point) : lexical_point_error(point) {};

		std::wstring info(language lang) {
			switch (lang) {
			case language::zh_cn:
				return L"词法错误：未终结的注释";
			default:
				return L"lexical error: unterminated comments";
			}
		}

	};

	class invalid_character : public lexical_point_error {
	public:
		invalid_character(int pos, wchar_t ch);

		std::wstring info(language lang);
	private:
		wchar_t ch;
	};
};