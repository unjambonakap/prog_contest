#include "opa/math/common/Utils.h"
#include <algorithm>

#include <glm/geometric.hpp>
#include <iterator>
#include <random>
#include <range/v3/view/enumerate.hpp>
#include <range/v3/view/transform.hpp>
#include <vector>
#define DEBUG
#define TEST_RAND 1
#define TEST_CHECK 0

#include "contest_base.h"
#include <opa/utils/hash.h>

using namespace opa::math::common;
using namespace opa;

namespace ranges {
// std::ranges::views are valid range-v3 views
template <class T>
requires std::derived_from<T, std::ranges::view_base> inline constexpr bool enable_view<T> = true;
} // namespace ranges

namespace std::ranges {
// range-v3 views are valid std::ranges::views
template <class T>
requires std::derived_from<T, ::ranges::view_base> inline constexpr bool enable_view<T> = true;
} // namespace std::ranges

namespace prob {

std::mt19937 rng(0);
ReaderHelper g_reader;
constexpr int mod = 1e9 + 7;
typedef GF_pMod<mod> GFP;

typedef Fraction<bignum> F;

const int maxn = 255555;
CombHelper<mod> ch(maxn);

typedef u32 T;
typedef Poly<T> PT;

struct Query {
  int a, b;
  bool add;

  friend std::istream &operator>>(std::istream &is, Query &p) {

    char c;
    is >> c >> p.a >> p.b;
    --p.a;
    --p.b;
    p.add = c == '+';
    return is;
  }
  OPA_DECL_COUT_OPERATOR2(Query, a.a, a.b, a.add);
};

struct LCData {
  int num_repr = 0;
  int num_clique = 0;
  int num_path = 0;

  int mut_num_path = 0;
  int child_num_clique = 0;
  OPA_DECL_COUT_OPERATOR2(LCData, a.num_repr, a.num_clique, a.num_path, a.mut_num_path,
                          a.child_num_clique);
};

struct Problem {
  int n;
  int nq;
  std::vector<pii> edges;
  std::vector<Query> queries;

  void read() {
    g_reader.readline() >> n;
    g_reader.readline();
    edges = g_reader.read_list<pii>(n - 1, g_reader.kNewLine);
    edges = edges | STD_TSFX(x - MP(1, 1)) | STD_VEC;
    g_reader.readline() >> nq;
    g_reader.readline();
    queries = g_reader.read_list<Query>(nq, g_reader.kNewLine);
  }
};

struct SolverContext {
  Problem prob;
  typedef std::vector<s64> ResT;

  ResT solve() {
    LinkCutTree<LCData> lctree;
    std::vector<s64> mi2_table;
    std::vector<s64> m2_table;
    s64 i2 = ch.inv(2);
    m2_table.pb(1);
    mi2_table.pb(1);
    REP (i, prob.nq) m2_table.pb(m2_table.back() * 2 % mod);
    REP (i, prob.nq) mi2_table.pb(mi2_table.back() * i2 % mod);
    s64 m1 = mod - 1;

    lctree.op = [&](auto &p, auto &a, auto &b) {
      a.mut_num_path += p.mut_num_path;
      b.mut_num_path += p.mut_num_path;
      p.num_path += p.mut_num_path;
      p.num_clique = m2_table[p.num_path - p.num_repr] * (m2_table[p.num_repr] - 1) % mod;
      s64 tmp = p.num_clique;
      if (a.child_num_clique > 0)
        tmp += a.child_num_clique *
               (a.mut_num_path < 0 ? mi2_table[-a.mut_num_path] : m2_table[a.mut_num_path]);
      if (b.child_num_clique > 0)
        tmp += b.child_num_clique *
               (b.mut_num_path < 0 ? mi2_table[-b.mut_num_path] : m2_table[b.mut_num_path]);

      p.child_num_clique = tmp % mod;
      p.mut_num_path = 0;
    };

    Tree t;
    t.init(prob.edges);
    lctree.init(t.n);
    ResT res;

    REP (i, t.n)
      if (t.par[i] != -1) lctree.nodes[i].path = t.par[i];
    s64 tot = 0;
    for (auto &q : prob.queries) {
      int a = q.a;
      int b = q.b;
      int dx = q.add ? 1 : -1;

      int lca = lctree.lca(a, b);
      s64 orig = lctree.do_path_query(a, b).child_num_clique;
      lctree.do_path_op(a, b, [&](LCData &data) { data.mut_num_path += dx; });
      lctree.do_node_op(lca, [&](LCData &data) { data.num_repr += dx; });
      s64 after = lctree.do_path_query(a, b).child_num_clique;
      tot = (mod + tot + after - orig) % mod;
      res.pb(tot);
    }
    return res;
  }

  ResT solve_dumb() {
    Tree t;
    t.init(prob.edges);
    ResT res;
    std::multiset<pii> active;
    for (auto q : prob.queries) {
      if (q.add)
        active.emplace(q.a, q.b);
      else
        active.erase(active.find(MP(q.a, q.b)));
      auto tb = active | STD_VEC;
      OPA_CHECK0(tb.size() < 30);
      int cnt = 0;

      std::vector<vi> paths = tb | STD_TSFX(t.path(x.ST, x.ND) | STD_SET | STD_VEC) | STD_VEC;

      REP (i, 1 << tb.size()) {
        if (!i) continue;
        auto can = STD_RANGE(0, prob.n) | STD_VECT(int);
        REP (j, tb.size())
          if (i >> j & 1) {
            vi inter;
            std::set_intersection(ALL(can), ALL(paths[j]), std::back_inserter(inter));
            can = inter;
          }
        if (can.size() > 0) ++cnt;
      }
      res.pb(cnt);
    }

    return res;
  }

  void read() {
    if (TEST_RAND) {
      Generator gen;
      prob.n = rng() % 200000 + 1;
      prob.nq = rng() % 30000 + 1;
      prob.edges = gen.generate_tree(prob.n);
      std::uniform_real_distribution<> dis(0, 1);
      std::vector<pii> active;
      REP (i, prob.nq) {
        int target = active.size() - prob.n / 2;

        if (dis(rng) < 1 / (1 + std::exp(-target * 0.2)) && active.size() > 0) {
          int x = rng() % active.size();
          std::swap(active[x], active.back());
          auto u = active.back();
          active.pop_back();
          prob.queries.pb(Query{ .a = u.ST, .b = u.ND, .add = false });
        } else {

          pii u = pii(rng() % prob.n, rng() % prob.n);
          active.pb(u);
          prob.queries.pb(Query{ .a = u.ST, .b = u.ND, .add = true });
        }
      }
    } else {
      prob.read();
    }
  }
};
} // namespace prob

int main(int argc, char **argv) {
  opa::init::opa_init(argc, argv);
  srand(0);
  int tn;

  if (TEST_RAND)
    tn = 10000;
  else {
    freopen("./prog_contest/misc/samples/ucup2_6_c.in", "r", stdin);
    // scanf("%d\n", &tn);
    tn = 1;
  }

  REP (ti, tn) {

    prob::SolverContext sc;
    sc.read();
    if (TEST_CHECK) {
      auto r1 = sc.solve();
      auto r2 = sc.solve_dumb();
      OPA_DISP0(r1, r2);
      if (r1 != r2) {
        printf("Case #%d: ", ti + 1);
        OPA_DISP0(r1, r2);
        puts("");
        assert(r1 == r2);
      }
    } else {

      auto res = sc.solve();
      std::cout << res << std::endl;
      // OPA_DISP0(res, sc.solve_dumb());
    }
  }

  return 0;
}
