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

const int maxN = 32;
const int maxn = maxN * (maxN + 1) / 2;
double vals[maxn];

double mat[maxn][maxn * 2];
int N;
int n;
double tsf[maxn];

inline int id(int a, int b) { return a * (a + 1) / 2 + b; }

int main() {
  scanf("%d", &N);
  int ns = N * (N + 1) / 2;
  REP (i, ns)
    scanf("%lf", vals + i);
  memset(mat, 0, sizeof(mat));
  REP (i, N) {
    REP (j, i + 1) {
      double p[5];
      scanf("%lf%lf%lf%lf%lf", p, p + 1, p + 2, p + 3, p + 4);
      int vy[] = { -1, 0, 0, 1, 0 };
      int vx[] = { -1, -1, 1, 1, 0 };
      int start = id(i, j);
      REP (k, 4) {
        int nx = i + vx[k];
        int ny = j + vy[k];
        if (nx < 0 || ny < 0 || nx == N || ny > nx){
          assert(p[k] == 0);
          continue;
        }

        mat[start][id(nx, ny)] = p[k];
      }
      tsf[start] = p[4];
    }
  }

  n = ns;

  REP (i, n)
    REP (j, n)
      mat[i][j] = (i == j) - mat[i][j];
  int nc = 2 * n;
  REP (i, n)
    mat[i][i + n] = 1;

  //REP (i, n) { out(mat[i], nc); }
  //puts("");

  REP (i, n) {
    int pivot = i;
    FOR (j, i + 1, n) {
      if (std::abs(mat[j][i]) > std::abs(mat[pivot][i])) pivot = j;
    }
    FOR (j, i, nc)
      std::swap(mat[i][j], mat[pivot][j]);

    double tmp = mat[i][i];
    FOR (j, i, nc)
      mat[i][j] /= tmp;
    REP (j, n) {
      if (j == i) continue;
      double mul = -mat[j][i];
      FOR (k, i, nc) { mat[j][k] = mat[j][k] + mat[i][k] * mul; }
    }
  }
  //REP (i, n) { out(mat[i], nc); }
  //out(tsf, ns);
  //out(vals, ns);


  double res = 0;
  REP (i, ns)
    res += vals[i] * mat[0][n+i] * tsf[i];
  printf("%lf\n", res);

  return 0;
}
