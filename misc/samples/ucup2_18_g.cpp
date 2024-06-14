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

struct CombHelperT {
  const Field<T> &field;
  CombHelperT(const Field<T> &field, int n = 0) : field(field) { this->init(n); }

  void init(int n) {
    fact.resize(n + 1);
    ifact.resize(n + 1);
    T cur = field.getE();
    fact[0] = cur;

    REP (i, n) {
      fact[i + 1] = field.mul(fact[i], cur);
      cur = field.add(cur, field.getE());
    }
    REP (i, n + 1) ifact[i] = field.inv(fact[i]);
  }

  u32 cnk(int n, int k) const {
    if (n < k) return 0;
    if (k < 0) return 0;
    return field.mul(fact[n], field.mul(ifact[k], ifact[n - k]));
  }

  std::vector<T> fact;
  std::vector<T> ifact;
};

struct PolyHelper {
  CombHelperT ch;
  const PolyRing<T> &pr;
  const opa::math::common::FastPoly<u32> &fp;

  mutable std::map<int, PT> pow_poly_data;
  const PT &pow_poly(int n) const {
    if (!pow_poly_data.count(n)) {

      auto ring = pr.underlying_ring();
      // auto a = diff_solver(pr.xpw(n), pr.underlying_ring()->getZ());
      auto xl = LQ::iota(0, n + 2) | STD_VECT(T);
      auto yl = xl | STD_TSFX(ring->faste(x, n)) | LQ::partial_sum(STD_FUNC2(ring->add)) | STD_VEC;
      auto b = fp.interpolate(xl, yl);
      pow_poly_data[n] = b;
    }
    return pow_poly_data[n];
  }

  PT diff_solver(const PT &diff, T p0) const {
    // pt(x) - pt(x-1) = diff
    int n = diff.deg() + 1;
    auto ring = pr.underlying_ring();
    Matrix<T> mat;
    mat.initialize(ring, n, n);
    REP (i, n)
      FOR (j, i, n) mat.set(i, j, ring->sgn_v(ch.cnk(j + 1, i), j - i));
    auto v = mat.solve_tri(diff.to_vec(), LowerType::Upper);
    auto res = pr.import(LQ::concat(STD_SINGLEV(p0), v) | STD_VEC);
    return res;
  }

  PT mix_poly_rec(const PT &p, const PT &q) const {
    // r(i) = p(j) q(i-j)
    auto r = pr.getZ();
    auto ring = pr.underlying_ring();
    REP (i, p.deg() + 1)
      REP (j, q.deg() + 1)
        REP (k, j + 1) {

          r = r + pr.mulc(pr.mulxpw(pow_poly(i + k), j - k),
                          ring->mul({ p[i], q[j], ring->sgn_v(ch.cnk(j, k), k) }));
        }

    return r;
  }
};

struct BinaryPartitionQuery {

  const opa::math::common::FastPoly<u32> &fp;
  const PolyHelper &ph;
  int k;

  u32 query(s64 n) {
    n -= 1ull << (k - 1);
    if (n < 0) return 0;
    auto pr = fp.pr;
    auto cur = pr.x() + 1;
    REP (i, k - 1) {
      cur = pr.eval2(cur, pr.x() * 2 + (n & 1));
      cur = ph.mix_poly_rec(cur, pr.constant(1));
      n >>= 1;
    }
    return pr.eval(cur, n % mod);
  }
};

struct Problem {
  s64 c, k;
  void read() { g_reader.readline() >> c >> k; }
};

struct SolverContext {
  Problem prob;
  typedef u32 ResT;

  void read() {
    prob.read();
    if (TEST_RAND) {

    } else {
    }
  }

  ResT solve() {
    auto cht = CombHelperT(gfp, 100);
    auto ph = PolyHelper{ .ch = cht, .pr = pr, .fp = fp };
    BinaryPartitionQuery o{ .fp = fp, .ph = ph, .k = (int)prob.k };
    return o.query(prob.c);
  }

  ResT solve_dumb() { return {}; }
};

int main(int argc, char **argv) {
  opa::init::opa_init(argc, argv);
  srand(0);
  int tn;
  auto cht = CombHelperT(gfp, 100);
  auto ph = PolyHelper{ .ch = cht, .pr = pr, .fp = fp };
  OPA_DISP0(ph.pow_poly(2) * 6, ph.pow_poly(1) * 2);
  OPA_DISP0(ph.mix_poly_rec(pr.getE(), pr.getE()));
  OPA_DISP0(ph.mix_poly_rec(pr.x(), pr.getE()));

  {
    BinaryPartitionQuery o{ .fp = fp, .ph = ph, .k = 35 };
    OPA_DISP0(o.query(30), o.query(1234567887654321LL));
  }
  {
    BinaryPartitionQuery o{ .fp = fp, .ph = ph, .k = 2 };
    OPA_DISP0(o.query(8), o.query(16));
  }

  return 0;

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
      std::cout << res << std::endl;
      // OPA_DISP0(res, sc.solve_dumb());
    }
  }

  return 0;
}
