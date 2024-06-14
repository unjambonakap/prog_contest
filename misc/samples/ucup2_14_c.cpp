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

struct Problem {
  int n, m;
  std::vector<Pd> p;
  std::vector<Pd> q;

  void read() {
    g_reader.readline() >> n;
    g_reader.readline();
    p = g_reader.read_list<Pd>(n, ReaderHelper::kNewLine);
    g_reader.readline() >> m;
    g_reader.readline();
    q = g_reader.read_list<Pd>(m, ReaderHelper::kNewLine);
  }
};

std::optional<std::pair<double, double> >
c1_intersection(const std::vector<std::pair<double, double> > &inters) {
  // for it to work, |inter| < pi
  std::pair<double, double> res = MP(0, OPA_PI);
  auto x0 = inters[0].ST;
  for (auto i : inters) {
    i = i - MP(x0, x0);
    if (i.ST < 0) i = i + MP(2 * OPA_PI, 2 * OPA_PI);
    if (i.ST > 2 * OPA_PI) i = i - MP(2 * OPA_PI, 2 * OPA_PI);
    checkmax(res.ST, i.ST);
    checkmin(res.ND, i.ND);
  }
  return res + MP(x0, x0);
}

bool c1_intersects(const std::pair<double, double> &p, const std::pair<double, double> &q) {
  auto tq = q - MP(p.ST, p.ST);
  if (tq.first < 0) tq = tq + MP(2 * OPA_PI, 2 * OPA_PI);
  return tq.ST < p.ND - p.ST || tq.ND > 2 * OPA_PI;
}

struct ConvexPolygon {
  std::vector<Pd> points;

  const Pd &at(int i) const { return points[(i + points.size()) % points.size()]; }
  const Pd &operator[](int i) const { return points[(i + points.size()) % points.size()]; }
  double line_angle(int i) const { return (at(i + 1) - at(i)).atan2(); }
  int size() const { return points.size(); }
};

struct SolverContext {
  Problem prob;
  typedef std::pair<double, std::pair<double, double> > ResT;
  ConvexPolygon pl, ql;

  ResT solve() {
    ResT res;

    auto prod = product<Pd>({ prob.p, prob.q });
    MinEnclosingBall meb;
    meb.points = prod | STD_TSFX((x[0] - x[1]).as_vec()) | STD_VEC;
    auto r = meb.compute();
    return { r.first, MP(-r.second[0], -r.second[1]) };
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
    Generator gen;
    gen.rng.seed(1);
    REP (k, 1) {
      MinEnclosingBall meb;
      int nd = 3;
      int np = 9;
      meb.points.resize(np);
      REP (i, np) meb.points[i] = gen.generate_vec(nd, 10);
      auto r = meb.compute();
      OPA_DISP0(r);
    }
    return {};
  }

  if (TEST_RAND)
    tn = 10000;
  else {
    freopen("./prog_contest/misc/samples/ucup2_14_c.in", "r", stdin);
    scanf("%d\n", &tn);
    // tn = 1;
    OPA_DISP0(tn);
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
      std::cout << res.ST << " " << res.ND.ST << " " << res.ND.ND << std::endl;
      // OPA_DISP0(res, sc.solve_dumb());
    }
  }

  return 0;
}
