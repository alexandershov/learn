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
    std::vector<size_t> sorted_numbers = ch1::bitvector_sort(numbers, 10);
    std::vector<size_t> expected_sorted_numbers;
    EXPECT_EQ(sorted_numbers, expected_sorted_numbers);
}

TEST(SortTest, ItSortsIterator) {
    std::vector<size_t> numbers{8, 9, 1, 4, 2};
    std::vector<size_t> sorted_numbers = ch1::bitvector_sort(numbers, 10);
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
// bitvector_sort is about 30% slower than std::sort on this data
    std::vector<size_t> numbers = _generate_numbers(27999, 27000);
    EXPECT_EQ(numbers.size(), 27000);
    auto bitvector_start = std::chrono::steady_clock::now();
    std::vector<size_t> bitvector_sorted_numbers = ch1::bitvector_sort(numbers, 28000);
    auto bitvector_end = std::chrono::steady_clock::now();
    auto bitvector_duration = std::chrono::duration_cast<std::chrono::microseconds>(
            bitvector_end - bitvector_start).count();

    auto cpp_start = std::chrono::steady_clock::now();
    std::vector<size_t> cpp_sorted_numbers = _cpp_sort(numbers);
    auto cpp_end = std::chrono::steady_clock::now();
    auto cpp_duration = std::chrono::duration_cast<std::chrono::microseconds>(
            cpp_end - cpp_start).count();
    testing::internal::CaptureStdout();
    std::cout << "bitvector took " << bitvector_duration << " microseconds" << std::endl;
    std::cout << "cpp took " << cpp_duration << " microseconds" << std::endl;
//    we need next line so te
    testing::internal::GetCapturedStdout();
    EXPECT_EQ(bitvector_sorted_numbers, cpp_sorted_numbers);
}

INSTANTIATE_TEST_CASE_P(
        InterestingBits,
        BitvectorTest,
        ::testing::Values(0, 32, 34, 199));
