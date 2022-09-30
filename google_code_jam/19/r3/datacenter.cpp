#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
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
#include <bitset>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <functional>
#include <memory>
#include <random>
#include <unordered_map>
#include <unordered_set>

#ifndef DEBUG
#define DEBUG_PRINT 0
#else
#define DEBUG_PRINT 1
#endif

// clang-format off
#define OPA_XSTR(x) OPA_STR(x)
#define OPA_STR(x) #x

#define VA_NUM_ARGS_IMPL(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...) N
#define VA_NUM_ARGS(...)                                                       \
  VA_NUM_ARGS_IMPL(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
#define OPA_DISPATCH(func, ...) OPA_DISPATCH_(func, VA_NUM_ARGS(__VA_ARGS__))
#define OPA_DISPATCH_(func, nargs) OPA_DISPATCH__(func, nargs)
#define OPA_DISPATCH__(func, nargs) func##nargs

#if DEBUG
#define OPA_DISP(msg, ...)                                                     \
  (std::cout << msg << ": " << RAW_OPA_DISP_VARS(__VA_ARGS__) << std::endl)
#define OPA_DISP0(...) OPA_DISP_VARS(__VA_ARGS__)
#else
#define OPA_DISP(msg, ...)                                                     \
  
#define OPA_DISP0(...)
#endif


#define _OPA_DISP_VAR1(a) #a << "=" << (a) << ","
#define _OPA_DISP_VAR2(a, b) _OPA_DISP_VAR1(a) << _OPA_DISP_VAR1(b)
#define _OPA_DISP_VAR3(a, b, c) _OPA_DISP_VAR2(a, b) << _OPA_DISP_VAR1(c)
#define _OPA_DISP_VAR4(a, b, c, d) _OPA_DISP_VAR3(a, b, c) << _OPA_DISP_VAR1(d)
#define _OPA_DISP_VAR5(a, b, c, d, e)                                          \
  _OPA_DISP_VAR4(a, b, c, d) << _OPA_DISP_VAR1(e)
#define _OPA_DISP_VAR6(a, b, c, d, e, f)                                       \
  _OPA_DISP_VAR5(a, b, c, d, e) << _OPA_DISP_VAR1(f)
#define _OPA_DISP_VAR7(a, b, c, d, e, f, g)                                    \
  _OPA_DISP_VAR6(a, b, c, d, e, f) << _OPA_DISP_VAR1(g)
#define _OPA_DISP_VAR8(a, b, c, d, e, f, g, h)                                 \
  _OPA_DISP_VAR7(a, b, c, d, e, f, g) << _OPA_DISP_VAR1(h)
#define _OPA_DISP_VAR9(a, b, c, d, e, f, g, h, i)                              \
  _OPA_DISP_VAR8(a, b, c, d, e, f, g, h) << _OPA_DISP_VAR1(i)
#define _OPA_DISP_VAR10(a, b, c, d, e, f, g, h, i, j)                          \
  _OPA_DISP_VAR9(a, b, c, d, e, f, g, h, i) << _OPA_DISP_VAR1(j)

#define RAW_OPA_DISP_VARS(...)                                                 \
  std::hex << std::showbase                                                    \
           << OPA_DISPATCH(_OPA_DISP_VAR, __VA_ARGS__)(__VA_ARGS__)

#define OPA_DISP_VARS(...)                                                     \
  (std::cout << RAW_OPA_DISP_VARS(__VA_ARGS__) << std::endl)

#define OPA_DISP_VARSERR(...)                                                  \
  (std::cerr << RAW_OPA_DISP_VARS(__VA_ARGS__) << std::endl)
#define OPA_DISPERR(msg, ...)                                                  \
  (std::cerr << msg << ": " << RAW_OPA_DISP_VARS(__VA_ARGS__) << std::endl)
#define OPA_DISP0ERR(...) OPA_DISP_VARSERR(__VA_ARGS__)

#define OPA_DISPL0(...)                                                        \
  (std::cout << OPA_LINE_INFO << ": " << RAW_OPA_DISP_VARS(__VA_ARGS__)        \
             << std::endl)
#define OPA_DISPL(msg, ...)                                                    \
  (std::cout << OPA_LINE_INFO << "msg:" << msg << ": "                         \
             << RAW_OPA_DISP_VARS(__VA_ARGS__) << std::endl)

#define OPA_STREAM_STR(a)                                                      \
  ((static_cast<std::ostringstream &>(std::ostringstream() << a)).str())

#define OPA_DISP_VARS1(a) (std::cout << _OPA_DISP_VAR1(a) << std::endl)
#define OPA_DISP_VARS2(a, b) (std::cout << _OPA_DISP_VAR2(a, b) << std::endl)
#define OPA_DISP_VARS3(a, b, c)                                                \
  (std::cout << _OPA_DISP_VAR3(a, b, c) << std::endl)
#define OPA_DISP_VARS4(a, b, c, d)                                             \
  (std::cout << _OPA_DISP_VAR4(a, b, c, d) << std::endl)
#define OPA_DISP_VARS5(a, b, c, d, e)                                          \
  (std::cout << _OPA_DISP_VAR5(a, b, c, d, e) << std::endl)
#define OPA_DISP_VARS6(a, b, c, d, e, f)                                       \
  (std::cout << _OPA_DISP_VAR6(a, b, c, d, e, f) << std::endl)
#define OPA_DISP_VARS7(a, b, c, d, e, f, g)                                    \
  (std::cout << _OPA_DISP_VAR7(a, b, c, d, e, f, g) << std::endl)
#define OPA_DISP_VARS8(a, b, c, d, e, f, g, h)                                 \
  (std::cout << _OPA_DISP_VAR8(a, b, c, d, e, f, g, h) << std::endl)
#define OPA_DISP_VARS9(a, b, c, d, e, f, g, h, i)                              \
  (std::cout << _OPA_DISP_VAR9(a, b, c, d, e, f, g, h, i) << std::endl)
#define OPA_DISP_VARS10(a, b, c, d, e, f, g, h, i, j)                          \
  (std::cout << _OPA_DISP_VAR10(a, b, c, d, e, f, g, h, i, j) << std::endl)
#define OPA_DISP_STR(...) (OPA_STREAM_STR(RAW_OPA_DISP_VARS(__VA_ARGS__)))


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
#define MP(x,y) std::make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef std::pair<int,int> pii;
typedef std::vector<int> vi;
typedef std::vector<std::string> vs;
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef signed long long s64;
typedef unsigned long long u64;


namespace std {
template <class T1, class T2>
std::ostream &operator<<(std::ostream &os, const std::pair<T1, T2> &a) {
  os << "(";
  os << a.ST << ", " << a.ND;
  os << ")";
  return os;
}

template <class T, class L>
std::ostream &operator<<(std::ostream &os, const std::unordered_set<T, L> &a) {
  os << "(";
  for (auto &x : a) os << x << ",";
  os << ")";
  return os;
}

template <class A, class B, class L>
std::ostream &operator<<(std::ostream &os,
                         const std::unordered_map<A, B, L> &a) {
  os << "(";
  for (auto &x : a) os << x << ",";
  os << ")";
  return os;
}

template <std::size_t N, typename... Args> class Opa_os_tuple_pipe {
public:
  static std::ostream &os_pipe_tuple(std::ostream &os,
                                     const std::tuple<Args...> &a) {
    Opa_os_tuple_pipe<N - 1, Args...>::os_pipe_tuple(os, a);
    os << "," << std::get<N>(a);
    return os;
  }
};

template <typename... Args> class Opa_os_tuple_pipe<0, Args...> {
public:
  static std::ostream &os_pipe_tuple(std::ostream &os,
                                     const std::tuple<Args...> &a) {
    os << std::get<0>(a);
    return os;
  }
};

template <typename... Args>
std::ostream &operator<<(std::ostream &os, const std::tuple<Args...> &a) {
  os << "<";
  Opa_os_tuple_pipe<sizeof...(Args) - 1, Args...>::os_pipe_tuple(os, a);
  os << ">";
  return os;
}

template <class T>
std::ostream &operator<<(std::ostream &os, const std::initializer_list<T> &a) {
  os << "(";
  for (auto &x : a) os << x << ",";
  os << ")";
  return os;
}

template <class T, size_t N>
std::ostream &operator<<(std::ostream &os, const std::array<T, N> &a) {
  os << "(";
  for (auto &x : a) os << x << ",";
  os << ")";
  return os;
}

template <class T, class L>
std::ostream &operator<<(std::ostream &os, const std::set<T, L> &a) {
  os << "(";
  for (auto &x : a) os << x << ",";
  os << ")";
  return os;
}

template <class A, class B, class L>
std::ostream &operator<<(std::ostream &os, const std::map<A, B, L> &a) {
  os << "(";
  for (auto &x : a) os << x << ",";
  os << ")";
  return os;
}

template <class T>
std::ostream &operator<<(std::ostream &os, const std::deque<T> &a) {
  os << "(";
  REP (i, a.size())
    os << a[i] << (i == a.size() - 1 ? "" : ",");
  os << ")";
  return os;
}

template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &a) {
  os << "(";
  REP (i, a.size())
    os << a[i] << (i == a.size() - 1 ? "" : ",");
  os << ")";
  return os;
}

template <class A, class B>
std::pair<A, B> operator+(const std::pair<A, B> &a, const std::pair<A, B> &b) {
  return MP(a.ST + b.ST, a.ND + b.ND);
}

template <class A, class B>
std::pair<A, B> operator-(const std::pair<A, B> &a, const std::pair<A, B> &b) {
  return MP(a.ST - b.ST, a.ND - b.ND);
}
}


template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){if (!DEBUG_PRINT) return ;REP(i, n)std::cout<<t[i]<<" "; std::cout<<std::endl;}
template<class T> void out(const std::vector<T>& t, int n=-1){ if (!DEBUG_PRINT) return; for (int i=0; i<(n==-1?t.size():n); ++i) std::cout<<t[i]<<" "; std::cout<<std::endl;
}
inline int count_bit(int n){return (n==0)?0:1+count_bit(n&(n-1));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(std::string s){int a; std::istringstream(s)>>a; return a;}
std::string toStr(int a){std::ostringstream os; os<<a; return os.str();}

std::mt19937 rng(0);
// clang-format on

#ifndef TEST_RAND
#define TEST_RAND 0
#endif

#ifndef TEST_CHECK
#define TEST_CHECK 0
#endif

const int dv[] = { -1, 0, 1, 0, -1 };

struct SolverContext {
  struct EdgeSpec {
    int x, y;
    char type;
  };

  static constexpr int maxn = 111;
  int nx, ny;
  int mp[maxn][maxn];

  char sol[maxn][maxn];
  std::map<int, EdgeSpec> e[maxn];
  std::map<int, EdgeSpec> ediff[maxn];
  std::map<int, int> uj_rmp;

  void read() {
    if (TEST_RAND) {
      ny = rng() % 10 + 3;
      nx = rng() % 4 + 1;
      REP (x, nx)
        REP (y, ny)
          mp[x][y] = rng() % 2;
      REP (y, ny) {
        REP (x, nx)
          printf("%d", mp[x][y]);
        puts("");
      }
      return;
    }
    scanf("%d%d\n", &ny, &nx);
    char buf[maxn];
    REP (y, ny) {
      scanf("%s", buf);
      REP (x, nx)
        mp[x][y] = buf[x] == 'B';
    }
  }

  mutable std::vector<int> par = std::vector<int>(maxn * maxn, -1);
  int root(int idx) const { return par[idx] < 0 ? idx : par[idx] = root(par[idx]); }
  bool join(int a, int b) {
    a = root(a);
    b = root(b);
    if (a != b) {
      par[a] = b;
      return true;
    }
    return false;
  }

  std::vector<pii> neighbors(int x, int y) const {
    std::vector<pii> res;
    REP (k, 4) {
      int nx = x + dv[k];
      int ny = y + dv[k + 1];
      if (is_in(nx, ny)) res.emplace_back(nx, ny);
    }
    return res;
  }

  int to_idx(int x, int y) const { return x * ny + y; }
  pii from_idx(int idx) const { return MP(idx / ny, idx % ny); }
  int is_in(int x, int y) const { return x >= 0 && y >= 0 && x < nx && y < ny; }

  bool go(int grp, std::unordered_set<int> &seen) const {
    std::unordered_set<int> next;
    for (auto &p : e[grp]) {
      if (!seen.count(p.first)) next.insert(p.first);
    }

    seen.insert(ALL(next));
    for (auto &x : next)
      if (!go(x, seen)) return false;
    return true;
  }

  std::string solve() {
    par = std::vector<int>(nx * ny, -1);

    REP (x, nx)
      REP (y, ny)
        for (auto p : neighbors(x, y))
          if (mp[x][y] == mp[p.ST][p.ND]) join(to_idx(x, y), to_idx(p.ST, p.ND));

    memset(sol, '.', sizeof(sol));
    REP (x, nx - 1)
      REP (y, ny - 1) {
        int i0 = root(to_idx(x, y));
        int i1 = root(to_idx(x + 1, y));
        int i2 = root(to_idx(x, y + 1));
        int i3 = root(to_idx(x + 1, y + 1));

        if (mp[x][y] == mp[x + 1][y + 1] && mp[x + 1][y] == mp[x][y + 1] &&
            mp[x][y] != mp[x][y + 1]) {
          if (mp[x][y])
            sol[x][y] = join(i0, i3) ? '\\' : (join(i1, i2), '/');

          else
            sol[x][y] = join(i1, i2) ? '/' : (join(i0, i3), '\\');
        }
      }

    std::set<int> lst[2];
    REP (x, nx)
      REP (y, ny)
        lst[mp[x][y]].insert(root(to_idx(x, y)));

    if (lst[0].size() > 1 || lst[1].size() > 1) return "";
    return build_sol();
  }

  std::string build_sol() const {
    std::string res;
    REP (y, ny - 1) {
      REP (x, nx - 1)
        res += sol[x][y];
      res += "\n";
    }
    return res;
  }

  std::map<vi, bool> dp[maxn][maxn][2][2];
  bool go(int x, int y, bool seen0, bool seen1, const std::vector<int> &v) {
    if (v.size() == 0) return false;

    if (x == nx) y++, x = 0;
    if (x == 0 && y == ny) {
      std::set<int> tb[2];
      REP (i, nx)
        tb[mp[i][ny - 1]].insert(v[i]);
      return tb[0].size() <= 1 && tb[1].size() <= 1;
    }

    auto &mm = dp[x][y][seen0][seen1];
    if (mm.count(v)) return mm[v];
    bool &res = mm[v];
    res = false;
    std::vector<int> ns = v;
    int next = *std::max_element(ALL(v));
    ++next;
    std::unordered_map<int, int> rmp;
    rmp[-1] = -1;
    REP (i, nx)
      if (i != x) rmp[v[i]] = v[i];
    ns[x] = next;
    ns[nx] = -1;
    rmp[next] = next;

    if (y > 0 && mp[x][y] == mp[x][y - 1]) rmp[v[x]] = next;
    if (x > 0 && mp[x][y] == mp[x - 1][y]) rmp[v[x - 1]] = next;

    if (v[nx] != -1) rmp[v[nx]] = next;
    seen0 |= mp[x][y] == 0;
    seen1 |= mp[x][y] == 1;

    if (rmp.count(v[x])) res = go(x + 1, y, seen0, seen1, normalize(ns, v, rmp));

    if (x == nx - 1 || y == 0) return res;
    sol[x][y - 1] = '.';
    if (res) return res;

    if (rmp.count(v[x]) && mp[x][y] == mp[x + 1][y - 1]) {
      sol[x][y - 1] = '/';
      rmp[v[x + 1]] = next;
      res = go(x + 1, y, seen0, seen1, normalize(ns, v, rmp));
      rmp[v[x + 1]] = v[x + 1];
    }

    if (mp[x + 1][y] == mp[x][y - 1]) {
      sol[x][y - 1] = '\\';
      ns[nx] = v[x];
      if (!rmp.count(v[x])) rmp[v[x]] = v[x];
      res = go(x + 1, y, seen0, seen1, normalize(ns, v, rmp));
      ns[nx] = -1;
      if (res) return res;
    }

    return res;
  }

  std::vector<int> normalize(const std::vector<int> &ns, const std::vector<int> &v,
                             const std::unordered_map<int, int> &rmp) {
    (void)v;
    std::vector<int> res = ns;
    std::unordered_map<int, int> reorder;
    int idx = 0;
    for (auto &u : res) {
      if (u == -1) continue;

      u = rmp.find(u)->second;
      if (!reorder.count(u)) reorder[u] = idx++;
      u = reorder[u];
    }
    return res;
  }

  std::string solve_dumb() {
    if (nx > 4) return "BAD";
    std::vector<int> tb(nx + 1, -1);
    if (!go(0, 0, false, false, tb)) return "";
    return build_sol();
  }
};

int main() {
  srand(0);
  int tn;

  if (TEST_RAND)
    tn = 10000;
  else
    scanf("%d", &tn);

  REP (ti, tn) {

    SolverContext sc;
    sc.read();
    printf("Case #%d: ", ti + 1);
    if (TEST_CHECK) {
      auto r1 = sc.solve();
      auto r2 = sc.solve_dumb();
      OPA_DISP0(r1);
      OPA_DISP0(r2);
      if (r1.size() != r2.size()) {
      }
      assert(r1.size() == r2.size());
    } else {

      auto res = sc.solve();
      puts(res.size() ? "POSSIBLE" : "IMPOSSIBLE");
      printf("%s", res.c_str());
    }
  }

  return 0;
}
