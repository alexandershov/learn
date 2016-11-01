#ifndef PEARLS_ANAGRAMS_H
#define PEARLS_ANAGRAMS_H

#include <string>

namespace ch2 {
    template<class callback_t>
    void for_each_permutation(std::string s, callback_t &callback, size_t start = 0) {
        if (start == s.size()) {
            callback(s);
            return;
        }
        for (size_t i = start; i < s.size(); i++) {
            std::swap(s[start], s[i]);
            for_each_permutation(s, callback, start + 1);
            std::swap(s[start], s[i]);
        }
    }
}

#endif //PEARLS_ANAGRAMS_H
