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

const int maxn = 1111111;
int w[2][maxn];
int n;
int vis[maxn];
int VISID=0;

bool checkit(int level) {
  ++VISID;
  REP (i, 2) {
    std::vector<int> tb;
    int last = -1;
    REP (j, n) {
      int v = w[i][j];
      if (v > level) {
        if (last != v && vis[v] == VISID) return false;
        vis[v] = VISID;
      last = v;
      }
    }
  }
  return true;
}

int main() {
  scanf("%d", &n);
  int mv = 0;
  std::set<int> levels;
  REP (i, 2)
    REP (j, n) {
      scanf("%d", w[i] + j);
      levels.insert(w[i][j]);
    }

  int level = 1;
  std::map<int,int> rmp;
  std::map<int,int> irmp;
  rmp[0] = 0;
  irmp[0] = 0;
  for (auto &x : levels){
    rmp[x] = level;
    irmp[level] = x;
    level++;
  }
  REP(i,2) REP(j,n) w[i][j] = rmp[w[i][j]];

  int T = 0;
  int H = *(--levels.end());
  while (T <= H) {
    int M = (T + H) / 2;
    if (checkit(M))
      H = M - 1;
    else
      T = M + 1;
  }

  printf("%d\n", irmp[T]);
  return 0;
}
