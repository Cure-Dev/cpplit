#include <unordered_set>
#include "scan_eol.hpp"
#include "tokens/symbol.hpp"

std::unordered_set<wchar_t> EOL_charset = {
	L'\u000A', // LF
	L'\u000D', // CR
	L'\u0085', // NEL
};

bool eol_matched(wchar_t c) {
	return EOL_charset.find(c) != EOL_charset.end();
}

token* scan_eol(char_stream* src) {
	int begin = src->get_pos();
	do {
		src->next();			
	} while (eol_matched(src->peek()));
	return new token_symbol {token_symbol::type::EOL_, begin, src->get_pos()};
}