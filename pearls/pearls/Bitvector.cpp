#include <climits>

#include "Bitvector.h"


size_t get_num_items(size_t size) {
    size_t denominator = sizeof(ch1::elem_type) * CHAR_BIT;
    auto result = size / denominator;
    auto remainder = size % denominator;
    if (remainder) {
        result++;
    }
    return result;
}

ch1::Bitvector::Bitvector(size_t size) : storage(get_num_items(size)) {

}

bool ch1::Bitvector::is_set(size_t index) {
    auto storage_index = index / sizeof(ch1::elem_type);
    auto bit_index = index % sizeof(ch1::elem_type);
    auto result = (((size_t)1) << bit_index) & storage[storage_index];
    return result != 0;
}
