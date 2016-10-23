#ifndef PEARLS_BITOPS_H
#define PEARLS_BITOPS_H

#include <cstddef>


namespace ch1 {
    class LogicBitOps {
    public:
        size_t LeftShift(size_t x, size_t num_bits);

        size_t RightShift(size_t x, size_t num_bits);
    };

    class ArithmeticBitOps {
    public:
        size_t LeftShift(size_t x, size_t num_bits);

        size_t RightShift(size_t x, size_t num_bits);
    };

    template<class BitOps>
    class BitVectorOps {
    public:
        BitVectorOps(BitOps bit_ops) : bit_ops(bit_ops) {}

        bool is_set(size_t x, size_t index) {
            return (bit_ops.RightShift(x, index) % 2) != 0;
        }

        void set_bit(size_t &x, size_t index) {
            if (is_set(x, index)) {
                return;
            }
            auto mask = bit_ops.LeftShift(size_t{1}, index);
            x += mask;
        }

    private:
        BitOps bit_ops;
    };
}

#endif //PEARLS_BITOPS_H
