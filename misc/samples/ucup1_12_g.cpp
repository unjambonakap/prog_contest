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

struct Problem {
  int n;
  int m;

  void read() { g_reader.readline() >> n >> m; }
};

typedef s64 ResT;
struct Result {
  ResT val;
  Result() {}
  Result(ResT v) { val = v; }

  std::string str() const { return toStr(val); }
};

struct SolverContext {
  Problem prob;

  Result solve() {
    auto v = pr.import_vec(
      STD_RANGE(0, prob.m + 1) |
      STD_TSFX(
        gfp.mulv({ ch.fact[prob.m], ch.fact[prob.m],
                   gfp.inv(gfp.mulv({ ch.fact[x], ch.fact[prob.m - x], ch.fact[prob.m - x] })) })) |
      STD_VECT(u32));

    auto pv = fp.pow(v, prob.n);
    int tot = prob.n * prob.m;
    auto tmp = STD_RANGE(0, tot + 1) | STD_TSFX(gfp.mul(ch.fact[tot - x], pv[x])) | STD_VEC;
    return pr.import_vec(tmp)(gfp.neg(1));
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
    freopen("./prog_contest/misc/samples/ucup1_12_g.in", "r", stdin);
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
