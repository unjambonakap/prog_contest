// O(n^4 log n) solution to contest.
// David Garcia Soriano.
#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

// O(n^2 log n)
bool possible(int pos, vector<int> sumx, vector<int> sumy) {
  int ly = sumy.size(), lx = sumx.size();
  int i = pos / lx, j = pos % lx;
  for (; i < ly; ++i) {
    typedef pair<int, int> pii;
    vector<pii> v;
    for (int k = j; k < lx; ++k) if (sumx[k] > 0)
      v.push_back(pii(sumx[k], k));
    sort(v.begin(), v.end(), greater<pii>());
    for (int k = 0; sumy[i] > 0 && k < v.size(); ++k) {
      --sumx[v[k].second];
      --sumy[i];
    }
    if (sumy[i]) return false;
    j = 0;
  }
  for (int k = 0; k < lx; ++k) if (sumx[k]) return false;
  return true;
}

int main() {
  int ly, lx;
  bool first = true;
  while (scanf("%i%i", &ly, &lx), ly) {
    vector<int> sumx(lx), sumy(ly);
    for (int i = 0; i < ly; ++i) scanf("%i", &sumy[i]);
    for (int j = 0; j < lx; ++j) scanf("%i", &sumx[j]);
    if (!first) puts(""); else first = false;

    if (!possible(0, sumx, sumy)) puts("Impossible");
    else {
      for (int n = 0; n < ly * lx; ++n) {
        if (!possible(n + 1, sumx, sumy)) {
          int y = n / lx, x = n % lx;
          --sumy[y]; --sumx[x];
          putchar('Y');
        } else putchar('N');
        if (n % lx == lx - 1) puts("");
      }
    }
  }
  return 0;
}
