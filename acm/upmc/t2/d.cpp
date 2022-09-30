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
#define MP(x,y) make_pair(x, y)

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

const int maxd = 1e6 + 10;
const int oo = 1e9;
const int maxn = 555;
const int maxN = 2 * maxn;
int n;
int dist[maxN][maxN];
s64 func[maxd];
std::set<int> edges[maxN];
int ne;
int par[maxN];
int root(int a) { return par[a] == -1 ? a : par[a] = root(par[a]); }

double sol;
s64 nn;
s64 N;
s64 sol_acc;
s64 sol_cnt;
std::set<int> seen;

void add_res(s64 v, s64 mul = 1) {

  s64 tmp = v / N * mul;
  s64 tmp_mod = v % N * mul;
  sol += tmp / (N - 1);
  sol_acc += tmp % (N - 1) * N;
  sol_acc += tmp_mod;
  assert(sol_acc >= 0);
  sol_cnt += sol_acc / nn;
  sol_acc %= nn;
}

bool join(int a, int b) {
  a = root(a);
  b = root(b);
  if (a == b) return false;
  par[b] = a;
  return true;
}

void adde(int a, int b, int d = -1) {
  join(a, b);
  edges[a].insert(b);
  edges[b].insert(a);
  if (d != -1) dist[a][b] = dist[b][a] = d;
}

void dele(int a, int b) {
  assert(edges[a].count(b));
  assert(edges[b].count(a));
  edges[a].erase(b);
  edges[b].erase(a);
}

void build() {
  std::priority_queue<pii> q;
  int N = 2 * n;
  REP (i, n)
    REP (j, i)
      q.emplace(-dist[i][j], i * N + j);

  memset(par, -1, sizeof(par));

  ne = n;
  while (q.size() != 0) {

    int a = q.top().second / N, b = q.top().second % N;
    OPA_DISP0(a, b, dist[a][b]);
    q.pop();
    if (root(a) == root(b)) {
      continue;
    }

    std::set<int> through_a;
    std::set<int> through_other_a;
    std::set<int> through_b;
    std::set<int> through_other_b;
    int va = -1;
    int vb = -1;
    REP (i, ne) {
      if (root(i) == root(a)) {
        if (dist[i][b] == dist[i][a] + dist[a][b])
          through_a.insert(i);
        else {
          through_other_a.insert(i);
          if (va == -1 || dist[i][a] < dist[va][a]) va = i;
        }
      } else if (root(i) == root(b)) {
        if (dist[i][a] == dist[i][b] + dist[a][b])
          through_b.insert(i);
        else {
          through_other_b.insert(i);
          if (vb == -1 || dist[i][b] < dist[vb][b]) vb = i;
        }
      }
    }

    OPA_DISP0(root(a), root(b));
    OPA_DISP0(a, b, va, vb, through_a, through_other_a, through_b,
              through_other_b, ne, n);
    OPA_DISP0(edges[a]);
    OPA_DISP0(edges[b]);

    if (vb!=-1) OPA_DISP0(vb, dist[vb][b], edges[vb]);
    for (auto &e : edges[b]) OPA_DISP0(e, dist[e][b], edges[e]);

    std::vector<std::tuple<int, int, int> > repl;
    int pne = ne;
    if (va != -1 && vb != -1) {
      dele(va, a);
      dele(vb, b);
      int na = ne++;
      int nb = ne++;
      int dist_a_na = (dist[a][b] - dist[va][b] + dist[a][va]) / 2;
      int dist_b_nb = (dist[b][a] - dist[vb][a] + dist[b][vb]) / 2;
      assert(dist_a_na >= 0);
      assert(dist_b_nb >= 0);
      assert(root(na) != root(a));
      assert(root(nb) != root(b));
      adde(a, na, dist_a_na);
      adde(va, na, dist[a][va] - dist_a_na);
      adde(b, nb, dist_b_nb);
      adde(vb, nb, dist[b][vb] - dist_b_nb);
      assert(root(na) != root(nb));
      adde(na, nb, dist[a][b] - dist[a][na] - dist[b][nb]);

      dist[b][na] = dist[b][nb] + dist[nb][na];
      dist[vb][na] = dist[vb][nb] + dist[nb][na];
      dist[a][nb] = dist[a][na] + dist[nb][na];
      dist[va][nb] = dist[va][na] + dist[nb][na];
      repl.emplace_back(a, va, na);
      repl.emplace_back(b, vb, nb);

    } else if (va == -1 && vb == -1) {
      adde(a, b);
    } else {
      if (va == -1) std::swap(va, vb), std::swap(a, b);
      int na = ne++;
      int dist_a_na = (dist[a][b] - dist[va][b] + dist[a][va]) / 2;
      assert(dist_a_na >= 0);
      OPA_DISP0(a, va, na, dist_a_na);
      dele(a, va);
      assert(root(a) != root(na));
      adde(a, na, dist_a_na);
      adde(va, na, dist[a][va] - dist_a_na);
      assert(root(na) != root(b));
      adde(na, b, dist[a][b] - dist[a][na]);

      repl.emplace_back(a, va, na);
    }
    assert(ne <= N);

    for (auto &e : repl) {
      int a = std::get<0>(e);
      int b = std::get<1>(e);
      int c = std::get<2>(e);
      REP (i, pne) {
        int ea = (dist[a][i] - dist[b][i] + dist[a][b])/2;
        int eb = (dist[b][i] - dist[a][i] + dist[a][b])/2;
        if (ea <= dist[a][c]) {
          dist[c][i] = dist[b][i] -dist[b][c];
        } else {
          dist[c][i] = dist[a][i] - dist[a][c];
        }

        dist[i][c] = dist[c][i];
        if (root(i) != root(c)) {
          q.emplace(-dist[i][c], i * N + c);
        }
      }
    }
    assert(root(a) == root(b));
  }

  OPA_DISP0(ne);
  REP (i, ne) { OPA_DISP0(i, edges[i]); }
}

typedef std::pair<s64, s64> res_t;
res_t data[maxN];

res_t shift_level(res_t e, s64 d) {
  res_t res = { e.ST + d * e.ND, e.ND };
  res = res + res_t{ d * (d - 1) / 2, d - 1 };
  return res;
}

res_t dfs1(int a, int p = -1) {
  assert(seen.insert(a).second);
  res_t res = { 0, 0 };

  for (auto &x : edges[a]) {
    if (x == p) continue;
    auto tmp = dfs1(x, a);
    int d = dist[a][x];
    OPA_DISP0(a, x, d, tmp, shift_level(tmp, d));
    res = res + shift_level(tmp, d);
  }
  res.ND += 1;
  data[a] = res;
  OPA_DISP("Dfs1 >> ", a, res);
  return res;
}

void dfs2(int a, res_t above, int p = -1) {
  res_t below = data[a];
  OPA_DISP0(a, p, above, below);

  add_res(below.ST);

  if (p == -1)
    below.ND -= 1, above.ND += 1;
  else {

    s64 d = dist[a][p];
    if (d > 1) {
      // add_res(below.ST * (d - 1));
      // add_res(above.ST * (d - 1));
      add_res(below.ST, d - 1);
      add_res(above.ST, d - 1);
      if (d % 2 == 0) {
        add_res(below.ND * d / 2, d - 1);
        add_res(above.ND * d / 2, d - 1);
      } else {
        add_res(below.ND * (d - 1) / 2, d);
        add_res(above.ND * (d - 1) / 2, d);
      }

      add_res(func[d - 1]);
      // add_res(d * (d - 1) / 2 * below.ND);
      // add_res(d * (d - 1) / 2 * above.ND);
    }

    above = shift_level(above, dist[a][p]);
    OPA_DISP0(above);
    add_res(above.ST);
    above.ND += 1;
  }
  OPA_DISP0(a, p, above, below);

  res_t n_above = above + data[a];
  n_above.ND--;

  for (auto &x : edges[a]) {
    if (x == p) continue;
    auto tmp = n_above - shift_level(data[x], dist[x][a]);
    OPA_DISP0(a, x, data[a], data[x], shift_level(data[x], dist[x][a]), tmp);
    dfs2(x, tmp, a);
  }
}

double solve() {
  auto t = dfs1(0);
  // Nv = N * maxd = 500 * 1e6.
  // Expected value has Nv * (Nv-1) terms
  N = t.ND;
  nn = t.ND * (t.ND - 1);
  sol = 0;
  dfs2(0, { 0, 0 });
  sol += sol_cnt + 1. * sol_acc / nn;
  OPA_DISP0(sol, sol_cnt, sol_acc, nn);
  return sol;
}

int main() {
  scanf("%d", &n);
  memset(dist, 0x1f, sizeof(dist));
  REP (i, maxN)
    dist[i][i] = 0;
  func[0] = func[1] = 0;
  FOR (i, 2, maxd) { func[i] = func[i - 1] + 1ull * i * (i - 1); }

  int dtest = 10;
  res_t tmp{ 0, 0 };
  REP (i, dtest) {
    REP (j, dtest)
      if (i != j) tmp.ND += 1, tmp.ST += std::abs(i - j);
  }
  assert(tmp.ST == func[dtest]);

  REP (i, n) {
    REP (j, n - 1 - i)
      scanf("%d", dist[i] + i + 1 + j), dist[i + 1 + j][i] = dist[i][i + 1 + j];
  }
  build();
  double res = solve();
  printf("%.15lf\n", res);

  return 0;
}
