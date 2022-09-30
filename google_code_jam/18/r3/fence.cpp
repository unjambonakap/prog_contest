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

// clang-format on

#ifndef TEST_RAND
#define TEST_RAND 0
#endif

#ifndef TEST_CHECK
#define TEST_CHECK 0
#endif

std::mt19937 rng(0);

const int maxf = 333;
const int maxn = 666;
struct Face;

struct Edge {
  Edge *next;
  Edge *inv;
  int src, dst;
  int pos;
  double angle;
  Face *f;
  int relpos;
  bool operator<(const Edge &peer) const { return angle < peer.angle; }
};

struct Face {
  int id;
  Edge *any;
  int relpos = -1;
};

struct FaceEdge {
  std::set<int> edges;
  pii key;
  bool removed = true;
  int relpos = -1;
  bool bridge = false;
  FaceEdge *peer;
};
struct FaceGraph {
  std::vector<FaceEdge> fel;
  std::map<int, std::map<int, FaceEdge *> > faceedges;
  std::vector<Face> faces;
};

struct twoco {
  int depth[maxn];
  int coid[maxn];
  int id = 0;
  std::vector<int> opened;
  std::set<int> vis;
  std::map<int, std::set<std::pair<int, FaceEdge *> > > coedges;
  std::map<int, vi> co_content;
  FaceGraph *_fg;

  void start(FaceGraph *fg, int fid) {
    _fg = fg;
    for (auto &x : _fg->faceedges)
      for (auto &y : x.second) OPA_DISP0(x.first, y.first);

    memset(coid, -1, sizeof(coid));
    memset(depth, -1, sizeof(depth));
    id = 0;
    dfs(fid, -1, 0);
    for (auto &fe : _fg->fel) {
      if (fe.removed) continue;
      int ia = coid[fe.key.first];
      int ib = coid[fe.key.second];
      fe.bridge = (ia != ib);
      if (ia != ib)
        coedges[ia].emplace(ib, &fe), coedges[ib].emplace(ia, fe.peer);
    }
  }

  bool dfs_inco(int a, int par, std::vector<FaceEdge *> &tree_edges,
                std::vector<FaceEdge *> &other_edges) {
    if (vis.count(a)) return false;
    vis.insert(a);
    for (auto &x : _fg->faceedges[a]) {
      if (x.first == par) continue;
      if (coid[x.first] != coid[a]) continue;
      if (dfs_inco(x.first, a, tree_edges, other_edges)) {
        tree_edges.pb(x.second);
      } else
        other_edges.pb(x.second);
    }
    return true;
  }

  int dfs(int fid, int par, int d) {
    if (depth[fid] != -1) {
      return depth[fid];
    }

    depth[fid] = d;
    opened.pb(fid);
    int md = depth[fid];
    for (auto &x : _fg->faceedges[fid]) {
      if (x.first == par) continue;
      assert(!x.second->removed);
      checkmin(md, dfs(x.first, fid, d + 1));
    }
    if (md == depth[fid]) {
      vi lst;
      while (true) {
        int x = opened.back();
        opened.pop_back();
        lst.pb(x);
        if (x == fid) break;
      }
      OPA_DISP0(fid, lst);
      for (auto &x : lst) coid[x] = id;
      co_content[id] = lst;
      ++id;
    }
    OPA_DISP0(fid, d, md);
    return md;
  }

  void dfs_cotree(int a, int par, std::vector<FaceEdge *> &postorder) {
    for (auto &x : coedges[a]) {
      if (x.first == par) continue;
      dfs_cotree(x.first, a, postorder);
      postorder.pb(x.second);
    }
  }

  pii analyse_bridge(int a, int b) {
    std::vector<FaceEdge *> fa, fb;
    dfs_cotree(a, b, fa);
    dfs_cotree(b, a, fb);
    vi coa, cob;
    coa.pb(a);
    cob.pb(b);
    for (auto &e : fa) coa.pb(coid[e->key.second]);
    for (auto &e : fb) cob.pb(coid[e->key.second]);
    pii res(-1, -1);

    for (auto &cox : coa) {
      OPA_DISP("T1 >> ", cox, co_content[cox]);
      for (auto &f : co_content[cox]) checkmax(res.first, _fg->faces[f].relpos);
    }
    for (auto &cox : cob) {
      OPA_DISP("T2 >> ", cox, co_content[cox]);
      for (auto &f : co_content[cox])
        checkmax(res.second, _fg->faces[f].relpos);
    }
    return res;
  }
};

struct solve_context {
  int k;
  int n;
  pii src[maxf], dst[maxf];
  std::map<pii, int> rmp;
  pii mp[maxn];
  std::vector<Edge> edges;
  std::vector<int> order;
  int ne, nf;

  std::map<pii, Edge> emap;
  std::map<int, std::vector<Edge *> > vedges;

  FaceGraph fg;

  twoco cur;
  bool compute_2co() {
    FaceEdge *first = nullptr;
    std::set<int> alive;
    for (auto &x : fg.fel)
      if (!x.removed) {
        first = &x;
        alive.insert(x.key.first);
        alive.insert(x.key.second);
      }
    cur = twoco();
    if (first == nullptr) return false;
    cur.start(&fg, first->key.first);
    REP(i,cur.id) OPA_DISP0(i, cur.co_content[i]);
    for (auto &a : alive) {

      OPA_DISP0(a, cur.coid[a]);
      assert(cur.coid[a] != -1);
    }
    return true;
  }

  void remove_edge(FaceEdge *e) {
    OPA_DISP("remove >> ", e->key, e->removed, order, ne, e->edges);
    if (e->removed) return;
    assert(!e->removed);
    for (auto &x : e->edges) {
      order.pb(x);
    }
    fg.faceedges[e->key.first].erase(e->key.second);
    fg.faceedges[e->key.second].erase(e->key.first);
    e->edges.clear();
    e->removed = e->peer->removed = true;
  }

  void remove_co(int v) {
    OPA_DISP("Remove co >> ", v, cur.coid[v], cur.co_content[cur.coid[v]]);
    std::vector<FaceEdge *> tree_edges;
    std::vector<FaceEdge *> other_edges;
    cur.dfs_inco(v, -1, tree_edges, other_edges);
    for (auto &e : other_edges) remove_edge(e);
    for (auto &e : tree_edges) remove_edge(e);
    OPA_DISP("Done remove ", v);
  }

  void remove_bridge(int v1, int vpar) {
    std::vector<FaceEdge *> tb;
    int co1 = cur.coid[v1];
    int copar = vpar == -1 ? -1 : cur.coid[vpar];
    cur.dfs_cotree(co1, copar, tb);
    OPA_DISP("REmove bridge > ", v1, co1, copar, cur.co_content[co1]);
    for (auto &e : tb) {
      OPA_DISP("rem bridge ", e->key);
      remove_co(e->key.second);
      remove_edge(e);
    }
    remove_co(v1);
  }

  std::vector<int> solve() {
    std::map<Edge *, FaceEdge *> e2fe;


    for (auto &x : edges) {
      const pii &a = mp[x.src];
      const pii &b = mp[x.dst];

      x.angle = std::atan2(b.second - a.second, b.first - a.first);
    }

    REP (i, n) {
      auto &ve = vedges[i];
      std::sort(ALL(ve), [](const Edge *a, const Edge *b) { return *a < *b; });
      OPA_DISP("On vertex ", i);
      REP (j, ve.size()) {
        ve[j]->inv->next = ve[(j + 1) % ve.size()];
        OPA_DISP0(ve[j]->pos);
      }
    }

    std::set<Edge *> seen;
    nf = 0;
    fg.faces.clear();
    fg.faces.resize(maxn);
    for (auto &x : edges) assert(x.next != nullptr);

    for (auto &x : edges) {
      if (seen.count(&x)) continue;
      Face &f = fg.faces[nf++];
      Edge *e = &x;
      do {
        e->f = &f;
        checkmax(f.relpos, e->relpos);
        seen.insert(e);
        e = e->next;
      } while (e != &x);
    }
    REP (i, nf)
      fg.faces[i].id = i;
    for (auto &e : edges) OPA_DISP("Edge >> ", e.pos, e.f->id, e.next->pos);

    int felpos = 0;
    fg.fel.resize(nf * nf * 2);
    for (auto &x : edges) {
      int f1 = x.f->id;
      int f2 = x.inv->f->id;

      if (&x < x.inv) {
        auto &e1 = fg.faceedges[f1][f2];
        auto &e2 = fg.faceedges[f2][f1];
        if (e1 == nullptr) {

          e1 = &fg.fel[felpos++];
          e2 = &fg.fel[felpos++];
          assert(fg.fel.size() >= felpos);
          e1->removed = false;
          e2->removed = false;
          e1->key = MP(f1, f2);
          e2->key = MP(f2, f1);
          e1->peer = e2;
          e2->peer = e1;
        }

        e1->edges.insert(x.pos);
        e2->edges.insert(x.inv->pos);
        e1->relpos = e2->relpos = std::max(e1->relpos, x.relpos);
        e2fe[&x] = e1;
        e2fe[x.inv] = e2;
      }
    }
    assert(e2fe.size() == edges.size());
    for (auto &e : fg.fel)
      if (!e.removed) OPA_DISP0(e.key, e.edges);

    order.clear();
    REP (i, k) {
      compute_2co();
      auto &e = edges[2 * i];
      auto fe = e2fe[&e];
      assert(fe != nullptr);
      OPA_DISP0(e.pos, i, fe->edges.size());
      assert(fe->edges.count(e.pos));
      if (fe->edges.size() > 1) {

        fe->edges.erase(i);
        fe->peer->edges.erase(i);
        order.pb(e.pos);
        continue;
      }
      OPA_DISP("Procesing rel ", fe->key);

      if (fe->bridge) {

        int pp[2] = { fe->key.first, fe->key.second };
        auto rel_pair = cur.analyse_bridge(cur.coid[pp[0]], cur.coid[pp[1]]);
        int pid = 0;
        assert(rel_pair.first <= i || rel_pair.second <= i);
        if (rel_pair.first <= i) pid = 1;

        remove_bridge(pp[pid ^ 1], pp[pid]);
      }
      remove_edge(fe);
    }

    if (compute_2co()) {
      assert(cur.id >= 1);
      remove_bridge(cur.co_content[0][0], -1);
    }

    for (auto &e : fg.fel) {
      if (e.removed) continue;
      OPA_DISP("rem ", e.key);
    }
    assert(!compute_2co());
    assert(order.size() == ne);

    return order;
  }

  pii rand_pts[maxn];
  int cross(pii o, pii b, pii c) {
    pii a0 = MP(b.first - o.first, b.second - o.second);
    pii a1 = MP(c.first - o.first, c.second - o.second);
    return (a0.first * a1.second - a0.second * a1.first);
  }

  bool intersect(pii a0, pii a1, pii b0, pii b1) {
    if (a0 == b0 || a0 == b1) return false;
    if (a1 == b0 || a1 == b1) return false;

    REP (f, 2) {
      std::swap(a0, b0);
      std::swap(a1, b1);
      int c0 = cross(a0, a1, b0);
      int c1 = cross(a0, a1, b1);
      if (c0 == 0 && c1 == 0) return true;
      if ((c0 < 0) == (c1 < 0)) return false;
    }
    return true;
  }

  bool try_adde(int a, int b) {
    if (a == b) return false;
    if (a > b) std::swap(a, b);

    REP (i, ne) {
      if (src[i] == rand_pts[a] && dst[i] == rand_pts[b]) return false;
    }
    REP (i, ne) {
      if (intersect(src[i], dst[i], rand_pts[a], rand_pts[b])) return false;
    }
    src[ne] = rand_pts[a];
    dst[ne] = rand_pts[b];
    ne++;
    return true;
  }

  bool gen_rand() {
    n = 5;
    ne = 0;
    REP (i, n) {
      while (true) {
        while (true) {
          bool ok = true;
          rand_pts[i] = MP(rng() % 100, rng() % 100);
          REP (j, i)
            REP (k, j)
              if (cross(rand_pts[i], rand_pts[j], rand_pts[k]) == 0) {
                ok = false;
              }
          if (ok) break;
        }
        bool conflict = false;
        REP (j, i)
          if (rand_pts[i] == rand_pts[j]) conflict = true;
        if (!conflict) break;
      }
    }

    REP (i, n - 1) {
      std::vector<int> cnds;
      REP (j, i + 1)
        cnds.pb(j);
      std::shuffle(ALL(cnds), rng);
      bool found = false;
      for (auto x : cnds) {
        if (try_adde(i + 1, x)) {
          found = true;
          break;
        }
      }
      if (!found) return false;
    }

    REP (a, n)
      REP (b, a)
        try_adde(a, b);

    return true;
  }

  void read() {
    if (TEST_RAND) {
      while (!gen_rand()) {
      }

      k = 2;
      if (1) {
        puts("1");
        printf("%d %d\n", ne, k);
        REP (i, ne)
          printf("%d %d %d %d\n", src[i].first, src[i].second, dst[i].first,
                 dst[i].second);
        fflush(stdout);
        OPA_DISP0(n, ne);
      }

    } else {
      scanf("%d%d", &ne, &k);
      REP (i, ne) {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        src[i] = MP(a, b);
        dst[i] = MP(c, d);
      }
    }

    vedges.clear();
    rmp.clear();
    edges.clear();

    n = 0;
    nf = 0;
    edges.resize(2 * ne);
    REP (i, ne) {
      if (!rmp.count(src[i])) rmp[src[i]] = n++;
      if (!rmp.count(dst[i])) rmp[dst[i]] = n++;

      int ia = rmp[src[i]];
      int ib = rmp[dst[i]];
      auto eb = &edges[2 * i];
      auto ea = &edges[2 * i + 1];
      eb->pos = ea->pos = i;
      ea->relpos = eb->relpos = i < k ? i : -1;
      ea->src = eb->dst = ia;
      eb->src = ea->dst = ib;
      ea->inv = eb;
      eb->inv = ea;
      vedges[ia].pb(ea);
      vedges[ib].pb(eb);
    }
    for (auto &x : rmp) mp[x.second] = x.first;
  }
};

int main() {
  srand(0);
  int tn;

  if (TEST_RAND)
    tn = 1000;
  else
    scanf("%d", &tn);

  REP (ti, tn) {
    solve_context sc;
    sc.read();

    printf("Case #%d: ", ti + 1);
    if (TEST_CHECK) {
    } else {
      std::vector<int> res = sc.solve();
      for (auto x : res) printf("%d ", x + 1);
    }
    puts("");
  }

  return 0;
}

