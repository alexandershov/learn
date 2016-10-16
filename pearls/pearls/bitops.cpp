#include <cstddef>
#include "bitops.h"


size_t ch1::RightShift(size_t x, size_t num_bits) {
    auto result = x;
    while (num_bits > 0) {
        result *= 2;
        num_bits--;
    }
    return result;
}
