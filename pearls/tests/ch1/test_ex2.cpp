#include "gtest/gtest.h"
#include "bitops.h"

class BitOpsRightShiftTest : public ::testing::TestWithParam<size_t> {

};


TEST_P(BitOpsRightShiftTest, ItCanRightShiftIntegers) {
    auto num_bits = GetParam();
    EXPECT_EQ(ch1::RightShift(1, num_bits), std::size_t{1} << num_bits);
}

INSTANTIATE_TEST_CASE_P(
        InterestingShifts,
        BitOpsRightShiftTest,
        ::testing::Values(0, 1, 3, 63, 64, 128));


