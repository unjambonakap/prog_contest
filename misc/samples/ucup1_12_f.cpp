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

const int maxn = 255555;
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

constexpr int M = 6;
constexpr int D = 10;
struct Problem {
  int n;
  std::vector<int> vals;

  void read() {
    g_reader.readline() >> n;
    g_reader.readline();
    vals = g_reader.read_list<int>(n, !ReaderHelper::kNewLine);
  }
};

typedef bool ResT;
struct Result {
  ResT val;
  Result() {}
  Result(ResT v) { val = v; }

  std::string str() const { return toStr(val ? "Yes" : "No"); }
};

struct SolverContext {
  Problem prob;

  static constexpr int maxb = 12;
  Result solve() {
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
namespace t1 {

struct NodeData {
  int key = -1;
  int agg_mink = INT_MAX;
  int agg_maxk = -1;
  double agg_e = 0;
  double mut_prob_mul = 1;
  double prob = 0;
  OPA_DECL_COUT_OPERATOR2(NodeData, a.num_repr, a.num_clique, a.num_path, a.mut_num_path,
                          a.child_num_clique);
};

void tx() {

  LinkCutTree<NodeData> lctree;

  lctree.op = [&](auto &p, auto &a, auto &b) {
    p.agg_mink = std::min(p.k, a.agg_mink);
    p.agg_maxk = std::max(p.k, b.agg_mink);
    a.mut_prob_mul *= p.mut_prob_mul;
    b.mut_prob_mul *= p.mut_prob_mul;
    p.prob *= p.mut_prob_mul;
    p.agg_e = a.agg_e * a.mut_prob_mul + b.agg_e * b.mut_prob_mul;

    p.mut_prob_mul = 1;
  };

  lctree.mutate_range(node, low, high, [&](auto &x) { x.mut_prob_mul *= prob; });

  Tree t;
  t.init(prob.edges);
  lctree.init(t.n);
}

} // namespace t1

int main(int argc, char **argv) {
  opa::init::opa_init(argc, argv);
  srand(0);
  int tn;

  if (0) {
  }

  if (TEST_RAND)
    tn = 10000;
  else {
    freopen("./prog_contest/misc/samples/ucup2_20_b.in", "r", stdin);
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
