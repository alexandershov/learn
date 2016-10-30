#ifndef PEARLS_BITVECTOR_H
#define PEARLS_BITVECTOR_H

#include <cstdint>
#include <vector>


namespace ch1 {
    typedef uint32_t elem_type;

    struct Position {
        size_t in_storage;
        size_t in_item;
    };

    class Bitvector {
    public:
        constexpr static size_t size_in_bits = sizeof(elem_type) * CHAR_BIT;
        Bitvector(size_t size);

        bool is_set(size_t index);

        void set(size_t index, bool value);

        size_t size();

    private:
        std::vector<elem_type> storage;
        size_t size_;

        Position get_position(size_t index);
    };

}

#endif //PEARLS_BITVECTOR_H
