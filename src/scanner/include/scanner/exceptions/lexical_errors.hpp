#pragma once

#include "language.hpp"
#include "input_device.hpp"

class lexical_error {
public:
	lexical_error(input_device* device) : device(device) {};

	std::wstring msg(language lang) {
		return head(lang) + body(lang);
	}

	std::wstring head(language lang) {
		return device->getinfo(lang) + L"\n";
	}

	virtual std::wstring body(language) = 0;

private:
	input_device* device = nullptr;
};

namespace lexical_errors {
	class unterminated_comments : public lexical_error {
	public:
		unterminated_comments(input_device* device) : lexical_error(device) {};

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