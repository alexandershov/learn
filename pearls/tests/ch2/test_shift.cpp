#include <vector>

#include "gtest/gtest.h"
#include "vector_shift.h"


TEST(InPlaceShift, ItWorks) {
    std::vector<int> numbers{0, 1, 2, 3, 4};
    auto shifted_vector = ch2::left_shift_vector(numbers, 3);
    std::vector<int> expected_shifted_vector{3, 4, 0, 1, 2};
    EXPECT_EQ(shifted_vector, expected_shifted_vector);
}
