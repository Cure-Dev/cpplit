#ifndef _EXCEPTIONS_COMMAND_ERRORS_HPP_
#define _EXCEPTIONS_COMMAND_ERRORS_HPP_

class command_error : public exception {};

class missing_argument : public command_error {
public:
	missing_argument(std::wstring type) : type(type) {};
	std::wstring type;

	std::wstring msg(language L) {
		return L"error: missing argument <" + this->type + L">";
	}
};

class unknown_command : public command_error {
public:
	unknown_command(std::wstring name) : name(name) {}
	std::wstring name;

	std::wstring msg(language L) {
		std::wstringstream result;

		if (L == language::zh_cn) {
			result << L"错误：未知命令 " << this->name;
		}
		else {
			result << "error: unknown command " << this->name << "\n(maybe try) type =help for more information";
		}
		return result.str();
	}
};


#endif