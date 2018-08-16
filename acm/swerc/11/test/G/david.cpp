// O(n log n) solution to 'Nonnegative Partial Sums'.
// David Garcia Soriano.
#include <algorithm>
#include <cstdio>
#include <set>
using namespace std;

const int maxn = 1000000;

int v[2 * maxn], sum[2 * maxn + 1];

int main() {
  int n;
  while (scanf("%i", &n), n) {
    sum[0] = 0;
    for (int i = 0; i < 2 * n; ++i) {
      if (i < n) scanf("%i", &v[i]);
      else v[i] = v[i - n];
      sum[i + 1] = sum[i] + v[i];
    }

    int total = 0;
    multiset<int> s(&sum[1], &sum[n + 1]);
    for (int i = 0; i < n; ++i) {
      if (sum[i] <= *s.begin()) ++total;
      s.erase(s.find(sum[i + 1]));
      s.insert(sum[i + n + 1]);
    }
    printf("%i\n", total);
  }
}
