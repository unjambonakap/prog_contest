#define OPA_HEX 0
#include "opa/algo/base.h"
#include "opa/math/common/Utils.h"
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

  void read() {}
};

struct SolverContext {
  Problem prob;
  typedef s64 ResT;

  ResT solve() {}

  ResT solve_dumb() { return {}; }

  void read() {
    prob.read();
    if (TEST_RAND) {

    } else {
    }
  }
};
} // namespace prob

inline bool checkit(const std::vector<int> &tb) {
  int n = tb.size() / 2;
  int n0 = 0, n1 = 0;
  REP (i, tb.size()) {
    n0 += tb[i] == 0;
    n1 += tb[i] == 1;
  }
  int nx = (2 * n - (n0 + n1) - std::abs(n1 - n0)) / 2;
  int no = 0;
  for (auto x : tb) {
    int v = x == 2 ? (nx-- <= 0) : x;
    no += v ? -1 : 1;
    if (no < 0) return false;
  }
  return no == 0;
}

s64 count(int n) {
  int m = 2 * n;
  std::vector<int> tb(m, 0);
  s64 cnt = 0;
  int x = 1;
  int base = 3;
  REP (i, m) x *= base;
  REP (i, x) {
    int v = i;
    REP (j, m) tb[j] = (v % base), v /= base;
    cnt += checkit(tb);
  }
  return cnt;
}

int main(int argc, char **argv) {
  opa::init::opa_init(argc, argv);
  srand(0);
  int tn;
  OPA_DISP0(STD_RANGE(0, 10) | STD_TSFX(count(x)) | STD_VEC);
  return 0;

  if (0) {
  }

  if (TEST_RAND)
    tn = 10000;
  else {
    freopen("./prog_contest/misc/samples/ucup2_20_l.in", "r", stdin);
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
