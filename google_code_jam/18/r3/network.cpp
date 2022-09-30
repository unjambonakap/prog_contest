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

#ifndef TEST_LOCAL
#define TEST_LOCAL 0
#endif

#ifndef TEST_RAND
#define TEST_RAND 0
#endif

#ifndef TEST_CHECK
#define TEST_CHECK 0
#endif

std::mt19937 rng(0);
const int maxn = 55;
const int DEG = 4;
std::vector<int> canl;
int n;
int trycount;

struct SigE {
  std::vector<int> e;
  int nid;
};

struct Graph {
  std::vector<std::set<int> > el;
  std::vector<std::vector<int> > sig[maxn];
  std::map<std::vector<int>, SigE> grouped_sig1;
  std::map<int, int> ids;
  std::map<int, std::vector<int> > rmp;
  std::vector<vi> perms;
  std::vector<int> ans;
};

Graph mg;

void adde(Graph &g, int a, int ib) {
  int b = canl[ib];
  g.el[a].insert(b);
  g.el[b].insert(a);

  if (g.el[b].size() == DEG) {
    std::swap(canl[ib], canl.back());
    canl.pop_back();
  }
  if (g.el[a].size() == DEG) {
    assert(std::find(ALL(canl), a) != canl.end());
    canl.erase(std::find(ALL(canl), a));
  }
}

bool trygen() {

  mg.el.clear();
  mg.el.resize(n);
  canl.clear();
  canl.pb(0);

  REP (i, n - 1) {
    int a = i + 1;
    assert(canl.size() > 0);
    int ib = rng() % canl.size();
    canl.pb(a);
    adde(mg, a, ib);
  }
  ++trycount;

  std::vector<int> il;
  REP (i, n)
    il.pb(i);
  REP (k, DEG) {
    std::shuffle(ALL(il), rng);

    for (auto i : il) {
      while (mg.el[i].size() < DEG) {

        auto il2 = il;
        std::shuffle(ALL(il2), rng);
        bool found = false;
        for (auto b : il2) {
          if (b != i && mg.el[b].size() < DEG && !mg.el[i].count(b)) {
            mg.el[i].insert(b);
            mg.el[b].insert(i);
            // adde(i, ib);
            found = true;
            break;
          }
        }
        if (!found) return false;
        break;
      }
    }
  }
  // assert(canl.size() == 0);

  return true;
}

void compute_sig1(Graph &g, int i) {
  int dist[maxn];
  memset(dist, -1, sizeof(dist));

  std::queue<int> q;
  dist[i] = 0;
  g.sig[i].clear();
  g.sig[i].resize(n);
  q.push(i);

  while (!q.empty()) {
    int a = q.front();
    q.pop();
    g.sig[i][dist[a]].pb(a);
    for (auto &b : g.el[a]) {
      if (dist[b] == -1) {
        dist[b] = dist[a] + 1;
        q.push(b);
      }
    }
  }
}

void compute_sig2(Graph &g) {
  std::map<int, int> ids;
  int id = 0;
  for (auto &x : g.grouped_sig1) {
    for (auto &e : x.second.e) ids[e] = id;
    x.second.nid = id++;
  }

  int prev = g.grouped_sig1.size();
  while (true) {
    std::map<std::vector<std::vector<int> >, SigE> grouped_sig2;

    REP (i, n) {
      std::vector<std::vector<int> > sx;
      for (auto &by_dist : g.sig[i]) {
        std::vector<int> u;
        for (auto &x : by_dist) u.pb(ids[x]);
        std::sort(ALL(u));
        sx.pb(u);
      }
      grouped_sig2[sx].e.pb(i);
    }
    int id = 0;
    ids.clear();
    for (auto &x : grouped_sig2) {
      for (auto &e : x.second.e) ids[e] = id;
      x.second.nid = id++;
    }
    if (prev == grouped_sig2.size()) break;
    prev = grouped_sig2.size();
  }
  g.ids = ids;
}

void proc_graph(Graph &g) {
  REP (i, n) { assert(g.el[i].size() == DEG && !g.el[i].count(i)); }
  REP (i, n) { compute_sig1(g, i); }

  g.grouped_sig1.clear();
  REP (i, n) {
    std::vector<int> s1;
    for (auto &x : g.sig[i]) s1.pb(x.size());
    g.grouped_sig1[s1].e.pb(i);
  }
  compute_sig2(g);
  g.rmp.clear();

  REP (i, n)
    g.rmp[g.ids[i]].pb(i);

  std::vector<vi> perms;
  vi p0;
  REP (i, n)
    p0.pb(i);
  perms.pb(p0);

  for (auto &x : g.rmp) {
    std::vector<vi> nperms;
    auto u = x.second;
    std::sort(ALL(u));
    for (auto p : perms) {
      do {
        REP (i, u.size()) { p[x.second[i]] = u[i]; }
        nperms.pb(p);
      } while (std::next_permutation(ALL(u)));
    }
    perms = nperms;
  }
  g.perms = perms;
}

Graph get_query_graph() {
  Graph ng;
  ng.el.resize(n);
  if (TEST_LOCAL) {
    std::vector<int> p;
    REP (i, n)
      p.pb(i);
    std::shuffle(ALL(p), rng);
    REP (i, n)
      for (auto &x : mg.el[i]) ng.el[p[i]].insert(p[x]);
    ng.ans = p;

  } else {

    printf("%d\n", n);
    REP (i, n)
      for (auto &x : mg.el[i])
        if (x > i) printf("%d %d\n", i + 1, x + 1);
    fflush(stdout);
    int nn;
    scanf("%d", &nn);
    assert(n == nn);
    REP (i, nn * 2) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a;
      --b;
      ng.el[a].insert(b);
      ng.el[b].insert(a);
    }

  }

  proc_graph(ng);
  return ng;
}

bool check_iso(Graph &g, Graph &ng, const std::vector<int> &perm) {
  REP (i, n)
    for (auto &b : g.el[i]) {
      if (!ng.el[perm[i]].count(perm[b])) return false;
    }
  return true;
}

std::vector<int> find_perm(Graph &g, Graph &ng) {
  std::vector<int> bperm(n);
  for (auto &x : g.rmp) {
    REP (i, x.second.size())
      bperm[x.second[i]] = ng.rmp[x.first][i];
  }

  for (auto &p : g.perms) {
    std::vector<int> bcomp(n);
    REP (i, n)
      bcomp[i] = bperm[p[i]];
    if (check_iso(g, ng, bcomp)) return bcomp;
  }
  assert(0);
}

void solve() {
  trycount = 0;
  while (true) {
    while (true) {
      if (trygen()) break;
    }
    proc_graph(mg);

    if (mg.rmp.size() <= 1) continue;
    if (n > 11 && mg.rmp.size() != n) continue;
    // if (rmp.size() <= 2) continue;

    int cnt = 0;
    for (auto &p : mg.perms) {
      // if (p==p0) continue;
      if (check_iso(mg, mg, p)) {
        ++cnt;
      }
    }
    // OPA_DISP0(n, prev, best, ids);
    if (cnt == 1) {

      auto ng = get_query_graph();
      auto p = find_perm(mg, ng);
      if (TEST_LOCAL)
        assert(p == ng.ans);
      else {
        REP (i, n)
          printf("%d ", p[i]+1);
        puts("");
        fflush(stdout);
      }
      return;

      assert(0);
    }
  }
  assert(0);
}

int main() {
  srand(0);
  int tn;
  int l, u;

  if (TEST_RAND)
    tn = 10000;
  else
    scanf("%d", &tn);

  REP (ti, tn) {
    scanf("%d%d", &l, &u);
    if (l == -1) exit(0);
    n = u;
    solve();
  }

  return 0;
}

