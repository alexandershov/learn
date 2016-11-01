
#include "vector_shift.h"

void ch2::left_shift_vector(std::vector<int> &numbers, size_t shift) {
    while (shift) {
        int first = numbers[0];
        for (auto i = 1; i < numbers.size(); i++) {
            numbers[i - 1] = numbers[i];
        }
        numbers[numbers.size() - 1] = first;
        shift--;
    }
}
