#include <utility>
#include <vector>

void insort(std::vector<int> &vector) {
    for (uint32_t i = 1; i < vector.size(); i++) {
        auto j = i;
        while (j > 0 && vector[j] < vector[j - 1]) {
            std::swap(vector[j - 1], vector[j]);
            j--;
        }
    }
}
