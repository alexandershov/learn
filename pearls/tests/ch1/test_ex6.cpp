#include "gtest/gtest.h"
#include "bitvector_sort.h"

TEST(SortInvalidTest, ItHandlesDuplicateNumbers) {
    std::vector<size_t> numbers{8, 8};
    EXPECT_THROW(ch1::bitvector_sort(numbers, 10), ch1::InvalidNumbers);
}
