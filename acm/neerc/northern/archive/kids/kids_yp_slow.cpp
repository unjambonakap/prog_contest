 
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <algorithm>

using namespace std;

#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ )
#  define LL "%I64d"
#else
#  define LL "%lld"
#endif

const int minN = 4;
const int maxN = 5000;
const int maxX = 100000000;
const long long inf = (long long)1e18;

struct vec {
  int x, y;
  vec() {
  }
  vec( int _x, int _y ): x(_x), y(_y) {
  }
  vec operator - ( vec b ) {
    return vec(x - b.x, y - b.y);
  }
  long long operator ^ ( vec b ) {
    return (long long)x * b.y - (long long)y * b.x;
  }
};

int n;
vec p[maxN * 3];
long long be = -inf;
int bei1, bej1, bek1, bei2, bej2, bek2;

long long square( int i, int j, int k ) {
  return abs((p[j] - p[i]) ^ (p[k] - p[i]));
}

void relax( int i1, int j1, int k1, int i2, int j2, int k2 ) {
  long long t = square(i1, j1, k1) - square(i2, j2, k2);
  if (be < t) {
    be = t;
    bei1 = i1; bej1 = j1; bek1 = k1;
    bei2 = i2; bej2 = j2; bek2 = k2;
  }
}

int main() {
  assert(freopen("kids.in", "r", stdin));
  assert(freopen("kids.out", "w", stdout));

  assert(scanf("%d", &n) == 1);
  assert(minN <= n && n <= maxN);
  for (int i = 0; i < n; i++) {
    assert(scanf("%d%d", &p[i].x, &p[i].y) == 2);
    assert(-maxX <= p[i].x && p[i].x <= maxX);
    assert(-maxX <= p[i].y && p[i].y <= maxX);
  }
  for (int i = n; i < 3 * n; i++) {
    p[i] = p[i - n];
  }
  be = -inf;
  bei1 = -1, bej1 = -1, bek1 = -1;
  bei2 = -1, bej2 = -1, bek2 = -1;
  for (int i = 0; i < n; i++) {
    int pmi = 0;
    for (int j = 2, k = 0; j < n; j++) {
      if (square(i + j - 2, i + j - 1, i + j) < square(i + pmi, i + pmi + 1, i + pmi + 2)) {
        pmi = j - 2;
      }
      while (k < j || (k + 1 < n && square(i, i + j, i + k + 1) >=
        square(i, i + j, i + k))) {
        k++;
      }
//      fprintf(stderr, "i=%d j=%d k=%d\n", i + 1, (i + j) % n + 1, (i + k) % n + 1);
      relax(i, i + j, i + k, i + pmi, i + pmi + 1, i + pmi + 2);
      relax(i, i + j, i + k, i, i + 1, i + j);
      relax(i, i + j, i + k, i, i + j - 1, i + j);
    }
  }
  printf(LL "." LL "\n", be / 2, (be % 2) * 5);
  printf("%d %d %d\n%d %d %d\n", bei1 % n + 1, bej1 % n + 1, bek1 % n + 1, bei2 % n + 1, bej2 % n + 1, bek2 % n + 1);

  return 0;
}
