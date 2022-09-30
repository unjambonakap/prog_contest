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
  std::hex << std::showbase                                                    \
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


namespace std {
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

#ifndef TEST_RAND
#define TEST_RAND 0
#endif

#ifndef TEST_CHECK
#define TEST_CHECK 0
#endif

template <class T> T _gcd(T a, T b) { return b == 0 ? a : _gcd(b, a % b); }

template <class T> T gcd(T a, T b) { return _gcd(std::max(a, b), std::min(a, b)); }

struct pt {
  int x, y;
  pt() {}
  pt(int x, int y) : x(x), y(y) {}
  pt operator-(const pt &peer) const { return pt(x - peer.x, y - peer.y); }
  pt abs() const { return pt(std::abs(x), std::abs(y)); }
  s64 cross(const pt &peer) const { return 1ll * x * peer.y - 1ll * y * peer.x; }
};

struct frac {
  s64 p, q;
  frac() {}
  frac(s64 p, s64 q) : p(p), q(q) {
    s64 d = gcd(std::abs(p), std::abs(q));
    if (this->q < 0) this->p = -this->p, this->q = -this->q;
    this->p /= d;
    this->q /= d;
  }
  frac operator+(const frac &peer) const { return frac(p * peer.q + peer.p * q, peer.q * q); }
  frac operator-(const frac &peer) const { return frac(p * peer.q - peer.p * q, peer.q * q); }
  frac operator/(int d) const { return frac(p, q * d); }
  bool operator<(const frac &peer) const { return (*this - peer).p < 0; }
};

struct ContFrac {
  std::vector<s64> tb;
  ContFrac(frac f) {
    while (true) {
      tb.pb(f.p / f.q);
      f.p -= f.q * tb.back();
      if (f.p == 0) break;
      OPA_DISP0(f.p, f.q);
      f = frac(f.q, f.p);
    }
  }

  frac comp(const frac &prev, const frac &cur, s64 ax) const {
    return frac(prev.p + cur.p * ax, prev.q + cur.q * ax);
  }
};

struct vec {
  int x, y;
  vec() {}
  vec(int _x, int _y) : x(_x), y(_y) {
    int d = gcd(std::abs(x), std::abs(y));
    if (y < 0) x = -x, y = -y;
    if (d > 0) x /= d, y /= d;
  }
  pii as_pii() const { return MP(x, y); }
  pt as_pt() const { return pt(x, y); }
  bool operator==(const vec &peer) const { return as_pii() == peer.as_pii(); }
  bool operator<=(const vec &peer) const { return cross(peer) >= 0; }
  bool operator<(const vec &peer) const { return cross(peer) > 0; }
  bool operator>(const vec &peer) const { return peer < *this; }

  pt lower_eval(int xe) const { return pt(xe, 1ll * xe * y / x); }
  pt upper_eval(int xe) const { return pt(xe, (1ll * xe * y + x - 1) / x); }
  vec swap() const { return vec(y, x); }
  s64 cross(const vec &peer) const { return 1ll * x * peer.y - 1ll * y * peer.x; }
};

struct SolverContext {
  std::vector<pii> pts;
  int n;
  const int maxv = 1e9 + 10;
  //const int maxv = 1100;
  vec low, high;
  pii bad{ INT_MAX, INT_MAX };

  void read() {
    if (TEST_RAND) {
      n = rng() % 10 + 2;
      n = 2;
      std::map<s64, pii> seen;
      pii sol(rng() % maxv + 1, rng() % maxv + 1);

      REP (i, n) {
        while (true) {
          pii pt(rng() % maxv + 1, rng() % maxv + 1);
          s64 v = 1ll * sol.ST * pt.ST + 1ll * sol.ND * pt.ND;
          v = rng();
          if (seen.emplace(v, pt).second) break;
        }
      }
      for (auto &kv : seen) pts.pb(kv.second);

      return;
    }

    scanf("%d", &n);
    REP (i, n) {
      pii pt;
      scanf("%d %d", &pt.first, &pt.second);
      pts.pb(pt);
    }
  }

  pii solve() {
    low = vec(maxv, 1);
    high = vec(1, maxv);

    REP (i, n - 1) {
      auto &a = pts[i];
      auto &b = pts[i + 1];
      if (a.ST == b.ST && a.ND > b.ND) return bad;
      if (a.ND == b.ND && a.ST > b.ST) return bad;

      pii d(a.ST - b.ST, b.ND - a.ND);
      vec mid(d.ND, d.ST);
      OPA_DISP0(mid.as_pii(), d);
      if (mid.x < 0) {
        if (d.ND < 0) return bad;
        continue;
      }
      if (d.ST == 0 || d.ND == 0) continue;
      if (d.ND < 0)
        checkmin(high, mid);
      else
        checkmax(low, mid);
    }
    return solveit(low, high);
  }

  pii solve_dumb() const {
    FOR (i, 1, 2000)
      FOR (j, 1, 2000)
        if (checkit(MP(i, j))) return MP(i, j);
    FOR (i, 1, 2000)
      FOR (j, 1, 2000)
        if (checkit(MP(i, j))) return MP(i, j);
    return bad;
  }

  frac solve_contfrac(const vec &low, const vec &high) {
    frac flow(low.y, low.x);
    frac fhigh(high.y, high.x);
    auto valid = [&](const frac &f) { return flow < f && f < fhigh; };

    frac mid = (flow + fhigh) / 2;
    OPA_DISP0(mid.p, mid.q, flow.p, flow.q, fhigh.p, fhigh.q);
    ContFrac cf(mid);
    frac pprev(0, 1);
    pprev.p = 1;
    pprev.q = 0;

    frac pcur(cf.tb[0], 1);
    OPA_DISP0(cf.tb);
    frac res;
    if (valid(pcur)) {
      res = pcur;
    } else {
      assert(cf.tb[1] > 0);

      //assert(valid(mid));

      FOR (i, 1, cf.tb.size()) {
        s64 x = cf.tb[i];
        if (valid(pcur)) {
          res = pcur;
          break;
        }
        auto np = cf.comp(pprev, pcur, x);
        OPA_DISP0(np.p, np.q, x);
        if (valid(np)) {
          s64 T = 1, H = x - 1, best = x;
          while (T <= H) {
            s64 M = (T + H) / 2;
            if (valid(cf.comp(pprev, pcur, M)))
              best = M, H = M - 1;
            else
              T = M + 1;
          }
          res = cf.comp(pprev, pcur, best);
          break;
        }
        pprev = pcur;
        pcur = np;
      }
    }
    s64 T = 1, H = res.p - 1, best = res.p;
    while (T <= H) {
      s64 M = (T + H) / 2;
      if (valid(frac(M, res.q)))
        H = M - 1, best = M;
      else
        T = M + 1;
    }
    return frac(best, res.q);
    assert(0);
  }

  pii solveit(const vec &low, const vec &high) {
    if (high <= low) return bad;
    if (1) {
      auto rf = solve_contfrac(low, high);
      return MP(rf.q, rf.p);
    }

    vec m1(maxv + 1, maxv);
    vec m2(maxv, maxv + 1);
    FOR (x, 1, 1e7) {
      auto px = low.lower_eval(x);
      px.y += 1;
      if (px.cross(high.as_pt()) > 0) return MP(px.x, px.y);
    }
    return std::min(go1(low, std::min(m2, high)), swap(go1(high.swap(), std::max(low, m1).swap())));
  }

  pii swap(pii p) const { return MP(p.ND, p.ST); }

  pii go1(const vec &l, const vec &h) {
    if (h <= l) return bad;
    int H = std::max(l.x, h.x) * 2 + 10;
    std::vector<pt> lowp, highp;
    lowp.emplace_back(0, 0);
    highp.emplace_back(l.lower_eval(H));
    highp.emplace_back(h.upper_eval(H));
    return rec(l, h, lowp, highp);
  }

  bool has_interior(const std::vector<pt> &lowp, const std::vector<pt> &highp) const {
    std::vector<pt> pts;
    pts.pb(lowp[0]);
    pts.pb(highp[0]);
    pts.pb(highp[1]);
    if (lowp.size() == 2) pts.pb(lowp[1]);
    pts.pb(pts[0]);
    s64 s = 0;
    REP (i, pts.size() - 1) { s += pts[i].cross(pts[i + 1]); }
    REP (i, pts.size() - 1) { s -= count_points_seg(pts[i], pts[i + 1]) - 1; }
    s = s / 2 + 1;
    return s > 0;
  }

  int count_points_seg(const pt &p1, const pt &p2) const {
    pt diff = (p2 - p1).abs();
    int d = gcd(diff.x, diff.y);
    return d + 1;
  }

  pii rec(const vec &l, const vec &h, const std::vector<pt> &lowp,
          const std::vector<pt> &highp) const {
    if (!has_interior(lowp, highp)) {
      // OPA_DISP0("bad", lowp[0].x, highp[1].x, highp[1].y);
      return bad;
    }

    if (lowp[0].x + 50 >= highp[0].x) {
      FOR (x, lowp[0].x, highp[0].x + 1) {
        auto pt = l.lower_eval(x);
        pt.y += 1;
        if (pt.cross(high.as_pt()) > 0) return MP(pt.x, pt.y);
      }
      return bad;
    }
    int M = ((s64)lowp[0].x + highp[0].x) / 2;
    assert(M > 0);
    // OPA_DISP0(M, lowp[0].x, highp[0].x);
    std::vector<pt> nm;
    nm.pb(l.lower_eval(M));
    nm.pb(h.upper_eval(M));
    pii best = rec(l, h, lowp, nm);
    if (best != bad) return best;
    if (nm[0].y + 1 < nm[1].y) return MP(M, nm[0].y + 1);
    return rec(l, h, nm, highp);
  }

  bool checkit(const vec &l, const vec &h, const pt &p) const {
    return l.as_pt().cross(p) > 0 && p.cross(h.as_pt()) > 0;
  }

  bool checkit(const pii &score) const {
    if (score.ST < 0 || score.ND < 0) return false;
    REP (i, n - 1) {
      auto &a = pts[i];
      auto &b = pts[i + 1];
      s64 v1 = 1ll * a.ST * score.ST + 1ll * a.ND * score.ND;
      s64 v2 = 1ll * b.ST * score.ST + 1ll * b.ND * score.ND;
      if (v1 >= v2) return false;
    }
    return true;
  }
};

int main() {
  srand(0);
  int tn;

  if (TEST_RAND)
    tn = 100000;
  else
    scanf("%d", &tn);

  int mx = 0;
  REP (ti, tn) {

    SolverContext sc;
    sc.read();
    printf("Case #%d: ", ti + 1);
    if (TEST_CHECK) {

      if (0) {
        auto v1 = vec(rng() % sc.maxv + 1, rng() % sc.maxv + 1);
        // if (ti != 215) continue;
        auto v2 = vec(v1.x, v1.y + 1);
        printf("%d %d %d %d\n", v1.x, v1.y, v2.x, v2.y);

        REP (f, 10) {
          auto res = sc.solveit(v1, v2);
          checkmax(mx, std::min(res.ST, res.ND));
          printf("%d %d >>> %d\n", res.ST, res.ND, mx);
        }
        printf("%d %d %d %d\n", v1.x, v1.y, v2.x, v2.y);
        if (0) break;
        continue;
      }

      auto r1 = sc.solve();
      auto r2 = sc.solve_dumb();
      if (r1 != r2) {

        OPA_DISP0(r1, r2, sc.pts);
      }
      assert(r1 == r2);
    } else {

      auto res = sc.solve();
      if (res.ST == INT_MAX)
        printf("IMPOSSIBLE");
      else
        printf("%d %d", res.ST, res.ND);
    }
    puts("");
  }

  return 0;
}
