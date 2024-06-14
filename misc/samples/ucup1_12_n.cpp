#include "opa/algo/base.h"
#include "opa/math/common/Utils.h"
#include "opa_common_base.h"
#include <numeric>
#include <opa/algo/graph.h>

#define DEBUG
#include "contest_base.h"
#include <opa/utils/hash.h>
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

using namespace opa::math::common;
using namespace opa;

namespace prob {

std::mt19937 rng(0);
ReaderHelper g_reader;
constexpr int mod = 998244353;
typedef GF_pMod<998244353> GFP;

typedef Fraction<bignum> F;

const int maxn = 1e6 + 11;
CombHelper<mod> ch(maxn);

GFP gfp = GFP{ { { 2, 23 }, { 7, 1 }, { 17, 1 } } };

opa::math::common::FractionField<bignum> ff{ &Ring_Z };
opa::math::common::PolyRing<u32> pr{ &gfp };

opa::math::common::FFT2Dispatcher<u32> fftd{
  20, [](int npw) { return (IFFTProvider<u32> *)new FFT2F<u32, GFP>(&gfp, npw); }
};
opa::math::common::FastPoly<u32> fp{ pr, fftd };
typedef u32 T;
typedef Poly<T> PT;
constexpr double kEps = 1e-9;
typedef Point<double> Pd;

struct Edge {
  u32 a, b, c;
  OPA_DECL_CIN_OPERATOR(
    Edge,
    {
      --a.a;
      --a.b;
    },
    a.a, a.b, a.c)
};


struct Problem {
  int n, m, k, nq;
  std::vector<Edge> edges;
  std::vector<u32> ql;

  void read() {
    g_reader.readline() >> n >> m >> k;
    g_reader.readline();
    edges = g_reader.read_list<Edge>(m, g_reader.kNewLine);
    g_reader.readline() >> nq;
    g_reader.readline();
    ql = g_reader.read_list<u32>(nq, g_reader.kNewLine);
  }
};

typedef std::vector<s64> ResT;
struct Result {
  ResT val;
  Result() {}
  Result(ResT v) { val = v; }

  std::string str() const {
    std::string res;
    REP (i, val.size()) res += (i == 0 ? "" : "\n") + toStr(val[i]);
    return res;
  }
};

struct SolverContext {
  Problem prob;
  PersistentUJ uj;

  void rec(int version, int pos, const std::vector<u32> &eil, const std::vector<u32> &qil,
           s64 delta, ResT &res) {
    if (qil.empty()) return;
    if (pos == -1 || eil.size() == 0) {
      for (auto x : qil) res[x] += delta;
      return;
    }
    int b = 1 << pos;
    std::vector<u32> neil[2];
    std::vector<u32> nqil[2];
    for (auto x : qil) nqil[prob.ql[x] >> pos & 1].pb(x);
    for (auto x : eil) neil[prob.edges[x].c >> pos & 1].pb(x);

    if (prob.k & b) {
      REP (f, 2) {
        if (nqil[f].size() == 0) continue;
        int nv = version;
        s64 ndelta = delta;
        for (auto x : neil[f]) {
          auto mod = uj.join(nv, prob.edges[x].a, prob.edges[x].b);
          if (mod.changes) {
            nv = mod.nversion;
            ndelta += 1ull * mod.old_s1 * mod.old_s2;
          }
        }
        rec(nv, pos - 1, neil[f ^ 1], nqil[f], ndelta, res);
      }

    } else {
      REP (f, 2) rec(version, pos - 1, neil[f], nqil[f], delta, res);
    }
  }

  Result solve() {
    ResT res;
    int v0 = uj.init(prob.n);
    const int maxb = 30;
    res.resize(prob.nq, 0);
    rec(v0, maxb - 1, STD_RANGE(0, prob.m) | STD_VECT(u32), STD_RANGE(0, prob.nq) | STD_VECT(u32),
        0, res);
    return res;
  }

  Result solve_dumb() { return {}; }

  void read() {
    prob.read();
    if (TEST_RAND) {

    } else {
    }
  }
};
} // namespace prob

int main(int argc, char **argv) {
  opa::init::opa_init(argc, argv);
  srand(0);
  int tn;

  if (0) {
  }

  if (TEST_RAND)
    tn = 10000;
  else {
    freopen("./prog_contest/misc/samples/ucup1_12_n.in", "r", stdin);
    if (1)
      scanf("%d\n", &tn);
    else
      tn = 1;
  }

  REP (ti, tn) {

    prob::SolverContext sc;
    sc.read();
    if (TEST_CHECK) {
      auto r1 = sc.solve();
      auto r2 = sc.solve_dumb();
      OPA_DISP0(r1.str(), r2.str());
      if (r1.val != r2.val) {
        printf("Case #%d: ", ti + 1);
        OPA_DISP0(r1.str(), r2.str());
        puts("");
        assert(r1.val == r2.val);
      }
    } else {

      auto res = sc.solve();
      std::cout << res.str() << std::endl;
      // OPA_DISP0(res, sc.solve_dumb());
    }
  }

  return 0;
}
