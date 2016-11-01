#include "gtest/gtest.h"
#include "missing_number.h"


TEST(MissingNumber, ItFindsMissingNumber) {
    std::vector<size_t> numbers{3, 4, 1, 5};
    EXPECT_EQ(ch2::get_missing_number(numbers), 2);
}


TEST(MissingNumber, ItHandlesNoMissing) {
    std::vector<size_t> numbers{3, 4, 2, 1, 5};
    EXPECT_EQ(ch2::get_missing_number(numbers), -1);
}


TEST(MissingNumber, ItWorksOnTwoConsecutiveNumbers) {
    std::vector<size_t> numbers{0, 1};
    EXPECT_EQ(ch2::get_missing_number(numbers), -1);
}

TEST(MissingNumber, ItWorksOnOneNumber) {
    std::vector<size_t> numbers{0};
    EXPECT_EQ(ch2::get_missing_number(numbers), -1);
}

TEST(MissingNumber, ItWorksOnNoNumber) {
    std::vector<size_t> numbers{};
    EXPECT_EQ(ch2::get_missing_number(numbers), -1);
}
