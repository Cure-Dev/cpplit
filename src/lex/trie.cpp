#include <string>

#include "lex/lexer.h"
#include "lex/tokens.h"
#include "lex/trie.h"

#include "exceptions/lex.h"

trie_node* symbol_tree = new trie_node(); // ！ new忘写了。。。

bool tree_made = false;

void make_symbol_tree() {

	for (auto sym : symbol_map) {
		symbol_tree->add(sym.first);
	}
	tree_made = true;
	
}

token_type get_longest_symbol_match(std::wstring text, int& index) {

	if (!tree_made) {
		make_symbol_tree();
	}

	trie_node* node = symbol_tree;
	int i = index, ori_index = index;

	int length = text.length();
	while (i < length) {

		if (node->find(text[i])) {
			node = node->children[text[i]];
			i += 1;
		}
		else {
			break;
		}

		if (node->is_end) {
			index = i;
		}
	}

	std::wstring match = text.substr(ori_index, index - ori_index);
	if (match == L"") {
		throw new invalid_character(index, text[index]);
	}
	return symbol_map[match];

}