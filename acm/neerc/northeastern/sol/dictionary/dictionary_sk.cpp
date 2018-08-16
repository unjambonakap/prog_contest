/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Outcome: passes TL, but uses 800 MB of memory
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
#define next next239

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

int n, is[26];
char s[mLen + 1];
ll res;

const int maxV = maxN * mLen * mLen / 2; 

int root1 = 1, root2 = 2, vn = 3, next[maxV][26]; // 800 MB = 10 000 * 40 * 40 * 26 * 4 / 2
ll num[maxV];

void add( int v, const char *s )
{
  while (*s)
  {
    int &x = next[v][*s++ - 'a'];
    if (!x)
      assert((x = vn++) < maxV);
    v = x;
  }
  num[v] = 1;
}

void calc( int v )
{
  forn(i, 26)
    if (next[v][i])
      calc(next[v][i]), num[v] += num[next[v][i]];
}

void dfs( int v, int dep = 0, int last = 0 )
{
  res += (num[v] || (dep > 1 && is[last]));
  forn(i, 26)
    if (next[v][i])
      dfs(next[v][i], dep + 1, i);
    else if (dep > 0)
      res += num[next[root2][i]];
}

int main()
{
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));

  assert(scanf("%d", &n) == 1);
  assert(1 <= n && n <= maxN);
  forn(i, n)
  {
    assert(scanf("%s", s) == 1);
    int len = strlen(s);
    assert(1 <= len && len <= mLen);
    is[s[len - 1] - 'a'] = 1;
    add(root1, s);
    forn(i, len)
      add(root2, s + i);
  }

  calc(root2);
  dfs(root1);
  printf(I64 "\n", res);
  return 0;
}
