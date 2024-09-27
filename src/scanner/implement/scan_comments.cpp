#include "scan_comments.hpp"
#include "exceptions/lexical_errors.hpp"

#include <unordered_set>

std::unordered_set<wchar_t> block_comments_headset = {
	L'#',
};

std::unordered_set<wchar_t> block_comments_termset = {
	L'#',
};

bool block_comments_matched(wchar_t c) {
	return block_comments_headset.find(c) != block_comments_headset.end();
}

token* scan_block_comments(char_stream* src) {
	try {
		do {
			src->next();
		} while (block_comments_termset.find(src->peek()) == block_comments_termset.end());
	}
	catch (const char* e) { //!!
		throw new lexical_errors::unterminated_comments { src->get_pos()-1 };
	}
	src->next();
	return nullptr;
}

bool line_comments_matched(wchar_t c) {
	return c == ';';
}


// comments.single_line
#include "tokens/symbol.hpp"
token* scan_line_comments(char_stream* src) {
	int begin = src->get_pos();
	src->next(); // if reaches end?
	if (src->peek() == L';') { // peek to EOF in stdin?
		while (!src->is_end() && src->peek() != L'\n') { //
			src->next();
		}
		return nullptr;
	}
	else {
		return new token_symbol {token_symbol::type::SEMICOLON, begin, src->get_pos()};
	}
}