#ifndef TEST_RAND
#define TEST_RAND 0
#endif

#ifndef TEST_CHECK
#define TEST_CHECK 0
#endif

#ifndef TEST_LARGE
#define TEST_LARGE 0
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
  std::showbase                                                    \
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


std::mt19937 rng(0);
// clang-format on
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

  frac(T p, T q) : p(p), q(q) {
    T d = gcd(std::abs(p), std::abs(q));
    if (this->q < 0) this->p = -this->p, this->q = -this->q;
    this->p /= d;
    this->q /= d;
  }
  template <typename U> frac<U> as() const { return frac<U>(p, q); }

  std::pair<T, T> as_pair() const { return MP(p, q); }
  frac operator+(const frac &peer) const { return frac(p * peer.q + peer.p * q, peer.q * q); }
  frac operator-(const frac &peer) const { return frac(p * peer.q - peer.p * q, peer.q * q); }
  frac operator*(const frac &peer) const { return frac(p * peer.p, peer.q * q); }
  frac operator/(T d) const { return frac(p, q * d); }
  bool operator<(const frac &peer) const { return (p * peer.q - peer.p * q) < 0; }
  bool operator>(const frac &peer) const { return (p * peer.q - peer.p * q) > 0; }
  bool operator<=(const frac &peer) const { return (p * peer.q - peer.p * q) <= 0; }
};
template <class T> struct Segment;

template <class T> struct Point {
  T x, y;
  Point() {}
  Point(T x, T y) : x(x), y(y) {}
  Point operator-(const Point &peer) const { return Point(x - peer.x, y - peer.y); }
  bool operator<(const Point &peer) const { return as_pair() < peer.as_pair(); }
  bool operator==(const Point &peer) const { return x == peer.x && y == peer.y; }
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
  Segment<T> make_seg(const Point<T> &peer) const;
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
template <class T> Segment<T> Point<T>::make_seg(const Point<T> &peer) const {
  return Segment<T>(*this, peer);
}

struct hash_t {
  template <typename T> size_t operator()(const Point<T> &x) const { return (*this)(x.as_pair()); }
  template <typename T1, typename T2> size_t operator()(const std::pair<T1, T2> &x) const {
    size_t h1 = std::hash<T1>{}(x.first);
    size_t h2 = std::hash<T1>{}(x.second);
    return (h1 * 31 + h2) ^ h1;
  }
};

struct Generator {
  bool check_colinear(Point<s32> pt, const std::vector<Point<s32> > &lst) {
    std::unordered_set<pii, hash_t> mp;
    for (auto &e : lst) {
      if (pt == e) return false;
      if (!mp.insert((e - pt).simplify().as_pair()).second) return false;
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
} // namespace std

namespace hull {

struct TNode {
  int left_bridge = -1;
  int right_bridge = -1;
  int cnt = 0;
};

struct DynamicHull {
  const int lowerhull = 1;
  const int upperhull = 0;
  std::vector<Point<s64> > pts;
  std::unordered_map<Point<s64>, int, hash_t> rmp;
  std::vector<TNode> segtrees[2];
  std::vector<Point<s64> > ptsf[2];
  std::vector<int> highbit;
  int pw;
  int n;
  int count(int f) const { return segtrees[f][1].cnt; }

  void setup(const std::vector<Point<s64> > &points) {
    pts = points;
    std::sort(ALL(pts));
    n = pts.size();
    REP (i, n)
      rmp[pts[i]] = i;
    REP (i, n)
      ptsf[0].emplace_back(pts[i]);
    REP (i, n)
      ptsf[1].emplace_back(pts[i].x, -pts[i].y);

    pw = 1;
    while (pw < n) pw <<= 1;
    REP (f, 2)
      segtrees[f].resize(2 * pw);
    highbit.resize(2 * pw);

    highbit[0] = -1;
    FOR (i, 1, highbit.size())
      highbit[i] = highbit[i >> 1] + 1;
  }

  int start_node_id(int pos) const {
    int hg = highbit[pos];
    return (pos ^ (1 << hg)) * (pw >> hg);
  }
  int node_size(int pos) const { return pw >> highbit[pos]; }

  void normalize(int f, int p) {
    if (p >= pw) return;
    auto &l = segtrees[f][2 * p];
    auto &r = segtrees[f][2 * p + 1];
    segtrees[f][p].cnt = l.cnt + r.cnt;
  }

  int only_child(int f, int pos) const {
    while (pos < pw) {

      if (segtrees[f][2 * pos].cnt == 0)
        pos = 2 * pos + 1;
      else if (segtrees[f][2 * pos + 1].cnt == 0)
        pos = 2 * pos;
      else
        break;
    }
    return pos;
  }

  void update_bridge(int f, int pos) {
    int lp = pos * 2;
    int rp = pos * 2 + 1;
    auto &vx = segtrees[f];
    auto &nx = vx[pos];

    if (nx.cnt == 0 || vx[lp].cnt == 0 || vx[rp].cnt == 0) {
      nx.left_bridge = nx.right_bridge = -1;
      return;
    }

    while (true) {
      if (vx[lp].cnt > 0) {
        lp = only_child(f, lp);
      }

      if (vx[rp].cnt > 0) {
        rp = only_child(f, rp);
      }
      assert(lp < 2 * pw);
      assert(rp < 2 * pw);
      if (lp >= pw && rp >= pw) break;
      auto &l = vx[lp];
      auto &r = vx[rp];
      auto &tb = ptsf[f];
      int llb = l.left_bridge == -1 ? lp - pw : l.left_bridge;
      int lrb = l.right_bridge == -1 ? lp - pw : l.right_bridge;
      int rlb = r.left_bridge == -1 ? rp - pw : r.left_bridge;
      int rrb = r.right_bridge == -1 ? rp - pw : r.right_bridge;
      int rid = start_node_id(rp);
      int lid = start_node_id(lp) + node_size(lp) - 1;
      int action =
        compute_action(tb[llb], tb[lrb], tb[rlb], tb[rrb], frac<s64>(pts[lid].x + pts[rid].x, 2));
      if (action < 2)
        lp = 2 * lp + action;
      else
        rp = 2 * rp + action - 2;
    }

    if (vx[lp].cnt > 0 && vx[rp].cnt > 0) {
      nx.left_bridge = lp - pw;
      nx.right_bridge = rp - pw;
    } else {

      nx.left_bridge = -1;
      nx.right_bridge = -1;
    }
  }

  int compute_action(const Point<s64> &ll, const Point<s64> &lr, const Point<s64> &rl,
                     const Point<s64> &rr, frac<s64> midpoint) {
    if (ll == lr) {
      return (rl - ll).cross(rr - ll) > 0 ? 3 : 2;
    }
    if (rl == rr) {
      return (ll - rl).cross(lr - rl) > 0 ? 0 : 1;
    }

    {
      auto v = lr - ll;
      auto v1 = rl - ll;
      auto v2 = rr - ll;
      bool s1 = v.cross(v1) > 0;
      bool s2 = v.cross(v2) > 0;
      if (s1 || s2) return 0;
    }

    {
      auto v = rl - rr;
      auto v1 = lr - rr;
      auto v2 = ll - rr;
      bool s1 = v.cross(v1) < 0;
      bool s2 = v.cross(v2) < 0;
      if (s1 || s2) return 3;
    }
    auto segl = Segment<s64>(ll, lr).as<s128>();
    auto segr = Segment<s64>(rl, rr).as<s128>();
    auto interpoint = segl.inter_point(segr);

    if (interpoint.x < midpoint.as<s128>()) return 1;
    return 2;
  }

  void update(const Point<s64> &p, bool remove_node) {
    REP (f, 2)
      update(p, remove_node, f);
  }

  void update(const Point<s64> &p, bool remove_node, int f) {
    assert(rmp.count(p));
    int pid = rmp[p];
    assert(pid < n);

    int pos = pid + pw;
    auto &nx = segtrees[f][pos];
    if (remove_node) {
      nx.cnt = 0;
      nx.left_bridge = -1;
      nx.right_bridge = -1;
    } else {
      nx.cnt = 1;
      nx.left_bridge = -1;
      nx.right_bridge = -1;
    }

    for (; pos > 1; pos >>= 1) {
      int np = pos >> 1;

      normalize(f, np);
      auto &node = segtrees[f][np];
      bool do_update = true;
      if (remove_node)
        do_update |= node.left_bridge == pid || node.right_bridge == pid || true;
      else {
        if (node.left_bridge == -1 || node.right_bridge == -1)
          do_update = true;
        else {
          auto seg = Segment<s64>(ptsf[f][node.left_bridge], ptsf[f][node.right_bridge]);
          do_update |= pid < node.left_bridge || pid > node.right_bridge || seg.ccw(ptsf[f][pid]);
        }
      }
      if (do_update) update_bridge(f, np);
    }
  }

  void fill_hull(int f, int pos, std::vector<int> &hull, int l, int r) const {
    auto &x = segtrees[f][pos];
    if (x.cnt == 0) return;
    int ln = start_node_id(pos);
    int rn = ln + node_size(pos) - 1;
    if (l > rn || r < ln) return;
    int nr = r;
    if (x.left_bridge != -1) checkmin(nr, x.left_bridge - 1);
    fill_hull(f, 2 * pos, hull, l, nr);
    if (x.left_bridge != -1 && x.left_bridge >= l && x.left_bridge <= r) hull.pb(x.left_bridge);
    if (x.right_bridge != -1 && x.right_bridge >= l && x.right_bridge <= r) hull.pb(x.right_bridge);

    if (pos >= pw && pos - pw >= l && pos - pw <= r) hull.pb(pos - pw);
    int nl = l;
    if (x.right_bridge != -1) checkmax(nl, x.right_bridge + 1);
    fill_hull(f, 2 * pos + 1, hull, nl, r);
  }

  std::vector<int> extract_hull(int f) const {
    std::vector<int> res;
    fill_hull(f, 1, res, 0, n);
    return res;
  }

  std::vector<int> compute_hull_dumb(int f) const {
    std::vector<int> tb;
    REP (i, n) {
      if (segtrees[f][i + pw].cnt == 0) continue;

      auto &a = ptsf[f][i];
      while (tb.size() >= 2) {
        int nx = tb.size();
        if ((ptsf[f][tb[nx - 1]] - a).cross(ptsf[f][tb[nx - 2]] - a) < 0)
          tb.pop_back();
        else
          break;
      }
      tb.pb(i);
    }
    return tb;
  }
  typedef std::function<bool(const Segment<s64> &)> FindF;
  typedef std::function<bool(int lb, int rb)> SearchF;

  int search(int f, const SearchF &func) const {
    int pos = 1;
    int low = 0;
    int high = n - 1;
    while (true) {
      pos = only_child(f, pos);
      if (pos >= pw) break;
      auto &node = segtrees[f][pos];
      if (node.right_bridge > high)
        pos = 2 * pos;
      else if (node.left_bridge < low)
        pos = 2 * pos + 1;
      else if (func(node.left_bridge, node.right_bridge)) {
        low = node.right_bridge;
        pos = 2 * pos + 1;
      } else {
        high = node.left_bridge;
        pos = 2 * pos;
      }
    }
    return pos - pw;
  }

  int find(int f, const FindF &func) const {
    int pos = 1;
    int low = 0;
    int high = n - 1;
    while (true) {
      pos = only_child(f, pos);
      if (pos >= pw) break;
      auto &node = segtrees[f][pos];
      if (node.left_bridge > high)
        pos = 2 * pos;
      else if (node.right_bridge < low)
        pos = 2 * pos + 1;
      else if (func(Segment<s64>(pts[node.left_bridge], pts[node.right_bridge]))) {
        low = node.right_bridge;
        pos = 2 * pos + 1;
      } else {
        high = node.left_bridge;
        pos = 2 * pos;
      }
    }
    return pos - pw;
  }

  int prev(int f, int p) const {
    int best = -1;
    search(f, [&](int a, int b) {
      if (a < p) checkmax(best, a);
      if (b < p) checkmax(best, b);
      return a < p;
    });
    return best;
  }
  int next(int f, int p) const {
    int best = INT_MAX;
    search(f, [&](int a, int b) {
      if (a > p) checkmin(best, a);
      if (b > p) checkmin(best, b);
      return b <= p;
    });
    return best == INT_MAX ? -1 : best;
  }

  int max(int f) const {
    return search(f, [](int a, int b) {
      (void)a;
      (void)b;
      return true;
    });
  }
  int min(int f) const {
    return search(f, [](int a, int b) {
      (void)a;
      (void)b;
      return false;
    });
  }
};

template <typename T> std::vector<int> compute_hull(const std::vector<Point<T> > &pts, bool upper) {
  int n = pts.size();
  vi tb;
  REP (i, n)
    tb.pb(i);
  std::sort(ALL(tb), [&](int a, int b) { return pts[a].x < pts[b].x; });
  vi res;

  for (auto i : tb) {
    auto &a = pts[i];
    while (res.size() >= 2) {
      int nx = res.size();
      if (((pts[res[nx - 2]] - a).cross(pts[res[nx - 1]] - a) > 0) ^ !upper)
        res.pop_back();
      else
        break;
    }
    res.pb(i);
  }
  return res;
}

struct SidedHull {
  DynamicHull *dh;
  bool lower;
  SidedHull(DynamicHull *dh, bool lower) : dh(dh), lower(lower) {}
  int count() const { return dh->count(lower); }
  Point<s64> pt(int i) const { return dh->pts[i]; }

  struct Iterator {
    const SidedHull *sh;
    int v;
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = int;
    using pointer = int *;         // or also value_type*
    using reference = const int &; // or also value_type&
    reference operator*() const { return v; }
    Point<s64> pt() const { return sh->pt(v); }

    Iterator operator-(int a) const { return *this + (-a); }
    Iterator operator+(int a) const {
      auto res = *this;
      if (a >= 0) REP (i, a)
          ++res;
      else
        REP (i, -a)
          --res;
      return res;
    }

    // Prefix increment
    Iterator &operator--() {
      if (v == -1)
        v = sh->dh->max(sh->lower);
      else
        v = sh->dh->prev(sh->lower, v);
      assert(v != -1);
      return *this;
    }

    Iterator &operator++() {
      assert(v != -1);
      v = sh->dh->next(sh->lower, v);
      return *this;
    }

    // Postfix increment
    Iterator operator--(int) {
      Iterator tmp = *this;
      --(*this);
      return tmp;
    }
    Iterator operator++(int) {
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }
  };

  Iterator begin() const {
    Iterator res;
    res.sh = this;
    res.v = dh->min(lower);
    return res;
  }
  Iterator end() const {
    Iterator res;
    res.sh = this;
    res.v = -1;
    return res;
  }

  friend bool operator==(const Iterator &a, const Iterator &b) {
    return a.sh == b.sh && a.v == b.v;
  }

  friend bool operator!=(const Iterator &a, const Iterator &b) { return !(a == b); }
};

template <typename T> struct IncrementalHull {
  struct PointCompare {
    const IncrementalHull &ih;
    PointCompare(IncrementalHull &ih) : ih(ih) {}
    bool operator()(const int &a, const int &b) const {
      if (a == -1)
        return !ih.search(b);
      else if (b == -1)
        return ih.search(a);
      return ih.tb[a].x < ih.tb[b].x;
    }
  };
  std::vector<Point<T> > tb;
  PointCompare pc;
  std::set<int, PointCompare> hull;
  std::vector<int> next;
  bool upper;
  int n;

  typedef std::function<bool(const Segment<T> &)> SearchF;
  mutable const SearchF *_searchF;

  IncrementalHull() : pc(*this), hull(pc) {}

  bool search(int v) const {
    if (next[v] == -1) return false;
    return (*_searchF)(Segment<T>(tb[v], tb[next[v]]));
  }

  void setup(const std::vector<Point<T> > &startpoints, bool upper) {
    tb = startpoints;
    this->upper = upper;
    auto hull = compute_hull(startpoints, upper);
    n = startpoints.size();
    next.resize(n, -1);
    REP (i, hull.size() - 1)
      next[hull[i]] = hull[i + 1];
    this->hull.insert(ALL(hull));
  }

  int find(const SearchF &func) const {
    OPA_DISP0(hull.size());
    if (hull.size() == 0) return -1;
    if (hull.size() == 1) return *hull.begin();
    _searchF = &func;
    auto it = hull.lower_bound(-1);
    _searchF = nullptr;
    OPA_DISP0(*it);
    return *it;
  }

  bool push(Point<T> pt) {
    int id = tb.size();
    OPA_DISP("PUsh ", pt, id);
    next.pb(-1);
    tb.pb(pt);
    auto it = hull.lower_bound(id);
    if (it != hull.begin()) {
      auto p1 = it;
      --p1;
      while (p1 != hull.begin()) {
        auto p2 = p1;
        --p2;
        if (!can_remove(*p2, *p1, id)) break;
        OPA_DISP("Remove 1", *p2, *p1, id);
        next[*p1] = -1;
        hull.erase(p1);
        p1 = p2;
      }
      it = ++p1;
    }

    while (it != hull.end()) {
      auto nit = it;
      ++nit;
      if (nit == hull.end()) break;
      if (!can_remove(id, *it, *nit)) break;
      OPA_DISP("Remove 1", id, *it, *nit);
      next[*it] = -1;
      it = hull.erase(it);
    }
    bool insert = false;
    OPA_DISP0(it == hull.end(), it == hull.begin());
    if (it == hull.end() || it == hull.begin())
      insert = true;
    else {
      auto prev = it;
      --it;
      insert = !can_remove(*prev, id, *it);
    }
    OPA_DISP0(id, insert);
    if (insert) {
      auto it = hull.insert(id).first;
      if (it != hull.begin()) {
        auto prev = it;
        next[*--prev] = id;
      }

      auto nit = ++it;
      if (nit != hull.end()) next[id] = *nit;
    }
    return insert;
  }

  bool can_remove(int a, int b, int c) const {
    auto pa = tb[a];
    auto pb = tb[b];
    auto pc = tb[c];
    return Segment<T>(pa, pb).ccw(pc) ^ !upper;
  }
};

} // namespace hull

struct SolverContext {
  char buf[11111];
  const int maxv = 1 ? 1000 : 1e9;
  const s64 xinter_lim = 5ll * maxv * maxv;
  std::vector<int> lst;

  std::istringstream iss;
  std::istringstream &readline() {
    fgets(buf, sizeof(buf) - 1, stdin);
    iss = std::istringstream(buf);
    return iss;
  }
  std::vector<Point<s64> > points;
  int n;
  std::vector<int> sol;

  void read() {
    if (TEST_RAND) {
      if (TEST_LARGE)
        n = 100000;
      else
        n = rng() % 210 + 2;
      Generator gen;
      auto pts = gen.generate_points(n * 2, maxv, true);
      for (auto &pt : pts) points.emplace_back(pt.first, pt.second);
      REP (i, 2 * n)
        sol.pb((i + n) % (2 * n));

    } else {
      scanf("%d", &n);
      REP (i, n * 2) {
        int a, b;
        scanf("%d%d", &a, &b);
        points.emplace_back(a, b);
      }
    }
    lst.resize(2 * n);
  }

  void pair(int a, int b) {
    lst[a] = b;
    lst[b] = a;
  }

  std::vector<int> solve_fail() {
    std::vector<int> vl;
    REP (i, 2 * n)
      vl.pb(i);
    std::unordered_map<Point<s64>, int, hash_t> rmp;
    REP (i, 2 * n)
      rmp[points[i]] = i;

    std::sort(ALL(vl), [&](int a, int b) { return points[a].y < points[b].y; });

    vi low(vl.begin(), vl.begin() + n);
    vi high(vl.begin() + n, vl.end());
    std::vector<Point<s64> > lowp, highp;
    for (auto x : low) lowp.pb(points[x]);
    for (auto x : high) highp.pb(points[x]);
    OPA_DISP0(points);

    OPA_DISP0(lowp, highp);
    hull::DynamicHull dhlow, dhhigh;
    dhlow.setup(lowp);
    dhhigh.setup(highp);
    REP (i, dhlow.n)
      dhlow.update(lowp[i], false);
    REP (i, dhhigh.n)
      dhhigh.update(highp[i], false);
    auto shlow = hull::SidedHull(&dhlow, false);
    auto shhigh = hull::SidedHull(&dhhigh, true);
    auto itl = shlow.begin();
    auto ith = shhigh.end();
    REP (i, n) {
      auto nits = find_cutline(itl, ith);
      itl = nits.first;
      ith = nits.second;

      auto line = itl.pt().make_seg(ith.pt());
      if (1) {
        OPA_DISP0(itl.pt(), ith.pt());
        OPA_DISP0(dhlow.compute_hull_dumb(shlow.lower));
        OPA_DISP0(dhhigh.compute_hull_dumb(shhigh.lower));
        OPA_DISP0(dhlow.extract_hull(shlow.lower));
        OPA_DISP0(dhhigh.extract_hull(shhigh.lower));
        for (auto x : shlow) OPA_DISP0(line.signed_dist(shlow.pt(x)), shlow.pt(x));
        puts("===");
        for (auto x : shhigh) OPA_DISP0(line.signed_dist(shhigh.pt(x)), shhigh.pt(x));
      }

      assert(itl != shlow.end());
      assert(ith != shhigh.end());
      assert(rmp.count(itl.pt()));
      assert(rmp.count(ith.pt()));
      int i1 = rmp[itl.pt()], i2 = rmp[ith.pt()];
      pair(i1, i2);
      OPA_DISP0(i1, i2);
      bool is_first = itl == shlow.begin();
      if (!is_first) --itl;
      ++ith;
      dhlow.update(nits.first.pt(), true);
      dhhigh.update(nits.second.pt(), true);
      if (is_first) itl = shlow.begin();
    }

    return lst;
  }
  std::pair<hull::SidedHull::Iterator, hull::SidedHull::Iterator>
  find_cutline(hull::SidedHull::Iterator itl, hull::SidedHull::Iterator ith) {
    auto shl = itl.sh;
    auto shh = ith.sh;
    if (ith == shh->end()) --ith;
    assert(ith != shh->end());
    assert(itl != shl->end());
    if (itl.sh->count() == 1) return MP(itl, ith);
    while (true) {
      auto pl0 = itl.pt();
      auto ph0 = ith.pt();
      auto itl1 = itl + 1;

      if (itl1 != shl->end()) {

        auto pl1 = itl1.pt();
        if ((pl1 - pl0).cross((ph0 - pl0)) < 0) {
          ++itl;
          continue;
        }
      }

      if (ith != shh->begin()) {

        auto ph1 = (ith - 1).pt();
        if ((ph1 - ph0).cross(pl0 - ph0) < 0) {
          --ith;
          continue;
        }
      }
      break;
    }
    return MP(itl, ith);
  }

  std::vector<int> solve_dumb() { return sol; }

  void split(const std::vector<int> &lst, const Segment<s64> &seg, std::vector<int> &l,
             std::vector<int> &r) const {
    int m = lst.size() / 2;
    std::vector<s64> dists(m*2);
    REP (i, m*2)
      dists[i] = seg.signed_dist(points[lst[i]]);
    std::vector<int> perm(2*m);
    REP (i, 2*m)
      perm[i] = i;

    std::sort(ALL(perm), [&](int a, int b) { return dists[a] < dists[b]; });
    l.resize(m);
    r.resize(m);
    REP (i, m)
      l[i] = perm[i];
    REP (i, m)
      r[i] = perm[i + m];
  }

  void rec(const std::vector<int> &l1, const std::vector<int> &l2) {
    assert(l1.size() == l2.size());
    int m = l1.size();
    if (m == 0) return;
    if (m <= 4) {
      if (m == 1) pair(l1[0], l2[0]);
      else {
        auto u = l2;
        std::sort(ALL(u));
        do{
          if (check(l1, u)){
            REP(i,m) pair(l1[i], u[i]);
            return;
          }

        }while(std::next_permutation(ALL(u)));
        assert(0);
      }
      return;
    }

    int a = rng() % l1.size(), b = rng() % l2.size();
    auto seg = points[l1[a]].make_seg(points[l2[b]]);

    std::vector<int> lst, l, r;
    lst.reserve(2 * m);
    for (auto x : l1) lst.pb(x);
    for (auto x : l2) lst.pb(x);
    split(lst, seg, l, r);
    std::vector<int> l11, l12, l21, l22;
    for (auto x : l) (x < m ? l11 : l21).pb(lst[x]);
    for (auto x : r) (x < m ? l12 : l22).pb(lst[x]);
    rec(l11, l22);
    rec(l12, l21);
  }

  std::vector<int> solve() {
    std::vector<int> ids;
    REP (i, 2 * n)
      ids.pb(i);
    std::vector<int> l, r;
    split(ids, Segment<s64>(Point<s64>(0, 0), Point<s64>(1, 0)), l, r);
    rec(l, r);
    return lst;
  }

  bool check(const std::vector<int> &a, const std::vector<int> &b) const {
    REP (i, a.size())
      REP (j, i) {
        if (!Segment<s64>(points[a[i]], points[b[i]])
               .intersects(Segment<s64>(points[a[j]], points[b[j]])))
          return false;
      }
    return true;
  }

  bool check_sol(const std::vector<int> &s) const {
    std::vector<int> a, b;
    REP (i, s.size()) {
      int ii = s[i];
      if (ii < i) a.pb(i), b.pb(ii);
    }
    return check(a, b);
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
    // if (ti != 240) continue;
    printf("Case #%d: ", ti + 1);
    if (TEST_CHECK) {
      auto r2 = sc.solve_dumb();
      assert(sc.check_sol(r2));
      auto r1 = sc.solve();
      if (r1 != r2) {
        OPA_DISP0(r1, r2);
        OPA_DISP0(sc.points);
        OPA_DISP0(sc.check_sol(r1));
        assert(r1 == r2);
      }
    } else {

      auto res = sc.solve();
      for (auto &x : res) printf("%d ", x + 1);
    }
    puts("");
  }

  return 0;
}
