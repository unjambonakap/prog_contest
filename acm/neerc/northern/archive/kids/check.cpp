#include "testlib.h"

#include <cstdlib>
#include <algorithm>

using namespace std;

#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ )
#  define LL "%I64d"
#else
#  define LL "%lld"
#endif

const int maxN = 5000;

int n, x[maxN], y[maxN];

bool under( int a, int b, int i, int j, int k ) {
  if (b < a) {
    b += n;
  }
  if (i < a) {
    i += n;
  }
  if (j < a) {
    j += n;
  }
  if (k < a) {
    k += n;
  }
  return i <= b && j <= b && k <= b;
}

bool intersect( int i1, int j1, int k1,
  int i2, int j2, int k2 ) {
  if (i1 > j1) {
    swap(i1, j1);
  }
  if (j1 > k1) {
    swap(j1, k1);
  }
  if (i1 > j1) {
    swap(i1, j1);
  }
  return !under(i1, j1, i2, j2, k2) &&
    !under(j1, k1, i2, j2, k2) &&
    !under(k1, i1, i2, j2, k2);
}

void readInput() {
  n = inf.readInt();
  for (int i = 0; i < n; i++) {
    x[i] = inf.readInt();
    y[i] = inf.readInt();
  }
}

long long sq( int i, int j, int k ) {
  long long x1 = x[j] - x[i], y1 = y[j] - y[i];
  long long x2 = x[k] - x[i], y2 = y[k] - y[i];
  return abs(x1 * y2 - x2 * y1);
}

long long readNum( InStream &in ) {
  string s = in.readToken("[0-9]*.[0-9]");
  long long res1, res2;
  if (sscanf(s.c_str(), LL "." LL, &res1, &res2) != 2) {
    quitf(_fail, "Can't read answer");
  }
  return res1 * 10 + res2;
}

long long checkAns( InStream &in, TResult err ) {
  long long res = readNum(in);
  int i1 = in.readInt(1, n) - 1;
  int j1 = in.readInt(1, n) - 1;
  int k1 = in.readInt(1, n) - 1;
  int i2 = in.readInt(1, n) - 1;
  int j2 = in.readInt(1, n) - 1;
  int k2 = in.readInt(1, n) - 1;
  if (i1 == j1 || i1 == k1 || j1 == k1 ||
    i2 == j2 || i2 == k2 || j2 == k2) {
    quitf(err, "Equal points detected: (%d %d %d) (%d %d %d)",
      i1 + 1, j1 + 1, k1 + 1, i2 + 1, j2 + 1, k2 + 1);
  }
  if (intersect(i1, j1, k1, i2, j2, k2)) {
    quitf(err, "Triangles (%d %d %d) and (%d %d %d) intersect",
      i1 + 1, j1 + 1, k1 + 1, i2 + 1, j2 + 1, k2 + 1);
  }
  long long realRes = sq(i1, j1, k1) - sq(i2, j2, k2);
  if (realRes * 10 != res * 2) {
    quitf(err, "Difference is wrong: promised " LL ", got " LL,
      res * 2, realRes * 10);
  }
  return res;
}

int main( int argc, char *argv[] ) {
  registerTestlibCmd(argc, argv);
  readInput();
  long long ja = checkAns(ans, _fail);
  long long pa = checkAns(ouf, _wa);
  if (ja < pa) {
    quitf(_fail, "Contestant found a better solution: " LL " instead of " LL,
      pa, ja);
  } else if (pa < ja) {
    quitf(_wa, "Jury has a better solution: " LL " instead of " LL,
      ja, pa);
  } else {
    quitf(_ok, LL, pa);
  }
  return 0;
}
