#include <sstream>

#include "exceptions/exception.hpp"
#include "language/language.hpp"

#ifndef _FSERRS_HPP_
#define _FSERRS_HPP_

class fs_err : public exception {};

class file_err : public fs_err {};

class file_not_exists : public file_err {
public:
	file_not_exists(std::wstring filepath) : filepath(filepath) {};
	std::wstring filepath;

	std::wstring msg(language L) {
		std::wstringstream result;

		if (L == language::zh_cn) {
			result << L"错误：找不到文件 " << this->filepath;
		}
		else {
			result << "error: file " << this->filepath << " not found";
		}
		return result.str();
	}
};

// cannot access (perms)

#endif