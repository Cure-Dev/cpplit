#include "scan_ignore.hpp"
#include <unordered_set>

/* // last by 1
template class trie<bool>;
trie<bool> ignore_set = {
	{ L" ", true },
	{ L"\t", true },
};
*/
/* // last by 2
trie ignore_set = {
	L" ",
	L"\t",
};
*/

std::unordered_set<wchar_t> ignore_charset = {
	L' ',
	L'\t',
	// `v
};

// whitespace (ignored character)
bool ignore_matched(wchar_t c) {
	return ignore_charset.find(c) != ignore_charset.end();
}

token* scan_ignore(char_stream* src) {
	src->next(); // src->pass();
	return nullptr;
}