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
typedef std::pair<int,int> pii;
typedef std::vector<int> vi;
typedef std::vector<std::string> vs;
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
template<class T> void out(T t[], int n){REP(i, n)std::cout<<t[i]<<" "; std::cout<<std::endl;}
template<class T> void out(std::vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) std::cout<<t[i]<<" "; std::cout<<std::endl;}
inline int count_bit(int n){return (n==0)?0:1+count_bit(n&(n-1));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(std::string s){int a; std::istringstream(s)>>a; return a;}
std::string toStr(int a){std::ostringstream os; os<<a; return os.str();}

// clang-format on

const int maxn = 2 * 33 * 33;
const int maxq = 33;
const int maxs = 111;
const int maxe = 10 * maxn;
int S, T;
int n, q, s;
int s_to_q[maxs];
int q_cap[maxq];
int qt[maxq];

int to[maxe];
int from[maxe];
int prev[maxe];
int cap[maxe];
int used[maxe];
int last[maxn];
int vis[maxn];
int ne;
int VISID;

int id(int round, int qi, bool after) {
  return (2 * round + after) * (q + 1) + qi;
}

void adde(int a, int b, int c, bool first = true) {
  int ei = ne++;
  assert(ei < maxe);
  to[ei] = b;
  from[ei] = a;
  cap[ei] = c;
  used[ei] = 0;
  prev[ei] = last[a];
  last[a] = ei;
  if (first) adde(b, a, 0, false);
}

int augment(int v, int push) {
  if (v == T) {
    return push;
  }

  if (vis[v] == VISID) return 0;
  vis[v] = VISID;

  for (int e = last[v]; e != -1; e = prev[e]) {
    if (used[e] == cap[e]) continue;
    int res = augment(to[e], std::min(push, cap[e] - used[e]));
    used[e] += res;
    used[e ^ 1] -= res;
    if (res != 0) return res;
  }
  return 0;
}

int max_flow(int S, int T) {
  int res = 0;
  memset(vis, 0, sizeof(vis));
  VISID = 0;
  while (true) {
    VISID += 1;
    int dv = augment(S, 1e9);
    if (dv == 0) break;
    res += dv;
  }
  return res;
}

int main() {
  memset(last, -1, sizeof(last));
  memset(prev, -1, sizeof(prev));

  scanf("%d%d%d", &n, &q, &s);
  REP (i, s)
    scanf("%d", s_to_q + i), --s_to_q[i];
  REP (i, q)
    scanf("%d", q_cap + i);
  S = id(n + 1, 0, false);
  T = S + 1;
  int TOT = 0;
  // maxe = n * (q + q + q +
  REP (i, n) {
    int D;
    scanf("%d", &D);
    memset(qt, 0, sizeof(qt));
    REP (j, s) {
      int a;
      scanf("%d", &a);
      TOT += a;
      qt[s_to_q[j]] += a;
    }

    REP (j, q) // incoming data
      adde(S, id(i, j, false), qt[j]);
    if (i != 0) REP (j, q) // copy remaining data from previous period
        adde(id(i - 1, j, true), id(i, j, false), q_cap[j]);

    REP (j, q) // split transmission - downlink steps
      adde(id(i, j, false), id(i, j, true), q_cap[j]);

    REP (j, q) // send by downlink
      adde(id(i, j, true), id(i, q, false), q_cap[j]);
    adde(id(i, q, false), T, D);
  }
  // REP (i, q)
  //  adde(id(n - 1, i, true), id(n, i, false), q_cap[i]),
  //    adde(id(n, i, false), T, q_cap[i]);

  int res = max_flow(S, T);
  puts(res == TOT ? "possible" : "impossible");
  return 0;
}
