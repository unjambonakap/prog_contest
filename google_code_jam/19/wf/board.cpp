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
  OPA_DISPATCH(_OPA_DISP_VAR, __VA_ARGS__)(__VA_ARGS__)

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
typedef __int128 s128;
typedef unsigned __int128 u128;


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

struct hash_t {
  template<typename T1,typename T2> size_t operator()(const std::pair<T1,T2> &x) const {
    size_t h1 = std::hash<T1>{}(x.first);
    size_t h2 = std::hash<T1>{}(x.second);
    return (h1 * 31 + h2) ^ h1;
  }
};

std::mt19937 rng(0);
// clang-format on

#ifndef TEST_RAND
#define TEST_RAND 0
#endif

#ifndef TEST_CHECK
#define TEST_CHECK 0
#endif
int nmax, m, r;

struct Simulator {
  std::vector<pii> kings;
  mutable pii req;
  mutable std::uniform_int_distribution<> dis;
  Simulator() : dis(-m, m) {}
  void gen() {
    int n = rng() % nmax + 1;
    REP (i, n) { kings.emplace_back(dis(rng), dis(rng)); }
  }

  int query(int x, int y) const {
    int res = 0;
    for (auto a : kings) {
      res += std::max(std::abs(x - a.first), std::abs(y - a.second));
    }
    return res;
  }

  pii get_req() const {
    req = MP(dis(rng), dis(rng));
    return req;
  }

  bool check_req(int ans) const { return (ans == query(req.first, req.second)); }
};

struct SolverContext {
  char buf[11111];
  std::string sx;
  bool done, error;
  int nq_ans = 0;
  int nq_ask = 0;
  pii cur_query;
  Simulator sim;
  Simulator build_sim;
  int n;

  std::istringstream iss;
  std::istringstream &readline() {
    fgets(buf, sizeof(buf) - 1, stdin);
    sx = std::string(buf);
    while (sx.size() >0  && std::isspace(sx.back())) sx.pop_back();
    done = sx == "DONE";
    error = sx == "ERROR";
    if (error) exit(0);
    iss = std::istringstream(buf);
    return iss;
  }

  void ready() {
    if (!TEST_RAND) puts("READY");
    fflush(stdout);
  }

  void output_query(int v) {
    if (TEST_RAND)
      assert(sim.check_req(v));
    else {
      printf("%d\n", v);
      fflush(stdout);
    }
  }

  bool get_query(pii &q) {
    ++nq_ans;
    if (TEST_RAND) {
      if (nq_ans == r) return false;
      q = sim.get_req();
      return true;
    }
    readline() >> q.ST >> q.ND;
    return !done;
  }

  int query(int x, int y) {
    ++nq_ask;
    assert(nq_ask <= r);

    int res;
    if (TEST_RAND) {
      res = sim.query(x, y);

    } else {
      printf("%d %d\n", x, y);
      fflush(stdout);

      readline() >> res;
    }
    res -= build_sim.query(x, y);
    return res;
  }

  void read() {
    if (TEST_RAND) sim.gen();
  }

  void solve(int T, int H, int difft, int valt, int targetdiff, std::map<int, pii> &res,
             std::function<int(int)> qf) {

    if (difft == targetdiff) return;
    int M = (T + H) / 2;
    if (H == T + 1) {
      int valh = qf(H);
      res[H - 1] = MP(valh, valh - valt);
      return;
    }
    int valm = qf(M);

    if (valm - valt == (M - T) * difft) {
      solve(M, H, difft, valm, targetdiff, res, qf);
    } else {
      solve(T, M, difft, valt, targetdiff, res, qf);
      int valh = qf(H);
      auto last = *res.rbegin();
      if (valh - last.second.first != (H - last.first - 1) * last.second.second)
        solve(M, H, res.rbegin()->second.second, valm, targetdiff, res, qf);
    }
  }

  void solve() {
    build_sim.kings.clear();
    int lim = 9 * m;
    n = query(lim, lim) - query(lim - 1, lim - 1);
    std::map<int, pii> px, py;
    OPA_DISP0(n);

    int Y0 = 5 * m;
    int s0 = query(-lim, Y0);
    int s1 = query(0, Y0);
    solve(-lim, 0, -n, s0, 0, px, [&](int x) { return query(x, Y0); });
    solve(0, lim, 0, s1, n, py, [&](int x) { return query(x, Y0); });
    int last = -n;
    std::vector<int> xmy, xpy;
    for (auto &e : px) {
      int curn = std::abs(last - e.second.second);
      REP (k, curn)
        xpy.pb(e.first + Y0);
      last = e.second.second;
    }

    last = 0;
    for (auto &e : py) {
      int curn = std::abs(last - e.second.second);
      REP (k, curn)
        xmy.pb(e.first - Y0);
      last = e.second.second;
    }
    OPA_DISP0(xpy, xmy);
    for (auto &k : sim.kings) OPA_DISP0(k.first - k.second, k.first + k.second);

    std::map<pii, int> ql;
    // ql[MP(-lim, Y0)] = s0;
    // ql[MP(0, Y0)] = s1;
    if (0)
      for (auto &k : sim.kings) {
        ql[k] = query(k.first, k.second);
      }

    if (1)
      while (nq_ask < r-100) {
        int x = build_sim.dis(rng);
        int y = build_sim.dis(rng);
        ql[MP(x, y)] = query(x, y);
      }
    vi perm;
    REP (i, n)
      perm.pb(i);
    std::vector<Simulator> found;
    OPA_DISP0(r - nq_ask);

    do {
      Simulator cur;
      bool ok = true;
      REP (i, n) {
        int x = (xpy[i] + xmy[perm[i]]) / 2;
        int y = xpy[i] - x;
        cur.kings.emplace_back(x, y);
        if (std::min(x,y) < -m || std::max(x,y) > m) {ok=false; break;}
      }
      if (!ok) continue;
      for (auto &q : ql) {
        if (cur.query(q.first.first, q.first.second) != q.second) {
          ok = false;
          break;
        }
      }
      if (!ok) continue;
      for (auto &k : cur.kings) {
        if (ql.count(k)) continue;
        auto nq = query(k.first, k.second);
        ql[k] = nq;
        if (cur.query(k.first, k.second) != nq) {
          ok = false;
          break;
        }
      }
      if (!ok) continue;
      found.pb(cur);
      break;
    } while (std::next_permutation(ALL(perm)));

    OPA_DISP0(found.size());
    assert(found.size() > 0);
    ready();
    pii qx;
    auto good = found[0];
    while (get_query(qx)) {
      output_query(good.query(qx.first, qx.second));
    }
    OPA_DISP0(nq_ans);
  }
  int solve_dumb() { return 0; }
};

int main() {
  srand(0);
  int tn;

  if (TEST_RAND) {
    tn = 10000;
    m = 1e6;
    r = 1000;
    nmax = 10;
  } else {
    SolverContext sc0;
    sc0.readline() >> tn >> nmax >> m >> r;
  }

  REP (ti, tn) {

    SolverContext sc;
    sc.read();
    sc.solve();
  }

  return 0;
}
