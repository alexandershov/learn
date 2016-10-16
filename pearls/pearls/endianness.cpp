#include <cstddef>
#include "endianness.h"


namespace ch1 {
    Endianness get_endianness() {
        size_t x = 1;
        char *bytes = (char*)(&x);
        if (bytes[0] == 1) {
            return Endianness::LITTLE;
        } else {
            return Endianness::BIG;
        }
    }
}
