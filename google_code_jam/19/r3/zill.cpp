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

std::mt19937_64 rng(0);
// clang-format on

#ifndef TEST_RAND
#define TEST_RAND 0
#endif

#ifndef TEST_CHECK
#define TEST_CHECK 0
#endif

#if 1
const s64 removel = 10000000000ll;
// const s64 startl = 30 * removel;
const s64 startl = 1000000000000ll;
#else
const s64 removel = 5000000;
const s64 startl = 100 * removel;
#endif
struct PrecompReal {
  std::vector<std::pair<s64, int> > tb;
  int query(s64 p) const { return (--std::lower_bound(ALL(tb), MP(p + 1, -1)))->second; }

  PrecompReal() {

    tb.emplace_back(0, 0);
    std::priority_queue<s64, std::vector<s64>, std::greater<s64> > q;
    std::set<s64> seen;
    q.push(0);
    int cnt = 0;
    while (q.size()) {
      ++cnt;
      s64 cur = q.top();
      q.pop();
      if (cur > startl) break;
      std::set<int> val;
      tb.emplace_back(cur + removel, 0);
      int high = tb.size() - 1;

      REP (low, std::min(tb.size() - 1, tb.size() / 2 + 1)) {
        for (; high > 0 && tb[high].ST + tb[low].ST > cur; --high)
          ;
        for (int chigh = high; chigh >= 0 && tb[chigh + 1].ST + tb[low + 1].ST - 2 >= cur;
             --chigh) {
          assert(chigh >= 0);
          assert(low + 1 < tb.size());
          if (tb[chigh].ST + tb[low].ST <= cur) {
            val.insert(tb[chigh].ND ^ tb[low].ND);
          }
        }
      }

      int mex = 0;
      REP (i, val.size() + 1)
        if (!val.count(i)) {
          mex = i;
          break;
        }
      tb.back().ND = mex;
      if (tb.back().ND == tb[tb.size() - 2].ND) {
        tb.pop_back();
        continue;
      }

      REP (i, tb.size() - 1) {
        s64 nv = tb[i].ST + tb.back().ST;
        if (seen.insert(nv).second) q.push(nv);

        {
          s64 nv = tb[i].ST - 1 + tb.back().ST;
          if (seen.insert(nv).second) q.push(nv);
        }
      }
    }
    OPA_DISP0(cnt);
  }

  std::vector<s64> list_actions(s64 v) const {
    std::vector<s64> res;
    (void)v;
    return res;
  }

  s64 find_action(s64 cur, int target) const {
    cur -= removel;
    int high = tb.size() - 1;
    REP (low, std::min(tb.size() - 1, tb.size() / 2 + 1)) {
      for (; high > 0 && tb[high].ST + tb[low].ST > cur; --high)
        ;
      for (int chigh = high; chigh >= 0 && tb[chigh + 1].ST + tb[low + 1].ST - 2 >= cur; --chigh) {
        assert(chigh >= 0);
        assert(low + 1 < tb.size());
        if (tb[chigh].ST + tb[low].ST <= cur) {
          if (target == (tb[chigh].ND ^ tb[low].ND)) {
            if (tb[low].ST + tb[chigh + 1].ST - 1 < cur) return tb[chigh + 1].ST-1;
            return tb[low].ST;
          }
        }
      }
    }
    assert(0);
  }
};
PrecompReal pc;

struct Precomp {
  struct State {
    s64 x;
    State(s64 x = 0) : x(x) {}
    bool operator<(const State &u) const { return x < u.x; }
    bool operator==(const State &u) const { return x == u.x; }
  };

  struct Action {
    Action(s64 p = 0) : p(p) {}
    s64 p;
  };

  static constexpr int maxn = 1e3 + 10;
  std::map<State, int> grundy;
  Precomp() {}

  int get(const State &s) {
    return pc.query(s.x);
    if (grundy.count(s)) return grundy[s];
    std::set<int> seen;
    for (auto &a : list_actions(s)) seen.insert(get(act(s, a)));
    int &r = grundy[s];

    REP (mex, seen.size() + 1)
      if (!seen.count(mex)) return r = mex;
    assert(0);
  }

  Action find_action(const State &s, int target) const {
    return Action{ pc.find_action(s.x, target) };
  }

  std::vector<Action> list_actions(const State &state) {
    std::vector<Action> actions;
    for (auto &r : pc.list_actions(state.x)) {
      actions.push_back(r);
    }
    // REP (i, state.x - removel + 1) { actions.push_back(Action{ i }); }
    return actions;
  }

  std::vector<State> act(const std::vector<State> &px, const std::pair<int, Action> &s) {
    std::vector<State> res;
    REP (i, px.size()) {
      if (i == s.first) {
        auto repl = act(px[s.first], s.second);
        res.insert(res.end(), ALL(repl));
      } else
        res.pb(px[i]);
    }
    return res;
  }

  std::vector<State> act(const State &s, const Action &action) {
    std::vector<State> res;
    res.pb(State{ action.p });
    res.pb(State{ (int)(s.x - action.p - removel) });

    REPV (i, res.size())
      if (res[i].x == 0) res.erase(res.begin() + i);
    return res;
  }

  int get(const std::vector<State> &state) {
    int x = 0;
    for (auto &s : state) x ^= get(s);
    return x;
  }
  std::pair<int, Action> loose_play = MP(0, Action{ 0 });

  std::pair<int, Action> get_play(const std::vector<State> &state) {
    int grundy = get(state);
    if (!grundy) {
      return loose_play;
    }

    REP (i, state.size()) {
      auto x = state[i];
      int g = get(x);
      int target = grundy ^ g;
      if (target < g) {
        auto a = find_action(x, target);
        return MP(i, a);
      }
    }
    assert(0);
  }
};

struct Sim {
  std::set<std::pair<s64, s64> > s;
  int pid = 1;
  Sim() { s.emplace(0, startl); }
  void gen_rand() {}

  bool is_over() const { return s.empty(); }
  bool is_winning() const { return pid == 1 && is_over(); }

  void push(s64 p, s64 l) {
    assert(l >= 0);
    if (l >= removel) s.emplace(p, l);
  }

  void play(s64 p) {
    auto it = s.lower_bound(MP(p + 1, p));
    assert(it != s.begin());
    auto target = *--it;
    // OPA_DISP0(p, s, p - target.first, removel);
    assert(p >= target.first);
    assert(p - target.first + removel <= target.second);
    s.erase(target);
    push(target.first, p - target.first);
    push(p + removel, target.second - removel - (p - target.first));
    pid ^= 1;
  }

  s64 get_rand() {
    s64 sum = 0;
    for (auto &x : s) sum += x.second - removel + 1;
    s64 p = rng() % sum;
    for (auto &x : s) {
      s64 u = x.second - removel + 1;
      assert(u > 0);
      if (p < u) {
        // OPA_DISP("Play ", x);
        return x.first + p;
      }
      p -= u;
    }
    assert(0);
  }

  s64 to_game(const std::pair<int, Precomp::Action> &x) {

    auto it = s.begin();
    REP (i, x.first)
      ++it;
    s64 res = it->first + x.second.p;
    return res;
  }

  std::vector<Precomp::State> get_state() {
    std::vector<Precomp::State> res;
    for (auto &x : s) {
      res.emplace_back(Precomp::State(x.second));
      if (res.back().x == 0) res.pop_back();
    }
    return res;
  }
};

Precomp precomp;

struct SolverContext {
  Sim sim;
  Sim rand_sim;
  char buf[11111];
  bool _ok = false;

  std::istringstream iss;
  std::istringstream &readline() {
    fgets(buf, sizeof(buf) - 1, stdin);
    iss = std::istringstream(buf);
    return iss;
  }

  void read() {
    if (TEST_RAND) rand_sim.gen_rand();
  }

  void solve() {
    while (true) {
      s64 q = adv_play();
      // OPA_DISP0(q);
      if (q < 0) {
        if (q == -1) exit(0);
        // assert(q != -1);
        _ok = q == -2;
        break;
      }
      auto px = get_play(q);
      play(px);
    }
  }

  s64 get_play(s64 adv) {
    sim.play(adv);
    if (TEST_RAND) assert(sim.s == rand_sim.s);
    bool should_win = precomp.get(sim.get_state()) != 0;
    auto s0 = sim.get_state();
    auto play = precomp.get_play(s0);
    auto s1 = precomp.act(s0, play);
    auto res = sim.to_game(play);
    sim.play(res);
    auto s1_true = sim.get_state();

    if (TEST_RAND) {
      // OPA_DISP0(s0, s1, s1_true, play);
      // OPA_DISP0(sim.s, should_win);
      // assert(s1 == s1_true);

      if (should_win) {
        // assert(precomp.get(sim.get_state()) == 0);
        // OPA_DISP0(sim.get_state());
      }
    }
    return res;
  }

  s64 adv_play() {
    s64 x;
    if (TEST_RAND) {
      // OPA_DISP0(rand_sim.s);
      if (rand_sim.is_over()) return -2;
      x = rand_sim.get_rand();
      rand_sim.play(x);
      // OPA_DISP0(rand_sim.s);
      if (rand_sim.is_over()) return -3;
      return x;
    }

    readline() >> x;
    --x;
    return x;
  }

  void play(s64 x) {
    // OPA_DISP0(x);
    if (TEST_RAND) {
      rand_sim.play(x);
    } else {
      printf("%Ld\n", x + 1);
      fflush(stdout);
    }
  }

  bool is_ok() const {
    if (TEST_RAND) return rand_sim.is_winning();
    return _ok;
  }
};

int main() {
  srand(0);
  int tn;
  SolverContext sc0;

  if (0) {
    REP (i, startl + 1) {
      assert(pc.query(i) == precomp.get(Precomp::State(i)));
      // OPA_DISP0(i, pc.query(i), precomp.get(Precomp::State(i)));
    }

    return 0;
  }
  int w;
  if (TEST_RAND)
    tn = 3000, w = tn * (1 - 1. / 500 * 0.1);
  else
    sc0.readline() >> tn >> w;
  int cnt = 0;

  REP (ti, tn) {
    rng.seed(ti + 1);

    SolverContext sc;
    sc.read();
    // printf("Case #%d: ", ti + 1);
    if (TEST_CHECK) {
    } else {

      sc.solve();
      bool ok = sc.is_ok();
      // if (!ok) exit(0);
      // assert(ok);
      cnt += ok;
    }
  }
  OPA_DISP0(cnt, tn, tn - cnt, cnt >= w);

  return 0;
}
