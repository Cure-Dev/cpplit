#pragma once

#include "input_device.hpp"
#include "language.hpp"

class file_input_device : public input_device {
public:
	file_input_device(std::wstring filepath) : filepath(filepath) {};

	std::wstring getinfo(language lang) {
		switch (lang) {
		case language::zh_cn:
			return L"在文件 \"" + filepath + L"\" 中";
		default:
			return L"In file \"" + filepath + L"\"";
		}
	}

private:
	std::wstring filepath;
};