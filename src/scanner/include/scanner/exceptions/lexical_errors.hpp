#pragma once

#include "language.hpp"
#include <string>
#include "lexical_error.hpp" //! (scanner)/exceptions/lexical_errors.hpp ?

namespace lexical_errors {
	class unterminated_comments : public lexical_point_error {
	public:
		unterminated_comments(int pos);
		std::wstring info(language lang);
	};

	class invalid_character : public lexical_point_error {
	public:
		invalid_character(int pos, wchar_t ch);
		std::wstring info(language lang);
	private:
		wchar_t ch;
	};
};