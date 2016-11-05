#include <vector>

#include "gtest/gtest.h"
#include "vector_shift.h"


class InPlaceShiftAlgo : public ::testing::TestWithParam<
        std::function<void(std::vector<int> &, size_t)>> {
};

TEST_P(InPlaceShiftAlgo, ItWorks) {
    std::vector<int> numbers{0, 1, 2, 3, 4};
    auto shift_algorithm = GetParam();
    shift_algorithm(numbers, 3);
    std::vector<int> expected_shifted_vector{3, 4, 0, 1, 2};
    EXPECT_EQ(numbers, expected_shifted_vector);
}

TEST(InPlaceShift, ZeroShiftDoesNothing) {
    std::vector<int> numbers{0, 1, 2, 3, 4};
    ch2::naive_left_shift_vector(numbers, 0);
    std::vector<int> expected_shifted_vector{0, 1, 2, 3, 4};
    EXPECT_EQ(numbers, expected_shifted_vector);
}

TEST(InPlaceShift, HugeShiftIsShiftModulo) {
    std::vector<int> numbers{0, 1, 2, 3, 4};
    ch2::naive_left_shift_vector(numbers, 6);
    std::vector<int> expected_shifted_vector{1, 2, 3, 4, 0};
    EXPECT_EQ(numbers, expected_shifted_vector);
}

TEST(InPlaceShift, ShiftByChunks) {
    std::vector<int> numbers{0, 1, 2, 3, 4};
    ch2::naive_left_shift_vector(numbers, 3, 2);
    std::vector<int> expected_shifted_vector{3, 4, 0, 1, 2};
    EXPECT_EQ(numbers, expected_shifted_vector);
}

TEST(InPlaceShift, ShiftByFullChunk) {
    std::vector<int> numbers{0, 1, 2, 3, 4};
    ch2::naive_left_shift_vector(numbers, 3, 3);
    std::vector<int> expected_shifted_vector{3, 4, 0, 1, 2};
    EXPECT_EQ(numbers, expected_shifted_vector);
}


void left_shift_vector(std::vector<int> &numbers, size_t shift) {
    ch2::naive_left_shift_vector(numbers, shift, shift);
}


INSTANTIATE_TEST_CASE_P(
        ShiftAlgorithms,
        InPlaceShiftAlgo,
        ::testing::Values(
                left_shift_vector,
                ch2::reversing_left_shift_vector
        ));
