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
template<class T> void out(const std::set<T>& t){for (auto &x : t) cout << x << " "; cout << endl;}
inline int count_bit(int n){return (n==0)?0:1+count_bit(n&(n-1));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

// clang-format on

const int maxn = 111111;
const int maxm = 1111111;
vi edges[maxn];
int n, m;

int VISID;
int vis[maxn];
std::vector<int> stack;
std::set<int> cycles[maxn];

int dp[maxn];
s64 group[maxn];
int cntx;
s64 open_id;

s64 dfs(int a) {
  if (vis[a] == VISID) {
    return group[a];
  }
  cntx += 1;

  group[a] = open_id++;
  vis[a] = VISID;
  stack.push_back(a);

  s64 lnk = group[a];
  for (auto &e : edges[a]) {
    lnk = std::min(lnk, dfs(e));
  }

  if (lnk == group[a]) {
    while (stack.back() != a) {
      int v = stack.back();
      cycles[a].insert(v);
      group[v] = maxn;
      stack.pop_back();
    }
    cycles[a].insert(a);
    for (auto &x : cycles[a]) {
      if (x != a) cycles[x] = cycles[a];
    }
    stack.pop_back();
    group[a] = maxn;
  }
  return lnk;
}

int rec(int a);

int rec2(int a, std::set<int> &cur, const std::set<int> &st) {
  if (cur.count(a)) return 0;
  cur.insert(a);

  int res = 0;
  for (auto &e : edges[a]) {
    if (st.count(e))
      res = std::max(res, rec2(e, cur, st));
    else
      res = std::max(res, rec(e));
  }
  cur.erase(a);
  return res + 1;
}

int rec(int a) {
  int &r = dp[a];
  if (r != -1) return r;
  r = 0;
  std::set<int> c = cycles[a];
  std::set<int> x;
  r = rec2(a, x, c);

  return r;
}

int solve() {
  memset(vis, 0, sizeof(vis));
  VISID = 0;
  ++VISID;
  cntx = 0;
  REP (i, n) {
    if (vis[i] == VISID) continue;
    stack.clear();
    open_id -= 2 * n;
    dfs(i);
    assert(stack.size() == 0);
  }

  memset(dp, -1, sizeof(dp));
  int res = 0;
  REP (i, n) { res = std::max(res, rec(i)); }
  return res;
}

void gen() {
  n = 11;
  REP (nstep, 100) {
    REP (i, n)
      edges[i].clear();
    m = rand() % (n * n);
    std::set<pii> seen;

    REP (i, m) {
      while (true) {
        int a = rand() % n;
        int b = rand() % n;
        if (seen.count(MP(a, b))) continue;
        seen.emplace(a, b);
        edges[a].push_back(b);
        break;
      }
    }

    std::vector<int> perm;
    REP (i, n)
      perm.push_back(i);
    int ans = 0;
    do {
      std::set<int> vis;
      int cur = 1;
      vis.insert(perm[0]);
      REP (i, n - 1) {
        if (vis.count(perm[i + 1])) break;
        if (!seen.count(MP(perm[i], perm[i + 1]))) break;
        vis.insert(perm[i + 1]);
        ++cur;
      }
      ans = std::max(ans, cur);
    } while (std::next_permutation(ALL(perm)));
    int res = solve();
    assert(ans == res);
  }
}

int main() {
  if (0) {
    gen();
    return 0;
  }

  scanf("%d %d", &n, &m);
  REP (i, m) {
    int a, b;
    scanf("%d%d", &a, &b);
    edges[a - 1].push_back(b - 1);
  }
  int res = solve();
  printf("%d\n", res);
  return 0;
}
