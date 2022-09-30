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

const int maxn = 111;
const int maxe = maxn * maxn / 2;

int tb[maxn];
int m;

std::vector<pii> edges[maxn];

std::priority_queue<pii, std::vector<pii>, std::greater<pii> > pq;
int dist[maxn];
int take[maxn];

pii solve(int s, int t) {
  memset(dist, 0x7f, sizeof(dist));
  memset(take, 0, sizeof(take));
  pq.push(MP(0, s));
  dist[s] = 0;
  take[s] = tb[s];

  while (!pq.empty()) {
    pii top = pq.top();
    pq.pop();
    int cur=  top.ND;
    if (cur == t){
      return MP(top.ST, take[t]);
    }

    if (dist[cur] != top.ST) continue;
    for (auto &edge : edges[cur]) {

      int nc = edge.second + top.ST;
      int to = edge.first;
      int nt = take[cur] + tb[to];
      if (dist[to] > nc) {
        dist[to] = nc;
        take[to] = nt;
        pq.push(MP(nc, to));
      } else if (dist[to] == nc) {
        take[to] = std::max(take[to], nt);
      }
    }
  }
  return MP(-1, -1);
}

int main() {
  int n;
  scanf("%d", &n);
  REP (i, n)
    scanf("%d", tb + i);
  scanf("%d", &m);

  REP (i, m) {
    int a, b, d;
    scanf("%d%d%d", &a, &b, &d);
    --a, --b;
    edges[a].emplace_back(b, d);
    edges[b].emplace_back(a, d);
  }

  pii res = solve(0, n - 1);
  if (res.first == -1) puts("impossible");
  else printf("%d %d\n", res.first, res.second);

  return 0;
}
