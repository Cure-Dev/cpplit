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

/*template <class T> class trie {
public:
	trie(std::initializer_list<std::pair<std::wstring, T>> map) {

		for (auto p : map) {
			if (p.first.length() == 0) {
				this->val = p.second;
			}
			else {
				trie { std::vector<std::pair<std::wstring, T>> {} };
			}
		}
	};

	std::map<wchar_t, trie*> children;
	T val;
};*/


template <class T> class trie {
public:
	trie(std::initializer_list<std::pair<std::wstring, T>> map) {
		for (auto p : map) {
			this->map[p.first] = p.second;
			this->tree->add(p.first);
		}
	};

	std::map<std::wstring, T> map;
	trie_node* tree = new trie_node {};

	T get_match(const std::wstring& src, int& index) {
		trie_node* node = this->tree;
		int i = index, ori_index = index;

		int length = src.length();
		while (i < length) {

			if (node->find(src[i])) {
				node = node->children[src[i]];
				i += 1;
			}
			else {
				break;
			}

			if (node->is_end) {
				index = i;
			}
		}

		std::wstring match = src.substr(ori_index, index - ori_index);
		if (match == L"") {
			throw "no match"; //
		}
		else {
			return this->map[match];
		}
	}

	bool include(wchar_t c) {
		if (this->tree->find(c)) {
			return true;
		}
		else {
			return false;
		}
	}
};

#endif