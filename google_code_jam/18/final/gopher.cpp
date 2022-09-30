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

#ifndef TEST_LOCAL
#define TEST_LOCAL 0
#endif

std::mt19937 rng(0);
const int maxs = 100000;
const int maxl = 1000000;
const int maxn = 25;
const int minn = 2;

struct Interval {
  int l, h;
  int count;
  pii vals[maxn + 1];

  Interval *prev = nullptr, *next = nullptr;

  void build(const std::set<int> &valids) {

    count = 0;
    if (l > h) return;
    for (auto &x : valids)
      if (vals[x].ST != vals[x].ND) ++count;
  }

  bool operator<(const Interval &peer) const { return count < peer.count; }
};

struct cmp {
  bool operator()(const Interval *a, const Interval *b) const { return *a < *b; }
};

typedef std::priority_queue<Interval *, std::vector<Interval *>, cmp> q_t;

struct state_t {
  std::deque<Interval> store;
  q_t q;
  std::set<int> valids;
  int t0 = 0;
  state_t() {
    FOR (i, minn, maxn + 1)
      valids.insert(i);
    store.emplace_back();
    Interval &i1 = store.back();
    i1.l = 1;
    i1.h = maxl;
    for (auto &x : valids) i1.vals[x] = MP(0, x);
    q.push(&i1);
    recompute();
  }

  pii get_query() const { return MP((q.top()->l + q.top()->h) >> 1, *valids.rbegin() * 4); }

  bool done() const { return q.empty() || q.top()->count <= 1; }

  void push(int ql, const std::vector<int> &obs) {
    Interval &ix = *q.top();
    q.pop();
    store.emplace_back();
    Interval &il = store.back();
    store.emplace_back();
    Interval &ih = store.back();
    il.prev = ix.prev;
    il.next = &ih;
    ih.prev = &il;
    ih.next = ix.next;

    il.l = ix.l;
    il.h = ql - 1;
    ih.l = ql + 1;
    ih.h = ix.h;

    int nx = obs.size();
    std::vector<int> bads;
    for (auto v : valids) {

      int sp = (v - t0 % v) % v;
      int cnt = -1;
      for (int i = sp; i + v <= nx; i += v) {
        int s = 0;
        REP (j, v)
          s += obs[i + j];
        if (cnt == -1 || cnt == s)
          cnt = s;
        else
          cnt = -2;
      }

      bool bad = true;
      OPA_DISP0(cnt, ix.vals[v].ST, ix.vals[v].ND, v, sp);
      if (cnt >= 0) {
        if (ix.vals[v].ST <= cnt && cnt <= ix.vals[v].ND) {
          il.vals[v] = MP(ix.vals[v].ST, cnt);
          ih.vals[v] = MP(cnt, ix.vals[v].ND);
          bad = false;
        }
      }
      if (bad) bads.pb(v);
    }
    for (auto x : bads) valids.erase(x);
    assert(valids.size() > 0);
    OPA_DISP0(bads, valids);

    il.build(valids);
    ih.build(valids);
    q.push(&il);
    q.push(&ih);
    t0 += nx;

    if (bads.size() > 0) recompute();
  }

  void recompute() {
    q_t nq;
    while (!q.empty()) {
      auto v = q.top();
      q.pop();
      v->build(valids);
      nq.push(v);
    }
    std::swap(q, nq);
  }

  int get_ans() const { return *valids.begin(); }
};

struct SolverContext {

  int s;
  void read() {
    if (TEST_LOCAL) {
      s = maxs;
      int n = rand() % (maxn - minn) + minn;
      REP (i, n)
        local_test.pb(rand() % (maxl + 1));
      OPA_DISP("TARGET >> ", n, local_test);
    } else{
      scanf("%d", &s);
      if (s < 0) exit(0);
    }
  }

  void solve() {
    state_t state;
    std::set<int> ql;
    while (!state.done()) {

      auto qq = state.get_query();
      OPA_DISP0(state.q.top()->l, state.q.top()->h);

      assert(ql.insert(qq.first).second);
      s -= qq.second;
      assert(s >= 0);

      auto obs = do_query(qq.ST, qq.second);
      OPA_DISP0(qq);
      state.push(qq.ST, obs);
      OPA_DISP0(obs);
    }
    int res = state.get_ans();
    if (TEST_LOCAL)
      assert(local_test.size() == res);
    else {
      printf("%d\n", -res);
      fflush(stdout);
    }
  }

  std::vector<int> do_query(int level, int count) {
    assert(level >= 1 && level <= maxl);
    std::vector<int> res(count);

    if (TEST_LOCAL) {
      REP (i, count)
        res[i] = local_query(level);

    } else {
      std::string s;
      REP (i, count)
        s += std::to_string(level) + "\n";
      printf("%s", s.data());
      fflush(stdout);
      REP (i, count) {
        scanf("%d", &res[i]);
        if (res[i] < 0) exit(0);
      }
    }
    return res;
  }

  int local_query(int level) {
    if (test_pos == local_test.size()) test_pos = 0, std::shuffle(ALL(local_test), rng);
    return local_test[test_pos++] <= level;
  }
  int test_pos = 0;
  std::vector<int> local_test;
};

int main() {
  srand(0);
  int tn;

  if (TEST_RAND || TEST_LOCAL)
    tn = 10000;
  else
    scanf("%d", &tn);

  REP (ti, tn) {

    SolverContext sc;
    sc.read();
    // printf("Case #%d: ", ti + 1);
    if (TEST_CHECK) {
    } else {

      sc.solve();
    }
  }

  return 0;
}

