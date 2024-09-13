#pragma once

#include "language.hpp"
#include "device_position.hpp"

class lexical_error {
public:
	lexical_error(int point) : point(point) {};

	std::wstring head(input_device* device, language lang) {
		return device->get_point_info(point, lang);
	}

	virtual std::wstring body(language) = 0;

private:
	int point;
};

namespace lexical_errors {
	class unterminated_comments : public lexical_error {
	public:
		unterminated_comments(int point) : lexical_error(point) {};

		std::wstring body(language lang) {
			switch (lang) {
			case language::zh_cn:
				return L"词法错误：未终结的注释\n";
			default:
				return L"lexical error: unterminated comments\n";
			}
		}
	};
};