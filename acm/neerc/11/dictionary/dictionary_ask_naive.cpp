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

    std::set<std::string> approved;
    approved.insert(a.begin(), a.end());
    for (auto s1: a)
        for (size_t i = 0; i < s1.length(); ++i)
            for (auto s2: a)
                for (size_t j = 0; j < s2.length(); ++j)
                    //std::cout << s1->substr(0, i) << "+" << s2->substr(j) << "\n";
                    approved.insert(s1.substr(0, i + 1) + s2.substr(j));
    std::cout << approved.size();
    return 0;
}
