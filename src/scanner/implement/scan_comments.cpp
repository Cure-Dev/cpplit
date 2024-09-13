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

void scan_block_comments(char_stream* src) {
	try {
		do {
			src->next();
		} while (block_comments_termset.find(src->peek()) == block_comments_termset.end());
	}
	catch (const char* e) { //!!
		throw new lexical_errors::unterminated_comments { src->get_pos()-1 };
	}
	src->next();
}

void scan_line_comments(char_stream*);