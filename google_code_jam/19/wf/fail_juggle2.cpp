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

struct hash_t {
  template<typename T1,typename T2> size_t operator()(const std::pair<T1,T2> &x) const {
    size_t h1 = std::hash<T1>{}(x.first);
    size_t h2 = std::hash<T1>{}(x.second);
    return (h1 * 31 + h2) ^ h1;
  }
};

std::mt19937 rng(0);
// clang-format on
template <class T> T _gcd(T a, T b) { return b == 0 ? a : _gcd(b, a % b); }
template <class T> T gcd(T a, T b) { return _gcd(std::max(a, b), std::min(a, b)); }
template <class T> int sign(T a) { return a > 0 ? 1 : (a < 0 ? -1 : 0); }

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
  std::pair<T, T> as_pair() const { return MP(p, q); }
  frac operator+(const frac &peer) const { return frac(p * peer.q + peer.p * q, peer.q * q); }
  frac operator-(const frac &peer) const { return frac(p * peer.q - peer.p * q, peer.q * q); }
  frac operator*(const frac &peer) const { return frac(p * peer.p, peer.q * q); }
  frac operator/(T d) const { return frac(p, q * d); }
  bool operator<(const frac &peer) const { return (p * peer.q - peer.p * q) < 0; }
};

template <class T> struct Point {
  T x, y;
  Point() {}
  Point(T x, T y) : x(x), y(y) {}
  Point operator-(const Point &peer) const { return Point(x - peer.x, y - peer.y); }
  bool operator<(const Point &peer) const { return as_pii() < peer.as_pii(); }
  bool operator==(const Point &peer) const { return x == peer.x && y == peer.y; }
  Point abs() const { return Point(std::abs(x), std::abs(y)); }
  T cross(const Point &peer) const { return 1ll * x * peer.y - 1ll * y * peer.x; }
  std::pair<T, T> as_pii() const { return MP(x, y); }

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
  frac<T> slope() const { return frac<T>(b.y - a.y, b.x - a.x); }

  frac<s128> eval(const T &x) const { return frac<s128>(b.y - a.y, b.x - a.x) * (x - a.x) + a.y; }

  bool vertical() const { return a.x == b.x; }
  bool parallel(const Segment &peer) const { return (b - a).cross(peer.b - peer.a) == 0; }
};

struct Generator {
  bool check_colinear(Point<s32> pt, const std::vector<Point<s32> > &lst) {
    std::unordered_set<pii, hash_t> mp;
    for (auto &e : lst) {
      if (pt == e) return false;
      if (!mp.insert((e - pt).simplify().as_pii()).second) return false;
    }
    return true;
  }
  std::vector<pii> generate_points(int n, int lim) {
    std::uniform_int_distribution<> dis(-lim, lim);
    std::unordered_set<int> seen;
    std::vector<Point<s32> > pts;

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
    std::vector<pii> res;
    for (auto &x : pts) res.pb(x.as_pii());
    return res;
  }
};

namespace std {
template <class T> std::ostream &operator<<(std::ostream &os, const Point<T> &a) {
  return os << a.as_pii();
}
template <class T> std::ostream &operator<<(std::ostream &os, const frac<T> &a) {
  return os << MP(a.p, a.q);
}
template <class T> std::ostream &operator<<(std::ostream &os, const Segment<T> &a) {
  return os << "Seg(" << a.a << ", " << a.b << ")";
}
} // namespace std

#ifndef TEST_RAND
#define TEST_RAND 0
#endif

#ifndef TEST_CHECK
#define TEST_CHECK 0
#endif

struct Event {
  s64 x;
  int id;
  bool remove;
  bool operator<(const Event &e) const { return x < e.x; }
  bool operator>(const Event &e) const { return x > e.x; }
};

struct State {
  int id;
  State(int id) : id(id) {}
};

struct StateComparer {
  s64 pos;
  const std::vector<Segment<s64> > *segs;

  bool operator()(const State &s1, const State &s2) const {
    return segs->at(s1.id).eval(pos) < segs->at(s2.id).eval(pos);
  }
};

struct SolverContext {
  char buf[11111];
  const int maxv = 1 ? 5 : 1e9;
  const s64 xinter_lim = 5ll * maxv * maxv;

  std::istringstream iss;
  std::istringstream &readline() {
    fgets(buf, sizeof(buf) - 1, stdin);
    iss = std::istringstream(buf);
    return iss;
  }
  std::vector<Segment<s64> > segs;
  std::unordered_set<int> blacklist;
  std::set<State, StateComparer> sl;
  int n;

  void read() {
    if (TEST_RAND) {
      n = (rng() % 50 + 3);
      n = 3;
      Generator gen;
      auto pts = gen.generate_points(n * 2, maxv);
      REP (i, n)
        segs.emplace_back(P64(pts[2 * i].first, pts[2 * i].second),
                          P64(pts[2 * i + 1].first, pts[2 * i + 1].second));

    } else {
      scanf("%d", &n);
      REP (i, n) {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        segs.emplace_back(P64(a, b), P64(c, d));
      }
    }
  }
  std::set<State>::iterator update(const std::set<State>::iterator &it) {
    auto pit = it;
    if (it == sl.end()) return it;
    if (it == sl.begin()) return it;
    --pit;
    if (pit == sl.end()) return it;
    OPA_DISP("Testit ", it->id, pit->id);
    auto &s0 = segs[it->id];
    auto &s1 = segs[pit->id];

    if (s0.intersects(s1)) return it;
    blacklist.insert(it->id);
    blacklist.insert(pit->id);
    auto fit = sl.erase(sl.erase(pit));
    return update(fit);
  }

  std::vector<int> solve() {
    std::priority_queue<Event, std::vector<Event>, std::greater<Event> > pq;
    StateComparer sc;
    sc.segs = &segs;
    sc.pos = -xinter_lim;

    sl = std::set<State, StateComparer>(sc);
    REP (i, n) {
      if (segs[i].vertical())
        blacklist.insert(i);
      else {
        Event ev1;
        ev1.id = i;
        ev1.remove = true;
        ev1.x = segs[i].a.x;
        Event ev2 = ev1;
        ev2.x = segs[i].b.x;
        ev2.remove = false;
        pq.push(ev1);
        pq.push(ev2);

        State s(i);
        update(sl.insert(s).first);
      }
    }

    while (!pq.empty()) {
      Event ev = pq.top();
      pq.pop();
      if (blacklist.count(ev.id)) continue;
      if (1) {
        puts("");
        for (auto &x : sl) OPA_DISP0(segs[x.id]);
      }
      sc.pos = ev.x;
      State s(ev.id);
      if (ev.remove) {

        auto it = sl.erase(sl.find(s));
        update(it);

      } else {
        auto it = sl.insert(s).first;
        it = update(it);
        if (it != sl.end()) update(++it);
      }
    }

    return check_list(std::vector<int>(ALL(blacklist)));
  }

  std::vector<int> check_list(const std::vector<int> &cnds) const {
    std::vector<int> lst;
    std::unordered_set<int> seen;
    std::queue<int> q;
    for (auto &i : cnds) {
      seen.insert(i);
      q.push(i);
    }

    while (!q.empty()) {
      int i = q.front();
      q.pop();
      bool bad = false;
      REP (j, n)
        if (i != j) {
          if (!segs[i].intersects(segs[j])) {
            bad = true;
            if (seen.insert(j).second) q.push(j);
          }
        }
      if (bad) lst.pb(i);
    }
    std::sort(ALL(lst));
    return lst;
  }

  std::vector<int> solve_dumb() {
    std::vector<int> lst;
    REP (i, n)
      lst.pb(i);
    return check_list(lst);
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
    if (ti != 240) continue;
    printf("Case #%d: ", ti + 1);
    if (TEST_CHECK) {
      auto r1 = sc.solve();
      auto r2 = sc.solve_dumb();
      if (r1 != r2) {
        OPA_DISP0(r1, r2);
        OPA_DISP0(sc.segs);
        assert(r1 == r2);
      }
    } else {

      auto res = sc.solve();
      if (res.size() == 0)
        printf("MAGNIFICIENT");
      else {
        for (auto &x : res) printf("%d ", x + 1);
      }
    }
    puts("");
  }

  return 0;
}
