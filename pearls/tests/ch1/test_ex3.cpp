#include "gtest/gtest.h"
#include "Bitvector.h"


class BitvectorTest : public ::testing::TestWithParam<size_t> {

};


TEST_P(BitvectorTest, IsNotSetByDefault) {
    ch1::Bitvector bitvector(200);
    EXPECT_FALSE(bitvector.is_set(GetParam()));
}

TEST_P(BitvectorTest, IsSetWorks) {
    ch1::Bitvector bitvector(200);
    bitvector.set(GetParam(), true);
    EXPECT_TRUE(bitvector.is_set(GetParam()));
}

INSTANTIATE_TEST_CASE_P(
        InterestingBits,
        BitvectorTest,
        ::testing::Values(0, 32, 34, 199));
