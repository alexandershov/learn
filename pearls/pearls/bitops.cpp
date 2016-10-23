#include <cstddef>
#include "bitops.h"


size_t ch1::RightShift(size_t x, size_t num_bits) {
    size_t shifted_x = x;
    while (num_bits > 0) {
        shifted_x *= 2;
        num_bits--;
    }
    return shifted_x;
}

bool ::ch1::IsSet(size_t x, size_t index) {
    size_t shifted_x = x;
    while (index > 0) {
        shifted_x /= 2;
        index--;
    }
    return (shifted_x % 2) != 0;
}
