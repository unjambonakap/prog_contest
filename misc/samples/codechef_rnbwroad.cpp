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

std::mt19937 rng(0);
ReaderHelper g_reader;
constexpr int mod = 998244353;
typedef GF_pMod<998244353> GFP;

struct Problem {
  s64 n, m, nq;
  std::vector<s64> al, ql;
  void read() {
    g_reader.readline() >> m >> n >> nq;
    al.resize(n);
    ql.resize(nq);

    g_reader.readline();
    REP (i, n) g_reader.iss >> al[i];
    REP (i, nq) g_reader.readline() >> ql[i];
  }
};
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

template <class T>
std::vector<T> partial_fraction_expansion(const opa::math::common::FastPoly<T> &fp,
                                          const Poly<T> &target, const std::vector<T> &roots) {
  // ret ki, ki/(x-ri) = target

  T prod = QQ::fold_left(roots, (T)1, STD_FUNCXY(gfp.mul(x, gfp.neg(y))));

  auto qinv =
    fp.interpolate(LQ::concat(roots, STD_SINGLEV(T(0))) | STD_VEC,
                   LQ::concat(STD_REPEAT((T)0, roots.size()), STD_SINGLEV(prod)) | STD_VEC);
  auto qd = qinv.derivate();
  auto qde = fp.eval(qd, roots);
  auto te = fp.eval(target, roots);
  OPA_DISP0(qde, te, roots, target);
  auto tmp = LQ::zip(te, qde) | STD_TSFTUPLE(gfp.div(p0, p1)) | STD_VEC;
  OPA_DISP0(tmp);

  return tmp;
}

struct SolverContext {
  Problem prob;
  typedef std::vector<s64> ResT;

  void read() {
    prob.read();
    if (TEST_RAND) {

    } else {
    }
  }

  ResT solve() {
    auto roots = prob.al | STD_TSFX(ch.inv(x)) | STD_VEC;
    u32 sgn = prob.al.size() % 2 == 0 ? 1 : mod - 1;
    u32 v = QQ::fold_left(prob.al | QQ::to<std::vector<u32> >(), sgn, STD_FUNC2(gfp.mul));

    OPA_DISP0(roots);
    u32 vv = QQ::fold_left(roots, 1, STD_FUNCXY(gfp.mul(x, gfp.neg(y))));
    u32 pall = QQ::fold_left(prob.al | STD_VECT(u32), 1, STD_FUNC2(gfp.mul));

    auto finalize = [&](QQ::forward_range auto &&xx) {
      return xx | STD_TSFX((s64)gfp.mul(x, pall)) | STD_VEC;
    };

    if (0 && prob.m < 1e6) {
      u32 prod = QQ::fold_left(roots, (u32)1, STD_FUNCXY(gfp.mul(x, gfp.neg(y))));
      auto qinv =
        fp.interpolate(LQ::concat(roots, STD_SINGLEV(s64(0))) | STD_VECT(u32),
                       LQ::concat(STD_REPEAT((u32)0, roots.size()), STD_SINGLEV(prod)) | STD_VEC);

      auto q = fp.invxmod(qinv, prob.m + 1);
      OPA_DISP0(qinv * q, q, v, gfp.neg(v));
      return finalize(prob.ql | STD_TSFX(q.get_safe(x - 1)));
    }

    auto fe = partial_fraction_expansion(fp, pr.constant(vv), roots);
    return finalize(
      prob.ql |
      STD_TSFX(QQ::fold_left(LQ::zip(fe, prob.al) |
                               STD_TSFTUPLE(gfp.mul(gfp.mul(p0, gfp.neg(p1)), ch.faste(p1, x - 1))),
                             0, STD_FUNC2(gfp.add))));
  }

  ResT solve_dumb() { return {}; }
};

int main(int argc, char **argv) {
  opa::init::opa_init(argc, argv);
  srand(0);
  int tn;

  if (TEST_RAND)
    tn = 10000;
  else {
    // scanf("%d\n", &tn);
    tn = 1;
  }

  REP (ti, tn) {

    SolverContext sc;
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
      // std::cout << res << std::endl;
      std::cout << std::dec;
      for (auto x : res) std::cout << x << ' ';
      std::cout << std::endl;
      // OPA_DISP0(res, sc.solve_dumb());
    }
  }

  return 0;
}
