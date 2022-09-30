
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
#include <complex>
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
std::pair<A, B> operator-(const std::pair<A, B> &a) {
  return MP(-a.ST, -a.ND);
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
template <class T> T _egcd(T a, T b, T ua, T va, T ub, T vb, T &ud, T &vd) {
  if (b == 0) {
    ud = ua;
    vd = va;
    return a;
  }
  T m = a / b;
  return _egcd(b, a - b * m, ub, vb, ua - m * ub, va - m * vb, ud, vd);
}
template <class T> T egcd(T a, T b, T &ud, T &vd) {
  if (std::abs(a) < std::abs(b)) return egcd(b, a, vd, ud);
  return _egcd<T>(a, b, 1, 0, 0, 1, ud, vd);
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
typedef long double ld;
const ld eps = 1e-5;
const ld pi = acos(-1.);
const int maxm = 512;
struct Point {
  int c[3];
  Point() {
    REP (i, 3)
      c[i] = 0;
  }

  Point operator-(const Point &peer) const {
    Point res;
    REP (i, 3)
      res.c[i] = c[i] - peer.c[i];
    return res;
  }

  Point operator+(const Point &peer) const {
    Point res;
    REP (i, 3)
      res.c[i] = c[i] + peer.c[i];
    return res;
  }

  Point operator-() const { return Point() - *this; }

  Point operator+(int v) const {
    Point res;
    REP (i, 3)
      res.c[i] = c[i] + v;
    return res;
  }
  Point cross(const Point &peer) const {
    Point res;
    REP (i, 3) {
      int ia = (i + 1) % 3;
      int ib = (i + 2) % 3;
      res.c[i] = c[ia] * peer.c[ib] - c[ib] * peer.c[ia];
    }
    return res;
  }

  int linf() const {
    int res = 0;
    REP (i, 3)
      checkmax(res, std::abs(c[i]));
    return res;
  }

  int get_e() const {
    REP (i, 3)
      if (c[i]) return i;
    assert(0);
  }

  std::vector<int> as_vec() const { return std::vector<int>(c, c + 3); }

  bool operator==(const Point &peer) const {
    REP (i, 3)
      if (c[i] != peer.c[i]) return false;
    return true;
  }

  int dot(const Point &peer) const {
    int res = 0;
    REP (i, 3)
      res += c[i] * peer.c[i];
    return res;
  }
};
namespace std {

template <> struct hash<Point> {
  size_t operator()(const Point &x) const { return std::hash<std::vector<int> >{}(x.as_vec()); }
};

} // namespace std

const s64 inf = LONG_LONG_MAX;
struct Rect {
  Point low, high;
  bool contains(int e, int px) const { return low.c[e] <= px && px < high.c[e]; }
};
struct Remapper {
  std::map<int, int> rmp;
  std::vector<int> mp;
  void build() {
    for (auto &x : rmp) x.second = mp.size(), mp.pb(x.first);
  }
};
struct Event {
  int t, tper;
  int e;
  bool dir;
  int id;

  s64 inter(const Event &peer) const {
    if (peer.id == id) return inf;
    if (t == peer.t) return t;
    if (e == peer.e) {
      if (dir == peer.dir) return inf;
      return (t + peer.t) / 2;
    } else {
      int d = gcd(tper, peer.tper);
      int diff = t - peer.t;
      if (diff % d) return inf;
      s64 ad, bd;
      s64 mod = (1ull * peer.tper / d * tper);
      s64 t1 = (mod - tper);
      egcd<s64>(t1, peer.tper, ad, bd);
      ad *= diff / d;
      bd *= diff / d;
      auto res = (t + tper * ad) % mod;

      res = (res + mod) % mod;
      assert(res % tper == t);
      assert(res % peer.tper == peer.t);
      assert(res >= 0);
      return res;
    }
  }
};

namespace std {
std::ostream &operator<<(std::ostream &os, const Event &a) {
  return os << "Event(" << OPA_DISP_STR(a.e, a.id, a.dir, a.t, a.tper) << ")";
}
std::ostream &operator<<(std::ostream &os, const Point &a) {
  return os << "Point(" << a.as_vec() << ")";
}
} // namespace std

Point get_dir(const std::string &s) {
  Point dir;
  if (s[0] == 'x') dir.c[0] = 1;
  if (s[0] == 'y') dir.c[1] = 1;
  if (s[0] == 'z') dir.c[2] = 1;
  if (s[1] == '-') dir = -dir;
  return dir;
}

struct Entry {
  Point p;
  std::string f, d;
  Point dir;
  Point up;
  Point normal;
  void build() {
    up = get_dir(f);
    dir = get_dir(d);
    normal = dir.cross(up);
  }
  int px() const { return std::abs(normal.dot(p)); }
};

const int maxn = 1111;
struct SolverContext {
  int n, k;
  std::vector<Rect> cubes;
  std::vector<Entry> entries;
  Remapper rmp[3];

  void addpt0(const Point &p) {
    REP (i, 3)
      rmp[i].rmp.emplace(p.c[i], 0);
  }
  void addpt(const Point &p) {
    addpt0(p + -1);
    addpt0(p + 1);
    addpt0(p);
  }
  Point iremap(const Point &a) {
    Point res;
    REP (i, 3)
      res.c[i] = rmp[i].mp[a.c[i]];
    return res;
  }
  Point remap(const Point &a) {
    Point res;
    REP (i, 3)
      res.c[i] = rmp[i].rmp[a.c[i]];
    return res;
  }

  void read() {
    scanf("%d%d", &n, &k);
    cubes.resize(n);
    REP (i, n) {
      auto &u = cubes[i];
      REP (i, 3)
        scanf("%d", &u.low.c[i]);
      REP (i, 3)
        scanf("%d", &u.high.c[i]);
      addpt(u.low);
      addpt(u.high + -1);
    }

    entries.resize(k);
    REP (i, k) {
      auto &u = entries[i];
      REP (i, 3)
        scanf("%d", &u.p.c[i]);
      char buf[5];
      scanf("%s", buf);
      u.f = buf;
      scanf("%s", buf);
      u.d = buf;
      addpt(u.p);
    }

    REP (i, 3) {

      rmp[i].build();
      assert(rmp[i].mp.size() < maxn);
    }

    for (auto &u : cubes) {
      u.low = remap(u.low);
      u.high = remap(u.high);
    }

    for (auto &u : entries) {
      u.p = remap(u.p);
      u.build();
    }
  }

  int map[maxn][maxn];
  void fillmap(int e, const Rect &cx) {
    int e0 = (e + 1) % 3, e1 = (e + 2) % 3;
    FOR (i, cx.low.c[e0], cx.high.c[e0])
      FOR (j, cx.low.c[e1], cx.high.c[e1])
        map[i][j] = 1;
  }

  s64 solve() {

    s64 res = inf;
    std::unordered_map<std::pair<Point, Point>, std::vector<std::unique_ptr<Event> > > evl;

    REP (i, k) {

      auto &ex = entries[i];
      memset(map, 0, sizeof(map));
      int e = ex.normal.get_e();
      bool ccw = ex.normal.c[e] == 1;
      int px = ex.p.c[e];
      int e0 = (e + 1) % 3, e1 = (e + 2) % 3;

      for (auto &c : cubes)
        if (c.contains(e, px)) {
          fillmap(e, c);
        }

      pii pos = MP(ex.p.c[e0], ex.p.c[e1]);
      pii dir = MP(ex.dir.c[e0], ex.dir.c[e1]);
      pii up = MP(ex.up.c[e0], ex.up.c[e1]);
      std::set<std::pair<pii, pii> > seen;
      int t = 0;
      std::vector<Event *> cur;
      while (seen.insert(MP(pos, up)).second) {
        Point up_world;
        up_world.c[e0] = up.ST;
        up_world.c[e1] = up.ND;
        Point pos_world;
        pos_world.c[e] = px;
        pos_world.c[e0] = pos.ST;
        pos_world.c[e1] = pos.ND;
        Event *ev = new Event;
        ev->id = i;
        ev->t = t;
        ev->e = e;
        ev->dir = std::max(dir.ST, dir.ND) == 1;
        cur.pb(ev);

        evl[MP(pos_world, up_world)].emplace_back(ev);

        auto odir = dir;
        auto oup = up;
        if (used(pos + dir + up)) {
          pos = pos + dir + up;
          dir = oup;
          up = -odir;
        } else if (used(pos + dir)) {

          pos = pos + dir;
        } else {
          dir = -oup;
          up = odir;
        }
        Point npos_world;
        npos_world.c[e] = px;
        npos_world.c[e0] = pos.ST;
        npos_world.c[e1] = pos.ND;
        int dt = (iremap(pos_world) - iremap(npos_world)).linf();
        checkmax(dt, 1);
        t += dt;
      }

      for (auto e : cur) e->tper = t;
    }
    for (auto &ex : evl) {
      REP (i, ex.second.size())
        REP (j, i) {
          auto &eva = ex.second[i];
          auto &evb = ex.second[j];
          checkmin(res, eva->inter(*evb));
        }
    }

    return res;
  }
  bool used(const pii &p) const {
    if (p.ST < 0 || p.ND < 0) return false;
    return map[p.ST][p.ND];
  }
};

int main() {
  SolverContext sc;
  sc.read();
  auto res = sc.solve();
  if (res == inf)
    puts("ok");
  else
    printf("%Ld\n", res);
  return 0;
}
