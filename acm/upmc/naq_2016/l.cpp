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

const int n = 7;
int px[n + 1];
int py[n + 1];
int px0[n + 1];
int py0[n + 1];
double p_target;
int perm[n];

int cross(int a, int b, int c) {
  int x1 = px[b] - px[a];
  int x2 = px[c] - px[a];
  int y1 = py[b] - py[a];
  int y2 = py[c] - py[a];
  return x1 * y2 - x2 * y1;
}

bool line_cross(int a, int b) {
  return 1ll * cross(a, a + 1, b) * cross(a, a + 1, b + 1) <= 0 &&
         1ll * cross(b, b + 1, a) * cross(b, b + 1, a + 1) <= 0;
}

bool checkit() {
  REP (i, n + 1)
    px[i] = px0[perm[i]];
  REP (i, n + 1)
    py[i] = py0[perm[i]];
  px[n] = px[0];
  py[n] = py[0];

  REP (i, n) {
    FOR (d, 2, n - 1) {
      int j = (i + d) % n;
      if (line_cross(i, j)) {
        // printf("Crossing >> %d %d %d %d, %d %d %d %d\n", px[i], py[i],
        // px[i+1], py[i+1], px[j], py[j], px[j+1], py[j+1]);
        return false;
      }
    }
  }
  int area = 0;
  REP (i, n) { area += px[i] * py[i + 1] - px[i + 1] * py[i]; }
  area /= 2;
  double ratio = std::abs(area) / 4e6;
  double prob = ratio * ratio * ratio;
  return std::abs(p_target - prob) < 1e-4;
}

int main() {
  int tn;
  scanf("%d", &tn);
  REP (ti, tn) {
    REP (i, n) {
      double x, y;
      scanf("%lf%lf", &x, &y);
      px0[i] = x * 1000+0.5;
      py0[i] = y * 1000+0.5;
    }
    px0[n] = px0[0];
    py0[n] = py0[0];

    scanf("%lf", &p_target);
    REP (i, n)
      perm[i] = i;
    bool debug = false;
    if (debug) {
      std::vector<int> force = { 0, 1, 2, 6, 4, 5, 3 };
      REP (i, n)
        perm[i] = force[i];
    }
    do {
      if (checkit()) {
        REP (i, n)
          printf("%d%c", perm[i] + 1, " \n"[i == n - 1]);
        break;
      }
      if (debug) break;
    } while (std::next_permutation(perm, perm + 8));
  }
  return 0;
}
