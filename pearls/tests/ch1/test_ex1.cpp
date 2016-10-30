#include "gtest/gtest.h"
#include "bitvector_sort.h"

TEST(SmallSizeSortTest, ItSortsWhenBitvectorSizeIsSmall) {
    std::vector<size_t> numbers{8, 9, 1, 4, 2};
    std::vector<size_t> sorted_numbers = ch1::bitvector_sort(numbers, 2);
    std::vector<size_t> expected_sorted_numbers{1, 2, 4, 8, 9};
    EXPECT_EQ(sorted_numbers, expected_sorted_numbers);
}
