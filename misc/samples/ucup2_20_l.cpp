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
  std::array<std::string, 4> lst;
  s64 n;

  void read() {
    g_reader.readline() >> n;
    g_reader.readline();
    lst = g_reader.read_array<std::string, 4>(ReaderHelper::kNewLine);
  }
};
template <class T>
std::vector<T> merge_sorted(const std::vector<T> &a, const std::vector<T> &b,
                            const std::function<bool(const T &, const T &)> &f = std::less<T>()) {
  std::vector<T> res;
  for (int ia = 0, ib = 0; ia < a.size() || ib < b.size();) {
    bool take0 = false;
    if (ia == a.size())
      take0 = false;
    else if (ib == b.size())
      take0 = true;
    else
      take0 = f(a[ia], a[ib]);
    res.pb(take0 ? a[ia++] : b[ib++]);
  }

  return res;
}

struct Decomp {
  struct Elem {
    std::vector<s64> a;
    s64 n;
    int pos;
    int d;
  };

  std::vector<Elem> lst;

  static Decomp Get(const std::vector<bool> &a, int d) {
    Decomp res;

    REP (i, d) {

      auto ta = STD_RANGE(0, a.size() / d) | STD_TSFX(a[x * d + i]) | STD_VEC;
      auto pa = STD_RANGE(0, ta.size()) | LQ::filter(STD_FUNCX(ta[x])) | STD_VECT(s64);
      res.lst.pb(Elem{ .a = pa, .n = ta.size(), .pos = i, .d = d });
    }
    return res;
  }
};

s64 compute_coprime(const Decomp::Elem &a, const Decomp::Elem &b, s64 v) {
  if (a.n > b.n) return compute_coprime(b, a, v);
  if (a.n == 1) {
    if (a.a.size() == 0) return {};
    return (b.a | LQ::filter(STD_FUNCX(x * a.d + a.pos < v)) | STD_VEC).size();
  }
  s64 mod = a.n * b.n * a.d;
  s64 ia = invmod(b.n, a.n) * b.n;
  s64 ib = invmod(a.n, b.n) * a.n;
  auto la = a.a | STD_TSFX(x * ia * a.d + a.pos % mod) | STD_VEC;
  auto lb = b.a | STD_TSFX(x * ib * a.d + a.pos % mod) | STD_VEC;
  std::sort(ALL(la));
  la = LQ::concat(la | STD_TSFX(x - mod), la) | STD_VEC;
  std::sort(ALL(lb));

  int l = lb.size() - 1, r = lb.size() - 1;
  s64 res = 0;
  for (auto x : la) {
    while (l >= 0 && x + lb[l] >= 0) --l;
    while (r >= 0 && x + lb[r] >= v) --r;
    res += r - l;
  }
  return res;
}

s64 compute_count(const Decomp &a, const Decomp &b, s64 v) {
  auto tmp =
    STD_RANGE(0, a.lst.size()) | STD_TSFX(compute_coprime(a.lst[x], b.lst[x], v)) | STD_VEC;
  return QQ::fold_left(tmp, s64(0), STD_FUNCXY(x + y));
}

s64 compute(const std::vector<bool> &a, const std::vector<bool> &b, s64 n) {
  int d = gcd<int>(a.size(), b.size());
  auto da = Decomp::Get(a, d);
  auto db = Decomp::Get(b, d);
  auto counts = LQ::zip(da.lst, db.lst) | STD_TSFTUPLE(p0.a.size() * p1.a.size()) | STD_VECT(s64);
  auto tot = QQ::fold_left(counts, s64(0), STD_FUNCXY(x + y));
  s64 per = (s64)a.size() * b.size() / d;
  if (tot == 0) return -1;

  s64 add = n / tot * per;
  n %= tot;
  s64 T = 0, H = per - 1;
  s64 res = 0;
  while (T <= H) {
    s64 M = (T + H) / 2;
    if (compute_count(da, db, M) <= n)
      T = M + 1, res = M;
    else
      H = M - 1;
  }
  return res + add + 1;
}

struct SolverContext {
  Problem prob;
  typedef s64 ResT;
  static constexpr char target[] = "TTPC";

  ResT solve() {
    std::vector<bool> vecs[2];
    REP (f, 2) {
      int i0 = 2 * f + 0, i1 = 2 * f + 1;
      const auto &a = prob.lst[i0];
      const auto &b = prob.lst[i1];
      REP (i, a.size() * b.size())
        vecs[f].pb(a[i % a.size()] == target[i0] && b[i % b.size()] == target[i1]);
    }

    return compute(vecs[0], vecs[1], prob.n - 1);
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
