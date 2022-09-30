
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
  os << "(";
  u128 b;
  if (a < 0)
  {
    os << "-";
     b= - a;
  } else b = a;
  os << (u64)(b>>64) << " x " << (u64)((b<<64)>>64);
  os << ")";
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
std::ostream &operator<<(std::ostream &os, const std::list<T> &a) {
  os << "(";
  int sz= a.size();
  for (auto x : a)
    os << x << (--sz==0 ? "" : ",");
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
    REP (i, x.size())
      h = (h * int(1e8 + 19) + hx(x[i])) % int(1e9 + 7);
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
  Point(const std::pair<T, T> &p) : Point(p.first, p.second) {}
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
typedef struct Point<s128> P128;

template <class T> struct Segment {
  Point<T> a, b;
  Segment(Point<T> _a, Point<T> _b) : a(_a), b(_b) {}

  int side(const Point<T> &peer) const {
    auto v = b - a;
    return sign(v.cross(peer - a));
  }

  int side(const Segment &peer) const {
    int s0 = side(peer.a);
    int s1 = side(peer.b);
    if (s0 == 0) return s1;
    return s0;
  }

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
  T proj(const Point<T> &p) const { return (p - a).dot(b - a); }

  bool vertical() const { return a.x == b.x; }
  bool parallel(const Segment &peer) const { return (b - a).cross(peer.b - peer.a) == 0; }
  Point<T> dir() const { return b - a; }
  Point<T> orth_dir() const {
    auto d = dir();
    return Point<T>(-d.y, d.x);
  }
  T signed_dist(const Point<T> &p) const {
    auto r = (b - a).cross(p - a);
    return r;
  }
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
struct PointSet {
  std::vector<P64> pts;
  P64 get(int i) const { return pts[i]; }
  Segment<s64> get(int a, int b) const { return Segment<s64>(get(a), get(b)); }
};

struct Hull {
  const PointSet &ps;
  vi hull;
  int n;
  int center;
  Hull(const PointSet &ps, const vi &ihull, const Segment<s64> &projline) : ps(ps) {
    hull = ihull;
    n = hull.size() - 1;
    center = std::min_element(ALL(hull),
                              [&](int a, int b) {
                                return std::abs(projline.signed_dist(ps.get(a))) <
                                       std::abs(projline.signed_dist(ps.get(b)));
                              }) -
             hull.begin();
  }
  int get_id(int x) const { return hull[(x + 2 * n + center) % n]; }
  P64 get_pt(int x) const { return ps.get(get_id(x)); }
  bool outside_line(int v, const P64 &p) const {
    return get_e(v).signed_dist(p) <= 0 || get_e(v - 1).signed_dist(p) <= 0;
  }
  Segment<s64> get_e(int x) const { return ps.get(get_id(x), get_id(x + 1)); }
};

struct Generator {
  bool check_colinear(Point<s32> pt, const std::vector<Point<s32> > &lst) {
    std::unordered_set<pii> mp;
    for (auto &e : lst) {
      if (pt == e) return false;
      auto dir = (std::max(e, pt) - std::min(e, pt)).simplify().as_pair();
      if (!mp.insert(dir).second) return false;
    }
    return true;
  }
  std::vector<pii> generate_points(int n, int lim, bool circle_like = false) {
    std::uniform_int_distribution<> dis(-lim, lim);
    std::unordered_set<int> seen;
    std::vector<Point<s32> > pts;
    if (circle_like || TEST_LARGE) {
      double pi = acos(-1.);
      int r = std::uniform_int_distribution<>(lim / 2, lim)(rng);
      std::uniform_int_distribution<> d2(-(lim * 2 * pi / n / 10 + 1), lim * 2 * pi / n / 10 + 1);

      REP (i, n) {
        double ang = 2 * pi / n * (i + 0.5);
        double x = cos(ang) * r + d2(rng) * 1;
        double y = sin(ang) * r + d2(rng) * 1;
        pts.emplace_back(x, y);
      }

    } else {

      REP (i, n) {
        while (true) {
          Point<s32> p(dis(rng), dis(rng));
          if (seen.count(p.x)) continue;
          if (check_colinear(p, pts)) {
            pts.pb(p);
            seen.insert(p.x);
            break;
          }
        }
      }
    }

    std::vector<pii> res;
    for (auto &x : pts) res.pb(x.as_pair());
    return res;
  }
};

struct SolverContext {
  char buf[11111];

  std::istringstream iss;
  std::istringstream &readline() {
    fgets(buf, sizeof(buf) - 1, stdin);
    iss = std::istringstream(buf);
    return iss;
  }
  std::vector<pii> pts0;
  std::vector<P64> pts;
  std::unordered_map<P64, int> rmp;
  PointSet ps;

  int n;
  int k;
  std::vector<pii> fences;
  bool has_vert() {
    std::unordered_map<s128, int> tb;
    for (auto &x : pts)
      if (++tb[x.x] > 1) return false;
    return true;
  }

  void read() {
    k = 2;
    fences.resize(k);

    if (TEST_RAND) {
      n = rng() % 20 + 8;
      Generator gen;
      pts0 = gen.generate_points(n, 100, false);
      REP (ik, k) {
        while (true) {
          int a = rng() % (n - 1) + 1;
          int b = rng() % a;
          fences[ik] = MP(b, a);
          auto cur = Segment<s64>(P64(pts0[a]), P64(pts0[b]));
          bool bad = false;
          REP (j, ik) {
            auto fj = fences[j];
            auto fk = fences[ik];
            auto cj = Segment<s64>(P64(pts0[fences[j].first]), P64(pts0[fences[j].second]));
            if (fences[j] == fences[ik] || (fj.ST != fk.ST && fj.ST != fk.ND && fj.ND != fk.ST &&
                                            fj.ND != fk.ND && cur.intersects(cj))) {
              bad = true;
              break;
            }
          }
          if (!bad) break;
        }
      }

    } else {
      readline() >> n;
      pts0.resize(n);
      REP (i, n)
        readline() >> pts0[i].first >> pts0[i].second;
      REP (i, k)
        readline() >> fences[i].first >> fences[i].second;
      REP (i, k)
        fences[i] = fences[i] - MP(1, 1);
    }
    REP (i, n)
      pts.emplace_back(pts0[i]);
    ps.pts = pts;
  }

  void split_points(const Segment<s64> &s, const vi &lst, int side_left, vi &left, vi &right) {
    for (auto &i : lst) {
      auto &pt = pts[i];
      int sx = s.side(pt);
      if (std::abs(sx - side_left) < 2) left.pb(i);
      if (std::abs(sx + side_left) < 2) right.pb(i);
    }
  }

  std::vector<int> get_hull(vi ids) {
    if (ids.size() < 3) {
      if (ids.size() > 0) ids.pb(ids[0]);
      return ids;
    }
    std::sort(ALL(ids), [&](int a, int b) { return pts[a] < pts[b]; });

    std::vector<int> lhull, uhull;
    for (auto i : ids) {
      while (lhull.size() > 1 &&
             (pts[i] - pts[lhull[lhull.size() - 2]]).cross(pts[i] - pts[lhull.back()]) < 0)
        lhull.pop_back();
      lhull.pb(i);
    }

    for (auto i : ids) {
      while (uhull.size() > 1 &&
             (pts[i] - pts[uhull[uhull.size() - 2]]).cross(pts[i] - pts[uhull.back()]) > 0)
        uhull.pop_back();
      uhull.pb(i);
    }
    std::reverse(ALL(uhull));
    uhull.pop_back();
    lhull.pop_back();

    lhull.insert(lhull.end(), ALL(uhull));
    lhull.pb(lhull[0]);
    return lhull;
  }
  Segment<s64> get_seg(int a, int b) { return Segment<s64>(pts[a], pts[b]); }

  void merge_hulls(const Hull &h1, const Hull &h2, std::vector<pii> &el) {
    int i1 = 0, i2 = 0;

    el.emplace_back(h1.get_id(0), h2.get_id(0));
    if (h1.get_id(1) == h2.get_id(-1))
      i1 = 1, i2 = -1;
    else if (h1.get_id(0) == h2.get_id(-1))
      i1 = 0, i2 = -1;
    else if (h1.get_id(1) == h2.get_id(0))
      i1 = 1, i2 = 0;

    int cnt1=h1.n-2, cnt2=h2.n-2;
    while (true) {
      if (cnt1 > 0 && h2.outside_line(i2, h1.get_pt(i1 + 1)) && h1.outside_line(i1 + 1, h2.get_pt(i2)))
        ++i1, --cnt1;
      else if (cnt2 > 0 && h1.outside_line(i1, h2.get_pt(i2 - 1)) && h2.outside_line(i2 - 1, h1.get_pt(i1)))
        --i2, --cnt2;
      else
        break;
      el.emplace_back(h1.get_id(i1), h2.get_id(i2));
    }
  }

  void merge_hulls(vi h1, vi h2, const Segment<s64> &split_line, std::vector<pii> &el) {
    if (!h1.size() || !h2.size()) return;

    int n1 = h1.size() - 1;
    int n2 = h2.size() - 1;
    if (n1 == 2 && n2 == 2) {
      el.emplace_back(h1[0], h2[0]);
      el.emplace_back(h1[0], h2[1]);
      el.emplace_back(h1[1], h2[1]);
      return;
    }

    if (n1 <= 2 || n2 <= 2) {
      if (n1 > n2) std::swap(h1, h2), std::swap(n1, n2);
      Hull hu2(ps, h2, split_line);
      Hull hu1(ps, h1, split_line);
      std::map<int, std::set<int> > mp;
      REP (i1, n1) {
        FOR (i2, -n2, n2) {
          if (hu2.outside_line(i2, hu1.get_pt(i1))) mp[i1].insert(i2);
        }
      }
      for (auto x : mp[0]) el.emplace_back(hu1.get_id(0), hu2.get_id(x));

      if (n1 == 2) {

        for (auto x : mp[1])
          if (!mp[0].count(x)) el.emplace_back(hu1.get_id(1), hu2.get_id(x));
        if (*mp[0].begin() < *mp[0].begin())
          el.emplace_back(hu1.get_id(1), hu2.get_id(*mp[0].rbegin()));
        else
          el.emplace_back(hu1.get_id(1), hu2.get_id(*mp[0].begin()));
      }
      return;
    }
    Hull hu2(ps, h2, split_line);
    Hull hu1(ps, h1, split_line);

    merge_hulls(hu1, hu2, el);
    merge_hulls(hu2, hu1, el);
  }

  void triangulate(vi lst, std::vector<pii> &el) {
    std::set<pii> line;
    std::sort(ALL(lst), [&](int a, int b) { return pts[a] < pts[b]; });
    line.emplace(INT_MIN, -1);
    line.emplace(INT_MAX, -1);

    if (lst.size() <= 1) return;
    el.emplace_back(lst[0], lst[1]);
    if (lst.size() == 2) return;
    el.emplace_back(lst[0], lst[2]);
    el.emplace_back(lst[1], lst[2]);

    std::list<int> hu;
    hu.pb(lst[0]);
    std::list<int>::iterator last;
    if (ps.get(lst[0], lst[1]).signed_dist(ps.get(lst[2])) < 0)
      hu.pb(lst[2]), hu.pb(lst[1]), last = ++hu.begin();
    else
      hu.pb(lst[1]), hu.pb(lst[2]), last = --hu.end();
    hu.pb(lst[0]);

    FOR (ii, 3, lst.size()) {
      int i = lst[ii];

      auto p = ps.get(i);
      auto itl = last;
      auto ith = last;
      el.emplace_back(i, *last);

      while (*itl != lst[0]) {
        int x = *itl;
        int nx = *std::next(itl, -1);
        if (ps.get(nx, x).signed_dist(p) > 0) break;
        --itl;
      }
      while (*ith != lst[0]) {
        int x = *ith;
        int nx = *std::next(ith, 1);
        if (ps.get(x, nx).signed_dist(p) > 0) break;
        ++ith;
      }

      el.emplace_back(i, *itl);
      el.emplace_back(i, *ith);
      assert(ith != itl);
      for (auto it = std::next(itl, 1); it != ith;) {
        el.emplace_back(i, *it);
        auto nit = std::next(it, 1);
        hu.erase(it);
        it = nit;
      }
      last = hu.insert(ith, i);
    }
  }

  std::vector<pii> solve() {
    REP (i, n)
      rmp[pts[i]] = i;
    int i0 = 0, i1 = 1;
    Segment<s64> s0(pts[fences[i0].first], pts[fences[i0].second]);
    Segment<s64> s1(pts[fences[i1].first], pts[fences[i1].second]);
    if (s0.different_side(s1)) std::swap(s0, s1), std::swap(i0, i1);

    int side = s0.side(s1);

    vi allpoints;
    REP (i, n)
      allpoints.pb(i);

    std::vector<int> pl1, pl2;
    split_points(s0, allpoints, side, pl2, pl1);
    std::vector<int> pl21, pl22;
    split_points(s1, pl2, 1, pl21, pl22);

    std::vector<pii> edges;

    auto h1 = get_hull(pl1);
    auto h2 = get_hull(pl2);

    auto h21 = get_hull(pl21);
    auto h22 = get_hull(pl22);

    merge_hulls(h1, h2, s0, edges);
    merge_hulls(h21, h22, s1, edges);
    triangulate(pl1, edges);
    triangulate(pl21, edges);
    triangulate(pl22, edges);
    std::set<pii> lst;
    for (auto &e : edges) {
      if (e.first != e.second)
        lst.emplace(std::min(e.first, e.second), std::max(e.first, e.second));
    }
    REP (i, k)
      lst.erase(fences[i]), lst.erase(MP(fences[i].second, fences[i].first));

    std::vector<pii> res(ALL(lst));
    return res;
  }

  std::vector<pii> solve_dumb() {
    std::vector<Segment<s64> > lst;
    std::vector<pii> res;
    for (auto &f : fences) {
      int i1 = std::min(f.first, f.second);
      int i2 = std::max(f.first, f.second);
      lst.emplace_back(pts[i1], pts[i2]);
    }

    while (true) {

      bool found = false;
      REP (i, n)
        REP (j, i) {
          bool bad = false;
          auto s = Segment<s64>(pts[j], pts[i]);
          for (auto &e : lst) {
            bool s1 = s.a == e.a || s.a == e.b;
            bool s2 = s.b == e.b || s.b == e.a;
            if ((s1 && s2) || (!s1 && !s2 && s.intersects(e))) {
              bad = true;
              break;
            }
          }
          if (!bad) {
            found = true;
            lst.pb(s);
            res.emplace_back(j, i);
          }
        }
      if (!found) break;
    }
    std::sort(ALL(res));
    return res;
  }
};

int main() {
  srand(0);
  int tn;

  if (TEST_RAND)
    tn = 100000;
  else
    scanf("%d\n", &tn);

  REP (ti, tn) {

    SolverContext sc;
    sc.read();
    if (TEST_CHECK) {
      puts("");
      OPA_DISP0(sc.pts0, sc.fences);
      auto r1 = sc.solve().size();
      auto r2 = sc.solve_dumb().size();
      OPA_DISP0(r1, r2);
      if (r1 != r2) {
        printf("Case #%d: ", ti + 1);
        OPA_DISP0(r1, r2);
        OPA_DISP0(sc.pts0, sc.fences);
        puts("");
        assert(r1 == r2);
      }
    } else {

      printf("Case #%d: ", ti + 1);
      auto res = sc.solve();
      printf("%lu\n", res.size());
      for (auto e : res) printf("%d %d\n", e.first + 1, e.second + 1);
    }
  }

  return 0;
}
