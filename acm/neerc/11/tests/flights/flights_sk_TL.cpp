/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

/* Template */

#include <cstdarg>
#include <ctime>
#include <cmath>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <functional>
#include <map>
#include <set>
#include <fstream>
#include <queue>

using namespace std;

#ifdef _WIN32
#  define I64 "%I64d"
#else             
#  define I64 "%Ld"
#endif

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define fornd(i, n) for (int i = (int)(n) - 1; i >= 0; i--)
#define forab(i, a, b) for (int i = (int)(a); i <= (int)(b); i++)
#define forabd(i, a, b) for (int i = (int)(b); i >= (int)(a); i--)
#define forit(i, a) for (__typeof((a).begin()) i = (a).begin(); i != (a).end(); i++)
#define sz(a) (int)(a).size()
#define all(a) (a).begin(), (a).end()
#define zero(a) memset(a, 0, sizeof(a))
#define fill(a, x) memset(a, x, sizeof(a))
#define pb push_back
#define mp make_pair

#define EOL(i, n) " \n"[i == (n) - 1]
#define LEN(a) (int)(sizeof(a) / sizeof(a[0]))
#define IS(a, i) (((a) >> (i)) & 1)
#define LAST(a) a[sz(a) - 1]

typedef unsigned int uint;
typedef double dbl;
typedef long long ll;
typedef unsigned long long ull;
typedef vector <int> vi;
typedef pair <int, int> pii;
typedef unsigned char byte;

inline dbl sqr(dbl x) { return x * x; }
template <class T> inline void relaxMin( T &a, T b ) { a = min(a, b); }
template <class T> inline void relaxMax( T &a, T b ) { a = max(a, b); }

string str( int i ) { char s[100]; sprintf(s, "%d", i); return string(s); }

template <class T> inline T sign( T x ) { return x > 0 ? 1 : (x < 0 ? -1 : 0); }
template <class T> inline T myAbs( T a ) { return a > 0 ? a : -a; }

#define DEBUG 1
void err( const char *fmt, ... )
{
  #if DEBUG
  va_list list;
  va_start(list, fmt);
  vfprintf(stderr, fmt, list);
  fflush(stderr);
  #endif
}

#define NAME "flights"

/* The main part */

const int maxN = 50000;
const int maxM = 20000;

int m, n, x[maxN], y[maxN], p[maxN];
dbl a[maxN];

int main()
{
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));

  assert(scanf("%d", &n) == 1);
  assert(1 <= n && n <= maxN);
  forn(i, n)
  {
    assert(scanf("%d%d%d", &p[i], &x[i], &y[i]) == 3);
    assert(0 <= p[i] && p[i] < x[i] && y[i] > 0 && x[i] <= (int)5e4 && y[i] <= 50);
    a[i] = y[i] / sqr(x[i] - p[i]);
    assert(a[i] > 0);
  }

  assert(scanf("%d", &m) == 1);
  assert(1 <= m && m <= maxM);
  while (m--)
  {
    int tl, tr, xl, xr;
    dbl res = 0.0;
    if (m % 1000 == 0)
      err("%d quries left\n", m);
    assert(scanf("%d%d%d%d", &tl, &tr, &xl, &xr) == 4), tl--, tr--;
    assert(0 <= tl && tl <= tr && tr < n && 0 <= xl && xl <= xr && xr <= (int)5e4);
    forab(t, tl, tr)
      if (xl <= x[t] && x[t] <= xr)
        res = max(res, (dbl)y[t]);
      else if (y[t] > res)
      {
        dbl X = xr < x[t] ? x[t] - xr : xl - x[t];
        res = max(res, y[t] - a[t] * X * X);
      }
    assert(res <= 50);
    printf("%.20lf\n", res);   
  }
  return 0;
}
