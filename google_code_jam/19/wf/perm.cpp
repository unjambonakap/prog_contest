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

const int maxn = 50;
struct AddExplainer {
  int prev[maxn];
  int action[maxn];
  int cost[maxn];
  vi vals;

  bool setup(int n, const vi &vals) {
    this->vals = vals;

    memset(prev, -1, sizeof(prev));
    memset(cost, 1, sizeof(cost));
    prev[0] = 0;
    cost[0] = 0;
    std::queue<int> q;
    q.push(0);

    while (!q.empty()) {
      int a = q.front();
      q.pop();

      REP (i, vals.size()) {
        int x = vals[i];
        int na = (a + x) % n;
        if (prev[na] == -1) {
          prev[na] = a;
          action[na] = i;
          cost[na] = cost[a] + 1;
          q.push(na);
        }
      }
    }
    FOR (i, 1, n)
      if (cost[i] > 4) return false;
    return true;
  }

  vi compute_actions(int cnt) const {
    vi res;
    while (cnt != 0) {
      res.pb(action[cnt]);
      cnt = prev[cnt];
    }
    return res;
  }
};

struct AddFinder {
  std::map<int, vi> expl;
  AddExplainer get(int n) {
    vi &res = expl[n];
    if (res.size() == 0) {
      int k = std::min(n - 1, 4);
      std::vector<vi> cnds;
      cnds.pb({});
      REP (ik, k) {
        std::vector<vi> ncnds;
        for (auto e : cnds) {
          FOR (i, e.size() == 0 ? 0 : e.back() + 1, n) {
            e.pb(i);
            ncnds.pb(e);
            e.pop_back();
          }
        }

        std::swap(cnds, ncnds);
      }
      for (auto e : cnds) {
        AddExplainer ex;
        if (ex.setup(n, e)) {
          res = e;
          break;
        }
      }
      assert(res.size() > 0 || n == 1);
    }
    auto expl = AddExplainer();
    assert(expl.setup(n, res));
    return expl;
  }
};

struct Perm {
  vi tb;
  int n;
  Perm(int n) : n(n) {
    REP (i, n)
      tb.pb(i);
  }
  Perm operator+(const Perm &p) const {
    Perm res(n);
    REP (i, n)
      res.tb[i] = tb[p.tb[i]];
    return res;
  }
  void disp() const {
    REP (i, n)
      printf("%d ", tb[i] + 1);
    puts("");
  }

  Perm pw(int a) const {
    Perm res(n);
    REP (i, a)
      res = res + *this;
    return res;
  }
};
AddFinder g_finder;

struct PermExplainer {
  std::vector<Perm> cycle_perms;
  Perm cycle21;
  int mod;
  std::vector<Perm> ops;
  AddExplainer expl;
  int n;

  PermExplainer(int n) : cycle21(n), n(n) {
    mod = n - 1;
    expl = g_finder.get(mod);

    std::swap(cycle21.tb[0], cycle21.tb[1]);
    Perm cycle2n(n);
    FOR (i, 1, n)
      cycle2n.tb[1 + i % mod] = i;
    for (auto x : expl.vals) {
      cycle_perms.pb(cycle2n.pw(x));
    }

    for (auto x : cycle_perms) ops.pb(x);
    ops.pb(cycle21);
  }

  void disp() {
    printf("%lu\n", ops.size());
    for (auto &op : ops) op.disp();
  }

  std::vector<int> expl_perm(const std::vector<int> &perm) {
    std::vector<int> seq;
    std::set<int> seen;
    REP (i, n) {
      if (seen.count(i)) continue;
      std::vector<int> cycle;
      int x = i;
      cycle.pb(x);
      while (perm[x] != i) {
        x = perm[x];
        cycle.pb(x);
      }
      for (auto &u : cycle) seen.insert(u);
      if (cycle.size() == 1) continue;
      for (auto &x : cycle) push_1inv(x, seq);
      push_1inv(cycle[0], seq);
    }
    auto ans = compile(seq);
    //auto check = apply(ans, Perm(n).tb);
    //assert(perm == check);
    return ans;
  }

  vi apply(const vi &prog, vi p) const {

    Perm res(n);
    for (auto e : prog) res = res + ops[e];
    vi ans(n);
    REP(i,n) ans[i] = p[res.tb[i]];
    return ans;
  }

  std::vector<int> compile(const vi &seq) const {
    std::vector<int> res;
    int cnt = 0;
    for (int i = 0; i < seq.size();) {
      while (i < seq.size() && seq[i] != -1) cnt += seq[i++];
      cnt = (cnt % mod + mod) % mod;
      auto actions = expl.compute_actions(cnt);
      res.insert(res.end(), ALL(actions));

      cnt = 0;
      if (i < seq.size()) {
        res.pb(cycle_perms.size());
        ++i;
      }
    }
    return res;
  }

  void push_1inv(int i, std::vector<int> &seq) {
    if (i == 0) return;
    seq.pb(mod - (i - 1));
    seq.pb(-1);
    seq.pb(i - 1);
  }
};

struct SolverContext {
  char buf[11111];

  std::istringstream iss;
  std::istringstream &readline() {
    fgets(buf, sizeof(buf) - 1, stdin);
    iss = std::istringstream(buf);
    return iss;
  }
  int p, s, k, n;
  std::vector<vi> perms;
  std::vector<vi> targets;

  void read() {
    std::vector<int> id;
    if (TEST_RAND) {
      n = rng() % (maxn - 1) + 2;
      assert(n > 1);
      p = 5;
      s = 450;
      k = 30;
      REP (j, n)
        id.pb(j);
      REP (i, k) {
        std::shuffle(ALL(id), rng);
        perms.pb(id);
      }
      return;
    }

    scanf("%d%d%d%d", &p, &s, &k, &n);
    std::vector<int> tb(n);
    REP (j, n)
      id.pb(j);
    REP (i, k) {
      REP (j, n)
        scanf("%d", &tb[j]);
      std::sort(ALL(id), [&](int a, int b) { return tb[a] < tb[b]; });
      std::vector<int> ip(n);
      REP (j, n)
        ip[id[j]] = j;
      targets.pb(tb);
      perms.pb(ip);
    }
  }
  void solve() {
    PermExplainer expl(n);
    expl.disp();
    REP (i, k) {
      auto res = expl.expl_perm(perms[i]);
      auto u = expl.apply(res, targets[i]);
      OPA_DISP0(u);
      OPA_DISP0(targets[i], perms[i]);
      OPA_DISP0(res);
      REP (i, n - 1)
        assert(u[i] <= u[i + 1]);
      assert(res.size() <= s);
      printf("%lu ", res.size());
      for (auto e : res) printf("%d ", e + 1);
      puts("");
    }
  }
  int solve_dumb() { return 0; }
};

int main() {
  srand(0);
  int tn;

  if (TEST_RAND)
    tn = 10000;
  else
    scanf("%d\n", &tn);

  REP (ti, tn) {

    SolverContext sc;
    sc.read();
    if (TEST_CHECK) {
    } else {

      printf("Case #%d:\n", ti + 1);
      sc.solve();
    }
  }

  return 0;
}
