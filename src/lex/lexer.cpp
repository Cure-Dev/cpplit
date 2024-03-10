#include "lex/lexer.hpp"
#include "lex/lex_string.hpp"

#include "reader/encoding.hpp"
#include "reader/reader.hpp"

#include "lex/tokens.hpp"
#include "lex/numcvt.hpp"
#include "exceptions/lex_errors.hpp"

#include "utils/ranges.hpp"

#include <string>
#include <vector>

#include <regex>

ranges identifier_charset = {

	{ 65, 90 },  // A-Z
	{ 97, 122 }, // a-z
	{ 95, 95 },  // _
	// { 36, 36 },  // $
	{ 48, 57 },  // 0-9
	{ 32, 32 },  // ␣

	{ 0x4E00, 0x9FFF }, // chinese characters

};

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

token_list lex(std::string filepath) {

	token_list Token_list;
	std::wstring src = read(filepath, encoding::UTF_8);

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
			while (i < length && src[i] != L'\n') { //
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

		// EOL
		else if (src[i] == L'\u000A' || src[i] == L'\u000D' || src[i] == L'\u0085') { // LF || CR || NEL
			if (Token_list.back()->TYPE != token_type::EOL_) {
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
		else if (identifier_charset.include(src[i])) {

			std::wstring val;

			do {

				if (src[i] != L' ' || src[i-1] != L' ') {
					val += src[i];
				}
				i += 1;

			} while(i < length && identifier_charset.include(src[i]));

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