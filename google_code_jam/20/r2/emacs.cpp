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
#define FORV(i, a, b) for(int i = (int)(b)-1; i >= a; --i)

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

// clang-format on

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

std::mt19937 rng(1);
const s64 inf = 1e17;

struct SolverContext {
  char buf[11111];
  int n, nq;
  std::string s;
  vi peer;
  std::vector<s64> cl, cr, cp;
  std::vector<pii> ql;
  vi par;
  vi repr;
  std::vector<vi> el;
  std::vector<s64> cost_peer;
  std::vector<vi> v2ql;
  std::vector<s64> resq;

  std::istringstream iss;
  std::istringstream &readline() {
    fgets(buf, sizeof(buf) - 1, stdin);
    iss = std::istringstream(buf);
    return iss;
  }
  const bool kLeft = false;
  const bool kRight = !kLeft;
  const bool kFrom = false;
  const bool kTo = !kFrom;

  struct NodeData {
    int parent = -1;
    int id;
    s64 cost = 0;
    bool self_parent() const { return parent == id; }
  };
  std::vector<NodeData> nd[2][2];
  void update(int x) {
    REP (f, 2) {
      auto &nl = nd[f][kLeft][x];
      auto &nr = nd[f][kRight][x];
      if (nl.parent == x) continue;
      if (nd[f][kLeft][nl.parent].self_parent()) return;
      update(nl.parent);
      update(nr.parent);
      std::vector<s64> costs(2);
      REP (side, 2)
        costs[side] =
          std::min(nl.cost + nd[f][side][nl.parent].cost, nr.cost + nd[f][side][nr.parent].cost);
      nl.cost = costs[kLeft];
      nr.cost = costs[kRight];
      nl.parent = nd[f][kLeft][nl.parent].parent;
      nr.parent = nd[f][kRight][nr.parent].parent;
    }
  }

  NodeData &access(int side, int left, int node) {
    NodeData &cur = nd[side][left][node];
    update(node);
    return cur;
  }

  void read() {
    if (TEST_RAND) {
      n = 2 * (rng() % int(30) + 1);
      nq = rng() % 2 + 1;
      cl.resize(n + 2);
      cr.resize(n + 2);
      cp.resize(n + 2);
      int nopen = 0;
      s.resize(n + 2);
      REP (i, n) {
        char c;
        if (n - i == nopen)
          c = ')';
        else if (nopen == 0)
          c = '(';
        else
          c = "()"[rng() % 5 == 0];
        nopen += c == '(' ? 1 : -1;
        s[i + 1] = c;
      }

      int cmax = 1e6;
      int clmax = cmax / (rng()%100+1);
      int crmax = cmax / (rng()%100+1);
      int cpmax = cmax / (rng()%100+1);
      FOR (i, 1, n + 1)
        cl[i] = 1 + rng() % clmax, cr[i] = 1 + rng() % crmax, cp[i] = 1 + rng() % cpmax;
      ql.resize(nq);
      REP (i, nq)
        ql[i].ST = rng() % n + 1, ql[i].ND = rng() % n + 1;

    } else {
      scanf("%d%d\n", &n, &nq);
      s.resize(n + 10);
      scanf("%s", &s[1]);
      cl.resize(n + 2);
      cr.resize(n + 2);
      cp.resize(n + 2);
      REP (i, n) scanf("%Ld", &cl[i + 1]);
      REP (i, n) scanf("%Ld", &cr[i + 1]);
      REP (i, n) scanf("%Ld", &cp[i + 1]);
      ql.resize(nq);
      REP (i, nq)
        scanf("%d", &ql[i].ST);
      REP (i, nq)
        scanf("%d", &ql[i].ND);
    }
    n += 2;
    s[0] = '(';
    s[n - 1] = ')';
    cl[0] = cr[0] = cp[0] = inf;
    cl[n - 1] = cr[n - 1] = cp[n - 1] = inf;
  }

  s64 solve() {
    vi open;
    vi dfs_order;
    vi rdfs_order;
    el.resize(n);
    v2ql.resize(n);
    resq.resize(nq, 0);
    par.resize(n, -1);
    peer.resize(n);
    repr.resize(n);
    REP (f, 2) {
      REP (side, 2) {
        nd[f][side].resize(n);
        REP (i, n) {
          nd[f][side][i].id = i;
          nd[f][side][i].parent = i;
        }
      }
    }

    REP (i, n) {
      if (s[i] == '(') {
        if (open.size() > 0) {
          int prev = open.back();
          par[i] = prev;
          el[prev].pb(i);
        }
        open.pb(i);

      } else {
        peer[i] = open.back(), peer[open.back()] = i, open.pop_back();
        dfs_order.pb(peer[i]);
      }
    }
    REP (i, n)
      repr[i] = std::min(i, peer[i]);
    REP (i, nq) {
      v2ql[repr[ql[i].first]].pb(i);
      v2ql[repr[ql[i].second]].pb(i);
    }

    rdfs_order = dfs_order;
    std::reverse(ALL(rdfs_order));

    cost_peer = cp;
    REP (ntry, 4) {
      auto prev = cost_peer;

      {
        for (auto a : dfs_order) {
          int b = peer[a];
          s64 curl = cl[b], curr = cr[a];
          for (auto x : el[a]) {
            curr += cost_peer[x] + cr[peer[x]];
            curl += cost_peer[peer[x]] + cl[x];
          }
          checkmin(cost_peer[a], curr);
          checkmin(cost_peer[b], curl);
        }
      }

      {
        for (auto a : rdfs_order) {
          int b = peer[a];
          s64 cost_left = cl[b] + cost_peer[a];
          s64 cost_right = cr[a] + cost_peer[b];
          for (auto x : el[a]) {
            cost_left += cost_peer[peer[x]] + cl[x];
            cost_right += cost_peer[x] + cr[peer[x]];
          }
          for (auto x : el[a]) {
            s64 old = cost_peer[peer[x]];
            checkmin(cost_peer[peer[x]], cost_right - cost_peer[x]);
            checkmin(cost_peer[x], cost_left - old);
          }
        }
      }
      if (ntry >= 1) assert(cost_peer == prev);
    }

    REP (i, nq) {
      s64 cost = -1;
      if (ql[i].first == ql[i].second)
        cost = 0;
      else if (repr[ql[i].first] == repr[ql[i].second])
      {
        assert(ql[i].second == peer[ql[i].first]);
        cost = cost_peer[ql[i].first];
      }
      resq[i] = cost;
    }

    std::vector<int> n2order(n, -1);
    REP (i, dfs_order.size())
      n2order[dfs_order[i]] = n2order[peer[dfs_order[i]]] = i;

    std::vector<vi> qevent(n);
    {
      for (auto a : dfs_order) {
        int b = peer[a];
        for (auto qi : v2ql[a]) {
          auto &q = ql[qi];
          int n1 = n2order[q.first];
          int n2 = n2order[q.second];
          int minx = std::min(n1, n2);
          int maxx = std::max(n1, n2);
          if (n2order[a] == maxx && minx != maxx) {
            auto nx = access(0, 0, repr[q.first] == a ? q.second : q.first);
            qevent[par[repr[nx.parent]]].pb(qi);
          }
        }

        int ne = el[a].size();
        vi nodes;
        nodes.pb(a);
        REP (i, ne)
          nodes.pb(el[a][i]), nodes.pb(peer[el[a][i]]);
        nodes.pb(b);

        int m = nodes.size() - 1;

        std::unordered_map<int, int> mp;
        REP (i, nodes.size())
          mp[nodes[i]] = i;
        std::vector<s64> costl(m + 1), costr(m + 1);
        costr[0] = 0;
        costl[0] = 0;
        REP (i, m)
          costr[i + 1] =
            costr[i] + (nodes[i] == peer[nodes[i + 1]] ? cost_peer[nodes[i]] : cr[nodes[i]]);
        REP (i, m)
          costl[i + 1] = costl[i] + (nodes[i] == peer[nodes[i + 1]] ? cost_peer[nodes[i + 1]]
                                                                    : cl[nodes[i + 1]]);

        REP (i, m)
          assert(costl[i] >= 0);

        for (auto qi : qevent[a]) {
          auto &qq = ql[qi];
          const auto &al = access(kFrom, kLeft, qq.first);
          const auto &ar = access(kFrom, kRight, qq.first);
          const auto &bl = access(kTo, kLeft, qq.second);
          const auto &br = access(kTo, kRight, qq.second);
          int ial = mp[al.parent];
          int ibl = mp[bl.parent];
          int iar = mp[ar.parent];
          int ibr = mp[br.parent];
          if (0) {
            OPA_DISP0(nodes, mp);
            OPA_DISP0(a, b, qq, ial, ibl, iar, ibr, qq.first, qq.second);
            OPA_DISP0(al.parent, ar.parent, bl.parent, br.parent);
            OPA_DISP0(al.cost, bl.cost, ar.cost, br.cost);
          }

          auto &rq = resq[qi];
          if (rq!=-1) continue;
          rq = inf;
          if (ial < ibl) {
            checkmin(rq, ar.cost + costr[ibl] - costr[iar] + bl.cost);
            checkmin(rq, al.cost + costl[ial] + (costl[m] - costl[ibr]) + cost_peer[a] + br.cost);
          } else {
            checkmin(rq, al.cost + costl[ial] - costl[ibr] + br.cost);
            checkmin(rq, ar.cost + (costr[m] - costr[iar]) + cost_peer[b] + costr[ibl] + bl.cost);
          }
        }

        REP (i, ne) {
          REP (fromto, 2) {
            auto x = el[a][i];
            auto y = peer[el[a][i]];
            int ix = mp[x];
            int iy = mp[y];
            auto &nlx = access(fromto, kLeft, x);
            auto &nly = access(fromto, kLeft, y);
            auto &nrx = access(fromto, kRight, x);
            auto &nry = access(fromto, kRight, y);

            nlx.parent = nly.parent = a;
            nrx.parent = nry.parent = b;
            nlx.cost = fromto == kFrom ? costl[ix] : costr[ix];
            nly.cost = fromto == kFrom ? costl[iy] : costr[iy];
            nrx.cost = fromto == kFrom ? costr[m] - costr[ix] : costl[m] - costl[ix];
            nry.cost = fromto == kFrom ? costr[m] - costr[iy] : costl[m] - costl[iy];
            assert(nlx.cost >= 0);
            assert(nly.cost >= 0);
            assert(nry.cost >= 0);
            assert(nrx.cost >= 0);
            checkmin(nlx.cost, nrx.cost + cost_peer[fromto == kFrom ? b : a]);
            checkmin(nrx.cost, nlx.cost + cost_peer[fromto == kFrom ? a : b]);
            checkmin(nly.cost, nry.cost + cost_peer[fromto == kFrom ? b : a]);
            checkmin(nry.cost, nly.cost + cost_peer[fromto == kFrom ? a : b]);
            // OPA_DISP0(x, y, nlx.cost, nly.cost, nrx.cost, nry.cost);
          }
        }
      }
    }

    s64 res = 0;
    for (auto &rq : resq) res += rq;
    return res;
  }

  s64 solve1(int a, int b) {
    std::priority_queue<std::pair<s64, int> > q;
    std::vector<s64> dist(n, inf);
    dist[a] = 0;
    q.emplace(0, a);

    while (true) {
      assert(!q.empty());
      int x = q.top().second;
      // OPA_DISP0(a, b, x, n);
      s64 cd = -q.top().first;

      q.pop();
      if (x == 0 || x == n - 1) continue;
      s64 cx = dist[x];
      if (cx != cd) continue;
      if (x == b) return cx;
      std::vector<std::pair<s64, int> > cnds;
      if (x > 1) cnds.emplace_back(cx + cl[x], x - 1);
      if (x < n - 1) cnds.emplace_back(cx + cr[x], x + 1);
      cnds.emplace_back(cx + cp[x], peer[x]);
      for (auto e : cnds) {
        if (dist[e.second] <= e.first) continue;
        dist[e.second] = e.first;
        q.emplace(-e.first, e.second);
      }
    }
  }

  s64 solve_dumb() {
    s64 res = 0;
    for (auto q : ql) res += solve1(q.first, q.second);
    return res;
  }
};

int main() {
  srand(0);
  int tn;

  if (TEST_RAND)
    tn = 10000000;
  else
    scanf("%d\n", &tn);

  REP (ti, tn) {

    SolverContext sc;
    sc.read();
    if (TEST_CHECK) {
      if (0 && ti != 14145) continue;
      auto r1 = sc.solve();
      auto r2 = sc.solve_dumb();
      OPA_DISP0(r1, r2);
      if (r1 != r2) {
        OPA_DISP0(sc.s);
        OPA_DISP0(sc.peer);
        OPA_DISP0(sc.cl);
        OPA_DISP0(sc.cr);
        OPA_DISP0(sc.cp);
        OPA_DISP0(sc.ql);
        OPA_DISP0(sc.cost_peer);
        printf("Case #%d: ", ti + 1);
        OPA_DISP0(r1, r2);
        puts("");
        assert(r1 == r2);
      }
    } else {

      printf("Case #%d: ", ti + 1);
      auto res = sc.solve();
      printf("%Ld", res);
      puts("");
    }
  }

  return 0;
}
