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
typedef __int128 s128;
typedef unsigned __int128 u128;


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

struct hash_t {
  template<typename T1,typename T2> size_t operator()(const std::pair<T1,T2> &x) const {
    size_t h1 = std::hash<T1>{}(x.first);
    size_t h2 = std::hash<T1>{}(x.second);
    return (h1 * 31 + h2) ^ h1;
  }
};

std::mt19937 rng(0);
// clang-format on

#ifndef TEST_RAND
#define TEST_RAND 0
#endif

#ifndef TEST_CHECK
#define TEST_CHECK 0
#endif
const int maxn = 111;
const int inf = maxn * maxn;
struct Map {
  int mp[maxn][maxn];
  int nx, ny;
  bool is_in(int x, int y) const { return x >= 0 && x < nx && y >= 0 && y < ny; }
  bool open(int x, int y) const { return is_in(x, y) && mp[x][y]; }
  void shift(const Map &peer, int dx, int dy) {
    REP (x, nx)
      REP (y, ny)
        mp[x][y] &= peer.open(x + dx, y + dy);
  }
};
int dd[] = { -1, 0, 1, 0, -1 };

struct MapState {
  int to[maxn][maxn];
  void compute(const Map &map, pii start) {
    memset(to, 1, sizeof(to));
    std::queue<pii> q;
    q.push(start);
    to[start.ST][start.ND] = 0;
    while (!q.empty()) {
      pii s = q.front();
      q.pop();
      int c = to[s.ST][s.ND];
      REP (k, 4) {
        pii ns = MP(s.ST + dd[k], s.ND + dd[k + 1]);
        if (map.open(ns.ST, ns.ND) && to[ns.ST][ns.ND] > inf) q.push(ns), to[ns.ST][ns.ND] = c + 1;
      }
    }
  }
};

struct SolverContext {
  char buf[11111];
  int dist[maxn][maxn];

  std::istringstream iss;
  std::istringstream &readline() {
    fgets(buf, sizeof(buf) - 1, stdin);
    iss = std::istringstream(buf);
    return iss;
  }
  pii start, end;
  Map map;
  int sol = -1;

  void read() {
    if (TEST_RAND) {
      map.ny = map.nx = 50;
      start = MP(rng() % map.nx, rng() % map.ny);
      end = MP(rng() % map.nx, rng() % map.ny);
      if (0) {

        REP (i, map.nx)
          REP (j, map.ny)
            map.mp[i][j] = 1;
      } else {
        while (true) {
          memset(map.mp, 0, sizeof(map.mp));
          int pre = rng() % 10 + 1;
          int loop = rng() % 8 + 1;
          int loop_cnt = rng() % 6 + 1;
          pii pos = start;
          vi pre_tb;
          vi loop_tb;
          REP (i, pre)
            pre_tb.pb(rng() % 4);
          REP (i, loop)
            loop_tb.pb(rng() % 4);

          bool ok = true;
          for (auto k : pre_tb) {
            map.mp[pos.ST][pos.ND] = true;
            pos.ST += dd[k];
            pos.ND += dd[k + 1];
            if (!map.is_in(pos.ST, pos.ND)) {
              ok = false;
              break;
            }
          }
          if (!ok) continue;
          int stop_at = rng() % (loop * loop_cnt) + 1;
          sol = pre + stop_at - 1 + 1;
          REP (u, loop_cnt) {
            if (!ok) break;
            for (auto k : loop_tb) {
              if (--stop_at < 0) break;
              map.mp[pos.ST][pos.ND] = true;
              pos.ST += dd[k];
              pos.ND += dd[k + 1];
              if (!map.is_in(pos.ST, pos.ND)) {
                ok = false;
                break;
              }
            }
          }
          if (!ok) continue;
          end = pos;
          map.mp[end.ST][end.ND] = true;
          break;
        }
      }

    } else {
      scanf("%d%d\n", &map.ny, &map.nx);
      REP (i, map.ny) {
        scanf("%s\n", buf);
        REP (j, map.nx) {
          map.mp[j][i] = buf[j] != '#';
          if (buf[j] == 'M')
            start = MP(j, i);
          else if (buf[j] == 'N')
            end = MP(j, i);
        }
      }
    }
  }

  int solve() {
    int res = inf;
    MapState ms_src, ms_dst;
    ms_src.compute(map, start);
    ms_dst.compute(map, end);

    REP (x, map.nx)
      REP (y, map.ny)
        checkmin(res, ms_src.to[x][y] + ms_dst.to[x][y]);

    FOR (dx, -map.nx, map.nx + 1)
      FOR (dy, -map.ny, map.ny + 1) {
        if (dx == 0 && dy == 0) continue;
        int tx = end.ST + dx;
        int ty = end.ND + dy;
        if (!map.is_in(tx, ty)) continue;
        int cur_cycle_cost = ms_dst.to[tx][ty];
        if (cur_cycle_cost + 1 >= res) continue;
        Map cur = map;
        MapState cmap = ms_dst;
        MapState cmap2;
        cmap2.compute(cur, MP(tx, ty));

        for (int k = 1; cur_cycle_cost < inf; ++k) {
          cur.shift(map, k * dx, k * dy);
          MapState nend;
          MapState ntx;
          nend.compute(cur, end);
          ntx.compute(cur, MP(tx, ty));

          REP (x, map.nx)
            REP (y, map.ny)
              if (cur.open(x, y)) {
                // new map does not change cost
                checkmin(res, (cmap2.to[x][y] + nend.to[x][y]) + ms_src.to[x + k * dx][y + k * dy] + 1);
              }
          cmap = nend;
          cmap2 = ntx;
          cur_cycle_cost = cmap.to[tx][ty];
        }
      }
    if (sol != -1) {
      if (res > sol) {
        OPA_DISP0(res, sol);
        REP (i, map.ny) {
          REP (j, map.nx)
            printf("%d", map.mp[j][i]);
          puts("");
        }
        OPA_DISP0(start, end);
        assert(res <= sol);
      }
    }
    return res;
  }

  int solve_dumb() { return 0; }
};

int main() {
  srand(0);
  int tn;

  if (TEST_RAND)
    tn = 100000;
  else
    scanf("%d\n", &tn);

  REP (ti, tn) {

    SolverContext sc;
    sc.read();

    // if (ti!=2)continue;
    if (TEST_CHECK) {
      auto r1 = sc.solve();
      auto r2 = sc.solve_dumb();
      OPA_DISP0(r1, r2);
      if (r1 != r2) {
        printf("Case #%d: ", ti + 1);
        OPA_DISP0(r1, r2);
        assert(r1 == r2);
      }
    } else {

      printf("Case #%d: ", ti + 1);
      auto res = sc.solve();
      if (res == inf)
        printf("IMPOSSIBLE");
      else
        printf("%d", res);
      puts("");
    }
  }

  return 0;
}
