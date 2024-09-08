#include "scan_identifier.hpp"
#include "ranges.hpp"
#include <unordered_map>
#include "tokens/keyword.hpp"
#include "tokens/entity.hpp" //!!

ranges identifier_charset = {

	{ 65, 90 },  // A-Z
	{ 97, 122 }, // a-z
	{ 95, 95 },  // _
	// { 36, 36 },  // $
	{ 48, 57 },  // 0-9
	{ 32, 32 },  // ␣

	{ 0x4E00, 0x9FFF }, // chinese characters

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

bool identifier_matched(wchar_t c) {
	return identifier_charset.include(c);
}

token* scan_identifier(char_stream* src) {
	int begin = src->get_pos();

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

	// keyword
	if (keyword_map.find(val) != keyword_map.end()) {
		return new token_keyword { keyword_map[val], begin, src->get_pos()};
	}
	// literal
	else if (literal_bool_map.find(val) != literal_bool_map.end()) {
		return new token_boolean { literal_bool_map[val], begin, src->get_pos() };
	}
	// normal identifier
	else { // is identifier
		return new token_identifier {val, begin, src->get_pos()};
	}
}