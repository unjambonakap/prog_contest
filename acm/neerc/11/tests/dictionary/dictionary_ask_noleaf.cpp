#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>

#define PROBLEM "dictionary"

#define A 'a'
#define Z 'z'
#define SIZE Z - A + 1

struct Trie;
typedef Trie* PTrie;
struct Trie {
    PTrie next_[SIZE];
    bool is_word_;

    Trie(): next_({0}), is_word_(false) {}
    ~Trie() { for (auto t: next_) delete t; }

    PTrie& next(char ch) { return next_[ch - A]; }

    PTrie add(const char *p) {
        PTrie &t = next(*p);
        if (!t) t = new Trie;
        return p[1] ? t->add(p + 1) : t;
    }

    template <typename Func> void dfs(Func visitor, size_t depth = 0) {
        for (auto &t: next_)
            if (t) {
                visitor(&t - next_ + A, t, depth);
                t->dfs(visitor, depth + 1);
            }
    }
};

int main() {
    freopen(PROBLEM ".in", "r", stdin);
    freopen(PROBLEM ".out", "w", stdout);

    Trie prefixes, suffixes;

    size_t n;
    std::cin >> n;
    while (n--) {
        std::string s;
        std::cin >> s;
        prefixes.add(s.c_str())->is_word_ = true;
        std::reverse(s.begin(), s.end());
        suffixes.add(s.c_str());
    }

    size_t suffix_counts[SIZE] = {0};
    suffixes.dfs([&](char ch, ...) { ++suffix_counts[ch - A]; });

    unsigned long long result = 0;

    prefixes.dfs([&](char ch, PTrie t, size_t d) {
        if (t->is_word_ || (d > 0 && suffixes.next(ch)))
            ++result;
        for (size_t i = 0; i < SIZE; ++i)
            if (!t->next_[i])
                result += suffix_counts[i];
    });
    std::cout << result;
    return 0;
}
