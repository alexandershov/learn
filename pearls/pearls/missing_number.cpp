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
    assert(numbers.size() > 0);
    std::sort(numbers.begin(), numbers.end());
    size_t begin = 0;
    size_t end = numbers.size();
    while (!_range_is_full(numbers, begin, end)) {
        if (end - begin == 2) {
            if (numbers[begin + 1] - numbers[begin] > 1) {
                return numbers[begin] + 1;
            }
        }
        size_t i = (begin + end) / 2;
        if (!_range_is_full(numbers, begin, i + 1)) {
//            TODO: hmm, looks suspicious, is end decreasing here?
            end = i + 1;
        } else if (!_range_is_full(numbers, i, end)) {
            begin = i;
        } else {
            return -1;
        }
    }
    return -1;
}
