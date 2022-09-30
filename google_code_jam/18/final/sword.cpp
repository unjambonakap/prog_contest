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

#ifndef TEST_RAND
#define TEST_RAND 0
#endif

#ifndef TEST_CHECK
#define TEST_CHECK 0
#endif

std::mt19937 rng(0);

struct graph {
  std::vector<vi> edges;
  int n;
  std::vector<vi> sccs;
  std::vector<int> stack;
  std::vector<int> vis;
  std::vector<vi> prev_cc_edges;
  std::vector<vi> cc_edges;
  std::vector<int> v2cc;
  int visid;

  graph(int n) : n(n) { edges.resize(n); }
  void adde(int a, int b) { edges[a].pb(b); }
  void compute_sccs() {
    vis.resize(n, 0);
    v2cc.resize(n, -1);
    visid = 0;
    REP (i, n) {
      if (!vis[i]) {
        OPA_DISP0(i, visid);
        dfs(i);
        assert(v2cc[i] != -1);
      }
    }
  }

  int dfs(int a) {
    if (vis[a] != 0) return vis[a];
    int md = vis[a] = ++visid;

    stack.pb(a);

    for (auto &x : edges[a]) {
      if (v2cc[x] == -1) checkmin(md, dfs(x));
    }
    OPA_DISP0(a, md, vis[a]);

    if (md == vis[a]) {
      std::vector<int> cc;
      while (stack.size() > 0) {
        int u = stack.back();
        stack.pop_back();
        cc.pb(u);
        if (u == a) break;
      }
      assert(cc.size() > 0);

      int ccid = sccs.size();
      sccs.pb(cc);
      std::set<int> cce;

      for (auto &x : cc) v2cc[x] = ccid;
      OPA_DISP0(cc);

      for (auto &x : cc) {
        for (auto &y : edges[x]) {
          assert(vis[y] != 0);
          assert(v2cc[y] != -1);
          cce.insert(v2cc[y]);
        }
      }
      assert(!cce.count(-1));
      cce.erase(ccid);
      cc_edges.emplace_back(ALL(cce));
      prev_cc_edges.emplace_back();
      for (auto &x : cce) prev_cc_edges[x].pb(ccid);
    }

    return md;
  }
};

struct SolverContext {
  int n;
  int p;
  std::vector<vi> al;
  std::vector<vi> dl;

  std::vector<vi> ia;
  std::vector<vi> id;
  void read() {
    if (TEST_RAND) {
      n = rng() % 10 + 2;
      p = rng() % 10 + 2;
      al.resize(n);
      dl.resize(n);
      ia.resize(p);
      id.resize(p);

      REP (i, n) {
        int na = rng() % p + 1;
        int nd = rng() % p + 1;
        vi perm;
        REP (i, p)
          perm.pb(i);

        if (TEST_CHECK) {
          perm.erase(perm.begin());
          al[i].pb(0);
          dl[i].pb(0);
          --na;
          --nd;
        }
        std::shuffle(ALL(perm), rng);
        REP (j, na)
          al[i].pb(perm[j]);
        std::shuffle(ALL(perm), rng);
        REP (j, nd)
          dl[i].pb(perm[j]);
        for (auto &a : al[i]) ia[a].pb(i);
        for (auto &d : dl[i]) id[d].pb(i);
      }

      return;
    }
    scanf("%d%d", &n, &p);
    id.resize(p);
    ia.resize(p);
    REP (i, n) {
      int na, nd;
      scanf("%d%d", &na, &nd);
      al.emplace_back(na);
      dl.emplace_back(nd);
      REP (j, na)
        scanf("%d", &al[i][j]);
      REP (j, nd)
        scanf("%d", &dl[i][j]);
      for (auto &a : al[i]) ia[--a].pb(i);
      for (auto &d : dl[i]) id[--d].pb(i);
    }
  }

  bool check_a0d1() {
      graph g(n + p);
      REP (i, n) {
        for (auto a : al[i]) g.adde(i, n + a);
      }
      REP (a, p) {
        std::unordered_set<int> sl(ALL(id[a]));
        REP (i, n)
          if (!sl.count(i)) g.adde(n + a, i);
      }
      g.compute_sccs();

      std::set<int> ccl;
      REP(i,n)
        ccl.insert(g.v2cc[i]);

      std::vector<bool> has_par(g.sccs.size());
      REPV (cc, g.sccs.size()) {
        for (auto &nxt : g.cc_edges[cc]) {
          has_par[nxt] = has_par[cc] || has_par[nxt] || ccl.count(cc);
        }
      }
      assert(!ccl.count(-1));
      OPA_DISP0(g.sccs);
      OPA_DISP0(g.cc_edges);
      OPA_DISP0(has_par);

      for (auto &cc : ccl) {
        if (has_par[cc]) continue;
        if (cc == g.v2cc[0]) continue;
        bool bad = false;
        for (auto x : g.sccs[cc]) {
          if (x >= n) continue;
          bool found = false;
          for (auto a : al[x])
            if (g.v2cc[n + a] != cc) {
              found = true;
              break;
            }
          if (!found) {
            bad = true;
            break;
          }
        }
        if (!bad) return true;
      }
      return false;
  }

  bool check_a0d1_small() {
    std::queue<int> can_a;
    std::set<int> seen_a;
    std::set<int> rem;
    FOR (i, 1, n)
      rem.insert(i);

    for (auto &a : al[0])
      if (seen_a.insert(a).second) can_a.push(a);

    while (!can_a.empty()) {
      int a = can_a.front();
      can_a.pop();
      vi reinsert;
      for (auto &i : id[a])
        if (rem.erase(i) > 0) reinsert.pb(i);
      for (auto &i : rem)
        for (auto &a : al[i])
          if (seen_a.insert(a).second) can_a.push(a);

      rem.clear();
      rem.insert(ALL(reinsert));
    }
    return rem.size() > 0;
  }

  bool check_a1d0() {
    std::vector<int> arem(n);
    std::set<int> seen_d;
    std::queue<int> q_d;
    int seen = 1;

    FOR (i, 1, n)
      arem[i] = al[i].size();
    for (auto &d : dl[0])
      if (seen_d.insert(d).second) q_d.push(d);

    while (q_d.size() > 0) {
      int d = q_d.front();
      q_d.pop();
      for (auto &i : ia[d]) {
        if (--arem[i] == 0) {
          ++seen;
          for (auto &d : dl[i])
            if (seen_d.insert(d).second) q_d.push(d);
        }
      }
    }
    OPA_DISP0(seen_d);
    FOR (i, 1, n)
      for (auto &a : al[i])
        if (!seen_d.count(a)) return true;
    OPA_DISP0(seen, n);
    return seen < n;
  }

  bool solve() {
    bool a0d1 = check_a0d1();
    bool a1d0 = check_a1d0();
    OPA_DISP0(a0d1, a1d0);
    return !a0d1 && !a1d0;
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
    // if (ti!=2) continue;

    printf("Case #%d: ", ti + 1);
    if (TEST_CHECK) {
      if (sc.check_a0d1() != sc.check_a0d1_small()){
        OPA_DISP0(sc.n,sc.p);
        REP(i,sc.n) OPA_DISP0(i, sc.al[i], sc.dl[i]);
        OPA_DISP0(sc.check_a0d1_small());
        assert(0);

      }
    } else {

      auto res = sc.solve();
      printf("%s", res ? "YES" : "NO");
    }
    puts("");
  }

  return 0;
}

