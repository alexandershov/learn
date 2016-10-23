#include <cstddef>
#include "bitops.h"


size_t ch1::ArithmeticBitOps::LeftShift(size_t x, size_t num_bits){
    size_t shifted_x = x;
    while (num_bits > 0) {
        shifted_x *= 2;
        num_bits--;
    }
    return shifted_x;
}

size_t ch1::ArithmeticBitOps::RightShift(size_t x, size_t num_bits){
    size_t shifted_x = x;
    while (num_bits > 0) {
        shifted_x /= 2;
        num_bits--;
    }
    return shifted_x;
}

size_t ch1::LogicBitOps::LeftShift(size_t x, size_t num_bits) {
    return x << num_bits;
}

size_t ch1::LogicBitOps::RightShift(size_t x, size_t num_bits) {
    return x >> num_bits;
}
