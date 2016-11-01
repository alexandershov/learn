#include "gtest/gtest.h"
#include "anagrams.h"

#define EXPECT_CONTAINS(container, value) EXPECT_TRUE(contains(callback.strings, value)) \
                        << ::testing::PrintToString(container) \
                        << " doesn't contain " << value;


class AppendingCallback {
public:
    void operator()(std::string string) {
        strings.push_back(string);
    }

    std::vector<std::string> strings;
};

bool contains(const std::vector<std::string> &strings, const std::string &string) {
    return std::find(strings.begin(), strings.end(), string) != strings.end();
}


TEST(Permutations, ItWorks) {
    AppendingCallback callback;
    ch2::for_each_permutation("tes", callback);
    EXPECT_EQ(callback.strings.size(), 6);
    EXPECT_CONTAINS(callback.strings, "tes");
    EXPECT_CONTAINS(callback.strings, "tse");
    EXPECT_CONTAINS(callback.strings, "ets");
    EXPECT_CONTAINS(callback.strings, "est");
    EXPECT_CONTAINS(callback.strings, "set");
    EXPECT_CONTAINS(callback.strings, "ste");
}
