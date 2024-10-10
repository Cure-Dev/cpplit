#include <vector>

#include "tokens/keyword.hpp"
#include "tokens/symbol.hpp"

#include "scan.hpp"
#include "scan_string.hpp"
#include "scan_number.hpp"
#include "scan_symbol.hpp"
#include "scan_identifier.hpp"
#include "scan_comments.hpp"
#include "scan_eol.hpp"
#include "scan_escape.hpp"
#include "scan_ignore.hpp"

// #include "position.hpp"
#include "exceptions/lexical_errors.hpp"

#include <functional>
std::vector<std::pair<std::function<bool(wchar_t)>, std::function<token*(char_stream*)>>> first_set = {
	{ ignore_matched, scan_ignore },
	{ symbol_matched, scan_symbol },
	{ number_matched, scan_number },
	{ identifier_matched, scan_identifier },
	{ string_head_matched, scan_string },
	{ eol_matched, scan_eol },
	{ line_comments_matched, scan_line_comments },
	{ block_comments_matched, scan_block_comments },
	{ escape_head_matched, scan_escape },
};

token_list scan(char_stream* src) {

	std::vector<token*> Token_list;

	while (!src->is_end()) {

		bool processed = false;
		for (auto f : first_set) {
			if (f.first(src->peek())) {
				token* result = f.second(src);
				if (result != nullptr) {
					Token_list.push_back(result);
				}
				processed = true;
				break;
			}
		}

		if (!processed) {
			throw new lexical_errors::invalid_character { src->get_pos(), src->peek() };
		}

	}

	Token_list.push_back(new token_symbol {token_symbol::type::EOF_, src->get_pos(), src->get_pos()});
	return token_list { Token_list };

}