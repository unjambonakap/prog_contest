// Alternate solution to genetics.
// David Garcia Soriano.
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <set>
#include <string>
using namespace std;

bool samenucleotiddif(char a, char b) {
  return abs(a - b) == 32;
}

bool samenucleotid(char a, char b) {
  return a == b || samenucleotiddif(a, b);
}

string rewrite(const string& s, int pos) {
  int n = s.size();
  string t(s);
  rotate(&t[0], &t[pos], &t[n]);
  char map[256];
  for (int i = 'A'; i <= 'z'; ++i) map[i] = -1;

  char next = 'a';
  for (int i = 0; i < n; ++i) {
    if (map[t[i]] < 0) {
      map[t[i]] = next;
      map[t[i] ^ 32] = next ^ 32;
      ++next;
    }
    t[i] = map[t[i]];
  }
  return t;
}

struct State {
  int arms, legs, n;
  string s;

  State(int a, int l, const string& str) : arms(a), legs(l), n(str.size()), s(str + str) { simplify(); }

  void setstring(const string& t) {
    n = t.size();
    s = t + t;
  }

  void print() const {
    if (arms) {
      printf("%i arm", arms);
      if (arms > 1) puts("s"); else puts("");
    } else if (legs) {
      printf("%i leg", legs);
      if (legs > 1) puts("s"); else puts("");
    } else puts("none");
  }

  void simplify() {
    for (;;) {
      bool change = false;
      for (int i = 0; !change && i < n; ++i)  // first rule
        if (samenucleotiddif(s[i + 1], s[i])) {
          setstring(s.substr(i + 2, n - 2));
          change = true;
        }
      for (int i = 0; !change && i < n; ++i)  // second rule
        if (s[i + 1] == s[i]) {
          setstring(s.substr(i + 2, n - 2));
          ++arms;
          change = true;
        }
      for (int i = 0; !change && i < n; ++i)  // third rule
        if (samenucleotiddif(s[i], s[i + 2]) &&
            samenucleotiddif(s[i + 1], s[i + 3]) &&
            !samenucleotid(s[i], s[i + 1])) {
          setstring(s.substr(i + 4, n - 4));
          ++legs;
          change = true;
        }
      if (!change) break;
    }

    // Take the lexicographically largest variation
    string a = s.substr(0, n), best = rewrite(a, 0);
    for (int i = 1; i < n; ++i) {
      string t = rewrite(a, i);
      if (t > best) best = t;
    }

    setstring(best);
    if (arms && legs) {
      arms += 2 * legs;
      legs = 0;
    }
  }
};

string turn(const string& s, int i) {
  string ret = s.substr(i + 1);
  ret += s[i];
  ret += s.substr(0, i);
  return ret;
}

void inverse(string& a) {
  reverse(a.begin(), a.end());
  for (int i = 0; i < a.size(); ++i)
    a[i] ^= 32;
}

set<string> queued;

bool bt(const State& st) {
  int n = st.n;
  if (!n) {
    st.print();
    return true;
  }

  const string& s(st.s);
  for (int j = 0; j < n; ++j)
    for (int k = j + 1; k < n; ++k)
      if (samenucleotid(s[j], s[k])) {
        for (int m = j + 1; m <= k; ++m) {
          string a(s.substr(0, m)), b(s.substr(m, n - m));
          int p = k - m;
          if (s[j] == s[k]) {
            inverse(b);
            p = n - m - 1 - p;
            b[p] ^= 32;
          }

          string t = turn(a, j) + turn(b, p);
          State newst(st.arms, st.legs, t);
          t = newst.s.substr(0, newst.n);

          if (queued.find(t) == queued.end()) {
            queued.insert(t);
            if (bt(newst)) return true;
            else assert(false); // I think this never happens!
          }
        }
      }
  return false;
}

int main() {
  string str;
  while (cin >> str, str != "END") {
    State st(0, 0, str);
    queued.clear();
    queued.insert(st.s.substr(0, str.size()));
    bt(st);
  }
  return 0;
}
