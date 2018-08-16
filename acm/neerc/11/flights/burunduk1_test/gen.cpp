#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cmath>

#include <algorithm>

#include "random.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int N = 50000;
const int M = 20000;

int p[N], x[N], y[N], ind[N];

dbl sqr( dbl x ) { return x * x; }

int main( int argc, char *argv[] )
{
  initrand(239);

  int X = 50000;
  int P = X - (6 << 13);
  int Y = 6 * 6;
  dbl a = Y / sqr(X - P);

  const int V = 4;
  int X1 = X - (V << 13);
  int Y1 = 6 * 6 - V * V;
  assert(fabs(Y - a * sqr(X1 - X) - Y1) < 1e-4);
  fprintf(stderr, "answer is %d\n", Y1);

  p[N - 1] = P, x[N - 1] = X, y[N - 1] = Y;

  forn(i, N - 1)
  {
    int cx, cy, cp = -1;
    while (1)
    {
      cx = R(0, 50000), cy = R(Y1 + 1, 50);
      if (cx == X1)
        continue;
      double a = (cy - Y1) / sqr(cx - X1);
      assert(a > 0);
      dbl x0 = cx - sqrt(cy / a);
      assert(fabs(cy - a * sqr(cx - x0)) < 1e-4);
      cp = (int)ceil(x0);
      if (cp < 0)
        continue;
      assert(cp < cx);
      a = cy / sqr(cx - cp);
      dbl Y2 = cy - a * sqr(cx - X1);
      if (Y2 < Y1 - 3e-4) // 3e-4 > eps from statements
        break;
    }
    x[i] = cx, y[i] = cy, p[i] = cp;
    //double a = cy / sqr(cx - cp);
    //fprintf(stderr, "%d > %.20lf\n", Y1, (double)(cy - a * sqr(cx - X1)));
  }

  printf("%d\n", N);
  forn(i, N)
    ind[i] = i;
  randomShuffle(ind, ind + N);
  forn(j, N)
  {
    int i = ind[j];
    printf("%d %d %d\n", p[i], x[i], y[i]);
  }
  printf("%d\n", M);
  forn(i, M)
  {
    const int dt = 500;
    printf("%d %d %d %d\n", 1 + R(0, dt), N - R(0, dt), X1, X1);
  }
  return 0;
}
