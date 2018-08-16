// O(n^3 log n) solution to contest.
// David Garcia Soriano.
#include <algorithm>
#include <cstdio>
#include <numeric>
#include <set>
#include <vector>
#include <queue>
using namespace std;

const int maxn = 80;
int ly, lx, n, sumx1[maxn], sumy1[maxn];

multiset<int, greater<int> > sumx, sumy;

void increase(multiset<int, greater<int> >& s, int x, int inc) {
  s.erase(s.find(x));
  s.insert(x + inc);
}

void decrease_greater(multiset<int, greater<int> >& s, int k) {
  multiset<int, greater<int> > t;
  for (multiset<int, greater<int> >::iterator it = s.begin(); ; ++it) {
    if (k-- == 0) { s.erase(s.begin(), it); break; }
    t.insert(*it - 1);
  }
  s.insert(t.begin(), t.end());
}

bool possible() {
  int a = 0, i = sumy.size() - 1;
  multiset<int, greater<int> >::iterator it = sumy.end(), it2 = sumx.begin();
  for (int k = 1; k <= n; ++k) {
    while (i >= 0 && *--it < k) --i;
    ++it;
    a += i + 1;
    a -= *(it2++);
    if (a < 0) return false;
  }
  return true;
}

int main() {
  bool first = true;
  while (scanf("%i%i", &ly, &lx), ly) {
    for (int i = 0; i < ly; ++i) scanf("%i", &sumy1[i]);
    for (int j = 0; j < lx; ++j) scanf("%i", &sumx1[j]);
    if (!first) puts(""); else first = false;

    n = max(lx, ly);
    fill(&sumy1[ly], &sumy1[n], 0);
    fill(&sumx1[lx], &sumx1[n], 0);
    sumx = multiset<int, greater<int> >(&sumx1[0], &sumx1[n]);
    sumy = multiset<int, greater<int> >(&sumy1[0], &sumy1[n]);

    if (accumulate(&sumx1[0], &sumx1[lx], 0) != accumulate(&sumy1[0], &sumy1[ly], 0) || !possible()) puts("Impossible");
    else
      for (int y = 0; y < ly; ++y) {
        for (int x = 0; x < lx; ++x) {
          sumx = multiset<int, greater<int> >(&sumx1[x + 1], &sumx1[n]);
          int nonzero = distance(sumx.begin(), sumx.upper_bound(1));

          int value = nonzero < sumy1[y] ? 1 : 0;
          if (value == 0 && sumy1[y] > 0) {
            decrease_greater(sumx, sumy1[y]);
            sumx.insert(&sumx1[0], &sumx1[x + 1]);
            sumy.erase(sumy.find(sumy1[y]));
            if (!possible()) value = 1;
            sumy.insert(sumy1[y]);
          }

          if (value == 1) {
            increase(sumy, sumy1[y], -1);
            --sumx1[x]; --sumy1[y];
          }
          putchar(value ? 'Y' : 'N');
        }
        puts("");
      }
  }
  return 0;
}
