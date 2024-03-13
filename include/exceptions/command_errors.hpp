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


#endif