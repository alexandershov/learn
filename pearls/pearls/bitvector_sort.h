#ifndef PEARLS_BITVECTOR_SORT_H
#define PEARLS_BITVECTOR_SORT_H

#include <exception>
#include <vector>

namespace ch1 {
    std::vector<size_t> bitvector_sort(const std::vector<size_t> &numbers, size_t max_num_bits);
    class InvalidNumbers : public std::exception {};
}


#endif //PEARLS_BITVECTOR_SORT_H
