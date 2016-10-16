#include "gtest/gtest.h"
#include "bitops.h"


TEST(BitOpsRightShift, ItCanRightShiftIntegers) {
    EXPECT_EQ(ch1::RightShift(1, 3), 1 << 3);
    EXPECT_EQ(ch1::RightShift(1, 4), 1 << 4);
}

