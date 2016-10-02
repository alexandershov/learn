#include <set>

#include "gtest/gtest.h"
#include "NumbersGenerator.h"


TEST(NumbersGenerator, GeneratesKNumbers) {
    ch1::NumbersGenerator generator(1, 10, 9);
    int num_numbers = 0;
    std::set<size_t> seen;
    while (!generator.IsFinished()) {
        auto next = generator.GetNextNumber();
        num_numbers++;
        EXPECT_TRUE(next >= 1 && next <= 10);
        EXPECT_TRUE(seen.find(next) == seen.end());
        seen.insert(next);
    }
    EXPECT_EQ(num_numbers, 9);
}
