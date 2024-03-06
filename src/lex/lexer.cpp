#include "lex/lexer.h"
#include "lex/lex_string.h"

#include "lex/tokens.h"
#include "lex/numcvt.h"
#include "exceptions/lex.h"

#include <string>
#include <vector>

#include <regex>
#include <stdexcept>

const std::vector<int> allowed_identifier_char_ranges = {
	65, 90,  // A-Z
	97, 122, // a-z
	95, 95,  // _
	// 36, 36,  // $
	48, 57,  // 0-9
	32, 32,  // ␣

	0x4e00, 0x9fff, // chinese characters
};

bool is_idn(wchar_t c) {

	for (int i = 0; i < allowed_identifier_char_ranges.size(); i += 2) {
		if (c >= allowed_identifier_char_ranges[i] && c <= allowed_identifier_char_ranges[i+1]) {
			return true;
			// break;
		}
	}
	return false;

}

bool is_num(wchar_t n) {

	if (n >= 48 && n <= 57) {
		return true;
	}
	else {
		return false;
	}
}

namespace pats {

	std::wregex num(L"^[0-9]+(\\.[0-9]+)?");

};

token_list lex(std::wstring src) {

	token_list Token_list;

	Token_list.push_back(new token_symbol {token_type::BOF_, 0, 0});

	int length = src.length();


	for (int i = 0; i < length; ) {

		int begin = i;

		// comments.sharp_comments
		if (src[i] == L'#') {

			do {
				i += 1;
				if (i >= length) {
					throw unterminated_comments(begin, i);
				}
			} while (src[i] != L'#');
			i += 1;
		}

		// comments.single_line

		else if (src.substr(i, 2) == L";;") {
			i += 2;
			while (i < length && src[i] != L'\n') {
				i += 1;
			}
		}

		// whitespace

		else if (src[i] == L' ') {
			i += 1;
		}

		else if (src[i] == L'\t' || src[i] == L'\v') {
			i += 1;
		}

		else if (src[i] == L'\n') { // or cr, nel
			token_type last_type = Token_list.back()->TYPE;
			if (
				last_type != token_type::EOL_ &&
				last_type != token_type::BOF_ &&
				last_type != token_type::COMMA &&
				last_type != token_type::SEMICOLON &&
				last_type != token_type::OPEN_PAREN &&
				last_type != token_type::OPEN_BRACKET &&
				last_type != token_type::OPEN_BRACE) {
				Token_list.push_back(new token_symbol {token_type::EOL_, begin, i});
			}
			i += 1;
		}

		// escape
		else if (src[i] == L'`') {
			i += 1;
			if (src[i] == L'\n') {
				i += 1;
			}
			// else if '`x837' 汉字标识符
			else {
				throw invalid_escape(begin, i);
			}
		}

		else if (string_head_matched(src[i])) {
			Token_list.push_back(lex_string(src, i));
		}

		// entity.literal.number
		else if (is_num(src[i])) {

			std::wsmatch regres;
			std::wstring matchfrom = src.substr(i);

			std::regex_search(matchfrom, regres, pats::num);
			std::wstring s_val = regres.str();
			// i += val.length();
			int val = cvt_dec(src, i);

			Token_list.push_back(new token_number { val, begin, i });
		}

		// entity.identifier || keyword || literal
		else if (is_idn(src[i])) {

			std::wstring val;

			do {

				if (src[i] != L' ' || src[i-1] != L' ') {
					val += src[i];
				}
				i += 1;

			} while(i < length && is_idn(src[i]));

			// remove back spaces
			if (val[val.length()-1] == L' ') {
				val = val.substr(0, val.length()-1);
			}

			if (keyword_map.find(val) != keyword_map.end()) { // is keyword
				Token_list.push_back(new token_keyword { keyword_map[val], begin, i});
			}
			else if (literal_bool_map.find(val) != literal_bool_map.end()) {
				Token_list.push_back(new token_boolean { literal_bool_map[val], begin, i });
			}
			else { // is identifier
				Token_list.push_back(new token_identifier {val, begin, i});
			}

		}

		// token.symbol
		else {

			token_type val = get_longest_symbol_match(src, i);
			Token_list.push_back(new token_symbol {val, begin, i});
			
		}

	}

	Token_list.push_back(new token_symbol {token_type::EOF_, length, length});
	return Token_list;

}