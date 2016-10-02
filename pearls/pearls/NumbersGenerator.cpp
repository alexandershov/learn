
#include <algorithm>
#include <cstdlib>
#include <numeric>
#include "NumbersGenerator.h"


ch1::NumbersGenerator::NumbersGenerator(size_t min_value, size_t max_value, size_t num_numbers) :
        min_value(min_value),
        max_value(max_value),
        num_numbers(num_numbers),
        num_generated(0),
        numbers(max_value - min_value + 1, 0) {
    std::iota(std::begin(numbers), std::end(numbers), min_value);
}

bool ch1::NumbersGenerator::IsFinished() {
    return num_generated == num_numbers;
}

size_t ch1::NumbersGenerator::GetNextNumber() {
    auto actual_size = (numbers.size() - num_generated);
    auto i = std::rand() % actual_size;
    size_t result = numbers[i];
    std::swap(numbers[i], numbers[actual_size - 1]);
    num_generated++;
    return result;
}




