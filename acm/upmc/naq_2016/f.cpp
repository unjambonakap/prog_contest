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
const int max_enum = 5000;
const int maxn = 20;
u64 d, d0;
int digits[maxn];
std::vector<int> da, db;
int n;

std::vector<std::pair<u64, u64> > res;
std::set<int> banned;
std::vector<int> allowed;
bool STOP_ENUM = false;

struct State {
  int used_a = 0;
  int used_b = 0;
  bool need_carry = false;
  bool started_a = false;
  bool first = true;

  bool operator<(const State &state) const {
    if (used_a != state.used_a) return used_a < state.used_a;
    if (used_b != state.used_b) return used_b < state.used_b;
    return 4 * first + 2 * need_carry + started_a <
           4 * state.first + 2 * state.need_carry + state.started_a;
  }
};

u64 getv(const std::vector<int> &tb) {
  u64 r = 0;
  for (auto &x : tb) r = r * 10 + x;
  return r;
}

std::map<State, u64> dp[maxn];

u64 go(int pos, const State &s) {
  if (pos == -1) {
    if (s.need_carry) return 0;
    if (!STOP_ENUM) {
      u64 va = getv(da);
      u64 vb = getv(db);
      assert(va + vb == d0);
      res.emplace_back(va, vb);
    }
    STOP_ENUM = res.size() == max_enum;
    return 1;
  }
  u64 *rv = nullptr;
  auto it = dp[pos].emplace(s, 0);
  if (STOP_ENUM && !it.second) return it.first->second;
  rv = &it.first->second;
  u64 r = 0;

  if (!s.started_a) {
    REPV (ib, allowed.size()) {
      int vb = allowed[ib];
      if (vb==0 && s.first) continue;
      int target = s.need_carry * 10 + digits[pos];
      int have = vb;
      int ncarry = target - have;
      if (ncarry != 0 && ncarry != 1) continue;
      db.push_back(vb);
      r += go(pos - 1, State{ 0, s.used_b | 1 << ib, ncarry, false, false });
      db.pop_back();
    }
  }

  REP (ia, allowed.size()) {
    if (s.used_b >> ia & 1) continue;
    int va = allowed[ia];
    if (va == 0 && !s.started_a) continue;
    da.push_back(va);

    REPV (ib, allowed.size()) {
      int vb = allowed[ib];
      if (ia == ib) continue;
      if (s.used_a >> ib & 1) continue;
      if (vb == 0 && pos == n - 1) continue;
      if (s.first && va > vb) continue;

      int target = s.need_carry * 10 + digits[pos];
      State ns = s;
      ns.started_a = true;
      ns.used_a |= 1 << ia;
      ns.used_b |= 1 << ib;
      ns.first = false;
      int have = va + vb;
      int ncarry = target - have;
      if (ncarry != 0 && ncarry != 1) continue;
      ns.need_carry = bool(ncarry);
      db.push_back(vb);
      r += go(pos - 1, ns);
      db.pop_back();
    }
    da.pop_back();
  }
  if (rv != nullptr) *rv = r;
  return r;
}

u64 solve() {
  n = 0;
  if (d == 1) return 0;
  while (d > 0) {
    digits[n++] = d % 10;
    d /= 10;
  }

  REP (i, n)
    banned.insert(digits[i]);
  REP (i, 10)
    if (!banned.count(i)) allowed.push_back(i);

  u64 count = 0;
  count += go(n - 1, State());
  if (digits[n - 1] == 1) count += go(n - 2, State{ 0, 0, true });

  return count;
}

int main() {
  cin >> d;
  d0 = d;
  u64 final_count = solve();

  printf("%Lu\n", final_count);
  REP (i, res.size()) { printf("%Lu %Lu\n", res[i].first, res[i].second); }

  return 0;
}
