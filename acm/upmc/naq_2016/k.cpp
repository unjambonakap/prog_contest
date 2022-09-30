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
int a1, b1, a2, b2, an, bn;

int main() {
  int tn;
  scanf("%d", &tn);
  REP (i, tn) {
    scanf("%d%d%d%d%d%d", &a1, &b1, &a2, &b2, &an, &bn);

    //int det = a1 * b2 - b1 * a2;
    //if (det != 0) {
    //  int n1 = (an * b2 - bn * a2) / det;
    //  int n2 = (a1 * bn - b1 * an) / det;
    //  if (a1 * n1 + a2 * n2 != an) goto fail;
    //  if (b1 * n1 + b2 * n2 != bn) goto fail;
    //  if (n1 < 0 || n2 < 0) goto fail;
    //  printf("%d %d\n", n1, n2);
    //  continue;
    //}
    if (1) {
      int nn1 = std::min(an / a1, bn / b1);
      int nn2 = std::min(an / a2, bn / b2);
      int cnt = 0;
      int n1, n2;
      FOR (i, 1, 10001) {
        int j = (an - a1 * i) / a2;
        if (j<= 0) continue;
        if (a1 * i + a2 * j == an && b1 * i + b2 * j == bn) {
          ++cnt;
          n1 = i;
          n2 = j;
          if (cnt == 2) break;
        }
      }
      if (cnt != 1)
        puts("?");
      else
        printf("%d %d\n", n1, n2);
      continue;
    }
  }
}