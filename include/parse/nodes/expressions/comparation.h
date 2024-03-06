#ifndef _PARSE_NODES_EXPRESSIONS_COMPARATION_H_
#define _PARSE_NODES_EXPRESSIONS_COMPARATION_H_

class comparation : public expr {
public:

	enum type {
		EQUAL,
		GREATER,
		LESS,
		NOT_EQUAL,
		GREATER_EQUAL,
		LESS_EQUAL,
	};

	comparation(type sym, expr* left, expr* right, int begin, int end) : expr(begin, end), SYM(sym), LEFT(left), RIGHT(right) {};

	type SYM;
	expr* LEFT;
	expr* RIGHT;

	std::wstring view() {
		static std::map<type, std::wstring> to_view = {
			{ EQUAL, L"==" },
			{ GREATER, L">" },
			{ LESS, L"<" },
			{ NOT_EQUAL , L"!=" },
			{ GREATER_EQUAL, L">=" },
			{ LESS_EQUAL, L"<=" },
		};

		std::wstring left, right;
		if (dynamic_cast<expr_entity*> (this->LEFT) != NULL) {
			left = this->LEFT->view();
		}
		else {
			left = L"(" + this->LEFT->view() + L")";
		}

		if (dynamic_cast<expr_entity*> (this->RIGHT) != NULL) {
			right = this->RIGHT->view();
		}
		else {
			right = L"(" + this->RIGHT->view() + L")";
		}

		return left + to_view[this->SYM] + right; // static method?
	}
};

#endif