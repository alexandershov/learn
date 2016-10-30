#include "gtest/gtest.h"
#include "Bitvector.h"
#include "bitvector_sort.h"


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

TEST(SortTest, ItSortsIterator) {
    std::vector<size_t> numbers{8, 9, 1, 4, 2};
    std::vector<size_t> sorted_numbers = ch1::bitvector_sort(numbers);
    std::vector<size_t> expected_sorted_numbers{1, 2, 4, 8, 9};
    EXPECT_EQ(sorted_numbers, expected_sorted_numbers);
}

INSTANTIATE_TEST_CASE_P(
        InterestingBits,
        BitvectorTest,
        ::testing::Values(0, 32, 34, 199));
