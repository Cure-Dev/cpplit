#pragma once

class lexical_error {
public:
	virtual std::wstring info(language) = 0;
};

class lexical_point_error : public lexical_error {
public:
	lexical_point_error(int position) : position(position) {};
	int get_pos() {
		return position;
	}

private:
	int position;
};

class lexical_segment_error : public lexical_error {
public:
	lexical_segment_error(std::pair<int, int> position) : position(position) {};
	std::pair<int, int> get_pos() {
		return position;
	}

private:
	std::pair<int, int> position;
};