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
const int maxn = 66;
int n;
char a[maxn];
char b[maxn];
typedef std::vector<bool> vb;

ull solve2(vb a, bool left = true, bool right = true) {
  if (a.size() == 0) return left && right;
  int ca = a.back();
  int n = a.size();
  if (a == vb(n, 0)) return left && right;

  a.pop_back();
  if (ca == 0) return solve2(a, left, right);
  return (1ull << n) - solve2(a, true, !right);
}

ull solve(vb a, vb b) {
  return solve2(b) - solve2(a) - 1;
  if (a.size() == 0) return 0;
  if (a.back() == b.back()) {
    if (a.back() == 0) {
      a.pop_back();
      b.pop_back();
      return solve(a, b);
    } else {
      a.pop_back();
      b.pop_back();
      return solve(b, a);
    }
  } else {
    assert(a.back() == 0);
    int n = a.size();
    a.pop_back();
    b.pop_back();
    ull res = (1ull << n-1) - solve2(a, true, false) + solve2(b, true, false);
    return res;
  }
}

std::vector<vb> lst_gray(int n) {
  if (n == 0) return {{}};
  std::vector<vb> sub = lst_gray(n - 1);
  std::vector<vb> res;
  for (auto &x : sub) {
    vb cur = { 0 };
    cur.insert(cur.end(), ALL(x));
    res.push_back(cur);
  }

  std::reverse(ALL(sub));
  for (auto &x : sub) {
    vb cur = { 1 };
    cur.insert(cur.end(), ALL(x));
    res.push_back(cur);
  }
  return res;
}

int main() {
  if (0) {
    srand(0);
    REP (nstep, 10) {
      puts("");
      std::vector<vb> lst = lst_gray(5);
      for (auto &x : lst) out(x);
      assert(lst.size() >= 1);
      int ib = rand() % (lst.size()-1) + 1;
      int ia = rand() % ib;
      vb ta = lst[ia];
      vb tb =  lst[ib];
      std::reverse(ALL(ta));
      std::reverse(ALL(tb));

      int res = solve(ta, tb);
      int want = ib- ia - 1;
      printf(" >>> %d %d xx %d %d\n", ia, ib, res, want);
      printf("%d %d\n", solve2(ta), solve2(tb));
      out(ta);
      out(tb);
      assert(res == want);
    }
  }
  int n;
  scanf("%d", &n);
  scanf("%s %s", a, b);

  REP (i, n)
    a[i] -= '0', b[i] -= '0';
  vb va, vb;
  REP (i, n) {
    va.push_back(a[i]);
    vb.push_back(b[i]);
  }
  std::reverse(ALL(va));
  std::reverse(ALL(vb));

  ull res = solve(va, vb);
  printf("%llu\n", res);
  return 0;
}
