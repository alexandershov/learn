#include "gtest/gtest.h"
#include "Bitvector.h"


TEST(BitvectorTest, IsNotSetByDefault) {
    ch1::Bitvector bitvector(200);
    EXPECT_FALSE(bitvector.is_set(0));
    EXPECT_FALSE(bitvector.is_set(199));
}

TEST(BitvectorTest, IsSetWorks) {
    ch1::Bitvector bitvector(200);
    bitvector.set(10, true);
    EXPECT_TRUE(bitvector.is_set(10));
}

