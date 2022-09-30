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
const int maxn = 111111;
int n;
vi e[maxn];
vi ie[maxn];
vi lst[2];
const int MAXC = 2 * maxn;

int cost[2][maxn];
int dist[maxn];

void compute_cost(const vi &l, int dist[maxn]) {

  std::queue<int> q;
  for (auto &x : l) {
    q.push(x);
    dist[x] = 0;
  }
  while (!q.empty()) {
    int a = q.front();
    q.pop();
    for (auto &x : ie[a]) {
      if (dist[x] == -1) {
        q.push(x);
        dist[x] = dist[a] + 1;
      }
    }
  }
}

int solve() {
  memset(cost, -1, sizeof(cost));
  compute_cost(lst[0], cost[0]);
  compute_cost(lst[1], cost[1]);
  int res = MAXC;

  std::queue<int> q;
  memset(dist, -1, sizeof(dist));
  q.push(0);
  dist[0] = 0;
  while (!q.empty()) {
    int a = q.front();
    q.pop();
    for (auto &x : e[a]) {
      if (dist[x] == -1) {
        q.push(x);
        dist[x] = dist[a] + 1;
      }
    }

    if (cost[0][a] != -1 && cost[1][a] != -1) {
      res = std::min(res, cost[0][a] + cost[1][a] + dist[a]);
    }
    for (auto &xa : e[a]) {
      if (cost[0][xa] == -1) continue;
      for (auto &xb : e[a]) {
        if (cost[1][xb] == -1) continue;
        res = std::min(res, dist[a] + 2 + cost[0][xa] + cost[1][xb]);
      }
    }
  }
  return res;
}

int main() {
  scanf("%d", &n);
  int nx[2];
  scanf("%d%d", nx, nx + 1);
  REP (j, 2) {
    REP (i, nx[j]) {
      int x;
      scanf("%d", &x);
      lst[j].push_back(x - 1);
    }
  }

  REP (i, n) {
    int m;
    scanf("%d", &m);
    REP (j, m) {
      int x;
      scanf("%d", &x);
      --x;
      e[i].push_back(x);
      ie[x].push_back(i);
    }
  }

  int res = solve();
  if (res == MAXC)
    puts("impossible");
  else
    printf("%d\n", res);
  return 0;
}
