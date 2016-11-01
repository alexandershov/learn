#include "gtest/gtest.h"
#include "missing_number.h"


TEST(MissingNumber, ItFindsMissingNumber) {
    std::vector<size_t> numbers = {3, 4, 1, 5};
    EXPECT_EQ(ch2::get_missing_number(numbers), 2);
}
