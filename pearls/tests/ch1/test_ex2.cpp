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
    EXPECT_EQ(ch1::LeftShift(1, num_bits), expected_result);
}

INSTANTIATE_TEST_CASE_P(
        InterestingShifts,
        BitOpsLeftShiftTest,
        ::testing::Values(0, 1, 3, 63, 64, 65, 128));


TEST(IsSetTest, IsSetWorks) {
    std::size_t x = std::size_t{1} << 3;
    x |= 1;
    EXPECT_TRUE(ch1::IsSet(x, 0));
    EXPECT_FALSE(ch1::IsSet(x, 1));
    EXPECT_TRUE(ch1::IsSet(x, 3));
    EXPECT_FALSE(ch1::IsSet(x, 4));
}

TEST(SetBitTest, SetBitWorks) {
    std::size_t x = 0;
    ch1::SetBit(x, 10);
    EXPECT_TRUE(ch1::IsSet(x, 10));
    ch1::SetBit(x, 10);
    EXPECT_TRUE(ch1::IsSet(x, 10));
}
