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
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <functional>
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

// clang-format on

#ifndef TEST_RAND
#define TEST_RAND 0
#endif

#ifndef TEST_CHECK
#define TEST_CHECK 0
#endif

const int maxn = 15;
const s64 inf = 1ll << 62;

struct Box {
  int xl, yl, xh, yh;
  Box() {}
  Box(int xl, int yl, int xh, int yh) : xl(xl), yl(yl), xh(xh), yh(yh) {}

  Box inter(const Box &peer) const {
    Box res;
    res.xl = std::max(xl, peer.xl);
    res.xh = std::min(xh, peer.xh);
    res.yl = std::max(yl, peer.yl);
    res.yh = std::min(yh, peer.yh);
    return res;
  }

  bool contains(int x, int y) const { return x >= xl && x <= xh && y >= yl && y <= yh; }

  s64 area() const {
    if (xl > xh || yl > yh) return 0;
    return 1ull * (xh - xl + 1) * (yh - yl + 1);
  }
};

struct flowgraph {
  struct Edge {
    s64 cap;
    s64 flow = 0;
    int src;
    int dst;
    int prev;
  };

  std::vector<Edge> edges;
  std::vector<int> last;
  std::vector<int> vis;
  int visid = 0;
  int n, s, t;

  int adde(int a, int b, s64 cap) {
    int id = edges.size();
    auto e = Edge();
    e.src = a;
    e.dst = b;
    e.cap = cap;
    e.prev = last[a];
    last[a] = id;
    OPA_DISP0(a, b, cap, id);
    edges.pb(e);
    if (cap > 0) adde(b, a, 0);
    return id;
  }

  void reset() {
    for (auto &e : edges) e.flow = 0;
  }

  flowgraph(int n) {
    s = n++;
    t = n++;
    vis.resize(n, -1);
    last.resize(n, -1);
    this->n = n;
  }

  s64 dfs(int x, s64 f) {
    if (x == t) return f;
    if (vis[x] == visid) return false;
    vis[x] = visid;
    for (int e = last[x]; e != -1; e = edges[e].prev) {
      auto &xe = edges[e];
      if (xe.flow == xe.cap) continue;
      s64 nf = dfs(edges[e].dst, std::min(f, xe.cap - xe.flow));
      if (nf > 0) {
        xe.flow += nf;
        edges[e ^ 1].flow -= nf;
        return nf;
      }
    }
    return 0;
  }

  s64 push() {
    ++visid;
    return dfs(s, inf);
  }

  s64 maxflow() {
    s64 res = 0;
    while (true) {
      s64 inc = push();
      if (inc == 0) break;
      res += inc;
    }
    return res;
  }
};

struct SolverContext {
  int x[maxn], y[maxn], d[maxn];
  Box bx[1 << maxn];
  s64 cnt[1 << maxn];
  std::vector<int> epos;
  s64 req;

  int n;
  int xn, yn;

  s64 box_count(const Box &b) const {
    s64 res = b.area();
    REP (i, n)
      if (b.contains(x[i], y[i])) --res;
    return res;
  }

  void read() {
    scanf("%d%d%d", &yn, &xn, &n);
    REP (i, n)
      scanf("%d%d%d", y + i, x + i, d + i);
  }

  bool checkit(flowgraph &fg, bool minv, s64 cap) {
    fg.reset();
    for (auto &x : epos) fg.edges[x].cap = cap;
    s64 f = fg.maxflow();
    OPA_DISP0(f, minv, req, cap);

    if (minv) {
      for (auto &x : epos)
        if (fg.edges[x].flow < cap) return false;
      return true;
    } else
      return f == req;
  }

  bool checkit2(flowgraph &fg, s64 mcap, s64 cap) {
    fg.reset();
    for (auto &x : epos) fg.edges[x].cap = mcap;
    s64 f = fg.maxflow();
    for (auto &x : epos) fg.edges[x].cap = cap;
    f += fg.maxflow();

    return f == req;
  }

  s64 findit(flowgraph &fg, bool minv) {
    s64 T = 0, H = req + 2;
    s64 best = 0;
    while (T <= H) {
      s64 M = (T + H) >> 1;
      if (checkit(fg, minv, M)) {
        best = M;
        if (minv)
          T = M + 1;
        else
          H = M - 1;

      } else {
        if (!minv)
          T = M + 1;
        else
          H = M - 1;
      }
    }
    return best;
  }
  s64 findit2(flowgraph &fg, s64 mcap) {
    s64 T = mcap, H = req + 2;
    s64 best = 0;
    while (T <= H) {
      s64 M = (T + H) >> 1;
      if (checkit2(fg, mcap, M)) {
        best = M;
        H = M - 1;

      } else {
        T = M + 1;
      }
    }
    return best;
  }

  s64 solve() {
    Box bound = Box(1, 1, xn, yn);
    REP (i, n)
      bx[1 << i] = bound.inter(Box(x[i] - d[i], y[i] - d[i], x[i] + d[i], y[i] + d[i]));

    REP (i, 1 << n) {
      REP (j, n) {
        if ((i >> j & 1) && i != (1 << j)) {
          bx[i] = bx[i ^ (1 << j)].inter(bx[1 << j]);
          break;
        }
      }
    }
    OPA_DISP0(bx[1<<2].area());
    OPA_DISP0(bx[1<<1].area());
    OPA_DISP0(bx[1<<0].area());
    REP(i,n) REP(j,n) OPA_DISP0(i,j, bx[1<<i].inter(bx[1<<j]).area());

    int M = (1 << n) - 1;
    std::vector<int> can;
    REPV (i, 1 << n)
      if (i > 0) {
        int ii = i ^ M;
        s64 r = box_count(bx[i]);
        for (int v = ii; v > 0; v = (v - 1) & ii) r -= cnt[i | v];
        cnt[i] = r;
        if (r > 0) can.pb(i);
      }
    flowgraph fg(n + can.size());
    out(cnt, 1<<n);

    req = 0;
    REP (i, can.size()) {
      fg.adde(fg.s, n + i, cnt[can[i]]);
      req += cnt[can[i]];
      REP (j, n) {
        if (can[i] >> j & 1) fg.adde(n + i, j, inf);
      }
    }
    REP (i, n) { epos.pb(fg.adde(i, fg.t, 1)); }
    OPA_DISP0(can, fg.s, fg.t, n, can.size());

    s64 minv = findit(fg, true);
    s64 maxv = findit(fg, false);

    s64 res = maxv - minv;
    OPA_DISP0(minv,maxv,res);
    return res;
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
    } else {
      auto res = sc.solve();
      printf("%Ld", res);
    }
    puts("");
  }

  return 0;
}

