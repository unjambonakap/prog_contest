#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <set>

#define PROBLEM "dictionary"

int main() {
    freopen(PROBLEM ".in", "r", stdin);
    freopen(PROBLEM ".out", "w", stdout);
    int n;
    std::cin >> n;
    std::vector<std::string> a;
    a.resize(n);
    for (auto &s: a) std::cin >> s;

    std::set<std::string> approved, prefixes, suffixes;
    approved.insert(a.begin(), a.end());
    for (auto s1: a)
        for (size_t i = 0; i < s1.length(); ++i) {
            prefixes.insert(s1.substr(0, i + 1));
            suffixes.insert(s1.substr(i));
        }

    for (auto s1: prefixes)
        for (auto s2: suffixes)
            approved.insert(s1 + s2);
    std::cout << prefixes.size() << " " << suffixes.size() << std::endl;
    std::cout << approved.size();
    return 0;
}
