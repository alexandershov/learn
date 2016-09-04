#include <iostream>
#include <vector>

#include "src/include/ch2/insort.h"


void test_insort();
std::string vector_to_string(std::vector<int>);
void insort_test_case(std::string, std::vector<int> input, std::vector<int> expected);

int main() {
    test_insort();
    std::cout << "done!" << std::endl;
}

void test_insort() {
    insort_test_case("basic", {8, 2, 1}, {1, 2, 8});
    insort_test_case("already sorted", {1, 3, 7}, {1, 3, 7});
    insort_test_case("empty", {}, {});
    insort_test_case("singleton", {8}, {8});
    insort_test_case("same value", {1, 1, 1, 1}, {1, 1, 1, 1});
}

void insort_test_case(std::string name, std::vector<int> input, std::vector<int> expected) {
    insort(input);
    if (input != expected) {
        std::cerr << name << " "
                  << vector_to_string(input)
                  << " != "
                  << vector_to_string(expected)
                  << std::endl;
    }
}

std::string vector_to_string(std::vector<int> vector) {
    std::string result;
    bool is_first = true;
    for (auto x: vector) {
        if (!is_first) {
            result += ", ";
        }
        result += std::to_string(x);
        is_first = false;
    }
    return "<" + result + ">";
}
