
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
struct Query {
  char type;
  int l, r, m;
};
const int maxn = 3e4 + 11;
struct Bitset {
  std::vector<u64> tb;
  int n;
  int nb;
  u64 mask_last;

  void setup(int n) {
    this->n = n;
    nb = (n + 63) / 64;
    mask_last = u64(-1) >> (nb * 64 - n);

    tb.resize(nb);
  }
  void toggle(int pos) { tb[pos / 64] ^= 1ull << (pos & 63); }

  Bitset &operator^=(const Bitset &peer) {
    REP (i, nb)
      tb[i] ^= peer.tb[i];
    return *this;
  }

  int find_single_unset() const {
    int pos = -1;
    REP (i, nb - 1) {
      if (tb[i] != -1) {
        if (pos != -1) return -1;
        pos = i;
      }
    }

    if (pos != -1 && tb.back() != mask_last) return -1;
    u64 m = 0;
    if (pos == -1) {
      pos = nb - 1;
      m = (tb.back() ^ -1) & mask_last;
    } else
      m = tb[pos] ^ -1;
    if (!m || ((m - 1) & m) != 0) return -1;
    return two_pow64(m) + 64 * pos;
  }
};
constexpr int kHashSize = 2;
struct Hash {
  std::vector<u64> hl;
  Hash() : hl(kHashSize, 0) {}
  void smix(const Hash &peer) {
    REP (i, kHashSize)
      hl[i] ^= peer.hl[i];
  }
};

struct Data {
  int n, m, nq;
  std::vector<pii> el;

  pii get_e(int id) const {
    --id;
    if (id < 0 || id >= el.size()) return {};
    return el[id];
  }
  void setup() {
    REP (i, n) {
      vhl.emplace_back();
      REP (j, kHashSize)
        vhl.back().hl[j] = rng_64();
      rmp[vhl.back().hl] = i;
    }
  }
  std::vector<Hash> vhl;
  std::unordered_map<std::vector<u64>, int> rmp;
};

struct Block {
  Hash degi;
  Hash dego;
  const Data *data;
  void setup(const Data *data) { this->data = data; }

  void update(pii e) {
    degi.smix(data->vhl[e.ND]);
    dego.smix(data->vhl[e.ST]);
  }
  void update(int st, int nd, int div) {
    for (; st <= nd; st += div) {
      pii e = data->get_e(st);
      update(e);
    }
  }

  void update(const Block &peer) {
    degi.smix(peer.degi);
    dego.smix(peer.dego);
  }

  pii res() const {
    auto it1 = data->rmp.find(degi.hl);
    if (it1 == data->rmp.end()) return {};
    auto it2 = data->rmp.find(dego.hl);
    if (it2 == data->rmp.end()) return {};
    return MP(it2->second, it1->second);
  }
};

struct Blocks {
  int div;
  std::vector<Block> blocks;
  Data *data;
  int bsize;
  int nb;
  void setup(Data *data, int div) {
    this->data = data;
    if (div == 0) return;
    this->div = div;
    int K = 1ll * data->m / div;
    bsize = std::sqrt(K / 2) + 1;
    bsize = 10;
    nb = ((data->m + div - 1) / div + bsize - 1) / bsize;
    blocks.resize(nb);
    Block cur;
    cur.setup(data);
    REP (i, nb) {
      REP (j, bsize)
        cur.update(data->get_e((i * bsize + j) * div));
      blocks[i] = cur;
    }
  }

  void update(int l, int r, Block &b, bool slow = false) const {

    assert((l) % div == 0);
    assert((r) % div == 0);
    int bs = (l / div + bsize - 1) / bsize;
    int be = (r / div - 1) / bsize - 1;
    if (!slow && bs < be) {
      b.update(l, bs * bsize * div - 1, div);
      b.update((be + 1) * bsize * div, r, div);
      if (bs > 0) b.update(blocks[bs - 1]);
      b.update(blocks[be]);
    } else
      b.update(l, r, div);

    // OPA_DISP0(b.degi.hl);
    // OPA_DISP0(b.dego.hl);
  }
};

struct SolverContext {
  Data data;

  std::vector<Query> ql;
  std::unordered_map<pii, int> edges;
  vi states;
  bool checkit(Query q) {
    for (int i = q.l; i <= q.r; ++i)
      if (i % q.m == 0)
        if ((q.type == 'E') == states[i - 1]) return false;
    return true;
  }

  void apply(Query q) {
    for (int i = q.l; i <= q.r; ++i)
      if (i % q.m == 0) states[i - 1] = (q.type == 'E');
  }

  void read() {
    if (TEST_RAND) {
      data.n = rng() % 5 + 30;
      data.n = 1000;
      data.m = rng() % std::min((data.n * (data.n - 1)), int(1e5)) + 1;
      data.nq = rng() % 1000 + 1;
      data.nq *= 2;

      std::unordered_set<pii> seen;
      REP (i, data.m) {
        while (true) {
          int a = rng() % data.n;
          int b = rng() % data.n;
          if (a != b && seen.emplace(a, b).second) {
            data.el.emplace_back(a, b);
            break;
          }
        }
      }

      states.resize(data.m, 0);
      REP (i, data.nq) {
        while (true) {
          Query q;
          q.r = rng() % data.m;
          q.l = rng() % (q.r + 1);
          ++q.r;
          ++q.l;
          q.m = rng() % data.m + 1;
          if (0) {
            q.type = "ED"[rng() % 2];
            if (checkit(q)) {
              apply(q);
              ql.pb(q);
              break;
            }
          } else {
            q.type = 'E';
            ql.pb(q);
            q.type = 'D';
            ql.pb(q);
            ++i;
            break;
          }
        }
      }
    } else {
      g_reader.readline() >> data.n >> data.m >> data.nq;
      data.el.resize(data.m);
      REP (i, data.m)
        g_reader.readline() >> data.el[i].ST >> data.el[i].ND, --data.el[i].ST, --data.el[i].ND;
      ql.resize(data.nq);
      REP (i, data.nq)
        g_reader.readline() >> ql[i].type >> ql[i].l >> ql[i].r >> ql[i].m;
    }
    data.setup();
    REP (i, data.m)
      edges[data.el[i]] = i;
  }

  std::vector<int> solve() {
    vi res;
    std::vector<Blocks> div2blocks;
    div2blocks.resize(3000);
    REP (i, div2blocks.size())
      div2blocks[i].setup(&data, i);
    Block cur;
    cur.setup(&data);
    REP (i, data.n)
      cur.degi.smix(data.vhl[i]);
    REP (i, data.n)
      cur.dego.smix(data.vhl[i]);
    int ne = 0;
    for (auto &q : ql) {
      int st = q.l + (q.m - q.l % q.m) % q.m;
      int nd = q.r - q.r % q.m;
      if (st > nd)
        res.pb(res.size() == 0 ? -1 : res.back());
      else {
        ne += ((nd - st) / q.m + 1) * (q.type == 'E' ? 1 : -1);
        if (1 && q.m < div2blocks.size()) {
          div2blocks[q.m].update(st, nd, cur);

          if (0) {
            Block tmp1, tmp2;
            tmp1.setup(&data);
            tmp2.setup(&data);
            OPA_DISP0(st, nd, q.m);
            div2blocks[q.m].update(st, nd, tmp1);
            div2blocks[q.m].update(st, nd, tmp2, true);
            assert(tmp1.degi.hl == tmp2.degi.hl);
            assert(tmp1.dego.hl == tmp2.dego.hl);
          }

        } else {
          cur.update(st, nd, q.m);
        }

        int rx = -1;
        if (ne == data.n - 1) {
          pii u = cur.res();
          if (edges.count(u)) {
            rx = edges[u];
          }
        }
        res.pb(rx);
      }
    }
    return res;
  }

  int find_dumb() {
    std::unordered_map<int, pii> cnt;
    vi l0, r0;
    int cntx = 0;
    REP (i, data.m)
      if (states[i]) {
        ++cntx;
        auto e = data.get_e(i);
        ++cnt[e.first].first;
        ++cnt[e.second].second;
      }
    if (cntx != data.n - 1) return -1;
    REP (i, data.n) {
      auto u = cnt[i];
      if (u.first > 1) return -1;
      if (u.second > 1) return -1;
      if (u.first == 0) l0.pb(i);
      if (u.second == 0) r0.pb(i);
    }
    if (l0.size() != 1 || r0.size() != 1) return -1;
    int a = l0[0];
    int b = r0[0];
    if (!edges.count(MP(a, b))) return -1;
    return edges[MP(a, b)];
  }

  vi solve_dumb() {
    states.clear();
    states.resize(data.m, 0);
    vi res;
    REP (i, data.nq) {
      apply(ql[i]);
      res.pb(find_dumb());
    }
    return res;
  }
};

int main() {
  srand(0);
  int tn;

  if (TEST_RAND)
    tn = 1000000;
  else
    scanf("%d\n", &tn);

  REP (ti, tn) {

    SolverContext sc;
    sc.read();
    if (TEST_CHECK) {
      auto r1 = sc.solve();
      auto r2 = sc.solve_dumb();
      OPA_DISP0(ti);
      if (r1 != r2) {
        OPA_DISP0(r1, r2);
        printf("Case #%d: ", ti + 1);
        OPA_DISP0(r1, r2);
        puts("");
        OPA_DISP0(sc.data.el, sc.data.n, sc.data.m);
        for (auto x : sc.ql) OPA_DISP0(x.l, x.r, x.m);
        assert(r1 == r2);
      }
    } else {

      printf("Case #%d:", ti + 1);
      auto res = sc.solve();
      for (auto x : res) printf(x == -1 ? " X" : " %d", x + 1);
      puts("");
    }
  }

  return 0;
}
