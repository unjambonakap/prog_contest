
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

#ifndef TEST_SINGLE
#define TEST_SINGLE 0
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
// #include <ext/hash_map>
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

#define OPA_TRACE0 fprintf(stderr, "%s:%s:%d\n", __FILE__, __func__, __LINE__)

#if OPA_HAS_STACKTRACE
#define OPA_PRINT_STACKTRACE()                                                                     \
  fprintf(stderr, "OPA_STACKTRACE_BEGIN: \n%s\nOPA_STACKTRACE_END\n",                              \
          opa::utils::get_stacktrace().c_str())
#else
#define OPA_PRINT_STACKTRACE()
#endif


#define OPA_LINE_INFO std::string(__FILE__) << ":" << __func__ << ":" << __LINE__

#define OPA_TRACE(msg, ...) fprintf(stderr, "%s\n", OPA_TRACE_STR(msg, __VA_ARGS__).c_str())

#define OPA_TRACES(...)                                                                            \
  fprintf(stderr,                                                                                  \
          "%s:%s:%d, msg=%s"                                                                       \
          "\n",                                                                                    \
          __FILE__, __func__, __LINE__, OPA_DISP_STR(__VA_ARGS__).c_str())

#define OPA_TRACE_STR(msg, ...)                                                                    \
  OPA_STREAM_STR(OPA_LINE_INFO << " msg=" << msg << " >> " << OPA_DISP_STR(__VA_ARGS__))

#define OPA_TRACEM(msg) fprintf(stderr, "%s:%s:%d, msg=" msg "\n", __FILE__, __func__, __LINE__)

#if OPA_DEBUG
#define OPA_ASSERT(cond, fmt, ...)                                                                 \
  do {                                                                                             \
    if (!(cond)) {                                                                                 \
      fprintf(stderr, "%s:%s:%d, err=%s: " fmt "\n", __FILE__, __func__, __LINE__, #cond,          \
              ##__VA_ARGS__);                                                                      \
      OPA_PRINT_STACKTRACE();                                                                      \
      assert(0);                                                                                   \
    }                                                                                              \
  } while (0)

#define OPA_ASSERTNO(cond, fmt, ...)                                                               \
  do {                                                                                             \
    if (!(cond)) {                                                                                 \
      fprintf(stderr, "%s:%s:%d, err=%s, errno=%s: " fmt "\n", __FILE__, __func__, __LINE__,       \
              #cond, strerror(errno), ##__VA_ARGS__);                                              \
      OPA_PRINT_STACKTRACE();                                                                      \
      assert(0);                                                                                   \
    }                                                                                              \
  } while (0)
#else
#define OPA_ASSERT(cond, fmt, ...) assert(cond);
#define OPA_ASSERTNO(cond, fmt, ...) assert(cond);
#endif

#define OPA_ASSERTNO0(cond) OPA_ASSERTNO(cond, "")
#define OPA_ASSERT0(cond) OPA_ASSERT(cond, "")

#define OPA_ABORT(cond, fmt, ...)                                                                  \
  do {                                                                                             \
    if (cond) {                                                                                    \
      fprintf(stderr, "Abort %s:%s:%d, err=%s: " fmt "\n", __FILE__, __func__, __LINE__, #cond,    \
              ##__VA_ARGS__);                                                                      \
      OPA_PRINT_STACKTRACE();                                                                      \
      std::abort();                                                                                \
    }                                                                                              \
  } while (0)

#define OPA_ABORTS(cond, ...)                                                                      \
  do {                                                                                             \
    if (cond) {                                                                                    \
      fprintf(stderr, "Abort %s:%s:%d, cond=%s, errno=%s: \n", __FILE__, __func__, __LINE__,       \
              #cond, strerror(errno));                                                             \
      fflush(stderr);                                                                              \
      std::cerr << RAW_OPA_DISP_VARS(__VA_ARGS__) << std::endl;                                    \
      OPA_PRINT_STACKTRACE();                                                                      \
      std::abort();                                                                                \
    }                                                                                              \
  } while (0)

#define OPA_ABORTNO(cond, fmt, ...)                                                                \
  do {                                                                                             \
    if (cond) {                                                                                    \
      fprintf(stderr, "Abort %s:%s:%d, err=%s, errno=%s: " fmt "\n", __FILE__, __func__, __LINE__, \
              #cond, strerror(errno), ##__VA_ARGS__);                                              \
      OPA_PRINT_STACKTRACE();                                                                      \
      std::abort();                                                                                \
    }                                                                                              \
  } while (0)
#define OPA_ABORT0(cond) OPA_ABORT(cond, "")
#define OPA_ABORTNO0(cond) OPA_ABORTNO(cond, "")

#define OPA_CHECK0(cond) OPA_ABORT0(!(cond))
#define OPA_CHECK(cond, ...) OPA_ABORTS(!(cond), __VA_ARGS__)
#define OPA_CHECKNO0(cond) OPA_ABORTNO0(!(cond))
#define OPA_CHECK_EQ0(a, b) OPA_ABORTS(!((a) == (b)), "Equality failure ", a, b)
#define OPA_CHECK_EQ(a, b, ...) OPA_ABORTS(!((a) == (b)), "Equality failure ", a, b, __VA_ARGS__)

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
  mutable char buf[111111];

  mutable std::istringstream iss;
  std::istringstream &readline() const {
    fgets(buf, sizeof(buf) - 1, stdin);
    iss = std::istringstream(buf);
    return iss;
  }
};
ReaderHelper g_reader;

const int mod = 1e9 + 7;
const int maxn = 333;
const int maxt = 1111;

struct Precomp {
  Precomp() {
    REP (i, maxn) {
      mulp[i][0] = 1;
      REP (j, maxn - 1) {
        mulp[i][j + 1] = 1ll * mulp[i][j] * (i + 1) % mod;
      }
    }
  }
  int mulp[maxn][maxn];
};
Precomp g_precomp;

s64 faste(s64 a, int p) {
  s64 x = 1;
  for (; p > 0; p >>= 1, a = 1ll * a * a % mod)
    if (p & 1) x = 1ll * x * a % mod;
  return x;
}

s64 inv(s64 x) { return faste(x, mod - 2); }
s64 negp(s64 x) { return (mod - x) % mod; }

int norm(const vi &p) {
  s64 v = 0;
  for (auto x : p) v += 1ll * x * x % mod;
  return v % mod;
}

vi normalize(const vi &p) {
  int in = inv(norm(p));
  auto res = p;
  for (auto &x : res) x = 1ll * x * in % mod;
  return res;
}

int dot(const vi &a, const vi &b) {
  s64 res = 0;
  REP (i, a.size()) res += 1ll * a[i] * b[i] % mod;
  return res % mod;
}

vi add(const vi &a, const vi &b) {
  vi res = a;
  REP (i, a.size()) res[i] = (a[i] + b[i]) % mod;
  return res;
}

vi mul(const vi &a, const vi &b) {
  vi res = a;
  REP (i, a.size()) res[i] = (1ll * a[i] * b[i]) % mod;
  return res;
}

vi mulc(const vi &a, s64 c) {
  vi res = a;
  REP (i, a.size()) res[i] = (a[i] * c) % mod;
  return res;
}

struct Matrix {
  int &operator()(int i, int j) { return data[i * n + j]; }
  int get(int i, int j) const { return data[i * n + j]; }
  vi col(int i) const {
    vi res(n);
    REP (j, n) res[j] = get(j, i);
    return res;
  }
  vi row(int i) const {
    vi res(n);
    REP (j, n) res[j] = get(i, j);
    return res;
  }

  Matrix() {}
  void resize(int n) {
    this->n = n;
    data.resize(n * n, 0);
  }
  Matrix(int n) { resize(n); }

  Matrix operator*(const Matrix &peer) const {
    Matrix res(n);
    REP (i, n)
      REP (j, n) {

        s64 v = 0;
        REP (k, n) v += s64(get(i, k)) * peer.get(k, j) % mod;
        res(i, j) = v % mod;
      }
    return res;
  }

  vi operator*(const vi &v) const {
    vi res(n, 0);
    REP (i, n)
      REP (j, n) res[i] = (res[i] + 1ll * v[j] * get(i, j)) % mod;
    return res;
  }

  static Matrix Ident(int n) {
    Matrix res(n);
    REP (i, n) res(i, i) = 1;
    return res;
  }

  Matrix inverse() const {
    Matrix res = Matrix::Ident(n);
    Matrix tmp = *this;
    REP (i, n) {
      int sel = i;
      while (tmp.get(sel, i) == 0) ++sel;
      REP (j, n) {
        std::swap(tmp(sel, j), tmp(i, j));
        std::swap(res(sel, j), res(i, j));
      }
      s64 mv = inv(tmp.get(i, i));
      REP (j, n) {
        res(i, j) = res(i, j) * mv % mod;
        tmp(i, j) = tmp(i, j) * mv % mod;
      }
      REP (j, n)
        if (j != i && tmp.get(j, i) != 0) {
          s64 cx = negp(tmp.get(j, i));
          REP (k, n) {
            tmp(j, k) = (tmp(j, k) + cx * tmp(i, k)) % mod;
            res(j, k) = (res(j, k) + cx * res(i, k)) % mod;
          }
        }
    }
    return res;
  }

  std::vector<std::vector<int> > eigenvecs_tri() const {
    std::vector<std::vector<int> > res(n, vi(n));

    std::vector<int> iev(n);

    REP (i, n) {
      std::vector<int> cur(n);
      res[i][i] = 1;
      REP (j, i) cur[j] = get(j, i);
      REPV (j, i) {
        if (cur[j] != 0) {
          s64 cx = negp(1ll * cur[j] * inv((j - i + mod)) % mod);
          res[i][j] = cx;
          REP (k, j + 1) cur[k] = (cur[k] + get(k, j) * cx) % mod;
        }
      }

      res[i] = normalize(res[i]);
    }

    return res;
  }

  int n;
  std::vector<int> data;
};

struct Query {
  int type;
  union {

    struct {
      int k, l, r;

    } q;
    struct {
      int i, x;

    } u;
  };
};
struct Data {
  vi tb;
  void push(const Data &peer, int dn = 0) {
    if (!peer.tb.size()) return;
    if (!tb.size()) tb.resize(peer.tb.size(), 0);
    tb = add(tb, peer.tb);
  }
  void reset() { tb.clear(); }
};

struct DataAgg {
  void reset() {}
  void push(const DataAgg &peer, int dn = 0) {}

  Data combine(const Data &d) const { return d; }
};

struct Node {
  Node *l, *r;
  int a, b;
  Data data;
  DataAgg agg;
  void norm() {
    if (l == nullptr) return;
    l->agg.push(agg);
    r->agg.push(agg, l->b - l->a + 1);
    agg.reset();
  }

  Data get_data() const { return agg.combine(data); }

  Data query(int low, int high) {
    Data res;
    if (low > b || high < a) return res;
    if (low <= a && b <= high) {
      return get_data();
    }

    res.push(l->query(low, high));
    res.push(r->query(low, high), l->b - l->a + 1);
    return agg.combine(res);
  }

  void recompute() {
    if (l == nullptr) return;
    data.reset();
    data.push(l->get_data());
    data.push(r->get_data(), l->b - l->a + 1);
  }

  void add1(int x, Data data, bool reset_agg = false) {
    if (x < a || b < x) return;
    if (l == nullptr) {
      this->data.push(data);
      if (reset_agg) agg.reset();
      return;
    }
    norm();
    l->add1(x, data, reset_agg);
    r->add1(x, data, reset_agg);
    recompute();
  }

  void add(int low, int high, DataAgg nd) {
    if (low > b || high < a) return;
    if (low <= a && b <= high) {
      agg.push(nd);
      return;
    }
    norm();
    l->add(low, high, nd);
    r->add(low, high, nd);
    recompute();
  }
};
struct SegTree {
  std::deque<Node> nodes;
  Node *root;
  Node *build1(int a, int b) {
    if (a > b) return nullptr;
    nodes.emplace_back();
    Node *cur = &nodes.back();
    cur->a = a;
    cur->b = b;
    if (a == b) return cur;
    int m = (a + b) / 2;
    cur->l = build1(a, m);
    cur->r = build1(m + 1, b);
    return cur;
  }

  void build(int n) { root = build1(0, n - 1); }
};

struct SolverContext {

  void read() {
    if (TEST_RAND) {

    } else {
    }
    g_reader.readline() >> n;
    v0.resize(n);
    mat.resize(n);
    g_reader.readline();
    REP (i, n) g_reader.iss >> v0[i];
    REP (i, n) mat(i, i) = i + 1;
    REP (i, n) {
      int nc;
      g_reader.readline() >> nc;
      REP (j, nc) {
        int a;
        g_reader.iss >> a;
        mat(i, a - 1) = a;
      }
    }

    int nq;
    g_reader.readline() >> nq;
    queries.resize(nq);
    REP (i, nq) {
      auto &q = queries[i];
      g_reader.readline() >> q.type;
      if (q.type == 1)
        g_reader.iss >> q.q.k >> q.q.l >> q.q.r, --q.q.l, --q.q.r;
      else
        g_reader.iss >> q.u.i >> q.u.x, --q.u.i;
    }
  }

  std::vector<int> solve() {
    vi res;
    auto evx = mat.eigenvecs_tri();

    Matrix ev2e(n);
    REP (i, n) {
      REP (j, n) ev2e(i, j) = evx[j][i];
    }
    Matrix e2ev = ev2e.inverse();

    std::vector<vi> csumv;
    vi cur(n, 0);
    csumv.pb(cur);
    REP (i, n) {
      cur = add(cur, ev2e.row(i));
      csumv.pb(cur);
    }
    Matrix imat = mat.inverse();

    std::vector<vi> pws(maxt + 1, vi(n));
    std::vector<vi> ipws(maxt + 1, vi(n));
    REP (i, n) {
      pws[0][i] = 1;
      ipws[0][i] = 1;
      int c = inv(i + 1);
      REP (j, maxt) pws[j + 1][i] = 1ll * pws[j][i] * (i + 1) % mod;
      REP (j, maxt) ipws[j + 1][i] = 1ll * ipws[j][i] * c % mod;
    }

    SegTree st;
    st.build(n + 1);
    dist.resize(n, vi(n, n));
    REP (i, n) {
      dist[i][i] = 0;
      REP (j, i) dist[j][i] = mat(j, i) ? 1 : n;
    }
    REP (i, n)
      REP (j, i)
        REP (k, j) checkmin(dist[k][i], dist[k][j] + dist[j][i]);

    vi active_at(n, n);
    REPV (i, n) {
      if (v0[i] > 0) {
        active_at[i] = 0;
        REP (j, i) checkmin(active_at[j], active_at[i] + dist[j][i]);
      }
    }
    auto v0mod = v0;
    REP (i, n) v0mod[i] = (mod + v0mod[i]) % mod;

    REP (i, n) {
      if (active_at[i] < n) {
        st.root->add1(active_at[i],
                      Data{ .tb = mul(mulc(e2ev.col(i), v0mod[i]), ipws[active_at[i]]) });
      }
    }

    for (auto &q : queries) {
      if (q.type == 2) {
        std::queue<int> ql;
        if (v0[q.u.i] + q.u.x > 0 && active_at[q.u.i] > 0) {
          REP (j, q.u.i + 1)
            if (active_at[j] > dist[j][q.u.i]) {
              st.root->add1(active_at[j], Data{ .tb = mul(mulc(e2ev.col(j), negp(v0mod[j])),
                                                          ipws[active_at[j]]) });
              active_at[j] = dist[j][q.u.i];
              st.root->add1(active_at[j],
                            Data{ .tb = mul(mulc(e2ev.col(j), v0mod[j]), ipws[active_at[j]]) });
            }
          v0[q.u.i] += q.u.x;
          v0mod[q.u.i] = (v0mod[q.u.i] + q.u.x) % mod;
        }
        if (active_at[q.u.i] < n)
          st.root->add1(active_at[q.u.i],
                        Data{ .tb = mul(mulc(e2ev.col(q.u.i), q.u.x), ipws[active_at[q.u.i]]) });

      } else {
        s64 v = 0;
        auto tmp = st.root->query(0, q.q.k).tb;
        tmp = mul(tmp, pws[q.q.k]);
        v = (mod + dot(csumv[q.q.r + 1], tmp) - dot(csumv[q.q.l], tmp)) % mod;
        FOR (i, q.q.l, q.q.r + 1)
          if (active_at[i] > q.q.k) v += v0[i];

        res.pb((v + mod) % mod);
      }
    }

    return res;
  }

  std::vector<int> solve_dumb() { return {}; }
  int n;
  std::vector<vi> dist;
  std::vector<int> v0;
  std::vector<Query> queries;
  Matrix mat;
};

int main() {
  srand(0);
  int tn;

  if (TEST_RAND)
    tn = 10000;
  else if (TEST_SINGLE)
    tn = 1;
  else
    scanf("%d\n", &tn);

  REP (ti, tn) {

    SolverContext sc;
    sc.read();
    if (TEST_CHECK) {
      auto rsolve = sc.solve();
      auto rdumb = sc.solve_dumb();
      OPA_DISP0(rsolve, rdumb);
      if (rsolve != rdumb) {
        printf("Case #%d: ", ti + 1);
        OPA_DISP0(rsolve, rdumb);
        puts("");
        assert(rsolve == rdumb);
      }
    } else {

      if (!TEST_SINGLE) printf("Case #%d: ", ti + 1);
      auto res = sc.solve();
      for (auto x : res) printf("%d\n", x);
    }
  }

  return 0;
}
