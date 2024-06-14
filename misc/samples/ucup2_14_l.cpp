#include "opa/algo/base.h"
#include <algorithm>
#include <opa/algo/graph.h>

#include <range/v3/view/enumerate.hpp>
#include <range/v3/view/transform.hpp>
#include <vector>
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
#define V_t(t) std::vector<t>
#define VV_t(t) V_t(std::vector<t>)
#define VVV_t(t) VV_t(std::vector<t>)

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
  int n, m;
  std::vector<int> lst;

  void read() {
    g_reader.readline() >> n >> m;
    g_reader.readline();
    lst = g_reader.read_list<int>(m, !ReaderHelper::kNewLine);
  }
};

struct SolverContext {
  Problem prob;
  typedef std::pair<int, VV_t(bool)> ResT;

  int checkit(const VV_t(bool) & map) {
    vi state(prob.m + 1, 0);
    REP (i, prob.n) {
      vi nstate = state;
      REP (j, prob.m) {
        nstate[j + 1] = std::max(state[j] + map[i][j], state[j + 1]);
      }
      std::swap(state, nstate);
    }
    OPA_DISP0(state);
    return *std::max_element(ALL(state));
  }

  ResT solve() {
    auto vals = prob.lst;
    std::sort(ALL(vals));
    int sum = QQ::fold_left(prob.lst, int(0), STD_FUNCXY(x + y));

    int nsteps = 0;
    {
      int pos = 0;
      int sx = sum;
      while (sx > 0) {
        while (vals[pos] <= nsteps) ++pos;
        int can = std::max(1, (prob.m - std::max(pos, nsteps)) + (prob.n - nsteps) - 1);
        sx -= can;

        ++nsteps;
      }
    }

    auto map = VV_t(bool)(prob.n, std::vector<bool>(prob.m));

    std::vector<int> maxv(prob.m, prob.n - 1);
    auto rem = prob.lst;
    REP (i, nsteps) {
      int pos = prob.n - nsteps+i;
      REP (j, prob.m) {
        int v = rem[j];
        if (v == 0) continue;
        map[pos][j] = true;
        --rem[j];
        while (rem[j] > nsteps-i-1 && pos > i) --rem[j], map[--pos][j] = true;
      }
    }
    OPA_DISP0(nsteps, map, rem);
    OPA_CHECK0(QQ::fold_left(rem, int(0), STD_FUNCXY(x + y)) == 0);
    OPA_CHECK0(checkit(map) == nsteps);

    return { nsteps, map };
  }

  ResT solve_dumb() { return {}; }

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
    freopen("./prog_contest/misc/samples/ucup2_14_l.in", "r", stdin);
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
      std::cout << std::dec << res.ST << std::endl;
      for (auto x : res.ND) {
        auto tmp = x | STD_TSFX(x ? '#' : '.') | STD_VEC;
        std::string s{ ALL(tmp) };

        std::cout << s << std::endl;
      }
      // OPA_DISP0(res, sc.solve_dumb());
    }
  }

  return 0;
}
