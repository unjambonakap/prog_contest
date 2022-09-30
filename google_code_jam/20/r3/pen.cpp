#ifndef DEBUG
#define DEBUG 0
#endif

#ifndef TEST_LARGE
#define TEST_LARGE 0
#endif

#ifndef TEST_RAND
#define TEST_RAND 0
#endif

#ifndef TEST_CHECK
#define TEST_CHECK 0
#endif

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
#define FORV(i, a, b) for(int i = (int)(b)-1; i >= (int)a; --i)

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


namespace std {
template <typename T1, typename T2> struct hash<std::pair<T1, T2> > {
  size_t operator()(const std::pair<T1, T2> &x) const {
    size_t h1 = std::hash<T1>{}(x.first);
    size_t h2 = std::hash<T1>{}(x.second);
    return (h1 * 31 + h2) ^ h1;
  }
};

template <typename T1> struct hash<std::vector<T1> > {
  size_t operator()(const std::vector<T1> &x) const {
    size_t h = 0;
    auto hx = std::hash<T1>{};
    REP (i, x.size())
      h = h * 31 + hx(x[i]);
    return h;
  }
};

} // namespace std

template <class T> T _gcd(T a, T b) { return b == 0 ? a : _gcd(b, a % b); }
template <class T> T gcd(T a, T b) { return _gcd(std::max(a, b), std::min(a, b)); }
template <class T> struct frac {
  T p, q;
  frac() {}
  frac(T p) : p(p), q(1) {}
  frac(const std::pair<T, T> &px) : frac(px.first, px.second) {}

  frac(T p, T q) : p(p), q(q) {
    T d = gcd(std::abs(p), std::abs(q));
    if (this->q < 0) this->p = -this->p, this->q = -this->q;
    this->p /= d;
    this->q /= d;
  }
  template <typename U> frac<U> as() const { return frac<U>(p, q); }
  T floor() const { return p / q; }
  T rem() const { return p % q; }
  T ceil() const { return (p + q - 1) / q; }

  std::pair<T, T> as_pair() const { return MP(p, q); }
  frac operator+(const frac &peer) const { return frac(p * peer.q + peer.p * q, peer.q * q); }
  frac operator-(const frac &peer) const { return frac(p * peer.q - peer.p * q, peer.q * q); }
  frac operator*(const frac &peer) const { return frac(p * peer.p, peer.q * q); }
  frac operator/(const frac &peer) const { return frac(p * peer.q, q * peer.p); }
  frac operator/(T d) const { return frac(p, q * d); }
  bool operator<(const frac &peer) const { return (p * peer.q - peer.p * q) < 0; }
  bool operator>(const frac &peer) const { return (p * peer.q - peer.p * q) > 0; }
  bool operator<=(const frac &peer) const { return (p * peer.q - peer.p * q) <= 0; }
};

std::mt19937 rng(0);
// clang-format on

const int N = 15;
const int maxd = 100;
const int NM = 16;
const int kAllowedDiff = 6;

struct StateData {
  std::vector<float> prob;
  std::vector<u8> pick_from;
  std::vector<u8> ql;
  float compute(int to, int from) const {
    float p = 1;
    FOR (u, to + 1, from + 1)
      p *= prob[u];
    p *= 1. * ql[to] / pick_from[to];
    return p;
  }
};

struct State_unpacked {

  bool done() const { return (rem & rem - 1) == 0; }
  int count_bucket(int x) const {
    int cnt = 0;
    FORV (i, x, N)
      cnt += rem >> i & 1;
    FORV (i, x, ql.size()) { cnt -= ql[i]; }
    return cnt;
  }
  int rem = 0;
  std::vector<u8> ql;

  StateData get_data() const {
    StateData data;
    int ccnt = 0;
    int pos = N - 1;
    data.pick_from.resize(ql.size());
    data.prob.resize(ql.size());
    data.ql = ql;
    REPV (i, ql.size()) {
      while (pos >= i) ccnt += rem >> pos & 1, --pos;
      data.pick_from[i] = ccnt;
      data.prob[i] = 1 - 1. * ql[i] / std::max(ccnt, 1);
      ccnt -= ql[i];
    }
    return data;
  }

  bool is_valid() const {
    int rem = 0;
    FORV (i, ql.size(), N)
      rem += this->rem >> i & 1;
    REPV (i, ql.size()) {
      rem += this->rem >> i & 1;
      rem -= ql[i];
      if (rem < 0) return false;
    }
    int low = N;
    int high = -1;
    REP (i, ql.size())
      if (ql[i] > 0) checkmin(low, i), checkmax(high, i);
    if (high == -1) return true;
    if (low + kAllowedDiff < high) return false;
    return true;
  }
};

struct State {
  int rem = 0;
  u64 ql;
  bool operator==(const State &peer) const { return rem == peer.rem && ql == peer.ql; }
  State(const State_unpacked &up) {
    rem = up.rem;
    ql = 0;
    REPV (i, up.ql.size())
      ql = ql * NM + up.ql[i];
  }

  State_unpacked unpack() const {
    State_unpacked res;
    res.rem = rem;
    u64 x = ql;
    while (x > 0) {
      res.ql.pb(x % NM);
      x /= NM;
    }
    return res;
  }
};

struct Result {
  float prob;
  int action = -1;
  int dist = -1;
  int valids = 0;
};

namespace std {

template <> struct hash<State> {
  size_t operator()(const State &x) const { return x.rem * 31 + x.ql; }
};
} // namespace std

struct Precomp {
  State_unpacked s0;
  std::unordered_map<State, Result> dp;

  std::pair<float, pii> compute_prob(const State_unpacked &s) const {
    if (s.done()) return MP(0, MP(0, 1));
    State_unpacked ns = s;

    auto d1 = s.get_data();
    int nx = s.ql.size();

    std::unordered_map<pii, std::pair<float, float> > tb;
    REP (i, s.ql.size()) {
      if (ns.ql[i] == 0) continue;
      ns.ql[i]--;
      FOR (a, i, N) {
        if (!(s.rem >> a & 1)) continue;
        int nrem = s.rem ^ 1 << a;
        ns.rem = nrem;
        if (!ns.is_valid()) continue;
        int bucket_a = std::min<int>(a, s.ql.size() - 1);
        float p0 = d1.compute(i, bucket_a);
        auto d2 = ns.get_data();

        REP (j, i + 1) {
          if (ns.ql[j] == 0) continue;
          ns.ql[j]--;
          float &cnt = tb[MP(i, j)].ST;
          float &sum = tb[MP(i, j)].ND;
          FOR (b, j, N) {
            int bucket_b = std::min<int>(b, s.ql.size() - 1);
            if (nrem >> b & 1) {

              ns.rem = s.rem ^ 1 << a ^ 1 << b;
              float p2 = d2.compute(j, bucket_b);

              float p = p0 * p2;
              sum += (a + b - i - j >= N) * p;
              assert(p > 0);
              cnt += p;
            }
            if (b + 1 < nx && (d2.pick_from[b + 1] == 0 || d2.pick_from[b + 1] == d2.ql[b + 1])) {
              break;
            }
          }
          ns.ql[j]++;
        }
      }
      ns.ql[i]++;
    }
    std::pair<float, pii> res = MP(-1, pii{});
    for (auto x : tb) checkmax(res, MP(x.second.second / x.second.first, x.first));

    assert(res.first >= 0);
    return res;
  }

  void compute(int n) {
    std::queue<State> q;
    s0.rem = (1 << N) - 1;
    s0.ql.pb(n);
    std::function<void(const State_unpacked &ns, int nd)> pushf = [&](const State_unpacked &ns,
                                                                      int nd) {
      auto ps = State(ns);
      auto &r = dp[ps];
      if (r.dist == -1) {
        r.dist = nd;
        q.push(ps);
      }
    };
    pushf(s0, 0);
    std::unordered_map<int, std::vector<State> > by_dist;

    while (true) {
      if (q.size() == 0) break;
      assert(q.size() > 0);
      auto sp = q.front();
      q.pop();
      auto cr = dp[sp];
      auto s = sp.unpack();
      by_dist[cr.dist].pb(sp);
      if (cr.dist > maxd) break;
      int rem = s.rem;
      int nd = cr.dist + 1;
      s.ql.pb(0);
      REP (i, s.ql.size()) {
        if (s.ql[i] == 0) continue;
        --s.ql[i];

        if (rem >> i & 1) {
          s.rem = rem ^ 1 << i;
          pushf(s, nd);
        }
        s.rem = rem;
        ++s.ql[i + 1];
        if (s.is_valid()) {
          pushf(s, nd);
          cr.valids |= 1 << i;
        }
        --s.ql[i + 1];

        ++s.ql[i];
      }
      dp[sp] = cr;
    }

    REPV (d, maxd + 1) {
      for (const auto &sp : by_dist[d]) {
        auto s = sp.unpack();
        auto &r = dp[sp];
        auto p = compute_prob(s).first;
        r.prob = p;
        if (r.dist == maxd || s.done()) continue;
        float np = 0;
        // puts("");
        // OPA_DISP0(s.ql, s.rem, p);

        int rem = s.rem;
        s.ql.pb(0);
        REP (i, s.ql.size()) {
          if (s.ql[i] == 0) continue;
          int can = s.count_bucket(i + 1);
          --s.ql[i];

          float cndp = 0;
          int cnt_pos = 0;
          if (rem >> i & 1) {
            s.rem = rem ^ 1 << i;
            assert(s.is_valid());
            cndp += dp[s].prob;
            ++cnt_pos;
          }
          s.rem = rem;
          ++s.ql[i + 1];
          // OPA_DISP0(s.ql, s.rem, is_valid(s), can);
          if (!(r.valids >> i & 1)) {
            --s.ql[i + 1];
            ++s.ql[i];
            continue;
          }
          cnt_pos += can;
          cndp += can * dp[s].prob;
          cndp /= cnt_pos;
          // OPA_DISP0(i, cndp);
          assert(cnt_pos > 0);
          if (np < cndp) np = cndp, r.action = i;
          ;
          --s.ql[i + 1];
          ++s.ql[i];
        }
        if (r.prob >= np)
          r.action = -1;
        else
          r.prob = np;
        // OPA_DISP0(r.action, r.prob);
      }
    }
    OPA_DISP0(dp.size(), dp[s0].prob);
  }
};
Precomp g_precomp;

struct SimState {
  vi vals;
};

struct Sim {
  int t, n, c;
  std::vector<SimState> tb;
  void gen_rand() {
    n = N;
    vi perm;
    REP (i, n)
      perm.pb(i);
    if (n < 8) {
      do {
        tb.emplace_back();
        tb.back().vals = perm;
      } while (std::next_permutation(ALL(perm)));
      t = tb.size();

    } else {
      t = 100000;
      tb.resize(t);

      REP (i, t) {
        std::shuffle(ALL(perm), rng);
        tb[i].vals = perm;
      }
    }
    c = 0.54 * t;
  }

  vi submit(const vi &actions) {
    vi res(t);
    bool seen = false;
    REP (i, t) {
      if (actions[i] == -1) continue;
      seen = true;

      int &v = tb[i].vals[actions[i]];
      res[i] = v != 0;
      v = std::max(v - 1, 0);
    }

    return seen ? res : vi{};
  }

  bool submit_ans(const std::vector<pii> &sol) const {
    int cnt = 0;
    REP (i, t) {
      auto p = sol[i];
      assert(p.first != p.second);
      int sc = tb[i].vals[p.first] + tb[i].vals[p.second];
      cnt += sc >= n;
    }
    OPA_DISP0(cnt, c, t, 1. * cnt / t);
    return cnt >= c;
  }
};

struct SolverContext {
  mutable Sim sim;
  mutable char buf[111111 * 20];
  int t;

  mutable std::istringstream iss;
  std::istringstream &readline() const {
    fgets(buf, sizeof(buf) - 1, stdin);
    iss = std::istringstream(buf);
    return iss;
  }

  void read() {
    if (TEST_RAND)
      sim.gen_rand();
    else
      readline() >> sim.t >> sim.n >> sim.c;
    t = sim.t;
  }
  struct StateTracking {
    std::vector<int> tries;
    std::vector<int> empty;
    State_unpacked state;
  };

  bool solve() {
    std::vector<StateTracking> track(sim.t);
    REP (i, t) {
      track[i].tries.resize(N, 0);
      track[i].empty.resize(N, 0);
      track[i].state = g_precomp.s0;
    }

    while (true) {
      std::vector<int> actions(t, -1);
      REP (i, t) {

        auto &tr = track[i];
        auto r = g_precomp.dp[tr.state];
        if (r.action == -1) continue;
        int sel = -1;
        REP (j, N)
          if (!tr.empty[j] && tr.tries[j] == r.action) {
            sel = j;
            break;
          }
        assert(sel != -1);
        actions[i] = sel;
      }
      vi res = submit(actions);
      if (res.size() == 0) break;
      REP (i, t) { update_state(track[i], actions[i], res[i]); }
    }

    std::vector<pii> sol(t);
    REP (i, t) {
      auto rx = get_choice(track[i]);
      sol[i] = rx;
    }
    return submit_ans(sol);
  }

  void update_state(StateTracking &st, int action, int res) const {
    if (action == -1) return;
    int nt = st.tries[action]++;
    st.empty[action] = res == 0;
    assert(st.state.ql.size() >= nt + 1);
    --st.state.ql[nt];
    if (res == 0) {
      assert(st.state.rem >> nt & 1);
      st.state.rem ^= 1 << nt;
    } else {
      if (st.state.ql.size() <= nt + 1) st.state.ql.pb(0);
      ++st.state.ql[nt + 1];
    }
    assert(st.state.is_valid());
  }

  pii get_choice(const StateTracking &st) const {
    pii bp = g_precomp.compute_prob(st.state).second;
    std::map<int, vi> by_tries;
    REP (i, N)
      if (!st.empty[i]) by_tries[st.tries[i]].pb(i);
    int sel1 = by_tries[bp.first].back();
    by_tries[bp.first].pop_back();
    int sel2 = by_tries[bp.second].back();
    return MP(sel1, sel2);
  }

  mutable int cntround = 0;
  vi submit(const vi &actions) const {
    if (TEST_RAND)
      return sim.submit(actions);
    else {
      assert(cntround < N * (N + 1) / 2);
      ++cntround;

      bool seen = false;

      assert(N == 15);
      REP (i, actions.size()) {
        seen |= actions[i] != -1;
        assert(actions[i] >= -1 && actions[i] < N);
        printf("%d", actions[i] + 1);
        if (i != actions.size() - 1) printf(" ");
      }
      puts("");
      fflush(stdout);
      if (!seen) return {};
      vi res(actions.size());
      readline();
      REP (i, res.size()) {
        assert(iss >> res[i]);
        assert(res[i] != -1);
        // if (res[i] == -1) exit(0);
      }
      return res;
    }
  }

  bool submit_ans(const std::vector<pii> &sol) const {
    if (TEST_RAND) {
      return sim.submit_ans(sol);
    }
    REP (i, sol.size())
      printf("%d %d ", sol[i].ST + 1, sol[i].ND + 1);
    puts("");
    fflush(stdout);
    return true;
  }
};

int main() {
  srand(0);
  SolverContext sc0;
  g_precomp.compute(N);

  if (0) {
    for (auto x : g_precomp.dp) {
      auto s = x.first.unpack();
      if (s.done()) continue;
      // if (++step >= 10) break;
      auto choice = g_precomp.compute_prob(s);
      auto cr = g_precomp.dp[s];
      vi perm;
      REP (i, N)
        perm.pb(i);
      OPA_DISP0(s.ql, s.rem);

      int cnt = 0;
      int cnt_discover = 0;
      int sum = 0;
      do {
        vi rem;
        for (auto x : perm)
          if (s.rem >> x & 1) rem.pb(x);
        vi used;
        vi startp;
        REP (i, s.ql.size()) {
          startp.pb(used.size());
          REP (j, s.ql[i])
            used.pb(i);
        }
        assert(used.size() == rem.size());
        bool bad = false;
        REP (i, used.size())
          bad |= (rem[i] -= used[i]) < 0;
        if (bad) {
          continue;
        }

        if (cr.action != -1) {
          cnt_discover += rem.at(startp[cr.action]) != 0;
        }
        ++cnt;
        // OPA_DISP0(choice, startp, s.ql);
        int v1 = rem.at(startp[choice.second.first]++);
        int v2 = rem.at(startp[choice.second.second]++);
        sum += (v1 + v2 >= N);

      } while (std::next_permutation(ALL(perm)));
      float p1 = 1. * cnt_discover / cnt;
      float realp = 1. * sum / cnt;

      OPA_DISP0(cnt, realp, choice.first, choice.second, cr.action, p1);
      if (choice.second.first != choice.second.second)
        assert(std::abs(realp - choice.first) < 1e-5);
      assert(cnt > 0);
    }
    exit(0);
  }

  SolverContext sc;
  sc.read();
  if (!sc.solve()) puts("FAIL");

  OPA_DISP0(g_precomp.dp.size(), g_precomp.dp[g_precomp.s0].prob);
  return 0;
}
