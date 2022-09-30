
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
    size_t h2 = std::hash<T2>{}(x.second);
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

template <class T> inline T _gcd(T a, T b) { return b == 0 ? a : _gcd(b, a % b); }
template <class T> inline T gcd(T a, T b) {
  int _a = std::max(a, b);
  int _b = std::min(a, b);
  while (_b != 0) {
    int tmp = _a % _b;
    _a = _b;
    _b = tmp;
  }
  return _a;
}
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
    if (this->q == 0 && this->p < 0) this->p = -this->p;
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
  Point(const std::pair<T, T> &pair) : x(pair.ST), y(pair.second) {}
  Point operator-(const Point &peer) const { return Point(x - peer.x, y - peer.y); }
  Point operator+(const Point &peer) const { return Point(x + peer.x, y + peer.y); }
  bool operator<(const Point &peer) const { return as_pair() < peer.as_pair(); }
  bool operator==(const Point &peer) const { return x == peer.x && y == peer.y; }
  bool operator!=(const Point &peer) const { return x != peer.x || y != peer.y; }
  Point abs() const { return Point(std::abs(x), std::abs(y)); }
  T norm2() const { return x * x + y * y; }
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
  T norm2() const { return (b - a).norm2(); }

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

struct PointSet {
  std::vector<P64> pts;
  P64 &get(int i) { return pts[i]; }
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
  template <typename T> static bool check_colinear(Point<T> pt, const std::vector<Point<T> > &lst) {
    std::unordered_set<std::pair<T, T> > mp;
    for (auto &e : lst) {
      if (pt == e) return false;
      auto dir = (std::max(e, pt) - std::min(e, pt)).simplify().as_pair();
      if (!mp.insert(dir).second) return false;
    }
    return true;
  }
  template <typename T>
  static std::vector<Point<T> > generate_points(int n, int lim, bool circle_like = false,
                                                bool allow_colinear = false) {
    std::uniform_int_distribution<> dis(-lim, lim);
    std::vector<Point<T> > pts;

    if (allow_colinear) {
      std::unordered_set<std::pair<T, T> > seen;
      REP (i, n) {
        while (true) {
          std::pair<T, T> p(dis(rng), dis(rng));
          if (seen.insert(p).second) {
            pts.emplace_back(p);
            break;
          }
        }
      }

    } else if (circle_like || TEST_LARGE) {
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

      std::unordered_set<int> seen;
      REP (i, n) {
        while (true) {
          Point<T> p(dis(rng), dis(rng));
          if (seen.count(p.x)) continue;
          if (check_colinear(p, pts)) {
            pts.pb(p);
            seen.insert(p.x);
            break;
          }
        }
      }
    }
    return pts;
  }
};

std::vector<int> compute_hull(const PointSet &ps, vi ids, bool upper) {
  std::sort(ALL(ids), [&](int a, int b) { return ps.get(a) < ps.get(b); });
  vi res;

  for (auto i : ids) {
    const auto &a = ps.get(i);
    while (res.size() >= 2) {
      int nx = res.size();
      if (((ps.get(res[nx - 2]) - a).cross(ps.get(res[nx - 1]) - a) > 0) ^ !upper)
        res.pop_back();
      else
        break;
    }
    res.pb(i);
  }
  return res;
}

struct DumbContext {
  typedef std::vector<vi> res_t;
  PointSet ps;
  int n;
  res_t res;

  bool check(const vi &tr1, const vi &tr2, bool inside = false) {
    REP (f, 3) {
      int f1 = (f + 1) % 3, f2 = (f + 2) % 3;
      auto seg = ps.get(tr1[f], tr1[f1]);

      std::map<int, int> cnt;
      bool sgn = std::signbit(seg.signed_dist(ps.get(tr1[f2])));

      REP (i, 3) {
        auto pt = ps.get(tr2[i]);
        auto d = seg.signed_dist(pt);
        if (d == 0)
          cnt[-1]++;
        else
          cnt[std::signbit(d) == sgn]++;
      }
      if (inside) {
        if (cnt[-1] > 1 || cnt[0] != 0) return false;

      } else if (cnt[-1] <= 1 && cnt[1] == 0)
        return true;
    }
    return inside;
  }

  bool is_good(const vi &tr) { return ps.get(tr[0], tr[1]).signed_dist(ps.get(tr[2])) != 0; }

  bool compat(const vi &tr1, const vi &tr2) {
    if (!is_good(tr1) || !is_good(tr2)) return false;
    return check(tr1, tr2) || check(tr2, tr1) || check(tr1, tr2, true) || check(tr2, tr1, true);
  }

  int get_id(int a, int b, int c) { return a * n * n + b * n + c; }
  vi get_vec(int id) {
    vi tb;
    REP (f, 3) tb.pb(id % n), id /= n;
    return tb;
  }
  std::unordered_map<pii, bool> edges;
  vi used;
  std::vector<int> rec_trs;

  void rec(int pos, vi cur) {
    if (cur.size() == 3) {
      auto vx = get_id(cur[0], cur[1], cur[2]);
      if (!is_good(get_vec(vx))) return;
      rec_trs.pb(vx);
      bool ok = true;
      REP (i, rec_trs.size() - 1) {
        int a = rec_trs[i];
        int b = rec_trs.back();
        if (a > b) std::swap(a, b);
        if (!edges[MP(a, b)]) {
          ok = false;
          break;
        }
      }
      if (ok) {
        if (res.size() < rec_trs.size()) {
          res.clear();
          for (auto x : rec_trs) res.pb(get_vec(x));
        }

        rec(0, {});
      }
      rec_trs.pop_back();
      return;
    }

    if (pos == n) return;
    if (!used[pos]) {
      cur.pb(pos);
      used[pos] = true;
      rec(pos + 1, cur);
      used[pos] = false;
      cur.pop_back();
    }

    rec(pos + 1, cur);
  }
  bool checkit(res_t res) {
    std::set<int> used;
    REP (i, res.size()) {
      if (!is_good(res[i])) return false;
      used.insert(ALL(res[i]));
      REP (j, i)
        if (!compat(res[j], res[i])) return false;
    }
    return used.size() == 3 * res.size();
  }

  res_t solve_dumb() {
    res.clear();
    vi all;
    REP (i, n) all.pb(i);
    if (n >= 13) assert(0);
    std::vector<int> trs;
    REP (i, n)
      REP (j, i)
        REP (k, j) trs.pb(get_id(k, j, i));

    used = vi(n, false);
    std::sort(ALL(trs));

    REP (i, trs.size())
      REP (j, i) {

        bool v = compat(get_vec(trs[j]), get_vec(trs[i]));
        edges[MP(trs[j], trs[i])] = v;
      }
    rec(0, {});
    return res;
  }

  void disp(const res_t &res) {
    printf("%lu\n", res.size());
    for (auto x : res) {
      for (auto y : x) printf("%d ", y + 1);
      puts("");
    }
  }
};

struct ColinearHelper {
  PointSet *ps;
  typedef u64 slope_t;
  std::vector<std::vector<int> > mp2slope;
  std::vector<std::unordered_map<int, int> > mp;
  std::vector<std::priority_queue<std::pair<int, int> > > bestx;
  std::vector<std::unordered_set<int> > dirty;
  int n;
  int bestv = -1;
  vi rem;

  void setup(PointSet *ps, bool init = true) {
    this->ps = ps;
    n = ps->pts.size();
    if (!init) return;
    mp.resize(n);
    std::unordered_map<slope_t, int> all_slopes;
    all_slopes.reserve(n * n);
    REP (i, n)
      REP (j, i) {
        all_slopes.emplace(get_slope0(i, j), all_slopes.size());
      }
    mp2slope.resize(n, vi(n, -1));

    REP (i, n)
      REP (j, i) mp2slope[i][j] = mp2slope[j][i] = all_slopes[get_slope0(i, j)];

    bestx.resize(n);
    dirty.resize(n);
    REP (a, n) rem.pb(a);

    REP (a, n) {
      REP (b, a) {
        auto sx = get_slope(a, b);
        mp[a][sx]++;
        mp[b][sx]++;
      }
    }

    REP (a, n) {
      std::vector<slope_t> thrash;
      for (auto &kv : mp[a]) {
        if (kv.second > 3)
          bestx[a].emplace(kv.second, kv.first);
        else
          thrash.pb(kv.first);
      }
      for (auto x : thrash) mp[a].erase(x);
    }
  }

  slope_t get_slope0(int i, int j) {
    auto slope = ps->get(i, j).slope();
    assert(std::abs(slope.p) < 2e9 + 10);
    assert(std::abs(slope.q) < 2e9 + 10);
    assert(slope.q >= 0);
    return ((u64)(u32)slope.p << 32) | (u32)slope.q;
  }

  int get_slope(int a, int b) { return mp2slope[a][b]; }

  vi get_max_colinear(int update_want = -1) {
    std::pair<int, std::pair<int, slope_t> > best(-1, {});
    checkmax(bestv, update_want);
    int nchange = 0;
    int nupdate = 0;
    for (auto b : rem) {
      auto &pq = bestx[b];
      if (!pq.size()) continue;
      if (pq.top().first >= std::min(best.first, bestv)) {
        ++nupdate;
        while (true) {
          auto e = pq.top();
          if (!dirty[b].count(e.second)) break;
          pq.pop();
          ++nchange;
          dirty[b].erase(e.second);
          int cntx = mp[b][e.second];
          if (cntx > 3) pq.emplace(cntx, e.second);
        }
      }
      if (!pq.size()) continue;
      auto &xx = pq.top();
      if (xx.first > best.first) best = MP(xx.first, MP(b, xx.second));
    }

    if (best.first == -1) {
      vi res;
      res.pb(rem[0]);
      res.pb(rem[1]);
      return res;
    }
    assert(best.first != -1);
    bestv = best.first;
    vi ans;
    for (auto a : rem) {
      if (a == best.second.first) continue;
      if (get_slope(a, best.second.first) == best.second.second) ans.pb(a);
    }
    ans.pb(best.second.first);
    // assert(are_colinear(ans));
    return ans;
  }

  void remove(int a) {
    if (!mp.size()) return;
    --bestv;

    REP (i, rem.size()) {
      if (rem[i] == a) {
        std::swap(rem[i], rem.back());
        rem.pop_back();
        break;
      }
    }
    for (auto b : rem) {
      auto slope = get_slope(b, a);
      if (mp[b].count(slope) && mp[b][slope]-- > 3) {
        dirty[b].emplace(slope);
      }
    }

    mp[a].clear();
  }

  vi get_max_colinear_dumb(const vi &pts) {
    vi best;
    REP (i, pts.size()) {
      int a = pts[i];
      std::unordered_map<slope_t, vi> mp;
      REP (j, i) {
        if (j == i) continue;
        int b = pts[j];
        mp[get_slope0(a, b)].pb(b);
      }
      for (auto &kv : mp)
        if (kv.second.size() + 1 > best.size()) {
          best = kv.second;
          best.pb(a);
        }
    }
    return best;
  }
  bool are_colinear(const vi &pts) {
    if (pts.size() <= 2) return true;
    auto s = ps->get(pts[0], pts[1]);
    FOR (i, 2, pts.size()) {
      if (s.signed_dist(ps->get(pts[i])) != 0) return false;
    }
    return true;
  }
};

struct SolverContext {
  typedef std::vector<vi> res_t;
  PointSet ps;
  int n;
  res_t res;
  ColinearHelper colinear;

  void read() {
    if (TEST_RAND) {
      n = rng() % 12 + 1;
      ps.pts.resize(n);
      std::unordered_set<P64> pts;
      int lim = 1e1;
      ps.pts = Generator::generate_points<s64>(n, lim, false, true);

    } else {
      g_reader.readline() >> n;
      ps.pts.resize(n);
      REP (i, n) g_reader.readline() >> ps.get(i).x >> ps.get(i).y;
    }
  }

  int find_cnd(const vi &lst, int p0, int p1) {
    // p0, p1: ccw desc, can have points on [p1, p0) but not on [p0, p1)

    int e0 = -1;
    auto seg = ps.get(p0, p1);
    for (auto i : lst)
      if (seg.signed_dist(ps.get(i)) != 0) {
        e0 = i;
        break;
      }

    if (e0 == -1) return -1;

    int target_sgn = !seg.ccw(ps.get(e0));
    int best = -1;
    for (auto p : lst) {
      if (p == p0 || p == p1) continue;
      if (seg.signed_dist(ps.get(p)) == 0) continue;
      bool change = false;
      if (best == -1)
        change = true;
      else {
        if (ps.get(p0, best).signed_dist(ps.get(p)) == 0) {
          change = (ps.get(p0, best).norm2() > ps.get(p0, p).norm2());
        } else if (ps.get(p0, best).ccw(ps.get(p)) == target_sgn)
          change = true;
      }
      if (change) best = p;
    }
    assert(best != -1);
    return best;
  }

  bool check(const vi &tr1, const vi &tr2, bool inside = false) {
    REP (f, 3) {
      int f1 = (f + 1) % 3, f2 = (f + 2) % 3;
      auto seg = ps.get(tr1[f], tr1[f1]);

      std::map<int, int> cnt;
      bool sgn = std::signbit(seg.signed_dist(ps.get(tr1[f2])));

      REP (i, 3) {
        auto pt = ps.get(tr2[i]);
        auto d = seg.signed_dist(pt);
        if (d == 0)
          cnt[-1]++;
        else
          cnt[std::signbit(d) == sgn]++;
      }
      if (inside) {
        if (cnt[-1] > 1 || cnt[0] != 0) return false;

      } else if (cnt[-1] <= 1 && cnt[1] == 0)
        return true;
    }
    return inside;
  }

  bool is_good(const vi &tr) { return ps.get(tr[0], tr[1]).signed_dist(ps.get(tr[2])) != 0; }

  bool compat(const vi &tr1, const vi &tr2) {
    if (!is_good(tr1) || !is_good(tr2)) return false;
    return check(tr1, tr2) || check(tr2, tr1) || check(tr1, tr2, true) || check(tr2, tr1, true);
  }

  void build_dumb(const vi &tb) {
    DumbContext dc;
    dc.n = tb.size();
    for (auto x : tb) dc.ps.pts.pb(ps.get(x));
    auto res = dc.solve_dumb();
    res_t rmp;
    for (auto tr : res) {
      vi rtr;
      for (auto x : tr) rtr.pb(tb[x]);
      rmp.pb(rtr);
    }
    this->res.insert(this->res.end(), ALL(rmp));
  }

  void build1(vi lined, vi targets) {
    if (lined.size() + targets.size() <= 9) {
      targets.insert(targets.end(), ALL(lined));
      return build_dumb(targets);
    }

    while (targets.size() > 3 && lined.size() > 3) {
      assert(lined.size() >= 2);
      int p1 = lined.back();
      lined.pop_back();
      int p0 = lined.back();
      lined.pop_back();
      int best = find_cnd(targets, p0, p1);
      assert(best != -1);

      res.pb({ p0, p1, best });
      REP (i, targets.size()) {
        if (targets[i] == best) {
          std::swap(targets[i], targets.back());
          targets.pop_back();
          break;
        }
      }
    }
    OPA_DISP0(lined.size(), targets.size(), res.size());
    if (lined.size() > 6) lined.resize(6);
    if (targets.size() > lined.size() * 2) targets.resize(lined.size() * 2);
    targets.insert(targets.end(), ALL(lined));
    OPA_DISP0(colinear.get_max_colinear_dumb(targets));
    build_dumb(targets);
    OPA_DISP0(lined.size(), targets.size(), res.size());
  }

  void compute(vi &sx) {
    int n = sx.size();
    if (sx.size() <= 9) {
      build_dumb(sx);
      return;
    }
    int maxtr = n / 3;
    auto cl1 = colinear.get_max_colinear(2 * maxtr - 10);

    if (maxtr * 2 < cl1.size() || n % 3 != 0) {
      REP (i, sx.size())
        if (sx[i] == cl1[0]) {
          std::swap(sx[i], sx.back());
          sx.pop_back();
          colinear.remove(cl1[0]);
          compute(sx);
          return;
        }
      assert(0);
    }

    if (maxtr * 2 == cl1.size() || maxtr * 2 == cl1.size() + 1) {
      // OPA_DISP0(n, cl1.size(), colinear.get_max_colinear_dumb(sx).size(), maxtr * 2 + 10);
      std::set<int> s_cl1(ALL(cl1));
      auto seg = ps.get(cl1[0], cl1[1]);
      std::sort(ALL(cl1), [&](int a, int b) {
        return seg.dir().dot(ps.get(cl1[0], a).dir()) < seg.dir().dot(ps.get(cl1[0], b).dir());
      });

      std::vector<int> sl[2];
      for (auto x : sx) {
        if (s_cl1.count(x)) continue;
        sl[std::signbit(seg.signed_dist(ps.get(x)))].pb(x);
      }

      int smallest = sl[0].size() < sl[1].size() ? 0 : 1;

      vi cl[2];

      REP (i, cl1.size())
        (i < 2 * sl[smallest].size() ? cl[smallest] : cl[smallest ^ 1]).pb(cl1[i]);
      build1(cl[smallest], sl[smallest]);
      build1(cl[smallest ^ 1], sl[smallest ^ 1]);

    } else {
      auto hull = compute_hull(ps, sx, true);
      // auto &hull = sx;
      int p0 = hull[1];
      int p1 = hull[0];
      int best = find_cnd(sx, p0, p1);
      assert(best != -1);
      // int best = hull[2];
      REP (i, sx.size()) {
        if (sx[i] == p0 || sx[i] == p1 || sx[i] == best) {
          std::swap(sx[i], sx.back());
          sx.pop_back();
          --i;
        }
      }

      res.pb({ p0, p1, best });
      for (auto x : res.back()) colinear.remove(x);
      compute(sx);
    }
  }

  void compute_with_split(vi &sx, vi colinear_set) {
    vi sides[2];
    auto seg = ps.get(colinear_set[0], colinear_set[1]);
    std::sort(ALL(colinear_set),
              [&](int a, int b) { return seg.dir().dot(ps.get(b) - ps.get(a)) < 0; });
    int cntx = 0;
    for (auto x : sx) {
      auto dst = seg.signed_dist(ps.get(x));
      if (dst != 0)
        sides[std::signbit(dst)].pb(x);
      else
        ++cntx;
    }
    assert(cntx == colinear_set.size());
    int smallest = sides[1].size() < sides[0].size();
    vi c1;
    REP (i, sides[smallest].size()) {
      REP (f, 2) {
        c1.pb(colinear_set.back());
        colinear_set.pop_back();
      }
    }

    std::reverse(ALL(c1));
    build1(c1, sides[smallest]);
    build1(colinear_set, sides[smallest ^ 1]);
  }

  void compute2(vi &sx, vi colinear_set) {
    if (sx.size() < 3) return;
    int p0, p1;
    int nx = colinear_set.size();
    if (nx < 2) {
      p0 = p1 = -1;
      for (auto i : sx)
        if (p0 == -1 || ps.get(i) < ps.get(p0)) p0 = i;

      for (auto i : sx)
        if (i != p0)
          if (p1 == -1 || ps.get(i) < ps.get(p1)) p1 = i;
      std::swap(p0, p1);

    } else {

      p1 = colinear_set.back();
      p0 = colinear_set[nx - 2];
    }
    int best = find_cnd(sx, p0, p1);
    if (best == -1) {
      p0 = sx[0];
      p1 = sx[1];
      while (sx.size() % 3 != 0) sx.pop_back();
      colinear_set = sx;

      auto seg = ps.get(p0, p1);
      while (true) {
        int maxtr = sx.size() / 3;
        if (maxtr * 2 - 1 >= colinear_set.size() || !res.size()) break;
        auto tr = res.back();
        res.pop_back();
        for (auto x : tr) {
          sx.pb(x);
          if (seg.signed_dist(ps.get(x)) == 0) colinear_set.pb(x);
        }
      }
      compute_with_split(sx, colinear_set);
      return;
    }

    // int best = hull[2];
    REP (i, sx.size()) {
      if (sx[i] == p0 || sx[i] == p1 || sx[i] == best) {
        std::swap(sx[i], sx.back());
        sx.pop_back();
        --i;
      }
    }

    res.pb({ p0, p1, best });
    compute2(sx, {});
  }

  res_t solve_slow() {
    colinear.setup(&ps);
    vi all;
    REP (i, n) all.pb(i);
    compute(all);
    assert(checkit(res));
    return res;
  }

  res_t solve() {
    colinear.setup(&ps, false);
    vi all;
    REP (i, n) all.pb(i);
    compute2(all, {});
    assert(checkit(res));
    return res;
  }

  int get_id(int a, int b, int c) { return a * n * n + b * n + c; }
  vi get_vec(int id) {
    vi tb;
    REP (f, 3) tb.pb(id % n), id /= n;
    return tb;
  }
  std::unordered_map<pii, bool> edges;
  vi used;
  std::vector<int> rec_trs;

  void rec(int pos, vi cur) {
    if (cur.size() == 3) {
      auto vx = get_id(cur[0], cur[1], cur[2]);
      if (!is_good(get_vec(vx))) return;
      rec_trs.pb(vx);
      bool ok = true;
      REP (i, rec_trs.size() - 1) {
        int a = rec_trs[i];
        int b = rec_trs.back();
        if (a > b) std::swap(a, b);
        if (!edges[MP(a, b)]) {
          ok = false;
          break;
        }
      }
      if (ok) {
        if (res.size() < rec_trs.size()) {
          res.clear();
          for (auto x : rec_trs) res.pb(get_vec(x));
        }

        rec(0, {});
      }
      rec_trs.pop_back();
      return;
    }

    if (pos == n) return;
    if (!used[pos]) {
      cur.pb(pos);
      used[pos] = true;
      rec(pos + 1, cur);
      used[pos] = false;
      cur.pop_back();
    }

    rec(pos + 1, cur);
  }
  bool checkit(res_t res) {
    std::set<int> used;
    REP (i, res.size()) {
      if (!is_good(res[i])) return false;
      used.insert(ALL(res[i]));
      REP (j, i)
        if (!compat(res[j], res[i])) {
          OPA_DISP0("Incompat ", j, i);
          OPA_DISP0(ps.pts.size());
          OPA_DISP0(res[i], res[j], i, j);
          for (auto x : res[j]) OPA_DISP0(ps.get(x), x);
          for (auto y : res[i]) OPA_DISP0(ps.get(y), y);
          OPA_DISP0(check(res[j], res[i], true), check(res[i], res[j], true), res[i], res[j]);
          return false;
        }
    }
    return used.size() == 3 * res.size();
  }

  res_t solve_dumb() {
    assert(n <= 12);
    res.clear();
    vi all;
    REP (i, n) all.pb(i);
    std::vector<int> trs;
    REP (i, n)
      REP (j, i)
        REP (k, j) trs.pb(get_id(k, j, i));

    used = vi(n, false);
    std::sort(ALL(trs));

    REP (i, trs.size())
      REP (j, i) {

        bool v = compat(get_vec(trs[j]), get_vec(trs[i]));
        edges[MP(trs[j], trs[i])] = v;
      }
    rec(0, {});
    return res;
  }

  void disp(const res_t &res) {
    printf("%lu\n", res.size());
    for (auto x : res) {
      for (auto y : x) printf("%d ", y + 1);
      puts("");
    }
  }
};

int main() {
  srand(0);
  int tn;

  g_precomp.setup();
  if (TEST_RAND)
    tn = 100000;
  else
    scanf("%d\n", &tn);

  REP (ti, tn) {

    SolverContext sc;
    sc.read();
    if (TEST_CHECK) {
      auto r1 = sc.solve();
      auto r2 = sc.solve_dumb();
      printf("Case #%d: ", ti + 1);
      OPA_DISP0(r1, r2);
      if (r1.size() != r2.size()) {
        printf("DUMB >> ");
        sc.disp(r2);
        printf("NORMAL >> ");
        sc.disp(r1);
        puts("");
        OPA_DISP0(sc.ps.pts);
        assert(r1.size() == r2.size());
      }
    } else {

      printf("Case #%d: ", ti + 1);
      auto res = sc.solve();
      // assert(sc.checkit(res));
      sc.disp(res);
    }
  }

  return 0;
}
