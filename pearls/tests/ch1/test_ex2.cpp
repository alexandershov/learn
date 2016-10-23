#include "gtest/gtest.h"
#include "bitops.h"

class BitOpsRightShiftTest : public ::testing::TestWithParam<size_t> {

};


TEST_P(BitOpsRightShiftTest, ItCanRightShiftIntegers) {
    auto num_bits = GetParam();
    size_t expected_result = 0;
    if (num_bits < (CHAR_BIT * sizeof(std::size_t))) {
        expected_result = std::size_t{1} << num_bits;
    }
    EXPECT_EQ(ch1::RightShift(1, num_bits), expected_result);
}

INSTANTIATE_TEST_CASE_P(
        InterestingShifts,
        BitOpsRightShiftTest,
        ::testing::Values(0, 1, 3, 63, 64, 65, 128));


TEST(IsSetTest, IsSetWorks) {
    std::size_t x = std::size_t{1} << 3;
    x |= 1;
    EXPECT_TRUE(ch1::IsSet(x, 0));
    EXPECT_FALSE(ch1::IsSet(x, 1));
    EXPECT_TRUE(ch1::IsSet(x, 3));
    EXPECT_FALSE(ch1::IsSet(x, 4));
}
