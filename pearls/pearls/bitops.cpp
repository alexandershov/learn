#include <cstddef>
#include "bitops.h"


size_t ch1::LeftShift(size_t x, size_t num_bits) {
    size_t shifted_x = x;
    while (num_bits > 0) {
        shifted_x *= 2;
        num_bits--;
    }
    return shifted_x;
}

size_t RightShift(size_t x, size_t num_bits) {
    size_t shifted_x = x;
    while (num_bits > 0) {
        shifted_x /= 2;
        num_bits--;
    }
    return shifted_x;
}

bool ::ch1::IsSet(size_t x, size_t index) {
    return (RightShift(x, index) % 2) != 0;
}

void ::ch1::SetBit(size_t &x, size_t index) {
    if (IsSet(x, index)) {
        return;
    }
    auto mask = LeftShift(size_t{1}, index);
    x += mask;
}
