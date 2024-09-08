#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "token_list.hpp"
#include "scan_string.hpp"

#include "codec.hpp"

#include "tokens/keyword.hpp"
#include "tokens/symbol.hpp"

#include "exceptions/lexical_errors.hpp"

#include "ranges.hpp"

#include "position.hpp"
#include "scan_symbol.hpp"

#include "rtenv.hpp"
#include "file_device_position.hpp"

ranges identifier_charset = {

	{ 65, 90 },  // A-Z
	{ 97, 122 }, // a-z
	{ 95, 95 },  // _
	// { 36, 36 },  // $
	{ 48, 57 },  // 0-9
	{ 32, 32 },  // ␣

	{ 0x4E00, 0x9FFF }, // chinese characters

};

ranges digit_charset = {
	{ 48, 57 },
};

std::unordered_map<std::wstring, token_keyword::type> keyword_map = {

// en-us
	{ L"import", token_keyword::type::IMPORT },
	{ L"if", token_keyword::type::IF },
	{ L"else if", token_keyword::type::ELSE_IF },
	{ L"else", token_keyword::type::ELSE },
	{ L"loop", token_keyword::type::LOOP },
	{ L"func", token_keyword::type::FUNC },
	{ L"class", token_keyword::type::CLASS },
	{ L"namespace", token_keyword::type::NAMESPACE },
	{ L"enum", token_keyword::type::ENUM },
	{ L"try", token_keyword::type::TRY },
	{ L"catch", token_keyword::type::CATCH },

// zh-cn
	{ L"导入", token_keyword::type::IMPORT },
	{ L"如果", token_keyword::type::IF },
	{ L"若", token_keyword::type::IF },
	{ L"又如果", token_keyword::type::ELSE_IF },
	{ L"否则", token_keyword::type::ELSE },
	{ L"循环", token_keyword::type::LOOP },
	{ L"函数", token_keyword::type::FUNC },
	{ L"类", token_keyword::type::CLASS },
	{ L"命名空间", token_keyword::type::NAMESPACE },
	{ L"枚举", token_keyword::type::ENUM },
	{ L"尝试", token_keyword::type::TRY },
	{ L"捕获", token_keyword::type::CATCH },

};

std::unordered_map<std::wstring, bool> literal_bool_map = {

// en-us
	{ L"true", true },
	{ L"false", false },

// zh-cn
	{ L"真", true },
	{ L"假", false },

};


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

std::unordered_set<wchar_t> string_head_set = {
// global
	L'\'',
	L'"',
};

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
		else if (string_head_set.find(src->peek()) != string_head_set.end()) {
			std::wstring filepath = L".lit"; //
			Token_list.push_back(scan_string(src, filepath));
		}

		// entity.literal.number
		else if (digit_charset.include(src->peek())) {
			std::wstring val;
			do {
				val += src->get();
			} while (digit_charset.include(src->peek()));
			Token_list.push_back(new token_number { encode(val), begin, src->get_pos() }); //!
		}

		// entity.identifier || keyword || literal
		else if (identifier_charset.include(src->peek())) {

			std::wstring val;
			wchar_t prev = L' ';

			do {

				wchar_t current = src->get();
				if (current != L' ' || prev != L' ') {
					val += current;
					prev = current;
				}

			} while(!src->is_end() && identifier_charset.include(src->peek()));

			// remove back spaces
			if (val[val.length()-1] == L' ') {
				val = val.substr(0, val.length()-1);
			}

			if (keyword_map.find(val) != keyword_map.end()) { // is keyword
				Token_list.push_back(new token_keyword { keyword_map[val], begin, src->get_pos()});
			}
			else if (literal_bool_map.find(val) != literal_bool_map.end()) {
				Token_list.push_back(new token_boolean { literal_bool_map[val], begin, src->get_pos() });
			}
			else { // is identifier
				Token_list.push_back(new token_identifier {val, begin, src->get_pos()});
			}

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