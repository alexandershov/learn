#include <unordered_map>
#include <unordered_set>
#include "vector_shift.h"

void ch2::naive_left_shift_vector(std::vector<int> &numbers, size_t shift, size_t chunk_size) {
    shift %= numbers.size();
    while (shift) {
        auto actual_chunk_size = std::min(chunk_size, shift);
        auto chunk_begin = 0;
        auto chunk_end = chunk_begin + actual_chunk_size;
        std::vector<int> chunk(numbers.begin(), numbers.begin() + actual_chunk_size);
        for (auto i = chunk_end; i < numbers.size(); i++) {
            numbers[i - actual_chunk_size] = numbers[i];
        }
        auto j = 0;
        for (auto i = numbers.size() - actual_chunk_size; i < numbers.size(); i++) {
            numbers[i] = chunk[j++];
        }
        if (actual_chunk_size > shift) {
            shift = 0;
        } else {
            shift -= actual_chunk_size;
        }
    }
}

template<class Iterator>
void reverse_range(Iterator begin, Iterator end) {
    while (begin < end) {
        end--;
        std::swap(*begin, *end);
        begin++;
    }
}

void ::ch2::reversing_left_shift_vector(std::vector<int> &numbers, size_t shift) {
    shift %= numbers.size();
    // k == shift
    //  a_1, a_2, ..., a_k, b_1, b_2, ..., b_n
    reverse_range(numbers.begin(), numbers.end());
    //  b_n, ..., b_2, b_1, a_k, ..., a_2, a_1
    reverse_range(numbers.begin(), numbers.end() - shift);
    //  b_n, ..., b_2, b_1, a_1, a_2, ..., a_k
    reverse_range(numbers.end() - shift, numbers.end());
    //  b_1, b_2, ..., b_k, a_1, a_2, ..., a_k
}


template<class Iterator>
void swap_range(Iterator x, Iterator y, size_t size) {
    for (auto i = std::size_t{0}; i < size; i++) {
        std::swap(*x++, *y++);
    }
}

// TODO: gcd?
void ::ch2::recursive_left_shift_vector(std::vector<int> &numbers, size_t shift) {
    auto begin = numbers.begin();
    auto end = numbers.end();
    shift %= std::distance(begin, end);
    while (begin < end && shift) {
        auto right_size = std::distance(begin, end) - shift;
        if (shift < right_size) {
            swap_range(begin, end - shift, shift);
            end -= shift;
        } else {
            swap_range(begin, end - right_size, right_size);
            shift -= right_size;
            begin += right_size;
        }
    }
}

void ::ch2::juggling_left_shift_vector(std::vector<int> &numbers, size_t shift) {
    shift %= numbers.size();
    std::unordered_set<size_t> seen_indexes;
    size_t first_not_seen_index = 0;
    while (first_not_seen_index < numbers.size()) {
        if (std::find(seen_indexes.begin(), seen_indexes.end(), first_not_seen_index) !=
            seen_indexes.end()) {
            first_not_seen_index++;
            continue;
        }
        auto tmp = numbers[first_not_seen_index];
        size_t i = first_not_seen_index;
        size_t stop_index = first_not_seen_index;
        do {
            auto j = (i + shift) % numbers.size();
            if (j != stop_index) {
                numbers[i] = numbers[j];
            } else {
                numbers[i] = tmp;
            }
            if (std::find(seen_indexes.begin(), seen_indexes.end(), i) != seen_indexes.end()) {
                break;
            }
            seen_indexes.insert(i);
            i = j;
        } while (i != stop_index);
        first_not_seen_index++;
    }
}
