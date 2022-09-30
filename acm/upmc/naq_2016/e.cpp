#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
//#include <ext/hash_map>
#include <fstream>
#include <unordered_map>
#include <unordered_set>

// clang-format off
using namespace std;
using namespace __gnu_cxx;



#define REP(i,n) for(int i = 0; i < int(n); ++i)
#define REPV(i, n) for (int i = (n) - 1; (int)i >= 0; --i)
#define FOR(i, a, b) for(int i = (int)(a); i < (int)(b); ++i)

#define FE(i,t) for (__typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (__typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

#define two(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()


#define pb push_back
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef signed long long s64;
typedef unsigned long long u64;

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n==0)?0:1+count_bit(n&(n-1));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

// clang-format on

const int maxn = 88;
int tb[maxn][maxn];
int n;
char s[2 * maxn];
int walls[maxn][maxn];
#define HASB(x, b) ((x) >> (b)&1)
int vx[] = { 0, 0, -1, 1 };
int vy[] = { -1, 1, 0, 0 };

const int maxm = maxn * maxn;
std::vector<int> edges[maxm];
int peer[maxm];
int VISID;
int vis[maxm];

bool dfs(int a) {
  if (vis[a] == VISID) return false;
  vis[a] = VISID;
  for (auto &e : edges[a]) {
    if (peer[e] == -1 || dfs(peer[e])) {
      peer[e] = a;
      peer[a] = e;
      return true;
    }
  }
  return false;
}

int max_match() {
  int res = 0;
  memset(vis, 0, sizeof(vis));
  memset(peer, -1, sizeof(peer));
  VISID = 0;
  REP (i, n)
    REP (j, n) {
      ++VISID;
      res += dfs(i * n + j);
    }

  REP (i, n) {
    REP (j, n)
      if (peer[i * n + j] == -1) ++res;
  }
  return res;
}

bool is_in(int i, int j) { return i >= 0 && j >= 0 && i < n && j < n; }

bool maybe_set(int i, int j, int b) {
  int ni = i + vy[b];
  int nj = j + vx[b];

  if ((!is_in(ni, nj) || tb[ni][nj] < 3) && tb[i][j] < 3 &&
      !HASB(walls[i][j], b)) {

    ++tb[i][j];
    walls[i][j] |= 1 << b;
    if (is_in(ni, nj)) {
      ++tb[ni][nj];
      walls[ni][nj] |= 1 << (b ^ 1);
    }
    return true;
  }
  return false;
}

void add_row(int i) {
  REP (j, n) {
    int has = s[2 * j + 1] == '-';
    if (has) maybe_set(i, j, 0);
  }
}

void add_col(int i) {
  REP (j, n + 1) {
    int has = s[2 * j] == '|';

    if (has) maybe_set(i, j, 2);
  }
}

int solve() {
  int res = 2 * n * (n + 1);

  REP (i, n) {
    res += maybe_set(i, 0, 2);
    res += maybe_set(0, i, 0);
    res += maybe_set(i, n - 1, 3);
    res += maybe_set(n - 1, i, 1);
  }

  REP (i, n) {
    REP (j, n) {
      REP (k, 4) {
        int ni, nj;
        ni = i + vy[k];
        nj = j + vx[k];
        int i1 = i * n + j;
        int i2 = ni * n + nj;

        if (walls[i][j] >> k & 1) {
          if (!is_in(ni, nj) || i1 < i2) {
            --res;
          }
        } else if (is_in(ni, nj) && (i + j & 1))
          edges[i1].push_back(i2);
      }
    }
  }
  int tmp = max_match();
  return res - tmp;
}

void disp_row(int i) {
  REP (j, n + 1) {
    s[2 * j] = '*';
    s[2 * j + 1] = (walls[i][j] >> 0 & 1 ? '-' : '.');
  }
  s[2 * n] = '*';
  s[2 * n + 1] = 0;
  printf("%s\n", s);
}

void disp_col(int i) {
  REP (j, n + 1) {
    s[2 * j] = (walls[i][j] >> 2 & 1 ? '|' : '.');
    s[2 * j + 1] = '.';
  }
  s[2 * n + 1] = 0;
  printf("%s\n", s);
}

void disp() {
  puts("");
  REP (i, n) {
    disp_row(i);
    disp_col(i);
  }
  disp_row(n);
}

int main() {
  scanf("%d", &n);
  --n;

  memset(tb, 0, sizeof(tb));
  memset(walls, 0, sizeof(walls));
  REP (i, n) {
    scanf("%s", s);
    add_row(i);
    scanf("%s", s);
    add_col(i);
  }
  scanf("%s", s);
  add_row(n);

  // disp();
  int res = solve();
  if (0) disp();
  printf("%d\n", res + 1);
  return 0;
}
