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

const int maxn = 5010;
char s[maxn];

bool valid_left[maxn];
int outstanding_left[maxn];
bool valid_right[maxn];
int outstanding_right[maxn];
int n;

struct dp_state_t {
  u16 left_state;
  u16 right_state;
};

dp_state_t dp[maxn][maxn][2];
bool done[maxn][maxn][2];

dp_state_t &proc(int l, int r, int f) {
  dp_state_t &st = dp[l][r][f];
  if (done[l][r][f]) return st;
  done[l][r][f] = true;

  if (l == r) {
    st.left_state = 0;
    st.right_state = 0;
    return st;
  }
  // if (l + 1 == r) {
  //  st.left_state = s[l] == ')';
  //  st.right_state = s[l] == '(';
  //  return st;
  //}

  if (f == 0) {
    const dp_state_t &stl = proc(l + 1, r, f);
    st = stl;
    if (s[l] == ')') {
      st.left_state++;
    } else {
      if (stl.left_state == 0) {
        st.right_state++;
      } else {
        st.left_state--;
      }
    }
  } else {
    const dp_state_t &stl = proc(l, r - 1, f);
    st = stl;
    if (s[r - 1] == ')') {
      st.left_state++;
    } else {
      if (stl.left_state == 0) {
        st.right_state++;
      } else {
        st.left_state--;
      }
    }
  }
  // printf("%d %d >> %d %d\n", l, r, st.left_state, st.right_state);

  return st;
}

bool check_valid() {
  int cnt = 0;
  REP (i, n) {
    cnt += (s[i] == '(') * 2 - 1;
    if (cnt < 0) return false;
  }
  return cnt == 0;
}

void check_ok(int l, int r) {
  FOR (i, l, l + (r - l) / 2)
    std::swap(s[i], s[r - 1 - i + l]);
  printf("%s\n", s);
  assert(check_valid());
}

bool solve() {
  n = strlen(s);
  if (n % 2 == 1) return false;
  memset(done, false, sizeof(done));
  auto &tall = proc(0, n, 0);
  if (tall.left_state == 0 && tall.right_state == 0) return true;
  FOR (r, 1, n + 1) {
    REP (l, r) {
      auto &left = proc(0, l, 0);
      auto mid = proc(l, r, 1);
      auto &right = proc(r, n, 0);
      std::swap(mid.left_state, mid.right_state);

      //printf("%d %d >> %d %d %d %d %d %d\n", l, r, mid.left_state,
      //       mid.right_state, left.left_state, right.right_state,
      //       left.right_state, right.left_state);
      if (left.left_state != 0) continue;
      if (right.right_state != 0) continue;
      if (mid.left_state > left.right_state) continue;
      if (mid.right_state > right.left_state) continue;
      if (mid.right_state + left.right_state !=
          mid.left_state + right.left_state)
        continue;
      if (0) {
        printf("%d %d xx %s\n", l, r, s);
        check_ok(l, r);
      }

      return true;
    }
  }
  return false;
}

std::string gen(int n) {
  std::string res(n, 0);
  int opened = 0;
  REP (i, n) {
    int rem = n - i;
    int v = rand() % 2;
    if (opened == rem)
      v = 0;
    else if (opened == 0)
      v = 1;
    res[i] = ")("[v];
    opened += 2 * v - 1;
  }
  return res;
}

std::string gen2(int n) {
  std::string res = gen(n);
  REP (i, 2) {
    int r = rand() % (n + 1);
    int l = rand() % (r + 1);
    FOR (i, l, l + (r-l)/2)
      std::swap(res[i], res[r - 1 - i + l]);
  }
  return res;
}

int main() {
  srand(0);
  if (0) {
    REP (ncheck, 100) {
      std::string tmp = gen(2 * ncheck + 100);
      memcpy(s, tmp.data(), tmp.size() + 1);
      assert(solve());

      tmp = gen2(2 * ncheck + 100);
      solve();
    }
    return 0;
  }

  scanf("%s", s);
  puts(solve() ? "possible" : "impossible");
}
