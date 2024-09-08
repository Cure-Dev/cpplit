#pragma once

#include <string>
#include <vector>

#include "tokens/token.hpp"

class token_list {
public:

	token_list(std::vector<token*> data) : data(data) {};

	token* this_() {
		return this->data[this->index];
	} //temp

	token* peek() {
		return this->data[this->index + 1];
	}

	void next() {
		this->index += 1;
	}

	void prev() {
		this->index -= 1;
	}

	token* fetch() {
		token* result = this->data[this->index];
		this->index += 1;
		return result;
	}

	std::wstring view() {
		std::wstring result;

		for (token* t : this->data) {
			result += t->view() + L" ";
		}

	    return result;
	}

private:
	std::vector <token*> data;
	int index = 0;
};