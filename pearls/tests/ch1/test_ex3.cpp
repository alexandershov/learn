#include <NumbersGenerator.h>
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


TEST(SortTest, ItSortsEmpty) {
    std::vector<size_t> numbers;
    std::vector<size_t> sorted_numbers = ch1::bitvector_sort(numbers);
    std::vector<size_t> expected_sorted_numbers;
    EXPECT_EQ(sorted_numbers, expected_sorted_numbers);
}

TEST(SortTest, ItSortsIterator) {
    std::vector<size_t> numbers{8, 9, 1, 4, 2};
    std::vector<size_t> sorted_numbers = ch1::bitvector_sort(numbers);
    std::vector<size_t> expected_sorted_numbers{1, 2, 4, 8, 9};
    EXPECT_EQ(sorted_numbers, expected_sorted_numbers);
}


std::vector<size_t> _generate_numbers(size_t max_value, size_t num_numbers) {
    ch1::NumbersGenerator generator(0, max_value, num_numbers);
    std::vector<size_t> numbers;
    while (!generator.IsFinished()) {
        numbers.push_back(generator.GetNextNumber());
    }
    return numbers;
}


std::vector<size_t> _cpp_sort(const std::vector<size_t> &numbers) {
    std::vector<size_t> numbers_copy(numbers);
    std::sort(numbers_copy.begin(), numbers_copy.end());
    return numbers_copy;
}

TEST(SortTest, CheckPerformance) {
    std::vector<size_t> numbers = _generate_numbers(28000, 27000);
    EXPECT_EQ(numbers.size(), 27000);
    std::vector<size_t> bitvector_sorted_numbers = ch1::bitvector_sort(numbers);
    std::vector<size_t> cpp_sorted_numbers = _cpp_sort(numbers);
    EXPECT_EQ(bitvector_sorted_numbers, cpp_sorted_numbers);
}

INSTANTIATE_TEST_CASE_P(
        InterestingBits,
        BitvectorTest,
        ::testing::Values(0, 32, 34, 199));
