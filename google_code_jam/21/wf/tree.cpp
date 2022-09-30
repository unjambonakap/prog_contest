
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

template <class T> T faste(T a, u64 p, T ident) {
  T x = ident;
  for (; p; p >>= 1, a = a * a)
    if (p & 1) x = a * x;
  return x;
}

namespace matrixmod {
const int maxn = 55;
const s64 oo = 2e18;
struct Matrix {
  s128 m[maxn][maxn];
  int nr = -1, nc = -1;
  static Matrix Identity(int n) {
    auto res = Matrix();
    res.nr = res.nc = n;
    REP (i, n)
      REP (j, n)
        res.m[i][j] = i == j;
    return res;
  }

  Matrix() {}
  Matrix(int n) {
    nr = nc = n;
    REP (i, n)
      REP (j, n)
        m[i][j] = 0;
  }

  Matrix operator*(const Matrix &peer) const {
    if (peer.nc == -1) return *this;
    if (nc == -1) return peer;
    Matrix res;
    res.nr = nr;
    res.nc = peer.nc;
    REP (i, nr)
      REP (j, peer.nc) {
        s128 x = 0;
        REP (k, nc) {
          x = x + m[i][k] * peer.m[k][j];
          checkmin<s128>(x, oo);
        }
        res.m[i][j] = x;
      }
    return res;
  }
  std::vector<s64> eval(const std::vector<s64> &in) const {
    std::vector<s64> res(nr, 0);
    REP (r, nr) {
      s128 e = 0;
      REP (c, nc) {
        e = e + m[r][c] * in[c];
        checkmin<s128>(e, oo);
      }
      res[r] = e;
    }
    return res;
  }
};
} // namespace matrixmod
namespace std {
std::ostream &operator<<(std::ostream &os, const matrixmod::Matrix &a) {
  REP (i, a.nr) {
    REP (j, a.nc)
      os << a.m[i][j] << ' ';
    os << std::endl;
  }
  return os;
}
} // namespace std

std::mt19937 rng(0);
std::mt19937_64 rng_64(0);
struct ReaderHelper {
  mutable char buf[111111];

  mutable std::istringstream iss;
  std::istringstream &readline() const {
    fgets(buf, sizeof(buf) - 1, stdin);
    iss = std::istringstream(buf);
    return iss;
  }
};
ReaderHelper g_reader;

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
  int n() const { return last.size(); }
  bool digraph = false;

  void setup_flow(int n, bool use_cost) {
    this->use_cost = use_cost;
    N = n + 2;
    S = n;
    T = n + 1;
    consider(N - 1);
  }

  void setup_digraph(int n = 0) {
    consider(n - 1);
    digraph = true;
  }
  void consider(int x) {
    if (n() <= x) last.resize(x + 1, -1);
  }

  vi next(int a) const {
    vi res;
    assert(a < last.size());
    for (int i = last[a]; i != -1; i = el[i].prev) res.pb(el[i].to);
    return res;
  }

  int adde(int a, int b, int c = 0, int cap = 0, int rev = 0) {
    consider(std::max(a, b));
    int id = el.size();
    Edge e;
    assert(a >= 0);
    e.from = a;
    e.to = b;
    e.cost = c;
    e.cap = cap;
    e.prev = last[a];
    e.id = id;
    el.pb(e);
    last[a] = id;

    if (!digraph && !rev) adde(b, a, -c, 0, 1);
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
        assert(eid < el.size());
        auto &e = el[eid];
        if (e.cap <= 0) continue;
        assert(e.to < N);
        if (push(e.to, c + e.cost)) par[e.to] = eid;
      }
    }

    if (par[T] == -1) return -1;
    int res = 0;
    int x = T;
    while (x != S) {
      assert(par[x] >= 0);
      auto &e = el[par[x]];
      x = e.from;
      res += e.cost;
      --e.cap;
      el[e.id ^ 1].cap++;
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

struct SCCDecomp {
  Graph *graph;
  Graph sccgraph;
  std::vector<vi> scc;
  vi v2scc;
  vi vis;
  vi stk;
  int visid;

  int dfs(int a) {
    if (vis[a]) return vis[a];
    int curid = vis[a] = visid++;
    int pos = stk.size();
    stk.pb(a);
    vi el;
    for (auto b : graph->next(a)) checkmin(vis[a], dfs(b));

    if (vis[a] == curid) {
      int scid = scc.size();
      scc.emplace_back(stk.begin() + pos, stk.end());
      for (auto x : scc.back()) v2scc[x] = scid, vis[x] = INT_MAX;

      std::unordered_set<int> e_scc;
      for (auto x : scc.back()) {
        for (auto b : graph->next(x)) e_scc.insert(v2scc[b]);
      }
      sccgraph.consider(scid);
      e_scc.erase(scid);
      for (auto x : e_scc) sccgraph.adde(scid, x);
      stk.resize(pos);
    }
    return vis[a];
  }

  void setup(Graph *g) {
    graph = g;
    sccgraph.setup_digraph();
    vis.resize(graph->n(), 0);
    v2scc.resize(graph->n(), -1);
    visid = -1;
    REP (i, graph->n()) {
      if (!vis[i]) {
        visid -= graph->n();
        dfs(i);
      }
    }
  }
};

struct PwHelper {
  std::vector<matrixmod::Matrix> pwmats;
  void setup(matrixmod::Matrix start, int npw)  {
    pwmats.pb(start);
    REP (i, npw)
      pwmats.pb(pwmats.back() * pwmats.back());
  }
  std::vector<s64> eval(s64 pw, std::vector<s64> state)  const {
    REP (i, pwmats.size()) {
      if (pw >> i & 1) state = pwmats[i].eval(state);
    }
    return state;
  }

  s64 eval(s64 pw, std::vector<s64> state, int idx)  const {
    return eval(pw, state)[idx];
  }
};

struct SolverContext {
  int n;
  std::vector<pii> next;
  s64 a, b;
  Graph g;
  SCCDecomp sccg;
  const int startid = 1;
  const s64 inf = 1e18;
  int cntid() { return n + 1; }
  PwHelper cum_mat, depth_mat;

  void read() {
    if (TEST_RAND) {
      s64 lim1 = 1e18 - 10;
      lim1 = 1e5 - 10;
      a = rng_64() % lim1 + 1;
      b = rng_64() % lim1 + 1;
      b += 2;
      n = rng() % 5 + 1;
      next.resize(n);
      REP (i, n) {
        next[i].ST = rng() % (n + 1);
        next[i].ND = rng() % (n + 1);
      }

    } else {
      g_reader.readline() >> n >> a >> b;
      next.resize(n);
      g_reader.readline();
      REP (i, n)
        g_reader.iss >> next[i].ST;
      g_reader.readline();
      REP (i, n)
        g_reader.iss >> next[i].ND;
      ;
    }
  }
  matrixmod::Matrix build_mat(bool cumulative) {
    matrixmod::Matrix m(n + 2);
    REP (i, n) {
      ++m.m[next[i].ST][i + 1];
      ++m.m[next[i].ND][i + 1];
      m.m[cntid()][i + 1] = 2;
    }
    m.m[cntid()][cntid()] = cumulative;
    return m;
  }

  std::vector<s64> unit_vec(int pos) {
    std::vector<s64> v(n + 2, 0);
    v[pos] = 1;
    return v;
  }

  s64 count_depth(s64 depth, const std::vector<s64> &sv) {
    if (depth < 0) return 0;
    if (depth == 0) return 1;
    return depth_mat.eval(depth, sv, cntid());
  }

  s64 count_depth(s64 depth, int from) {
    if (depth < 0) return 0;
    if (depth == 0) return 1;
    return count_depth(depth, unit_vec(from));
  }

  s64 count_depth_le(s64 depth, int from) {
    if (depth < 0) return 0;
    if (depth == 0) return 1;
    return cum_mat.eval(depth, unit_vec(from), cntid()) + 1;
  }

  s64 get_depth(s64 num) {
    s64 T = 0, H = inf;
    s64 res = -1;
    while (T <= H) {
      s64 M = (T + H) / 2;
      if (count_depth_le(M, startid) >= num)
        res = M, H = M - 1;
      else
        T = M + 1;
    }
    return res;
  }
  struct State {
    s64 a;
    s64 b;
    s64 da, db;
    bool valid() const { return da >= 0 && db >= 0 && a >= 0 && b >= 0; }
  };

  s64 solve_sim(int pos, State s, bool force_dumb = false) {
    assert(pos != 0);
    if (s.da == 0 || s.db == 0) return s.da + s.db;
    int sx = sccg.v2scc[pos];
    while (sccg.v2scc[pos] == sx) {
      if (s.da == 0 || s.db == 0) return s.da + s.db;
      assert(pos != 0);
      int l = next[pos - 1].first;
      int r = next[pos - 1].second;
      s64 ra = count_depth(s.da - 1, l);
      s64 rb = count_depth(s.db - 1, l);
      if ((s.a < ra) != (s.b < rb)) return s.da + s.db;
      --s.da;
      --s.db;
      if (s.a < ra)
        pos = l;
      else {
        pos = r;
        s.a -= ra;
        s.b -= rb;
      }
    }
    return solveit(pos, s, force_dumb);
  }

  State compute_ns(int pos, const PwHelper &cyclem, State s, s64 ncycles,
                   bool advance = false) {
    int nx = sccg.scc[sccg.v2scc[pos]].size();

    auto sv = cyclem.eval(ncycles, unit_vec(pos));
    s.da -= ncycles * nx;
    s.db -= ncycles * nx;
    if (advance) sv[pos] = 0;
    s.a -= count_depth(s.da, sv);
    s.b -= count_depth(s.db, sv);
    //OPA_DISP0(s.a, s.b, s.da, s.db, ncycles);
    return s;
  }

  s64 find_ncycle_length(int pos, const PwHelper &cyclem, const State &s) {
    int nx = sccg.scc[sccg.v2scc[pos]].size();

    s64 T = 1;
    s64 H = std::min(s.da - 1, s.db - 1) / nx;
    s64 nc = H;
    while (T <= H) {
      s64 M = (T + H) >> 1;
      auto ns1 = compute_ns(pos, cyclem, s, M, true);
      auto ns2 = compute_ns(pos, cyclem, s, M, false);
      if ((ns1.a < 0) || (ns1.b < 0))
        H = M - 1, nc = M;
      else {
        if (ns2.a >= 0 || ns2.b >= 0) H = M - 1, nc = M;
        else T = M + 1;
      }
    }
    return nc - 1;
  }

  s64 solveit(int pos, const State &s, bool force_dumb = false) {
    if (pos == 0) {
      return -1;
      assert(0);
    }
    bool has_double = false;
    int sx = sccg.v2scc[pos];
    int nx = sccg.scc[sx].size();
    for (auto x : sccg.scc[sx])
      has_double |= sccg.v2scc[next[x - 1].first] == sx && sccg.v2scc[next[x - 1].second] == sx;
    if (std::min(s.da, s.db) < 2 * nx || has_double || force_dumb)
      return solve_sim(pos, s, force_dumb);

    matrixmod::Matrix tsfmat = build_mat(false);
    REP (i, tsfmat.nr)
      for (auto x : sccg.scc[sx]) tsfmat.m[i][x] = 0;

    auto mat = matrixmod::Matrix::Identity(n + 2);
    int x = pos;
    REP (i, nx) {
      int l = next[x - 1].first;
      int r = next[x - 1].second;
      int nxp, other;
      if (sccg.v2scc[l] == sx)
        nxp = l, other = r;
      else
        nxp = next[x - 1].second, other = l;

      if (other == l) tsfmat.m[l][x] = 1;
      tsfmat.m[nxp][x] = 1;
      mat = tsfmat * mat;
      tsfmat.m[nxp][x] = 0;
      tsfmat.m[l][x] = 0;
      x = nxp;
    }

    PwHelper pwx;
    pwx.setup(mat, two_pow64(std::min(s.da, s.db)/nx)+1);
    s64 nc = find_ncycle_length(pos, pwx, s);
    State ns = compute_ns(pos, pwx, s, nc, true);
    //OPA_DISP0(nc, pos, mat);
    // OPA_DISP0(pos, ns.a, ns.b, ns.da, ns.db);
    return solve_sim(pos, ns);
  }

  void setup() {
    cum_mat.setup(build_mat(true), two_pow64(inf) + 1);
    depth_mat.setup(build_mat(false), two_pow64(inf) + 1);
    g.setup_digraph(n + 1);
    REP (i, next.size())
      g.adde(i + 1, next[i].ST), g.adde(i + 1, next[i].ND);
  }

  s64 solve(bool force_dumb = false) {
    if (a == b) return 0;
    State s;
    s.da = get_depth(a);
    s.db = get_depth(b);
    if (s.da == -1 || s.db == -1) return -1;
    // if (s.da == -1 || s.db == -1) return -1;
    s.a = a - count_depth_le(s.da - 1, startid) - 1;
    s.b = b - count_depth_le(s.db - 1, startid) - 1;
    sccg.setup(&g);
    s64 r1 = solveit(1, s, force_dumb);
    return r1;
  }
  s64 solve_dumb() { return solve(true); }
};

int main() {
  srand(0);
  int tn;

  if (TEST_RAND)
    tn = 10000;
  else
    scanf("%d\n", &tn);

  REP (ti, tn) {

    SolverContext sc;
    sc.read();
    if (0 && ti != 7826) continue;
    sc.setup();
    OPA_DISP0(ti);
    if (TEST_CHECK) {
      auto r1 = sc.solve();
      auto r2 = sc.solve_dumb();
      OPA_DISP0(r1, r2);
      if (r1 != r2) {
        printf("Case #%d: ", ti + 1);
        OPA_DISP0(r1, r2);
        OPA_DISP0(sc.next, sc.a, sc.b, sc.n, sc.sccg.v2scc);
        puts("");
        assert(r1 == r2);
      }
    } else {

      printf("Case #%d: ", ti + 1);
      auto res = sc.solve();
      printf("%Ld", res);
      puts("");
    }
  }

  return 0;
}
