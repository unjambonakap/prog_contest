// O(log(numcalls) * (numqueries + numcalls)) solution to telephones.
// David Garcia Soriano.
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

int main() {
  int numcalls, numqueries;
  while (scanf("%i%i", &numcalls, &numqueries), numcalls) {
    if (!numcalls) break;

    vector<int> start, end;
    for (int i = 0; i < numcalls; ++i) {
      int a, b, s, e;
      scanf("%i%i%i%i", &a, &b, &s, &e);
      e += s;      // [e, s)
      start.push_back(s);
      end.push_back(e);
    }
    sort(start.begin(), start.end());
    sort(end.begin(), end.end());

    while (numqueries--) {
      int a, b;
      scanf("%i%i", &a, &b); // [a, b)
      b += a;
      int // No. of calls with start >= b
          i = start.end() - lower_bound(start.begin(), start.end(), b),
          // No. of calls with end <= a
          j = upper_bound(end.begin(), end.end(), a) - end.begin();
      int ret = numcalls - (i + j);  // no call is discounted twice.
      printf("%i\n", ret);
    }
  }
  return 0;
}
