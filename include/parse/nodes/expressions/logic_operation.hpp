#ifndef _PARSE_NODES_EXPRESSIONS_LOGIC_OPERATION_H_
#define _PARSE_NODES_EXPRESSIONS_LOGIC_OPERATION_H_

class expr_logic : public expr {
public:
	enum class type {
		AND,
		XOR,
		OR,
	};

	expr_logic(type sym, expr* left, expr* right, int begin, int end) : expr(begin, end), SYM(sym), LEFT(left), RIGHT(right) {}

	type SYM;
	expr* LEFT;
	expr* RIGHT;

	std::wstring view() {
		static std::map<type, std::wstring> to_view = {
			{ type::AND, L"&&" },
			{ type::XOR, L"\\\\" },
			{ type::OR, L"||" },
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

		return left + to_view[this->SYM] + right;
	}
};

// NOT

#endif