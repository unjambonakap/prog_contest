
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
  Segment(Point<T> _a, Point<T> _b) : a(_a), b(_b) {
    if (a.x > b.x) std::swap(a, b);
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
const int mod = 1e9 + 7;
const int maxl = 6;
const int maxm = 33;
const int maxn = 33;

int faste(s64 a, int p) {
  s64 x = 1;
  for (; p; p >>= 1, a = a * a % mod)
    if (p & 1) x = a * x % mod;
  return x;
}

int inv(int a) { return faste(a, mod - 2); }

struct Matrix {
  int m[2 * maxm][2 * maxm];
  int nr, nc;
  static Matrix Identity(int n) {
    auto res = Matrix();
    res.nr = res.nc = n;
    REP (i, n)
      REP (j, n)
        res.m[i][j] = i == j;
    return res;
  }
  Matrix operator*(const Matrix &peer) const {
    Matrix res;
    res.nr = nr;
    res.nc = peer.nc;
    REP (i, nr)
      REP (j, peer.nc) {
        int x = 0;
        REP (k, nc)
          x = (x + 1ll * m[i][k] * peer.m[k][j]) % mod;
        res.m[i][j] = x;
      }
    return res;
  }

  Matrix inv() const;
};

namespace std {
std::ostream &operator<<(std::ostream &os, const Matrix &a) {
  REP (i, a.nr) {
    REP (j, a.nc)
      os << a.m[i][j] << ' ';
    os << std::endl;
  }
  return os;
}
} // namespace std

Matrix Matrix::inv() const {
  assert(nr == nc);
  int n = nr;
  Matrix res = Matrix::Identity(n);
  Matrix work = *this;

  REP (i, n) {
    int pivot = -1;
    FOR (j, i, n)
      if (work.m[j][i]) {
        pivot = j;
        break;
      }
    REP (j, n) {
      std::swap(work.m[pivot][j], work.m[i][j]);
      std::swap(res.m[pivot][j], res.m[i][j]);
    }
    int u = ::inv(work.m[i][i]);
    assert(u != 0);
    REP (k, n) {
      work.m[i][k] = 1ll * work.m[i][k] * u % mod;
      res.m[i][k] = 1ll * res.m[i][k] * u % mod;
    }
    REP (j, n)
      if (j != i) {
        int mulc = (mod - work.m[j][i]) % mod;
        REP (k, n) {
          work.m[j][k] = (work.m[j][k] + 1ll * work.m[i][k] * mulc) % mod;
          res.m[j][k] = (res.m[j][k] + 1ll * res.m[i][k] * mulc) % mod;
        }
      }
  }
  return res;
}
struct PolyFinder {
  Matrix imat;
  Matrix mat;
  void setup(int deg) {
    int n = deg + 1;
    mat.nr = mat.nc = n;
    REP (i, n)
      mat.m[i][0] = 1;
    FOR (j, 1, n)
      REP (i, n)
        mat.m[i][j] = 1ll * mat.m[i][j - 1] * (3 * i + 1) % mod;
    imat = mat.inv();
  }

  std::vector<int> find(const std::function<int(int)> &evalf) {

    Matrix b;
    b.nr = mat.nc;
    b.nc = 1;
    REP (i, b.nr)
      b.m[i][0] = evalf(mat.m[i][1]);
    auto res = imat * b;
    vi coeffs;
    REP (i, mat.nr)
      coeffs.pb(res.m[i][0]);
    return coeffs;
  }

  int eval(const vi &poly, int v) {
    s64 res = 0;
    s64 x = 1;
    REP (i, poly.size()) {
      res = (res + poly[i] * x) % mod;
      x = x * v % mod;
    }
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
  int n, m, L;
  vi al;
  PolyFinder pf;

  std::unordered_map<pii, int> poly2val;

  int get_val(const pii &tg) {
    if (poly2val.count(tg)) return poly2val[tg];

    std::function<int(int)> func = [&](int nx) {
      s64 v = 0;
      FOR (i, 1, nx + 1)
        v = (v + 1ull * faste(i - 1, tg.first) * faste(nx + 1 - i, tg.second)) % mod;
      return (int)v;
    };
    auto poly = pf.find(func);
    int fullv = pf.eval(poly, m);
    assert(fullv >= 0);
    return poly2val[tg] = fullv;
  }

  void read() {
    if (TEST_RAND) {
      L = 4;
      n = rng() % std::min(1 << L, 8) + 2;
      m = rng() % 5 + 1;
      al.resize(1 << L);
      REP (i, 1 << L)
        al[i] = rng() % n;

    } else {
      readline() >> n >> m >> L;
      al.resize(1 << L);
      readline();
      REP (i, 1 << L)
        iss >> al[i], --al[i];
    }
    pf.setup(n + 2);
  }
  vi par;
  std::vector<vi> groups;
  std::vector<vi> group_al;
  std::vector<int> dp[maxl + 1][2];

  int root(int a) { return par[a] < 0 ? a : par[a] = root(par[a]); }
  void join(int a, int b) {
    a = root(a);
    b = root(b);
    if (a != b) par[a] = b;
  }

  // max on even
  inline int op(int depth, int a, int b) {
    if (depth & 1) return std::min(a, b);
    return std::max(a, b);
  }

  std::vector<int> list_choices(int depth, int v) {
    auto &r = dp[depth][v];
    if (r.size()) return r;
    if (depth == L - 1) {
      r.pb(v);
      return r;
    }

    int shift = 1 << (L - 2 - depth);
    REP (lv, 2)
      REP (rv, 2) {
        if (op(depth, lv, rv) != v) continue;
        auto lc = list_choices(depth + 1, lv);
        auto rc = list_choices(depth + 1, rv);
        for (auto a : lc)
          for (auto b : rc) {
            r.pb(a | (b << shift));
          }
      }
    return r;
  }

  struct State {
    vi fixcount;
    vi val;
    std::unordered_map<pii, int> cnt;
    u32 target;
    vi group;
    int gid;

    State() {
      fixcount.resize(maxn, 0);
      val.resize(maxn, 0);
    }
  };

  void rec(State &s, int pos) {
    if (pos == s.group.size()) {
      pii cur{};
      for (auto &ax : group_al[s.gid]) {
        if (s.val[ax] == 0)
          ++cur.ST;
        else
          ++cur.ND;
      }
      ++s.cnt[cur];
      return;
    }
    int node = s.group[pos];
    assert(node<=30);
    int l = al[node * 2];
    int r = al[node * 2 + 1];
    int v = (s.target >> node) & 1;
    REP (lv, 2)
      REP (rv, 2) {
        if (op(L - 1, lv, rv) != v) continue;
        if (s.fixcount[l] && lv != s.val[l]) continue;
        if (s.fixcount[r] && rv != s.val[r]) continue;
        if (l == r && lv != rv) continue;

        ++s.fixcount[l];
        ++s.fixcount[r];
        s.val[l] = lv;
        s.val[r] = rv;
        rec(s, pos + 1);

        --s.fixcount[l];
        --s.fixcount[r];
      }
  }

  vi group_mask;
  std::unordered_map<int, std::unordered_map<pii, int> > dp2[maxn];

  std::unordered_map<pii, int> &query(int group, int target) {
    target = group_mask[group] & target;
    std::unordered_map<pii, int> &r = dp2[group][target];
    if (r.size() > 0) return r;
    State s;
    s.target = target;
    s.group = groups[group];
    s.gid = group;
    rec(s, 0);
    r = s.cnt;
    return r;
  }

  int solve() {
    int nl = 1 << L;
    par.resize(n, -1);
    REP (i, nl / 2)
      join(al[2 * i], al[2 * i + 1]);
    std::map<int, std::set<int> > rmp;
    std::set<int> seen(ALL(al));
    REP (i, nl)
      rmp[root(al[i])].insert(i / 2);

    std::vector<vi> tmpgroups;
    for (auto &kv : rmp) {
      tmpgroups.emplace_back(ALL(kv.second));
    }
    std::sort(ALL(tmpgroups));
    std::set<int> cural;
    for (auto &g : tmpgroups) {

      std::set<int> alx;
      for (auto x : g) alx.insert(al[2 * x]), alx.insert(al[2 * x + 1]);

      if (groups.size() == 0 || alx.size() + cural.size() >= 0) {
        groups.pb(g);
        group_al.emplace_back();
        cural = alx;
      } else {
        cural.insert(ALL(alx));
        groups.back().insert(groups.back().end(), ALL(g));
      }
      group_al.back().insert(group_al.back().end(), ALL(alx));
    }

    group_mask.resize(groups.size(), 0);
    REP (gid, groups.size()) {
      int mask = 0;
      for (auto &e : groups[gid]) mask |= 1 << e;
      group_mask[gid] = mask;
    }

    auto canlist = list_choices(0, 1);

    s64 res = 0;
    REP (i, canlist.size()) {
      auto &c = canlist[i];

      std::unordered_map<pii, int> cur;
      cur[MP(0, 0)] = 1;

      REP (gid, groups.size()) {
        const auto &v = query(gid, c);
        std::unordered_map<pii, int> nc;
        for (auto &a : cur)
          for (auto &b : v) nc[a.ST + b.ST] = (nc[a.ST+b.ST] + 1ull * a.ND * b.ND) % mod;
        cur = nc;
      }
      for (auto x : cur) {
        res = res + 1ull * get_val(x.first) * x.second % mod;
      }
    }
    res %= mod;
    REP (i, n)
      if (!seen.count(i)) res = res * m % mod;

    return res % mod;
  }

  int rec_dumb(vi &state, int pos) {
    if (pos == n) {
      vi cur(1 << L);
      REP (i, 1 << L)
        cur[i] = state[al[i]];
      REPV (j, L) {
        vi ns;
        REP (k, 1 << j)
          ns.pb(op(j, cur[2 * k], cur[2 * k + 1]));
        cur = ns;
      }
      return cur[0];
    }
    int res = 0;

    FOR (i, 1, m + 1) {
      state[pos] = i;
      res = (res + rec_dumb(state, pos + 1)) % mod;
    }
    return res;
  }

  int solve_dumb() {
    vi sx(n, 0);
    //return rec_dumb(sx, 0);

    int res = 0;
    for (s64 s=0; s < 1ull<<(1<<L); ++s){
      int w = s;
      REPV (j, L) {
        int ns = 0;
        REP (k, 1 << j)
          ns |= op(j, w >> (2 * k) & 1, w >> (2 * k + 1) & 1) << k;
        w = ns;
      }
      if (w != 1) continue;
      std::map<int, std::set<int> > vals;
      REP (i, n)
        vals[i];
      REP (i, 1 << L)
        vals[al[i]].insert(s >> i & 1);
      int cur = 1;
      pii cx = {};
      for (auto x : vals) {
        if (x.second.size() == 2)
          cur = 0;
        else if (x.second.size() == 0)
          cur = 1ull * cur * m % mod;
        else if (*x.second.begin() == 0)
          ++cx.first;
        else
          ++cx.second;
      }
      cur = 1ull * cur * get_val(cx) % mod;
      res = (res + cur) % mod;
    }
    return res;
  }
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
    if (TEST_CHECK) {
      auto r1 = sc.solve();
      auto r2 = sc.solve_dumb();
      OPA_DISP0(r1, r2);
      if (r1 != r2) {
        printf("Case #%d: ", ti + 1);
        OPA_DISP0(r1, r2);
        puts("");
        assert(r1 == r2);
      }
    } else {

      printf("Case #%d: ", ti + 1);
      auto res = sc.solve();
      printf("%d", res);
      puts("");
    }
  }

  return 0;
}
