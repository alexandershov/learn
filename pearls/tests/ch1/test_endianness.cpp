#include "gtest/gtest.h"
#include "endianness.h"


TEST(Endianness, ItsLittleEndian) {
    // I think that any relevant CPU is little endian :)
    EXPECT_EQ(ch1::get_endianness(), ch1::Endianness::LITTLE);
}
