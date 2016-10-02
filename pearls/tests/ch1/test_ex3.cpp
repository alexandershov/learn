#include "gtest/gtest.h"
#include "Bitvector.h"


TEST(test_is_set_empty, test_eq) {
    ch1::Bitvector bitvector(200);
    ASSERT_EQ(bitvector.is_set(0), false);
}
