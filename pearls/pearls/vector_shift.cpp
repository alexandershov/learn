#include "vector_shift.h"

void ch2::left_shift_vector(std::vector<int> &numbers, size_t shift, size_t chunk_size) {
    shift %= numbers.size();
    while (shift) {
        auto actual_chunk_size = std::max(chunk_size, shift);
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
