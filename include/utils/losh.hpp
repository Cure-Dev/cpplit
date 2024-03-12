#include <vector>
#include <string>
#include <map>

#include "utils/coding.hpp"

#ifndef _LOSH_HPP_
#define _LOSH_HPP_

class losh {
public:
	losh(int argc, char** args) {
		for (int i = 1; i < argc; i += 1) {
			std::wstring arg = to_wstring(coding::UTF_8, args[i]);

			if (arg.find(L'=') != std::wstring::npos) {
				int index = arg.find(L'=');
				std::wstring front = arg.substr(0, index);
				std::wstring end = arg.substr(index + 1);

				if (front == L"") {
					if (end[0] == L'!') {
						this->bool_args[end.substr(1)] = false;
					}
					else {
						this->bool_args[end] = true;
					}
				}
				else {
					this->string_args[front] = end;
				}
			}
			else if (arg[0] == L'≠') {
				this->bool_args[arg.substr(1)] = false;
			}
			else {
				this->single_args.push_back(arg);
			}
		}
	}

	std::wstring view() {
		std::wstring result;
		for (auto arg : this->single_args) {
			result += arg + L" ";
		}
		for (auto pair : this->bool_args) {
			result += (pair.second ? L"=" : L"≠") + pair.first + L" ";
		}
		for (auto pair : this->string_args) {
			result += pair.first + L"=" + pair.second + L" ";
		}
		return result;
	}

private:
	std::vector<std::wstring> single_args;
	std::map<std::wstring, bool> bool_args;
	std::map<std::wstring, std::wstring> string_args;
};

#endif