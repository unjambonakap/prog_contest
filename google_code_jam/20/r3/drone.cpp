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

struct SolverContext {
  char buf[11111];
  int n, d;
  std::vector<P64> pts;

  std::istringstream iss;
  std::istringstream &readline() {
    fgets(buf, sizeof(buf) - 1, stdin);
    iss = std::istringstream(buf);
    return iss;
  }

  void read() {
    if (TEST_RAND) {

      n = rng() % 11 + 1;
      std::set<pii> seen;
      const int maxv = 4;
      const int maxd = 100000;
      d = rng() % maxd + 1;
      std::uniform_int_distribution<> dis(-maxv, maxv);
      pts.resize(n);
      REP (i, n) {
        while (true) {
          pii pt(dis(rng), dis(rng));
          if (seen.insert(pt).second) {
            pts[i] = P64(pt.first, pt.second);
            break;
          }
        }
      }

    } else {
      scanf("%d%d\n", &n, &d);
      pts.resize(n);
      assert(n >= 0);
      REP (i, n)
        readline() >> pts[i].x >> pts[i].y;
    }

    REP (i, n) {
      int nx = pts[i].x + pts[i].y;
      int ny = pts[i].x - pts[i].y;
      pts[i].x = nx;
      pts[i].y = ny;
    }
  }

  struct PointSource {
    std::set<int> see;
    P64 pt;
    int id;
    void add(int porigin, int pid) {
      (void)pid;
      see.insert(porigin);
    }
  };

  struct Event {
    int x;
    int id;
    bool close;
    Event(int x, int id, bool close) : x(x), id(id), close(close) {}
    bool operator<(const Event &ev) const { return x < ev.x; }
    bool operator==(const Event &ev) const { return x == ev.x && id == ev.id; }
  };

  struct SweepLine {
    std::map<int, std::unordered_set<int> > evl;
    std::vector<std::pair<int, bool> > id_and_close;
    void add(int id, int x1, int x2) {
      evl[x1].insert(id);
      evl[x2].insert(-id - 1);
    }
    void remove(int id, int x1, int x2) {
      evl[x1].erase(id);
      if (evl[x1].size() == 0) evl.erase(x1);
      evl[x2].erase(-id - 1);
      if (evl[x2].size() == 0) evl.erase(x2);
    }

    void setup_next(int x) {
      id_and_close.clear();
      for (auto e : evl[x]) {
        if (e < 0)
          id_and_close.emplace_back(-e - 1, true);
        else
          id_and_close.emplace_back(e, false);
      }
    }
  };

  struct SegTree {
    struct Node {
      int h = 0;
      int first = INT_MAX, last = -1;
      int cnt = 0;
    };
    std::vector<Node> nodes;
    int leaf_start;
    int n;
    const int rootid = 1;
    static const int kMaxPass = 5;
    const int mods[5] = { int(1e9 + 9), int(1e9 + 21), int(1e9 + 33), int(1e9 + 87),
                          int(1e9 + 93) };
    const int kmuls[5] = { int(1e6 + 3), int(1e6 + 33), int(1e6 + 37), int(1e7 + 79),
                           int(1e5 + 43) };
    int cnt = 0;

    int mod;
    s64 mul;
    const std::vector<P64> &pts;
    std::vector<s64> mulPw;
    SegTree(const std::vector<P64> &pts, int pass_number) : pts(pts) {

      n = pts.size();
      mod = mods[pass_number];
      mul = kmuls[pass_number];
      mulPw.pb(1);
      REP (i, 2 * n)
        mulPw.pb(mulPw.back() * mul % mod);

      int b = 1;
      while (1 << b < n) ++b;
      leaf_start = 1 << b;
      nodes.resize(2 * leaf_start);
    }

    std::vector<int> extract_lst() const {
      std::vector<int> res;
      FOR (i, leaf_start, leaf_start + n)
        if (nodes[i].cnt) res.pb(i - leaf_start);
      return res;
    }

    size_t get_h() const { return nodes[rootid].h; }
    void update(int x, bool add) {
      cnt += add ? 1 : -1;
      int pos = x + leaf_start;

      auto &cur = nodes[pos];
      cur.cnt += add ? 1 : -1;
      if (add)
        cur.first = cur.last = x;
      else
        cur.first = INT_MAX, cur.last = -1;

      for (; pos >= rootid; pos >>= 1) {
        norm(pos);
      }
    }
    void norm(int id) {
      Node &x = nodes[id];
      if (id >= leaf_start) {
        x.h = 0;
      } else {

        const Node &l = nodes[2 * id];
        const Node &r = nodes[2 * id + 1];
        x.cnt = l.cnt + r.cnt;
        x.first = std::min(l.first, r.first);
        x.last = std::max(l.last, r.last);
        if (l.last == -1)
          x.h = r.h;
        else if (r.last == -1)
          x.h = l.h;
        else {
          auto diff = pts[r.first] - pts[l.last];
          auto diff0 = diff;
          diff = diff + P64(mul / 2, mul / 2);
          assert(l.cnt > 0);
          x.h =
            (l.h + (((diff.x + r.h * mul % mod) * mul + diff.y) % mod) * mulPw[2 * (l.cnt - 1)]) %
            mod;
        }
      }
    }
  };

  struct SegTree2 {
    struct Node {
      int size = 0;
      int low, high;
      int id;

      int child_cover_size = 0;
      s64 tot_sum = 0;
      int cover_size = 0;
      s64 val = 0;
      int full_count = 0;
    };
    std::vector<Node> nodes;
    int leaf_start;
    int n;
    const int rootid = 1;
    SegTree2(const std::vector<int> &sl) {

      n = sl.size();

      int b = 1;
      while (1 << b < n) ++b;
      leaf_start = 1 << b;
      nodes.resize(2 * leaf_start);
      REP (i, leaf_start)
        nodes[leaf_start + i].low = i, nodes[leaf_start + i].high = i;
      REPV (i, n)
        nodes[leaf_start + i].size = sl[i];

      REPV (i, leaf_start) {
        nodes[i].low = nodes[2 * i].low;
        nodes[i].high = nodes[2 * i + 1].high;
        nodes[i].size = nodes[2 * i].size + nodes[2 * i + 1].size;
      }
      REP (i, 2 * leaf_start)
        nodes[i].id = i;
    }

    void norm(Node &node) {
      s64 child_val = 0;
      if (node.id < leaf_start) {
        Node &l = nodes[2 * node.id];
        Node &r = nodes[2 * node.id + 1];
        node.child_cover_size = l.cover_size + r.cover_size;
        node.tot_sum = l.tot_sum + r.tot_sum;
        child_val = l.val + r.val;
      } else {
        node.tot_sum = 0;
      }
      node.tot_sum += 1ull * node.full_count * node.size;
      node.cover_size = node.full_count > 0 ? node.size : node.child_cover_size;
      if (node.full_count == 0) {
        node.val = child_val;
      } else if (node.full_count == 1) {
        node.val = node.tot_sum + node.child_cover_size - node.size;
      } else {
        node.val = node.tot_sum;
      }
    }

    void update(Node &node, int low, int high, bool add) {
      if (high < node.low) return;
      if (low > node.high) return;
      if (low <= node.low && node.high <= high) {
        node.full_count += add ? 1 : -1;
      } else if (node.id < leaf_start) {
        update(nodes[2 * node.id], low, high, add);
        update(nodes[2 * node.id + 1], low, high, add);
      }
      norm(node);
    }
    void update(int low, int high, bool add) { update(nodes[rootid], low, high, add); }
  };

  struct AreaData {
    pii xr, yr;
  };

  typedef struct std::vector<size_t> SetSig;
  std::unordered_map<SetSig, std::vector<int> > mp;
  std::unordered_map<int, SetSig> rmp;
  std::unordered_map<int, AreaData> area_data;
  s64 tot_area = 0;
  s64 bad_area = 0;

  s64 do_sweep(std::vector<AreaData> areas) const {
    if (areas.size() <= 1) return 0;
    std::map<int, int> rmpx;
    std::map<int, int> rmpy;
    for (auto a : areas) {
      rmpx[a.xr.first] = rmpx[a.xr.second] = 0;
      rmpy[a.yr.first] = rmpy[a.yr.second] = 0;
    }
    int ix = 0;
    for (auto &v : rmpx) v.second = ix++;
    int iy = 0;
    for (auto &v : rmpy) v.second = iy++;

    for (auto &a : areas) {
      a.xr.first = rmpx[a.xr.first];
      a.xr.second = rmpx[a.xr.second];
      a.yr.first = rmpy[a.yr.first];
      a.yr.second = rmpy[a.yr.second];
    }

    s64 res = 0;
    SweepLine slx;
    REP (i, areas.size()) { slx.add(i, areas[i].xr.first, areas[i].xr.second); }
    vi yl;
    vi xl;
    for (auto x : rmpx) xl.pb(x.first);
    for (auto y : rmpy) yl.pb(y.first);
    REPV (i, yl.size() - 1)
      yl[i + 1] -= yl[i];
    yl.erase(yl.begin());
    SegTree2 stree(yl);

    int lastx = slx.evl.begin()->first;
    std::set<int> in;
    for (const auto &kv : slx.evl) {
      int x = kv.first;
      slx.setup_next(x);
      int xp = x;
      if (lastx < xp) {
        res += 1ull * (xl[xp] - xl[lastx]) * stree.nodes[1].val;
        if (0) {
          std::map<int, int> cnt;
          s64 s = 0;
          for (auto u : in) {
            auto &a = areas[u];
            FOR (j, a.yr.first, a.yr.second)
              ++cnt[j];
          }
          for (auto e : cnt) {
            if (e.second > 1) s += (1ull) * yl[e.first] * e.second;
          }
          assert(s == stree.nodes[1].val);
        }
      }

      for (auto p : slx.id_and_close) {
        auto &a = areas[p.first];
        if (p.second)
          in.erase(p.first);
        else
          in.insert(p.first);
        stree.update(a.yr.first, a.yr.second - 1, !p.second);
      }
      checkmax(lastx, xp);
    }

    return res;
  }

  void do_pass(int pass_number) {
    std::unordered_map<SetSig, std::vector<int> > nmp;

    SweepLine slx;
    REP (i, n) {
      auto &pt = pts[i];
      slx.add(i, pt.x - d, pt.x + d);
    }

    tot_area = 0;
    bad_area = 0;
    int area_id = 0;
    SweepLine sly;
    int lastx = slx.evl.begin()->first;
    std::map<SetSig, std::vector<P64> > real_sig;
    for (const auto &kv : slx.evl) {
      int x = kv.first;
      slx.setup_next(x);
      int xp = x;

      if (lastx < xp && sly.evl.size() > 0) {
        SegTree stree(pts, pass_number);
        int diff = xp - lastx;
        int lasty = sly.evl.begin()->first;
        for (const auto &kv2 : sly.evl) {
          int y = kv2.first;
          sly.setup_next(y);
          int yp = y;
          if (lasty < yp && stree.cnt > 0) {
            ++area_id;
            int diffy = yp - lasty;
            s64 area = 1ull * diffy * diff;
            tot_area += area;

            auto &pfirst = pts[stree.nodes[stree.rootid].first];
            area_data[area_id].xr = pii(lastx - pfirst.x, xp - pfirst.x);
            area_data[area_id].yr = pii(lasty - pfirst.y, yp - pfirst.y);

            auto cur = rmp[area_id];
            size_t h = stree.get_h();
            cur.pb(h);
            nmp[cur].pb(area_id);

            if (0 && pass_number >= 0) {
              vi lst = stree.extract_lst();
              std::vector<P64> difflist;
              REP (i, lst.size() - 1)
                difflist.pb(pts[lst[i + 1]] - pts[lst[i]]);
              if (real_sig.count(cur)) {
                assert(real_sig[cur] == difflist);
              }
              real_sig[cur] = difflist;
            }
          }
          checkmax(lasty, yp);
          for (auto p : sly.id_and_close) {
            stree.update(p.first, !p.second);
          }
        }
      }
      checkmax(lastx, xp);

      for (auto p : slx.id_and_close) {
        auto &pt = pts[p.first];
        if (p.second) {
          sly.remove(p.first, pt.y - d, pt.y + d);
        } else {
          sly.add(p.first, pt.y - d, pt.y + d);
        }
      }
    }
    mp = nmp;
    rmp.clear();
    for (auto &x : mp) {
      for (auto y : x.second) rmp[y] = x.first;
    }
    if (0) {
      std::set<std::vector<P64> > seen;
      for (auto x : real_sig) {
        OPA_DISP0(x);
        assert(seen.insert(x.second).second);
      }
    }
  }

  frac<s64> solve() {
    std::sort(ALL(pts));
    mp.clear();

    REP (pid, SegTree::kMaxPass) { do_pass(pid); }

    for (auto &x : mp) {
      std::vector<AreaData> areas;
      for (auto u : x.second) areas.pb(area_data[u]);
      bad_area += do_sweep(areas);
    }

    return frac<s64>(tot_area - bad_area, tot_area);
  }

  frac<s64> solve_dumb() {
    std::unordered_map<P64, PointSource> mp;
    std::vector<PointSource *> rmp;

    REP (i, n)
      REP (j, n)
        mp[pts[j] - pts[i]].add(i, j);
    for (auto &kv : mp) {
      kv.second.id = rmp.size();
      kv.second.pt = kv.first;
      rmp.pb(&kv.second);
    }
    frac<s128> tot_area = 0;
    frac<s128> bad_area(0);

    int M = rmp.size();
    SweepLine slx;
    REP (i, M) {
      const auto &ps = *rmp[i];
      auto &pt = ps.pt;
      slx.add(ps.id, pt.x - d, pt.x + d);
    }

    SweepLine sly;
    int lastx = -d;
    for (const auto &kv : slx.evl) {
      int x = kv.first;
      slx.setup_next(x);
      int xp = std::min(x, d);

      if (lastx < xp) {
        int diff = xp - lastx;
        int lasty = -d;
        std::set<int> alive;
        for (const auto &kv2 : sly.evl) {
          int y = kv2.first;
          sly.setup_next(y);
          int yp = std::min(d, y);
          if (lasty < yp) {
            int diffy = yp - lasty;
            s128 area = 1ull * diffy * diff;

            std::vector<int> cnt(n, 0);
            std::vector<std::set<int> > sets(n);
            std::set<int> can;
            for (auto u : alive) {
              REP (i, n)
                if (rmp[u]->see.count(i)) {
                  cnt[i]++;
                  sets[i].insert(u);
                }
            }
            std::map<std::set<int>, int> mpx;
            REP (i, n)
              mpx[sets[i]]++;
            frac<s128> farea(area);
            REP (i, n) { tot_area = tot_area + farea / cnt[i]; }
            for (auto e : mpx) {
              if (e.second == 1) continue;
              bad_area = bad_area + farea * e.second / e.first.size();
            }
          }

          checkmax(lasty, yp);
          for (auto p : sly.id_and_close) {
            if (p.second)
              alive.erase(p.first);
            else
              alive.insert(p.first);
          }
        }
      }
      checkmax(lastx, xp);

      for (auto p : slx.id_and_close) {
        auto &ps = *rmp[p.first];
        auto &pt = ps.pt;
        int xx = pt.y;
        if (p.second) {
          sly.remove(ps.id, xx - d, xx + d);
        } else {
          sly.add(ps.id, xx - d, xx + d);
        }
      }
    }

    return ((tot_area - bad_area) / tot_area).as<s64>();
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
    if (0 && ti != 972) continue;
    if (TEST_CHECK) {
      auto r1 = sc.solve();
      auto r2 = sc.solve_dumb();
      OPA_DISP0(r1, r2);
      if (r1 != r2) {
        printf("Case #%d: ", ti + 1);
        OPA_DISP0(sc.pts, sc.d);
        OPA_DISP0(r1, r2);
        puts("");
        assert(r1 == r2);
      }
    } else {

      printf("Case #%d: ", ti + 1);
      auto res = sc.solve().as<s64>();
      printf("%Ld %Ld", res.p, res.q);
      puts("");
    }
  }

  return 0;
}
