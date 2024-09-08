#include <string>
#include <vector>
#include <unordered_set>

#include "token_list.hpp"
#include "scan_string.hpp"
#include "scan_number.hpp"
#include "scan_symbol.hpp"
#include "scan_identifier.hpp"

#include "codec.hpp"

#include "tokens/keyword.hpp"
#include "tokens/symbol.hpp"

#include "exceptions/lexical_errors.hpp"

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

token_list scan(char_stream* src) {

	std::vector<token*> Token_list;

	while (!src->is_end()) {

		int begin = src->get_pos();

		// comments.sharp_comments
		if (src->peek() == L'#') {
			try {
				do {
					src->next();
				} while (src->peek() != L'#');
			}
			catch (const char* e) { //!!
				throw new lexical_errors::unterminated_comments { device->get_point() };
			}
			src->next();
		}

		// comments.single_line
		else if (src->peek() == L';') {
			src->next(); // if reaches end
			if (src->peek() == L';') {
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

		// string
		else if (string_head_matched(src->peek())) {
			Token_list.push_back(scan_string(src));
		}

		// entity.literal.number
		else if (number_matched(src->peek())) {
			Token_list.push_back(scan_number(src));
		}

		// entity.identifier || keyword || literal
		else if (identifier_matched(src->peek())) {
			Token_list.push_back(scan_identifier(src));
		}

		// token.symbol
		else if (symbol_matched(src->peek())) {
			Token_list.push_back(scan_symbol(src));
		}

		else {
			// throw new invalid_character { filepath, position_format(src, i), src[i] };
			throw "invalid character";
		}

	}

	Token_list.push_back(new token_symbol {token_symbol::type::EOF_, src->get_pos(), src->get_pos()});
	return token_list { Token_list };

}