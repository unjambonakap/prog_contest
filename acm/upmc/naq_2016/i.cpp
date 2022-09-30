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

const int maxn = 20;
const int maxp = 98;
int tb[maxn][maxn];
const int maxnn = maxn * maxn;
int p;
int n, m;
int mat[maxnn][maxnn * 2];

inline int id(int a, int b) { return a * m + b; }
int inv[maxp];

int main() {
  scanf("%d%d%d", &n, &m, &p);
  REP (i, n)
    REP (j, m)
      scanf("%d", tb[i] + j), tb[i][j] %= p;
  memset(mat, 0, sizeof(mat));
  FOR (i, 1, p) {
    REP (j, p)
      if (i * j % p == 1) inv[i] = j;
  }

  int nn = n * m;
  REP (i, n) {
    REP (j, m) {
      REP (k, n)
        mat[id(i, j)][id(k, j)] = 1;
      REP (k, m)
        mat[id(i, j)][id(i, k)] = 1;
      mat[id(i, j)][id(i, j) + nn] = 1;
    }
  }

  int nc = nn * 2;
  int c = 0;
  std::vector<int> rmp;
  REP (i, nn) {
    if (c == nn) break;
    int pivot = -1;
    FOR (j, i, nn) {
      if (mat[j][c] != 0) {
        pivot = j;
        break;
      }
    }
    if (pivot == -1) {
      ++c;
      continue;
    }
    if (pivot != i) {
      REP (j, nc)
        std::swap(mat[i][j], mat[pivot][j]);
    }
    rmp.push_back(i);
    int mc = inv[mat[i][c]];
    REP (j, nc)
      mat[i][j] = mat[i][j] * mc % p;

    REP (k, nn) {
      if (k == i) continue;
      if (mat[k][c] == 0) continue;
      int mul = p - mat[k][c];
      FOR (j, c, nc) { mat[k][j] = (mat[k][j] + mul * mat[i][j]) % p; }
      assert(mat[k][c] == 0);
    }

    ++c;
  }
  //REP (i, nn) {
  //  REP (j, nc) { printf("%d ", mat[i][j]); }
  //  puts("");
  //}

  std::vector<int> target(nn, 0);
  std::vector<int> res(nn, 0);

  REP (pos, rmp.size()) {
    int pivot = rmp[pos];
    int v = (tb[pivot / m][pivot %m] - target[pivot])%p;
    if (v != 0) {
      REP (u, nn) {
        res[u] = (res[u] + v * mat[pivot][nn + u]) % p;
        target[u] = (target[u] + v * mat[pivot][u]) % p;
      }
    }
  }

  std::vector<pii> sol;
  REP (i, n) {
    REP (j, m) {
      if (target[id(i, j)] != tb[i][j]) goto fail;
      int want = (p - res[id(i, j)]) % p;
      REP (k, want)
        sol.emplace_back(i, j);
    }
  }
  printf("%d\n", sol.size());

  REP (a, sol.size()) {
    printf("%d", sol[a].first * m + sol[a].second + 1);
    printf("%c", " \n"[a == sol.size() - 1]);
  }
  return 0;
fail:;
  puts("-1");
  return 0;
}
