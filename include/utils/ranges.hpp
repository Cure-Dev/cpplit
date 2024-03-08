#include <vector>
#include <utility>

#ifndef _UTILS_RANGES_HPP_
#define _UTILS_RANGES_HPP_

class ranges {
public:
	ranges(std::initializer_list<std::pair<int, int>> ranges_set) {
		for (auto range : ranges_set) {
			this->insert(range);
		}
	}

private:
	std::vector<std::pair<int, int>> ranges_set;

	void insert(std::pair<int, int> range) {
		if (range.first > range.second) {
			throw "first must <= second";
		}
		
		int len = this->ranges_set.size();
/*		int mid = len / 2;
		while () {
			if (range.first() <= this->ranges_set[mid].first()) {
				if (range.first() > this->ranges_set[mid-1]) //out of range
			}
		}*/
        for (int i = 0; i < len; i += 1) {
            if (this->ranges_set[i].first <= range.first && i+1 < len && range.first < this->ranges_set[i+1].first) {

            }
        }
	}
};


#include <algorithm>

class Range {
public:
    int start;
    int end;

    Range(int s, int e) : start(s), end(e) {}

    bool operator<(const Range& other) const {
        return start < other.start;
    }
};

class Ranges {
private:
    std::vector<Range> intervals;

    // 合并重叠的区间
    void mergeIntervals() {
        std::sort(intervals.begin(), intervals.end());
        auto newIntervals = std::vector<Range>();
        for (const auto& interval : intervals) {
            if (newIntervals.empty() || newIntervals.back().end < interval.start) {
                newIntervals.push_back(interval);
            } else {
                newIntervals.back().end = std::max(newIntervals.back().end, interval.end);
            }
        }
        intervals.swap(newIntervals);
    }

public:
    // 构造方法，支持列表初始化
    Ranges(std::initializer_list<Range> ranges) : intervals(ranges) {
        mergeIntervals();
    }

    // 插入新的区间
    void insert(const Range& range) {
        intervals.push_back(range);
        mergeIntervals();
    }

    // 判断一个元素是否在区间集内
    bool include(int value) const {
        // 二分查找找到第一个大于或等于value的区间
        auto it = std::lower_bound(intervals.begin(), intervals.end(), Range{value, 0});
        if (it != intervals.end() && it->start <= value) {
            return true;
        }
        return false;
    }

    // 打印区间，用于调试
    void print() const {
        for (const auto& interval : intervals) {
            std::cout << "[" << interval.start << ", " << interval.end << "]" << std::endl;
        }
    }
};

#endif