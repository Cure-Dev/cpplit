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

#include "utils/position.hpp"

#include <codecvt>

std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

std::wstring to_wstring(const std::string& str) {
    return converter.from_bytes(str);
}


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

static trie<token_type> symbol_map = {

// 通用

	{ L"@", token_type::AT },
	{ L"?", token_type::QUESTION },
	{ L"!", token_type::NOT },
	{ L"&", token_type::AND },
	{ L"|", token_type::OR },
	{ L"\\", token_type::XOR },

	{ L"+", token_type::PLUS },
	{ L"-", token_type::MINUS },
	{ L"*", token_type::ASTERISK },
	{ L"/", token_type::SLASH },
	{ L"^", token_type::CARET },
	{ L"^/", token_type::CARET_SLASH },
	{ L"%", token_type::PERCENT },


	{ L".", token_type::DOT },
	{ L",", token_type::COMMA },
	{ L":", token_type::COLON },
	{ L";", token_type::SEMICOLON },
	{ L"(", token_type::OPEN_PAREN },
	{ L")", token_type::CLOSE_PAREN },
	{ L"[", token_type::OPEN_BRACKET },
	{ L"]", token_type::CLOSE_BRACKET },
	{ L"{", token_type::OPEN_BRACE },
	{ L"}", token_type::CLOSE_BRACE },
	{ L"<<", token_type::DOUBLE_ANGLE_BRACKET_LEFT },
	{ L">>", token_type::DOUBLE_ANGLE_BRACKET_RIGHT },

	{ L">", token_type::GREATER },
	{ L"<", token_type::LESS },
	{ L">=", token_type::GREATER_EQUAL },
	{ L"<=", token_type::LESS_EQUAL },
	{ L"==", token_type::EQUAL_EQUAL },
	{ L"!=", token_type::NOT_EQUAL },

	{ L"->", token_type::BELONG },
	{ L"=>", token_type::SUB },
	{ L"!->", token_type::NOT_BELONG },
	{ L"!=>", token_type::NOT_SUB },

	{ L"=", token_type::EQUAL },
	{ L"+=", token_type::PLUS_EQUAL },
	{ L"-=", token_type::MINUS_EQUAL },
	{ L"*=", token_type::ASTERISK_EQUAL },
	{ L"/=", token_type::SLASH_EQUAL },
	{ L"^=", token_type::CARET_EQUAL },
	{ L"^/=", token_type::CARET_SLASH_EQUAL },
	{ L"%=", token_type::PERCENT_EQUAL },

// zh-cn
	{ L"？", token_type::QUESTION },
	{ L"！", token_type::NOT },

	{ L"，", token_type::COMMA },
	{ L"：", token_type::COLON },
	{ L"；", token_type::SEMICOLON },
	{ L"（", token_type::OPEN_PAREN },
	{ L"）", token_type::CLOSE_PAREN },
	{ L"【", token_type::OPEN_BRACKET },
	{ L"】", token_type::CLOSE_BRACKET },
	{ L"｛", token_type::OPEN_BRACE },
	{ L"｝", token_type::CLOSE_BRACE },
	{ L"《", token_type::DOUBLE_ANGLE_BRACKET_LEFT },
	{ L"》", token_type::DOUBLE_ANGLE_BRACKET_RIGHT },

	{ L"！->", token_type::NOT_BELONG },
	{ L"！=>", token_type::NOT_SUB },

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
					throw new unterminated_comments { to_wstring(filepath), position_format(src, i) };
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

		// whitespace (ignore character)

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
				throw new invalid_escape { to_wstring(filepath), position_format(src, i) };
			}
		}

		// string
		else if (string_head_matched(src[i])) {
			Token_list.push_back(lex_string(src, i, to_wstring(filepath)));
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
		else if (symbol_map.include(src[i])) {
			token_type val = symbol_map.get_match(src, i);
			Token_list.push_back(new token_symbol { val, begin, i });
		}

		else {
			throw new invalid_character { to_wstring(filepath), position_format(src, i), src[i] };
		}

	}

	Token_list.push_back(new token_symbol {token_type::EOF_, length, length});
	return Token_list;

}