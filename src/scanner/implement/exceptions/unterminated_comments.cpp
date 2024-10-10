#include "exceptions/lexical_errors.hpp"

lexical_errors::unterminated_comments::unterminated_comments(int pos) : lexical_point_error(pos) {};

std::wstring lexical_errors::unterminated_comments::info(language lang) {
	switch (lang) {
	case language::zh_cn:
		return L"词法错误：未终结的注释";
	default:
		return L"lexical error: unterminated comments";
	}
}