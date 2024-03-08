#include <vector>
#include <utility>

#ifndef _UTILS_RANGES_HPP_
#define _UTILS_RANGES_HPP_

class ranges {
public:
	ranges(std::initializer_list<std::pair<int, int>> Ranges) {
		for (auto range : Ranges) {
			this->Ranges.push_back(range);
		}
	}

    bool include(int element) {
        bool result = false;
        for (auto range : this->Ranges) {
            if (element >= range.first && element <= range.second) {
                result = true;
                break;
            }
        }
        return result;
    }

private:
	std::vector<std::pair<int, int>> Ranges;
};

/*#include <algorithm>

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
};*/

#endif