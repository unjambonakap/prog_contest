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
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <functional>
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

// clang-format on
const double pi = acos(-1.0);
std::mt19937 rng(0);

#ifndef TEST_RAND
#define TEST_RAND 0
#endif

#ifndef TEST_CHECK
#define TEST_CHECK 0
#endif

const int maxn = 1111;

struct Pt {
  double x = 0, y = 0, z = 0;
  Pt() {}
  Pt(double x, double y, double z) : x(x), y(y), z(z) {}
  Pt operator-(const Pt &peer) const { return Pt(x - peer.x, y - peer.y, z - peer.z); }
  Pt operator+(const Pt &peer) const { return Pt(x + peer.x, y + peer.y, z + peer.z); }
  Pt operator/(double d) const { return Pt(x / d, y / d, z / d); }
  Pt operator*(double d) const { return Pt(x * d, y * d, z * d); }
  double norm() const { return std::sqrt(dot(*this)); }
  Pt normalize() const { return *this / this->norm(); }
  double dot(const Pt &peer) const { return x * peer.x + y * peer.y + z * peer.z; }
  Pt cross(const Pt &a) const {
    return Pt(y * a.z - z * a.y, z * a.x - x * a.z, x * a.y - y * a.x);
  }
};

std::ostream &operator<<(std::ostream &os, const Pt &pt) {
  os << pt.x << "," << pt.y << "," << pt.z;
  return os;
}

struct SolverContext {
  Pt pts[maxn];
  int n;

  void read() {
    if (TEST_RAND) {
      n = 30;
      REP (i, n) {
        while (true) {
          int bound = 50;
          pts[i].x = rng() % bound;
          pts[i].y = rng() % bound;
          pts[i].z = rng() % bound;
          bool bad = false;
          REP (j, i) {

            if (pts[i].x == pts[j].x && pts[i].y == pts[j].y) {
              bad = true;
              break;
            }
            REP (k, j) {
              auto kx = (pts[i] - pts[k]).cross(pts[j] - pts[k]);
              if (std::abs(kx.z) < 1e-7) bad = true;
              kx.normalize();
              REP (l, k) {
                if (std::abs(kx.dot(pts[l] - pts[k])) < 1e-7) {
                  bad = true;
                  break;
                }
              }
            }
          }
          if (!bad) break;
        }
        OPA_DISP0(pts[i]);
      }
      out(pts, n);

    } else {
      scanf("%d", &n);
      REP (i, n)
        scanf("%lf%lf%lf", &pts[i].x, &pts[i].y, &pts[i].z);
    }
  }
  double ang(int a, int b) const { return std::atan2(pts[b].y - pts[a].y, pts[b].x - pts[a].x); }

  double eval(int ix, int i0, int i1) const {
    Pt p0 = pts[i0];
    Pt p1 = pts[i1] - p0;
    Pt px = pts[ix] - p0;
    Pt vz = p1.normalize();
    OPA_DISP0(pts[i0], pts[i1], pts[ix], p1, vz);
    Pt vy = Pt(0, 0, 1);
    vy = (vy - vz * vy.dot(vz)).normalize();
    Pt vx = vy.cross(vz);
    double res = pi / 2 - std::atan2(px.dot(vy), px.dot(vx));
    if (res > pi) res -= 2 * pi;
    OPA_DISP0(px.dot(vy), px.dot(vx), px, vx, vy, vz, vx.dot(vy), vx.dot(vy), vy.dot(vz));
    OPA_DISP0(ix, i0, i1, res);
    return std::abs(res);
  }

  std::vector<int> solve() {
    std::vector<int> res;

    std::deque<int> dq;
    std::set<int> rem;
    {
      REP (i, n)
        rem.insert(i);
      int p0 = *std::min_element(ALL(rem),
                                 [&](const int &a, const int &b) { return pts[a].x < pts[b].x; });
      rem.erase(p0);
      int p1 = *std::max_element(
        ALL(rem), [&](const int &a, const int &b) { return ang(p0, a) < ang(p0, b); });
      rem.erase(p1);
      res.pb(p0);
      res.pb(p1);
    }

    REP (npick, n - 3) {
      int p0 = res[res.size() - 2];
      int p1 = res[res.size() - 1];
      int p2 = *std::min_element(
        ALL(rem), [&](const int &a, const int &b) { return eval(a, p0, p1) < eval(b, p0, p1); });
      rem.erase(p2);
      res.pb(p2);
    }

    for (auto &i : rem) res.pb(i);

    OPA_DISP0(res);
    std::reverse(ALL(res));
    FOR (i, 3, n) {
      OPA_DISP0((pts[res[i]] - pts[res[i - 2]]), pts[res[i - 1]] - pts[res[i - 2]]);
      Pt norm =
        (pts[res[i]] - pts[res[i - 2]]).cross(pts[res[i - 1]] - pts[res[i - 2]]).normalize();
      if (norm.z < 0) norm = norm * -1;
      REP (j, i - 2) {
        double v = norm.dot(pts[res[j]] - pts[res[i - 2]]);
        if (v >= 0) OPA_DISP0(i, res[j], v, norm);

        assert(v < 0);
      }
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
    scanf("%d", &tn);

  REP (ti, tn) {

    printf("Case #%d: ", ti + 1);
    SolverContext sc;

    if (TEST_CHECK) {
    } else {
      sc.read();
      auto res = sc.solve();
      REP (i, res.size())
        printf("%d ", res[i] + 1);
    }
    puts("");
  }

  return 0;
}

