#include <vector>

#include "gtest/gtest.h"
#include "vector_shift.h"


TEST(InPlaceShift, ItWorks) {
    std::vector<int> numbers{0, 1, 2, 3, 4};
    ch2::left_shift_vector(numbers, 3);
    std::vector<int> expected_shifted_vector{3, 4, 0, 1, 2};
    EXPECT_EQ(numbers, expected_shifted_vector);
}

TEST(InPlaceShift, ZeroShiftDoesNothing) {
    std::vector<int> numbers{0, 1, 2, 3, 4};
    ch2::left_shift_vector(numbers, 0);
    std::vector<int> expected_shifted_vector{0, 1, 2, 3, 4};
    EXPECT_EQ(numbers, expected_shifted_vector);
}
