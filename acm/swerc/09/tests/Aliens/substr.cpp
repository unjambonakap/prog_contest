// Average O(n log n) solution to substr.
// David Garcia Soriano.
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

const int maxlen = 40000;
char str[maxlen + 2];
int n, mintimes, tablesize;

typedef unsigned long long ull;
ull mod = 288230376151711013ull;

ull stephash(ull hash, int letter) {
  return ((hash << 5) | letter) % mod;
}

ull hashfunc(const char* str, int l) {
  ull h = 0;
  while (l--) h = stephash(h, *str++ - 'a');
  return h;
}

typedef pair<ull, int> hash_entry;  // hash code, times
vector<hash_entry> table[maxlen + 1];

// Insert a string in the table and return the number
// of times it (or rather, its hash code) has appeared so far.
int insert(ull hash) {
  int pos = hash % tablesize;
  for (int i = 0; i < table[pos].size(); ++i)
    if (table[pos][i].first == hash)
      return ++table[pos][i].second;
  table[pos].push_back(make_pair(hash, 1));
  return 1;
}

bool possible(int len, int& best) {
  if (len > n) return false;

  tablesize = max((n - len + 1) / 2, 100);
  for (int i = 0; i < tablesize; ++i) table[i].clear();

  // Compute what one needs to add to get the hash of s.substr(1)
  // from that of s.
  ull add[26];
  ull pot32 = 1;
  for (int i = 0; i < len - 1; ++i) pot32 = (pot32 << 5) % mod;
  for (int i = 0; i < 26; ++i) {
    add[i] = (pot32 * i) % mod;
    add[i] = (mod - add[i]) % mod;
  }

  ull hash = hashfunc(str, len - 1);
  int bestindex = -1;
  for (int i = 0; i + len <= n; ++i) {
    if (i) hash = (hash + add[str[i - 1] - 'a']) % mod;
    hash = stephash(hash, str[i + len - 1] - 'a');
    int times = insert(hash);
    if (times >= mintimes)
      bestindex = i;
  }
  best = bestindex;
  return bestindex >= 0;
}

int main() {
  while (scanf("%i\n", &mintimes), mintimes) {
    gets(str);
    n = strlen(str);

    int best;
    if (!possible(1, best))
      puts("none");
    else {
      int a = 1, b = n + 1;
      while (b - a != 1) {
        int m = (a + b) / 2;
        if (possible(m, best))
          a = m;
        else
          b = m;
      }
      possible(a, best); // compute the rightmost solution.
      printf("%i %i\n", a, best);
    }
  }
  return 0;
}
