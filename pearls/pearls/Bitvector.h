#ifndef PEARLS_BITVECTOR_H
#define PEARLS_BITVECTOR_H

#include <cstdint>
#include <vector>


namespace ch1 {
    typedef uint32_t elem_type;

    class Bitvector {
    public:
        Bitvector(size_t size);

        bool is_set(size_t index);

    private:
        std::vector<elem_type> storage;
    };

}

#endif //PEARLS_BITVECTOR_H
