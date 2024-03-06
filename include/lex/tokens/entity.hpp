#ifndef _TOKENS_ENTITY_H_
#define _TOKENS_ENTITY_H_

class token_entity : public token {
public:
	token_entity(token_type type, int begin, int end) : token(type, begin, end) {};
};

class token_identifier : public token_entity {
public:
	std::wstring VALUE; // name
	token_identifier(std::wstring value, int begin, int end) : token_entity(token_type::temp, begin, end), VALUE(value) {};

	std::wstring view() {
		return this->VALUE;
	};
};

class token_literal : public token_entity {
public:
	token_literal(int begin, int end) : token_entity(token_type::temp, begin, end) {};
};

class token_number : public token_literal {
public:
	token_number(int val, int begin, int end) : token_literal(begin, end), val(val) {};
	int val;

	std::wstring view() {
		return std::to_wstring(this->val);
	};
};

#include <regex>
class token_string : public token_literal {
public:
	std::wstring VALUE;
	token_string(std::wstring value, int begin, int end) : token_literal(begin, end), VALUE(value) {};

	std::wstring view() {
		std::wstring text = std::regex_replace(this->VALUE, std::wregex(L"\\n"), L"\\n");
		return L"'" + text + L"'";
	};
};

class token_boolean : public token_literal {
public:
	bool VALUE;
	token_boolean(bool val, int begin, int end) : token_literal(begin, end), VALUE(val) {};

	std::wstring view() {
		std::wstring result = L"\033[34m";
		if (this->VALUE) {
			result += L"true";
		}
		else {
			result += L"false";
		}
		result += L"\033[0m";
		return result;
	}
};

#endif