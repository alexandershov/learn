#include "gtest/gtest.h"
#include "Bitvector.h"


TEST(basic_check, test_eq) {
    Bitvector bitvector;
    EXPECT_EQ(bitvector.count(), 9);
}
