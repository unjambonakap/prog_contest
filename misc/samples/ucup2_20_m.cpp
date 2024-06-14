#include "opa/algo/base.h"
#include "opa/math/common/Utils.h"
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
  std::vector<pii> lst;

  void read() {
    g_reader.readline() >> n;
    g_reader.readline();
    lst = g_reader.read_list<pii>(n, ReaderHelper::kNewLine);
  }
};
constexpr int NP = 4;
constexpr int primes[NP] = { int(1e9 + 7), int(1e9 + 9), int(1e9 + 21), int(1e9 + 33) };

struct SolverContext {
  Problem prob;
  typedef s64 ResT;
  typedef std::array<int, NP> state_t;

  ResT solve() {
    ResT res = {};
    auto csum_float = STD_PARTIAL_SUM(prob.lst | STD_TSFX(double(x.ST) / x.ND));

    auto states =
      prob.lst |
      STD_TSFX((MAKE_ARRAY(
        int, NP, x.ST *opa::math::common::u32_faste(x.ND, primes[i] - 2, primes[i]) % primes[i]))) |
      STD_VEC;

    auto csum_states =
      STD_PARTIAL_SUM_OP(states, STD_FUNCXY(MAKE_ARRAY(int, NP, (x[i] + y[i]) % primes[i])));
    auto tb = LQ::zip(csum_states, csum_float) |
              STD_TSFTUPLE(
                MAKE_ARRAY(int, NP, (p0[i] + (s64)std::round(p1) * (primes[i] - 1)) % primes[i]));
    std::unordered_map<state_t, int> cnt;
    for (auto x : tb) cnt[x] += 1;
    REP (i, prob.n) {
      auto sx = i == 0 ? state_t{} : tb[i - 1];
      res += cnt[sx];
      cnt[tb[i]] -= 1;
    }

    return res;
  }

  ResT solve_dumb() { return {}; }

  void read() {
    prob.read();
    if (TEST_RAND) {

    } else {
    }
  }
}; // namespace prob
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
    freopen("./prog_contest/misc/samples/ucup2_20_m.in", "r", stdin);
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
      OPA_DISP0(r1, r2);
      if (r1 != r2) {
        printf("Case #%d: ", ti + 1);
        OPA_DISP0(r1, r2);
        puts("");
        assert(r1 == r2);
      }
    } else {

      auto res = sc.solve();
      std::cout << std::dec << res << std::endl;
      // OPA_DISP0(res, sc.solve_dumb());
    }
  }

  return 0;
}
