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
const int maxn = 44;
const int maxm = 444;
int n, m;
char tb[maxn][maxm];
char vals[maxn][maxm];
int dp[maxn][maxn][maxm][11];
const int inf = 1e9;
bool ENUM = false;

int solve(int a, int b, int pos, int v, bool force = false) {
  if (pos == m) return 0;
  if (a == b) return 0;
  if (v == 10) return inf;
  int &r = dp[a][b][pos][v];
  int best = r;
  if (!force && r != -1) return r;
  r = solve(a, b, pos, v + 1);

  if (ENUM && r == best) {
    solve(a, b, pos, v + 1, true);
    return r;
  }

  int cnt = 0;
  FOR (i, a, b) {
    cnt += tb[i][pos] != v;
    vals[i][pos] = v;
    r = std::min(r, cnt + solve(a, i + 1, pos + 1, 0) +
                      solve(i + 1, b, pos, v + 1));
    if (ENUM && r == best) {
      solve(a, i + 1, pos + 1, 0, true);
      solve(i + 1, b, pos, v + 1, true);
      return r;
    }
  }

  return r;
}

int main() {
  scanf("%d %d", &n, &m);
  REP (i, n) {
    scanf("%s", tb + i);
    REP (j, m)
      tb[i][j] -= '0';
  }
  memset(dp, -1, sizeof(dp));
  int res = solve(0, n, 0, 0);
  ENUM = true;
  solve(0, n, 0, 0, true);
  REP (i, n) {
    vals[i][m] = 0;
    REP (j, m)
      vals[i][j] += '0';
    printf("%s\n", vals[i]);
  }
  return 0;
}
