#ifndef _ANSI_HPP_
#define _ANSI_HPP_

#include <regex>
/*#include <unistd.h>


bool out_is_redired = isatty(STDOUT_FILENO) == 0;
bool err_is_redired = isatty(STDERR_FILENO) == 0;
*/
std::wregex ansipat(L"\x1B\\[([0-9]{1,2}(;[0-9]{1,2})?)?[m|K]");

std::wstring rmansi(const std::wstring& input) {
    return std::regex_replace(input, ansipat, L"");
}

#endif