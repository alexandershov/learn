#include "gtest/gtest.h"
#include "bitops.h"

class BitOpsLeftShiftTest : public ::testing::TestWithParam<size_t> {

};


TEST_P(BitOpsLeftShiftTest, ItCanLeftShiftIntegers) {
    auto num_bits = GetParam();
    size_t expected_result = 0;
    if (num_bits < (CHAR_BIT * sizeof(std::size_t))) {
        expected_result = std::size_t{1} << num_bits;
    }
    EXPECT_EQ(ch1::ArithmeticBitOps::LeftShift(1, num_bits), expected_result);
}

INSTANTIATE_TEST_CASE_P(
        InterestingShifts,
        BitOpsLeftShiftTest,
        ::testing::Values(0, 1, 3, 63, 64, 65, 128));


TEST(IsSetTest, IsSetWorks) {
    std::size_t x = std::size_t{1} << 3;
    x |= 1;
    ch1::BitVectorOps<ch1::ArithmeticBitOps> bit_vector_ops;
    EXPECT_TRUE(bit_vector_ops.is_set(x, 0));
    EXPECT_FALSE(bit_vector_ops.is_set(x, 1));
    EXPECT_TRUE(bit_vector_ops.is_set(x, 3));
    EXPECT_FALSE(bit_vector_ops.is_set(x, 4));
}

TEST(SetBitTest, SetBitWorks) {
    ch1::BitVectorOps<ch1::ArithmeticBitOps> bit_vector_ops;

    std::size_t x = 0;
    bit_vector_ops.set_bit(x, 10);
    EXPECT_TRUE(bit_vector_ops.is_set(x, 10));
    bit_vector_ops.set_bit(x, 10);
    EXPECT_TRUE(bit_vector_ops.is_set(x, 10));
}
