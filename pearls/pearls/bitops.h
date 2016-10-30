#ifndef PEARLS_BITOPS_H
#define PEARLS_BITOPS_H

#include <cstddef>


namespace ch1 {
    class LogicBitOps {
    public:
        static size_t LeftShift(size_t x, size_t num_bits);

        static size_t RightShift(size_t x, size_t num_bits);
    };

    class ArithmeticBitOps {
    public:
        static size_t LeftShift(size_t x, size_t num_bits);

        static size_t RightShift(size_t x, size_t num_bits);
    };

    template<class BitOps>
    class BitVectorOps {
    public:
        static bool is_set(size_t x, size_t index) {
            return (BitOps::RightShift(x, index) % 2) != 0;
        }

        static void set_bit(size_t &x, size_t index) {
            if (is_set(x, index)) {
                return;
            }
            auto mask = BitOps::LeftShift(size_t{1}, index);
            x += mask;
        }
    };

    typedef BitVectorOps<LogicBitOps> logic_bit_vector_ops_t;
}

#endif //PEARLS_BITOPS_H
