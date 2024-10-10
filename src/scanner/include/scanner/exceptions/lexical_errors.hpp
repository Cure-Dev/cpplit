#pragma once

#include "language.hpp"
#include <string>
#include "lexical_error.hpp" //! (scanner)/exceptions/lexical_errors.hpp ?

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