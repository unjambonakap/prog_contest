
#ifndef DEBUG
#define DEBUG 0
#endif

#ifndef TEST_LARGE
#define TEST_LARGE 0
#endif

#ifndef TEST_RAND
#define TEST_RAND 0
#endif

#ifndef TEST_CHECK
#define TEST_CHECK 0
#endif

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
#define FORV(i, a, b) for(int i = (int)(b)-1; i >= (int)a; --i)

#define FE(i,t) for (__typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (__typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

#define two(x) (1LL << (x))
#define two_pow32(x) (31-__builtin_clz(x))
#define two_pow64(x) (63-__builtin_clzll(x))
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
std::ostream &operator<<(std::ostream &os, const s128 &a) {
  u128 b;
  if (a < 0)
  {
    os << "-";
     b= - a;
  } else b = a;
  std::string s;

  if (b==0) s.pb('0');
  while(b) s.pb(b%10 + '0'),  b/=10;

  std::reverse(ALL(s));

  os << s;
  return os;
}

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
std::ostream &operator<<(std::ostream &os, const std::multiset<T, L> &a) {
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
std::ostream &operator<<(std::ostream &os, const std::multimap<A, B, L> &a) {
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
std::ostream &operator<<(std::ostream &os, const std::unique_ptr<T> &a) {
  return os << "*" << *a;
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

namespace std {
template <typename T1, typename T2> struct hash<std::pair<T1, T2> > {
  size_t operator()(const std::pair<T1, T2> &x) const {
    size_t h1 = std::hash<T1>{}(x.first);
    size_t h2 = std::hash<T1>{}(x.second);
    return (h1 * int(1e9 + 7) + h2) ^ h1;
  }
};

template <typename T1> struct hash<std::vector<T1> > {
  size_t operator()(const std::vector<T1> &x) const {
    size_t h = 0;
    auto hx = std::hash<T1>{};
    REP (i, x.size()) h = (h * int(1e8 + 19) + hx(x[i])) % int(1e9 + 7);
    return h;
  }
};

} // namespace std

template <class T> T _gcd(T a, T b) { return b == 0 ? a : _gcd(b, a % b); }
template <class T> T gcd(T a, T b) { return _gcd(std::max(a, b), std::min(a, b)); }
template <class T> int sign(T a) { return a > 0 ? 1 : (a < 0 ? -1 : 0); }

#if !LOCAL
namespace std {
s128 abs(s128 x) { return x < 0 ? -x : x; }
template <> struct hash<u128> {
  size_t operator()(const u128 &x) const {
    size_t h1 = std::hash<u64>{}((u64)x);
    size_t h2 = std::hash<u64>{}((u64)(x >> 64));
    return (h1 * int(1e9 + 7) + h2) ^ h1;
  }
};

template <> struct hash<s128> {
  size_t operator()(const s128 &x) const { return std::hash<u128>{}(x); }
};
} // namespace std
#endif

template <class T> struct frac {
  T p, q;
  frac() {}
  frac(T p) : p(p), q(1) {}
  frac(const std::pair<T, T> &px) : frac(px.first, px.second) {}

  frac(T p, T q) : p(p), q(q) {
    T d = gcd(std::abs(p), std::abs(q));
    if (this->q < 0) this->p = -this->p, this->q = -this->q;
    this->p /= d;
    this->q /= d;
  }
  template <typename U> frac<U> as() const { return frac<U>(p, q); }
  T floor() const { return p / q; }
  T rem() const { return p % q; }
  T ceil() const { return (p + q - 1) / q; }

  std::pair<T, T> as_pair() const { return MP(p, q); }
  frac operator+(const frac &peer) const { return frac(p * peer.q + peer.p * q, peer.q * q); }
  frac operator-(const frac &peer) const { return frac(p * peer.q - peer.p * q, peer.q * q); }
  frac operator*(const frac &peer) const { return frac(p * peer.p, peer.q * q); }
  frac operator/(const frac &peer) const { return frac(p * peer.q, q * peer.p); }
  frac operator/(T d) const { return frac(p, q * d); }
  bool operator<(const frac &peer) const { return (p * peer.q - peer.p * q) < 0; }
  bool operator>(const frac &peer) const { return (p * peer.q - peer.p * q) > 0; }
  bool operator<=(const frac &peer) const { return (p * peer.q - peer.p * q) <= 0; }
  bool operator==(const frac &peer) const { return p == peer.p && q == peer.q; }
  bool operator!=(const frac &peer) const { return p != peer.p || q != peer.q; }
};

template <class T> struct Point {
  T x, y;
  Point() {}
  Point(T x, T y) : x(x), y(y) {}
  Point operator-(const Point &peer) const { return Point(x - peer.x, y - peer.y); }
  Point operator+(const Point &peer) const { return Point(x + peer.x, y + peer.y); }
  bool operator<(const Point &peer) const { return as_pair() < peer.as_pair(); }
  bool operator==(const Point &peer) const { return x == peer.x && y == peer.y; }
  bool operator!=(const Point &peer) const { return x != peer.x || y != peer.y; }
  Point abs() const { return Point(std::abs(x), std::abs(y)); }
  T cross(const Point &peer) const { return x * peer.y - y * peer.x; }
  template <typename T2> Point<T2> as() const { return Point<T2>(x, y); }
  T dot(const Point &peer) const { return x * peer.x + y * peer.y; }
  std::pair<T, T> as_pair() const { return MP(x, y); }

  Point simplify() const {
    T d = gcd(std::abs(x), std::abs(y));
    if (d == 0) return *this;
    if (y < 0) d = -d;
    return Point(x / d, y / d);
  }
};
typedef struct Point<s64> P64;

template <class T> struct Segment {
  Point<T> a, b;
  Segment(Point<T> _a, Point<T> _b) : a(_a), b(_b) {}

  bool different_side(const Segment &peer) const {
    auto v = b - a;
    return sign(v.cross(peer.a - a)) != sign(v.cross(peer.b - a));
  }

  bool intersects(const Segment &peer) const {
    if (parallel(peer)) return false;
    return different_side(peer) && peer.different_side(*this);
  }
  template <typename T2> Segment<T2> as() const {
    return Segment<T2>(a.template as<T2>(), b.template as<T2>());
  }
  frac<T> slope() const { return frac<T>(b.y - a.y, b.x - a.x); }

  frac<s128> eval(const T &x) const { return frac<s128>(b.y - a.y, b.x - a.x) * (x - a.x) + a.y; }

  bool vertical() const { return a.x == b.x; }
  bool parallel(const Segment &peer) const { return (b - a).cross(peer.b - peer.a) == 0; }
  Point<T> dir() const { return b - a; }
  Point<T> orth_dir() const {
    auto d = dir();
    return Point<T>(-d.y, d.x);
  }
  T signed_dist(const Point<T> &p) const { return (b - a).cross(p - a); }
  bool ccw(const Point<T> &p) const { return dir().cross(p - a) > 0; }

  Point<frac<T> > inter_point(const Segment<T> &peer) const {
    auto v1 = orth_dir();
    auto v2 = peer.orth_dir();
    auto d = v1.cross(v2);
    auto p1 = v1.dot(a);
    auto p2 = v2.dot(peer.a);

    auto xx = p1 * v2.y - p2 * v1.y;
    auto yy = v1.x * p2 - v2.x * p1;
    return Point<frac<T> >(frac<T>(xx, d), frac<T>(yy, d));
  }
};

namespace std {
template <class T> std::ostream &operator<<(std::ostream &os, const Point<T> &a) {
  return os << a.as_pair();
}
template <class T> std::ostream &operator<<(std::ostream &os, const frac<T> &a) {
  return os << MP(a.p, a.q);
}
template <class T> std::ostream &operator<<(std::ostream &os, const Segment<T> &a) {
  return os << "Seg(" << a.a << ", " << a.b << ")";
}

template <typename T> struct hash<frac<T> > {
  size_t operator()(const frac<T> &x) const { return std::hash<std::pair<T, T> >{}(x.as_pair()); }
};
template <typename T> struct hash<Point<T> > {
  size_t operator()(const Point<T> &x) const { return std::hash<std::pair<T, T> >{}(x.as_pair()); }
};
} // namespace std

std::mt19937 rng(0);
struct ReaderHelper {
  mutable char buf[11111111];

  mutable std::istringstream iss;
  std::istringstream &readline() const {
    fgets(buf, sizeof(buf) - 1, stdin);
    iss = std::istringstream(buf);
    return iss;
  }
};
ReaderHelper g_reader;

struct Precomp {

  void setup() {}
};
Precomp g_precomp;

struct DG {
  int n, m;
  std::vector<vi> el;
  std::vector<vi> rel;

  vi build_walk(std::vector<pii> el, int s0 = 0) {
    std::sort(ALL(el));
    std::vector<vi> exl(n);
    for (auto x : el) exl[x.ST].pb(x.ND);
    std::vector<int> stk;
    stk.pb(s0);

    vi walk;
    while (stk.size() > 0) {
      auto e = stk.back();
      if (exl[e].size() > 0) {
        stk.pb(exl[e].back());
        exl[e].pop_back();
        continue;
      }

      stk.pop_back();
      walk.pb(e);
    }
    if (walk.size() != el.size() + 1) return {};
    std::reverse(ALL(walk));
    return walk;
  }
};
struct Edge {
  int prev, cost, cap;
  int from, to, id;
};
struct Graph {
  std::vector<int> last;
  std::vector<Edge> el;
  int ne;
  int N;
  int S, T;
  std::vector<int> cx;
  std::priority_queue<pii> q;
  std::queue<int> q2;
  bool use_cost;

  void setup(int n, bool use_cost) {
    this->use_cost = use_cost;
    N = n + 2;
    S = n;
    T = n + 1;
    last.resize(N, -1);
  }

  int adde(int a, int b, int c, int cap, int rev = 0) {
    int id = el.size();
    Edge e;
    e.from = a;
    e.to = b;
    e.cost = c;
    e.cap = cap;
    e.prev = last[a];
    e.id = id;
    el.pb(e);
    last[a] = id;

    if (!rev) adde(b, a, -c, 0, 1);
    return id;
  }

  bool push(int a, int c) {
    if (cx[a] <= c) return false;
    if (use_cost)
      q.emplace(-c, a);
    else
      q2.push(a);
    cx[a] = c;
    return true;
  }

  int augment() {

    while (q.size()) q.pop();
    while (q2.size()) q2.pop();
    cx.clear();
    cx.resize(N, INT_MAX);
    push(S, 0);
    std::vector<int> par(N, -1);

    while (true) {
      int a;
      if (use_cost) {
        if (!q.size()) break;
        pii cur = q.top();
        q.pop();
        a = cur.second;
        if (cx[a] != -cur.first) continue;
      } else {
        if (!q2.size()) break;
        a = q2.front();
        q2.pop();
      }

      if (a == T) break;
      int c = cx[a] + 1;

      for (int eid = last[a]; eid != -1; eid = el[eid].prev) {
        auto &e = el[eid];
        if (e.cap <= 0) continue;
        if (push(e.to, c + e.cost)) par[e.to] = eid;
      }
    }

    if (par[T] == -1) return -1;
    int x = T;
    std::vector<int> used;
    int mcap = INT_MAX;
    while (x != S) {
      auto &e = el[par[x]];
      x = e.from;
      checkmin(mcap, e.cap);
      used.pb(e.id);
    }
    for (auto id : used) {
      auto &e = el[id];
      e.cap -= mcap;
      el[e.id ^ 1].cap += mcap;
    }
    return 1;
  }

  int augment_mfmc() {
    while (q.size()) q.pop();
    cx.clear();
    cx.resize(N, INT_MAX);
    push(S, 0);
    std::vector<int> par(N, -1);

    while (q.size() > 0) {
      pii cur = q.top();
      q.pop();
      int a = cur.second;
      if (cx[a] != -cur.first) continue;
      if (a == T) break;
      int c = cx[a];

      for (int eid = last[a]; eid != -1; eid = el[eid].prev) {
        auto &e = el[eid];
        if (e.cap <= 0) continue;
        if (push(e.to, c + e.cost)) par[e.to] = eid;
      }
    }

    if (par[T] == -1) return -1;
    int res = 0;
    int x = T;
    while (x != S) {
      auto &e = el[par[x]];
      x = e.from;
      res += e.cost;
      --e.cap;
      el[e.id ^ 1].cap++;
    }
    return res;
  }

  int find_flow() {
    int res = 0;

    int cnt = 0;
    while (true) {

      int x = use_cost ? augment_mfmc() : augment();
      if (x < 0) break;
      ++cnt;
      res += x;
    }
    return res;
  }
};

const int oo = 1e9;
struct SolverContext {
  typedef vi res_t;
  DG dg;

  void read() {
    if (TEST_RAND) {
      int n = rng() % 2 + 2;
      int m = rng() % (n * n - n) + 1;
      std::vector<pii> tb;
      REP (i, n)
        REP (j, n)
          if (i != j) tb.emplace_back(i, j);
      dg.n = n;
      dg.el.resize(dg.n);
      dg.rel.resize(dg.n);
      REP (i, m) {
        int j = rng() % tb.size();
        int a = tb[j].ST;
        int b = tb[j].ND;
        std::swap(tb[j], tb.back());
        tb.pop_back();
        dg.el[a].pb(b);
        dg.rel[b].pb(a);
      }

    } else {
      g_reader.readline() >> dg.n >> dg.m;
      dg.el.resize(dg.n);
      dg.rel.resize(dg.n);
      REP (i, dg.m) {
        int a, b;
        g_reader.readline() >> a >> b;
        --a;
        --b;
        dg.el[a].pb(b);
        dg.rel[b].pb(a);
      }
    }
  }

  res_t solve_slow() {
    res_t res;
    REP (i, dg.n)
      if (dg.el[i].size() == 0 || dg.rel[i].size() == 0) return {};

    vi diff(dg.n, 0);
    int md = 0;
    REP (i, dg.n) {
      diff[i] = dg.el[i].size() - dg.rel[i].size();
      checkmax<int>(md, dg.el[i].size());
      checkmax<int>(md, dg.rel[i].size());
    }

    Graph g;
    g.setup(2 * dg.n, false);
    vi tg1;
    vi tg2;
    vi rem;
    REP (a, dg.n) {
      for (auto b : dg.el[a]) {
        rem.pb(g.adde(a, dg.n + b, 1, oo));
      }
      int i1 = g.adde(g.S, a, 1, std::max<int>(0, md - dg.el[a].size()));
      tg1.pb(i1);
      int i2 = g.adde(dg.n + a, g.T, 1, std::max<int>(0, md - dg.rel[a].size()));
      tg2.pb(i2);
    }
    int tg = 0;
    for (auto i : tg1) tg += g.el[i].cap;

    int have = 0;

    const int mv = 1e6;
    while (tg < mv) {
      have += g.find_flow();
      if (have == tg) break;
      for (auto i : tg1) g.el[i].cap += 1;
      for (auto i : tg2) g.el[i].cap += 1;
      tg += dg.n;
    }
    if (have != tg) return {};

    std::vector<pii> lst;
    REP (a, dg.n)
      for (auto b : dg.el[a]) lst.emplace_back(a, b);
    for (auto x : rem) {
      REP (f, g.el[x ^ 1].cap) {
        lst.emplace_back(g.el[x].from, g.el[x].to - dg.n);
      }
    }
    return dg.build_walk(lst);
  }

  std::unordered_map<pii, int> e2match;
  std::vector<std::vector<pii> > matchings;
  vi match_a2b, match_b2a;
  vi vis;
  int visid;
  bool dfs(int a) {
    if (vis[a] == visid) return false;
    vis[a] = visid;
    for (auto x : dg.el[a]) {
      if (match_b2a[x] == -1 || dfs(match_b2a[x])) {
        match_b2a[x] = a;
        match_a2b[a] = x;
        return true;
      }
    }
    return false;
  }

  res_t solve() {

    std::vector<pii> lst;
    match_a2b.resize(dg.n, -1);
    match_b2a.resize(dg.n, -1);
    visid = 0;
    vis.resize(dg.n, -1);
    REP (i, dg.n) {
      ++visid;
      if (!dfs(i)) return {};
    }

    REP (i, dg.n)
      for (auto j : dg.el[i]) {
        int mid = matchings.size();
        if (!e2match.emplace(MP(i, j), mid).second) continue;

        if (match_a2b[i] != j) {
          int i2 = match_b2a[j];
          assert(match_a2b[i] != j);
          assert(match_a2b[i] != -1);
          assert(match_b2a[j] != -1);
          match_b2a[match_a2b[i]] = -1;
          assert(match_b2a[j] != -1);
          match_a2b[match_b2a[j]] = -1;
          match_a2b[i] = j;
          match_b2a[j] = i;
          ++visid;
          vis[i]= visid;
          if (!dfs(i2)) return {};
        }
        matchings.emplace_back();
        REP (k, dg.n) {
          auto ex = MP(k, match_a2b[k]);
          e2match.emplace(ex, mid);
          matchings.back().pb(ex);
          lst.pb(ex);
        }
      }

    return dg.build_walk(lst);
  }

  res_t solve_dumb() { return solve_slow(); }
  void disp(const res_t &res) {
    if (res.size() == 0)
      puts("IMPOSSIBLE");
    else {
      printf("%lu\n", res.size());
      for (auto x : res) printf("%d ", x + 1);
      puts("");
    }
  }
};

int main() {
  srand(0);
  int tn;

  g_precomp.setup();
  if (TEST_RAND)
    tn = 10000;
  else
    scanf("%d\n", &tn);

  REP (ti, tn) {

    SolverContext sc;
    sc.read();
    if (TEST_CHECK) {
      auto r1 = sc.solve();
      auto r2 = sc.solve_dumb();
      OPA_DISP0(r1, r2);
      if (r1.empty() != r2.empty()) {
        printf("Case #%d: ", ti + 1);
        printf("DUMB >> ");
        sc.disp(r2);
        printf("NORMAL >> ");
        sc.disp(r1);
        OPA_DISP0(sc.dg.el, sc.dg.n);
        puts("");
        assert(0);
      }
    } else {

      printf("Case #%d: ", ti + 1);
      auto res = sc.solve();
      sc.disp(res);
    }
  }

  return 0;
}
