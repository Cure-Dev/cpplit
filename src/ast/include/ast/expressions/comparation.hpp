#pragma once

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

	comparation(expr* left, std::vector<std::pair<type, expr*>> right, int begin, int end) : expr(begin, end), LEFT(left), RIGHT(right) {};

	expr* LEFT;
	std::vector<std::pair<type, expr*>> RIGHT;

	std::wstring view() {
		static std::unordered_map<type, std::wstring> to_view = {
			{ EQUAL, L"==" }, // u+2a75
			{ GREATER, L">" },
			{ LESS, L"<" },
			{ NOT_EQUAL , L"≠" },
			{ GREATER_EQUAL, L"≥" },
			{ LESS_EQUAL, L"≤" },
		};

		std::wstring result = L"(";
		result += this->LEFT->view();

		for (auto p : this->RIGHT) {
			result += to_view[p.first] + p.second->view();
		}
		result += L")";

		return result;
	}
};