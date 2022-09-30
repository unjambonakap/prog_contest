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

const int mod = 1e9 + 7;
void add(int &a, int b) { a = (a + b) % mod; }

struct Graph {
  std::vector<vi> edges;
  int n;
  std::vector<int> ccid;
  std::vector<vi> ccs;

  std::vector<int> vis;
  std::vector<int> stack;
  int cur_ccid;
  int visid = 0;
  std::unique_ptr<Graph> cc_graph;

  int dfs(int a) {
    if (ccid[a] != -1) return INT_MAX;
    if (vis[a] != -1) return vis[a];
    int best = vis[a] = visid++;
    stack.pb(a);
    for (auto &peer : edges[a]) {

      checkmin(best, dfs(peer));
    }
    if (best == vis[a]) {
      std::vector<int> cc;
      while (true) {
        int x = stack.back();
        stack.pop_back();
        cc.pb(x);
        if (x == a) break;
      }
      int cid = ccs.size();
      for (auto &x : cc) ccid[x] = cid;
      ccs.pb(cc);
    }
    return best;
  }

  void compute_ccs() {
    vis = std::vector<int>(n, -1);
    ccid = std::vector<int>(n, -1);
    cur_ccid = 0;
    visid = 0;
    REP (i, n)
      dfs(i);
    cc_graph = std::make_unique<Graph>();
    cc_graph->n = ccs.size();
    REP (cid, ccs.size()) {
      std::vector<int> el;
      for (auto &x : ccs[cid])
        for (auto &b : edges[x])
          if (ccid[b] != cid) el.pb(ccid[b]);
      cc_graph->edges.push_back(el);
    }
  }
  std::set<int> compute_reach(int target_v) {
    std::set<int> res;
    std::vector<int> vis(n, -1);

    std::function<int(int)> dfs_func = [&](int a) {
      if (a == target_v) return 1;
      int &r = vis[a];
      if (r != -1) return r;
      r = 0;
      for (auto &b : edges[a]) r |= dfs_func(b);
      return r;
    };
    REP (i, n)
      if (dfs_func(i)) res.insert(i);
    return res;
  }
};

struct SolverContext {
  std::vector<int> start;
  int n;
  Graph graph;

  void read() {
    if (TEST_RAND)
      n = rng() % 5 + 3;
    else
      scanf("%d", &n);
    graph.edges.resize(n, std::vector<int>(2));
    start.resize(n);
    graph.n = n;
    REP (i, n) {
      REP (f, 2) {
        if (TEST_RAND) {
          while (true) {
            graph.edges[i][f] = rng() % n;
            if (f == 1 && graph.edges[i][0] == graph.edges[i][1])
              ;
            else
              break;
          }
        } else
          scanf("%d", &graph.edges[i][f]), --graph.edges[i][f];
      }
    }
    REP (i, n) {
      if (TEST_RAND)
        start[i] = rng() % 10;
      else
        scanf("%d", &start[i]);
    }
  }

  int solve() {
    graph.compute_ccs();
    OPA_DISP0(graph.ccs);
    int lead = 0;
    int lead_cc = graph.ccid[lead];

    auto lead_reach = graph.cc_graph->compute_reach(lead_cc);
    vi reach_ordered(ALL(lead_reach));
    std::reverse(ALL(reach_ordered));

    std::set<int> unbounded;
    std::set<int> autogen;
    for (auto &x : lead_reach) {
      for (auto &v : graph.ccs[x]) {
        std::map<int, int> cnt;
        for (auto &b : graph.edges[v]) cnt[graph.ccid[b]] += 1;
        if (cnt[x] > 0) autogen.insert(x);
        if (cnt[x] > 1) unbounded.insert(x);
      }
    }

    OPA_DISP0(lead_reach);
    OPA_DISP0(autogen, unbounded);
    std::set<int> has;
    std::vector<int> state = start;
    REP (i, n)
      if (state[i]) has.insert(i);

    for (auto &x : reach_ordered) {
      int cnt = 0;
      bool any = 0;

      for (auto &y : graph.ccs[x]) add(cnt, state[y]), any |= has.count(y);
      if (any && unbounded.count(x)) return INT_MAX;
      if (x == lead_cc) return cnt;
      if (any && autogen.count(x)) return INT_MAX;
      if (any)
        for (auto &y : graph.cc_graph->edges[x]) {
          int u = graph.ccs[y][0];
          has.insert(u);
          add(state[u], cnt);
        }
    }
    assert(0);
  }

  int try1(bool use0) {
    std::vector<int> state = start;
    int step = 0;
    const int maxs = 20;

    int mx = 0;
    while (true) {
      ++step;
      std::vector<int> ns(n);

      REP (i, n) {
        if (i == 0 && !use0) {
          add(ns[0], state[0]);
          continue;
        }
        REP (f, 2)
          add(ns[graph.edges[i][f]], state[i]);
      }

      if (ns[0] > mx && step > maxs) return INT_MAX;
      if (step > maxs + n) return state[0];
      state = ns;
      checkmax(mx, state[0]);
    }
  }
  int solve_dumb() { return std::max(try1(false), try1(true)); }
};

int main() {
  srand(0);
  int tn;

  if (TEST_RAND)
    tn = 100000;
  else
    scanf("%d", &tn);

  REP (ti, tn) {

    SolverContext sc;
    sc.read();
    printf("Case #%d: ", ti + 1);
    if (TEST_CHECK) {
      auto r1 = sc.solve();
      auto r2 = sc.solve_dumb();
      if (r1 != r2) {
        OPA_DISP0(sc.graph.edges);
        OPA_DISP0(sc.start);
      }
      OPA_DISP0(r1, r2);
      assert(r1 == r2);
    } else {

      auto res = sc.solve();
      if (res == INT_MAX)
        printf("UNBOUNDED");
      else
        printf("%d", res);
    }
    puts("");
  }

  return 0;
}
