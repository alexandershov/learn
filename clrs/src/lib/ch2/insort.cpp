#include <utility>
#include <vector>

void insort(std::vector<int> &vector) {
    for (int i = 1; i < vector.size(); i++) {
        auto key = vector[i];
        int j = i;
        while (j > 0 && vector[j - 1] > key) {
            j--;
        }
        int k = i - 1;
        while (k >= j) {
            std::swap(vector[k], vector[k + 1]);
            k--;
        }
        vector[j] = key;
    }
}
