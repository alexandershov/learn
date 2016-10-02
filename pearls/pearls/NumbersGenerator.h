
#ifndef PEARLS_NUMBERSGENERATOR_H
#define PEARLS_NUMBERSGENERATOR_H

#include <cstddef>
#include <vector>

namespace ch1 {
    class NumbersGenerator {
    public:
        NumbersGenerator(size_t min_value, size_t max_value, size_t num_numbers);
        bool IsFinished();

        size_t GetNextNumber();

    private:
        size_t min_value;
        size_t max_value;
        size_t num_numbers;
        size_t num_generated;
        std::vector<size_t> numbers;
    };
}
#endif //PEARLS_NUMBERSGENERATOR_H
