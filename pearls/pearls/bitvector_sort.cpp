#include <cassert>
#include "bitvector_sort.h"
#include "Bitvector.h"

std::vector<size_t> ch1::bitvector_sort(const std::vector<size_t> &numbers, size_t max_num_bits) {
    assert(max_num_bits > 0);
    if (numbers.size() == 0) {
        return {};
    }
    std::vector<size_t> sorted;
    size_t num_total_bits = 1 + *std::max_element(numbers.begin(), numbers.end());
    for (size_t offset = 0; offset < num_total_bits; offset += max_num_bits) {
        ch1::Bitvector bitvector(max_num_bits);
        for (size_t one_number: numbers) {
            if (one_number >= offset && one_number < offset + max_num_bits) {
                size_t index = one_number - offset;
                if (bitvector.is_set(index)) {
                    throw ch1::InvalidNumbers();
                }
                bitvector.set(index, true);
            }
        }
        for (size_t i = 0; i < bitvector.size(); i++) {
            if (bitvector.is_set(i)) {
                sorted.push_back(i + offset);
            }
        }
    }
    return sorted;
}

