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
const int maxv = 101001;
int t1[maxv];
int t2[maxv];

const int maxn = 111;
int v1[maxn];
int v2[maxn];
int n1, n2;

int main() {
  scanf("%d", &n1);
  REP (i, n1)
    scanf("%d", v1 + i);
  scanf("%d", &n2);
  REP (i, n2)
    scanf("%d", v2 + i);
  memset(t1, 0x1, sizeof(t1));
  memset(t2, 0x1, sizeof(t2));
  t1[0] = 0;
  t2[0] = 0;

  REP (i, n1) {
    REPV (j, maxv-1000)
      if (t1[j] < maxn) t1[j + v1[i]] = std::min(t1[j] + 1, t1[j + v1[i]]);
  }

  REP (i, n2) {
    REPV (j, maxv-1000)
      if (t2[j] < maxn) t2[j + v2[i]] = std::min(t2[j] + 1, t2[j + v2[i]]);
  }
  int best = 2 * maxn;
  FOR (j, 1, maxv) {

    best = std::min(best, t1[j] + t2[j]);
  }
  if (best == 2 * maxn)
    puts("impossible");
  else
    printf("%d\n", best);
}
