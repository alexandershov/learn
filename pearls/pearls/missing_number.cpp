#include <cassert>
#include <algorithm>
#include "missing_number.h"


bool _range_is_full(const std::vector<size_t> &numbers, size_t begin, size_t end) {
    if (begin >= end) {
        return true;
    }
    size_t size = end - begin;
    size_t num_possible_numbers = 1 + numbers[end - 1] - numbers[begin];
    return size >= num_possible_numbers;
}

ssize_t ch2::get_missing_number(std::vector<size_t> &numbers) {
    std::sort(numbers.begin(), numbers.end());
    size_t begin = 0;
    size_t end = numbers.size();
    while (!_range_is_full(numbers, begin, end)) {
        if (end - begin == 2) {
            return numbers[begin] + 1;
        }
        size_t i = (begin + end) / 2;
//      end is decreasing, because the only case when i + 1 == end is when size is 2 and we handle
//      this case
        if (!_range_is_full(numbers, begin, i + 1)) {
            end = i + 1;
        } else if (!_range_is_full(numbers, i, end)) {
            begin = i;
        } else {
            return -1;
        }
    }
    return -1;
}
