#include "bitvector_sort.h"
#include "Bitvector.h"

std::vector<size_t> ch1::bitvector_sort(const std::vector<size_t> &numbers) {
    if (numbers.size() == 0) {
        return {};
    }
    ch1::Bitvector bitvector(1 + *std::max_element(numbers.begin(), numbers.end()));
    for (size_t one_number: numbers) {
        bitvector.set(one_number, true);
    }
    std::vector<size_t> sorted;
    for (size_t i = 0; i < bitvector.size(); i++) {
        if (bitvector.is_set(i)) {
            sorted.push_back(i);
        }
    }
    return sorted;
}

