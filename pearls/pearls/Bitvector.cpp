#include "Bitvector.h"


size_t get_num_items(size_t size) {
    auto result = size / ch1::Bitvector::size_in_bits;
    auto remainder = size % ch1::Bitvector::size_in_bits;
    if (remainder) {
        result++;
    }
    return result;
}

ch1::Bitvector::Bitvector(size_t size) : size_(size), storage(get_num_items(size), 0) {

}

bool ch1::Bitvector::is_set(size_t index) {
    ch1::Position position = get_position(index);
    auto mask = (ch1::elem_type {1}) << position.in_item;
    auto result = mask & storage[position.in_storage];
    return result != 0;
}

void ch1::Bitvector::set(size_t index, bool value) {
    Position position = get_position(index);
    ch1::elem_type mask = (ch1::elem_type {1}) << position.in_item;
    if (value) {
        storage[position.in_storage] |= mask;
    } else {
        storage[position.in_storage] &= ~mask;
    }
}

ch1::Position ch1::Bitvector::get_position(size_t index) {
    auto storage_index = index / ch1::Bitvector::size_in_bits;
    auto bit_index = index % ch1::Bitvector::size_in_bits;
    ch1::Position result = {storage_index, bit_index};
    return result;
}

size_t ch1::Bitvector::size() {
    return size_;
}
