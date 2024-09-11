#include <string>
#include <vector>
#include <unordered_set>

#include "tokens/keyword.hpp"
#include "tokens/symbol.hpp"

#include "scan.hpp"
#include "scan_string.hpp"
#include "scan_number.hpp"
#include "scan_symbol.hpp"
#include "scan_identifier.hpp"
#include "scan_comments.hpp"

#include "codec.hpp"
#include "position.hpp"

#include "rtenv.hpp"
#include "file_device_position.hpp"


std::unordered_set<wchar_t> ignore_charset = {
	L' ',
	L'\t',
};

std::unordered_set<wchar_t> EOL_charset = {
	L'\u000A', // LF
	L'\u000D', // CR
	L'\u0085', // NEL
};

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

#include <functional>
std::vector<std::pair<std::function<bool(wchar_t)>, std::function<token*(char_stream*)>>> first_set = {
	{ symbol_matched, scan_symbol },
	{ number_matched, scan_number },
	{ identifier_matched, scan_identifier },
	{ string_head_matched, scan_string },
};

std::vector<std::pair<std::function<bool(wchar_t)>, std::function<void(char_stream*)>>> first_set_void = {
	{ block_comments_matched, scan_block_comments },
};

token_list scan(char_stream* src) {

	std::vector<token*> Token_list;

	while (!src->is_end()) {

		int begin = src->get_pos();

		// comments.single_line
		if (src->peek() == L';') {
			src->next(); // if reaches end
			if (src->peek() == L';') { // peek to EOF in stdin?
				while (!src->is_end() && src->peek() != L'\n') { //
					src->next();
				}
			}
			else {
				Token_list.push_back(new token_symbol {token_symbol::type::SEMICOLON, begin, src->get_pos()});
			}
		}

		// whitespace (ignored character)
		else if (ignore_charset.find(src->peek()) != ignore_charset.end()) { // `v
			src->next();
		}

		// EOL
		else if (EOL_charset.find(src->peek()) != EOL_charset.end()) {
			do {
				src->next();			
			} while (EOL_charset.find(src->peek()) != EOL_charset.end());
			Token_list.push_back(new token_symbol {token_symbol::type::EOL_, begin, src->get_pos()});
		}

		// escape
		else if (src->peek() == L'`') {
			src->next();
			if (src->peek() == L'\n') {
				src->next();
			}
			// else if '`x837' 汉字标识符
			else {
				// throw new invalid_escape { filepath, position_format(src, i) };
				throw "invalid_escape";
			}
		}

		else {
			bool processed = false;
			for (auto f : first_set) {
				if (f.first(src->peek())) {
					Token_list.push_back(f.second(src));
					processed = true;
					break;
				}
			}
			if (!processed) {
				for (auto f : first_set_void) {
					if (f.first(src->peek())) {
						f.second(src);
						processed = true;
						break;
					}
				}
			}
			if (!processed) {
				throw "invalid character";
			}
		}

	}

	Token_list.push_back(new token_symbol {token_symbol::type::EOF_, src->get_pos(), src->get_pos()});
	return token_list { Token_list };

}