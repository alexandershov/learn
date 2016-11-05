#ifndef PEARLS_VECTOR_SHIFT_H
#define PEARLS_VECTOR_SHIFT_H

#include <vector>

namespace ch2 {
    void naive_left_shift_vector(std::vector<int> &numbers, size_t shift, size_t chunk_size = 1);
    void reversing_left_shift_vector(std::vector<int> &numbers, size_t shift);
}

#endif //PEARLS_VECTOR_SHIFT_H
