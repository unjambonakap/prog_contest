/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Outcome: TL 11
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
#define hash hash239

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

template <class T> T inline sqr(T x) { return x * x; }
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

#define NAME "dictionary"

/* The main part */

const int mLen = 40;
const int maxN = 10000;
const int P = 239017;

int n, len[maxN];
char s[maxN][mLen + 1];
ll h[maxN][mLen + 1], deg[mLen + 1];

const int maxh = (int)1e7 + 19;

int res, cc;
char hu[maxh];
ull hash[maxh];

void clear() { cc++; }

int cnt1 = 0, size = 0; // statistic for debug

void add( ull h )
{
  int i = h % maxh;
  while (hu[i] == cc && hash[i] != h)
    if (++i == maxh)
      i = 0;
  if (hu[i] != cc)
    hu[i] = cc, hash[i] = h, res++, size++;
  cnt1++;
}

int main()
{
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));

  deg[0] = 1;
  forn(i, mLen)
    deg[i + 1] = deg[i] * P;
  
  assert(scanf("%d", &n) == 1);
  assert(1 <= n && n <= maxN);
  forn(i, n)
  {
    assert(scanf("%s", s[i]) == 1);
    len[i] = strlen(s[i]);
    assert(1 <= len[i] && len[i] <= mLen);
    h[i][0] = 0;
    forn(j, len[i])
      h[i][j + 1] = h[i][j] * P + s[i][j];
  }

  forab(l, 1, mLen * 2)
  {
    err("l = %d, cnt1 = %d, size = %d\n", l, cnt1, size), size = 0;
    clear();
    forn(i, n)
      if (len[i] == l)
        add(h[i][len[i]]);
    forn(i, n)
      forab(a, 1, len[i])
      {
        int b = l - a;
        if (1 <= b && b <= mLen)
          forn(j, n)
            if (b <= len[j])
              add(h[j][len[j]] + (h[i][a] - h[j][len[j] - b]) * deg[b]);
      }
  }
  printf("%d\n", res);
  return 0;
}
