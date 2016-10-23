#ifndef PEARLS_BITOPS_H
#define PEARLS_BITOPS_H

#include <cstddef>


namespace ch1 {
    size_t LeftShift(size_t x, size_t num_bits);
    bool IsSet(size_t x, size_t index);
    void SetBit(size_t &x, size_t index);
}

#endif //PEARLS_BITOPS_H
