#include <string>
#include <map>

#ifndef _TRIE_HPP_
#define _TRIE_HPP_

class trie_node {
public:
	trie_node() : is_end(false) {};

	// bool is_end = false; // ?
	bool is_end;
	std::map<wchar_t, trie_node*> children;

	void add(std::wstring data) {
		trie_node* node = this;
		for (wchar_t c : data) {
			if (!node->children[c]) { // c !-> node.children ;; node->children.find(c) == node->children.end()
				node->children[c] = new trie_node {};
			}
			node = node->children[c];
		}
		node->is_end = true;
	}

	bool find(wchar_t c) { // search
		if (!this->children[c]) { // this->children.find(c) == this->children.end()
			return false;
		}
		else {
			return true;
		}
	}
};

#endif