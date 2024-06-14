#include "contest_base.h"
#include "opa/math/common/FFT.h"
#include "opa/math/common/FractionField.h"
#include "opa/math/common/Types.h"
#include "opa/math/common/Z.h"
#include "opa_common_base.h"
#include <opa/math/common/crt_fft.h>
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
struct ReaderHelper {
  mutable char buf[111111];

  mutable std::istringstream iss;
  std::istringstream &readline() const {
    fgets(buf, sizeof(buf) - 1, stdin);
    iss = std::istringstream(buf);
    return iss;
  }
};
ReaderHelper g_reader;
constexpr int mod = 998244353;
typedef GF_pMod<998244353> GFP;

struct Problem {
  std::vector<int> entries;
  u32 N;
  void read() {
    int n;
    g_reader.readline() >> n;
    g_reader.readline();
    entries.resize(n);
    N = 0;
    REP (i, n) g_reader.iss >> entries[i], N += entries[i];
  }
};
typedef Fraction<bignum> F;

template <int mod> class CombHelper {
public:
  CombHelper(int n = 0) { this->init(n); }
  void init(int n) {
    fact.resize(n + 1);
    ifact.resize(n + 1);
    fact[0] = 1;
    REP (i, n) fact[i + 1] = 1ull * fact[i] * (i + 1) % mod;
    ifact[0] = 1;
    REP (i, n + 1) ifact[i] = opa::math::common::u32_faste(fact[i], mod - 2, mod);
  }

  u32 cnk(int n, int k) const {
    if (n < k) return 0;
    if (k < 0) return 0;
    return 1ull * fact[n] * ifact[k] % mod * ifact[n - k] % mod;
  }

  std::vector<int> fact;
  std::vector<int> ifact;
};

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

struct CumSumP {
  int start, end;
  PT p;
  std::vector<T> prod;
  void setup(const PT &_p, int _start, int _end) {
    start = _start;
    end = _end;
    this->p = _p;
    prod.pb(1);
    FOR (i, start, end + 1) {
      prod.pb(gfp.mul(_p(i), prod.back()));
    }
  }

  T query_prod(int a, int b) {
    OPA_CHECK(a >= start && b - start < prod.size(), a, b, start, prod.size());
    // [a,b)
    return gfp.div(prod[b - start], prod[a - start]);
  }

  T query_csum(int a, int b) {
    T res = 0;
    FOR (i, a, b) res = gfp.add(res, query_prod(a, i));
    return res;
  }
};

struct DoubleEval {

  std::vector<T> proc(const std::vector<T> &vals, int vals_start, int new_idx) {
    std::vector<T> a, b;
    int n = vals.size();
    b.pb(gfp.getZ());
    FOR (i, 1, 2 * n) b.pb(gfp.inv(new_idx - n + i));
    auto c = gfp.mul(ch.fact[n - 1], gfp.faste(gfp.neg(1), n - 1));
    REP (i, n) {
      a.pb(gfp.div(vals[i], c));
      auto v = gfp.neg(n - 1 - i);
      c = gfp.mul(c, gfp.div(i + 1, v == 0 ? 1 : v));
    }

    auto pa = pr.import_vec(a);
    auto pb = pr.import_vec(b);
    auto resp = fp.mulxmod(pa, pb, 2 * n);
    auto fx = gfp.div(ch.fact[new_idx], ch.fact[new_idx - n]);

    std::vector<T> res;
    REP (i, n) {
      res.pb(gfp.mul(fx, resp.get_safe(n + i)));
      fx = gfp.mul(gfp.div(fx, new_idx - n + i + 1), new_idx + i + 1);
    }
    return res;
  }
};

struct CumSumProd {
  int n;
  int bsize;
  PT p, q;
  PT Q, P;
  PT R;
  CumSumP csump, csumq;
  std::vector<T> block_prod, block_sum;
  DoubleEval de;

  void setup(const PT &_p, const PT &_q, int _n) {
    n = _n;
    p = _p;
    q = _q;
    int bsize_log2 = (1 + log2_high_bit(n)) / 2 + 1;
    this->bsize = 1 << bsize_log2;
    csump.setup(p, 0, 3 * bsize * p.size());
    csumq.setup(q, 0, 3 * bsize * p.size());

    int sQ = bsize * q.deg();
    std::vector<T> pt_r, pt_q, pt_p;
    std::vector<T> pt_x;
    REP (i, sQ + 1) {
      pt_x.pb(i);
      pt_q.pb(csumq.query_prod(i, i + bsize));
      pt_p.pb(csump.query_prod(i, i + bsize));
    }

    T sum = 0;
    REP (i, sQ) sum = gfp.add(sum, gfp.mul(csump.query_prod(0, i), csumq.query_prod(i, sQ - 1)));

    pt_r.pb(sum);
    REP (i, sQ) {
      T mul = gfp.div(q(sQ - 1 + i), p(i));
      sum = gfp.mul(gfp.sub(sum, csumq.query_prod(i, sQ - 1 + i)), mul);
      sum = gfp.add(sum, csump.query_prod(i + 1, sQ + i));
      pt_r.pb(sum);
    }
    block_prod.pb(1);
    block_sum.pb(0);
    std::vector<T> block_pt_evalx;

    REP (i, n / bsize + 1) {
      block_pt_evalx.pb(i * bsize);
    }

    std::vector<T> p_eval, q_eval, r_eval;
    if (0) {
      P = fp.interpolate(pt_x, pt_p);
      p_eval = fp.eval(P, block_pt_evalx);
      R = fp.interpolate(pt_x, pt_r);
      Q = fp.interpolate(pt_x, pt_q);
      q_eval = fp.eval(Q, block_pt_evalx);
      r_eval = fp.eval(R, block_pt_evalx);
    }

    OPA_DISP0(1);
    if (1) {
      p_eval.clear();
      p_eval.pb(csump.p(gfp.getZ()));
      p_eval.pb(csump.p(gfp.getE()));
      q_eval.clear();
      q_eval.pb(csumq.p(gfp.getZ()));
      q_eval.pb(csumq.p(gfp.getE()));
      r_eval.pb(csump.p(gfp.getZ()) + csumq.p(gfp.getZ()));
      r_eval.pb(csump.p(gfp.getE()) + csumq.p(gfp.getE()));

      REP (i, bsize_log2) {

        auto p1 = de.proc(p_eval, 0, p_eval.size());
        auto p2 = de.proc(p_eval, 0, p_eval.size() * 2);
        auto p3 = de.proc(p_eval, 0, p_eval.size() * 3);
        std::vector<T> np = p_eval;
        np.insert(np.end(), ALL(p1));
        np.insert(np.end(), ALL(p2));
        np.insert(np.end(), ALL(p3));

        auto q1 = de.proc(q_eval, 0, q_eval.size());
        auto q2 = de.proc(q_eval, 0, q_eval.size() * 2);
        auto q3 = de.proc(q_eval, 0, q_eval.size() * 3);
        std::vector<T> nq = q_eval;
        nq.insert(nq.end(), ALL(q1));
        nq.insert(nq.end(), ALL(q2));
        nq.insert(nq.end(), ALL(q3));

        auto r1 = de.proc(r_eval, 0, r_eval.size());
        auto r2 = de.proc(r_eval, 0, r_eval.size() * 2);
        auto r3 = de.proc(r_eval, 0, r_eval.size() * 3);
        std::vector<T> nr = r_eval;
        nr.insert(nr.end(), ALL(r1));
        nr.insert(nr.end(), ALL(r2));
        nr.insert(nr.end(), ALL(r3));

        p_eval.clear();
        REP (i, np.size() / 2) p_eval.pb(gfp.mul(np[2 * i], np[2 * i + 1]));
        q_eval.clear();
        REP (i, nq.size() / 2) q_eval.pb(gfp.mul(nq[2 * i], nq[2 * i + 1]));
        r_eval.clear();
        REP (i, nr.size() / 2)
          r_eval.pb(gfp.add(gfp.mul(nr[2 * i], nq[2*i+1]), gfp.mul(nr[2 * i + 1], np[2 * i])));
      }
    }

    OPA_DISP0(2);

    if (0) {
      auto rcheck = pr.getZ();
      auto qcheck = pr.getE();
      REP (i, bsize) {
        qcheck = qcheck * pr.eval2(q, pr.xpa(i));
        auto tmp = pr.getE();
        REP (j, bsize - 1) tmp = tmp * pr.eval2(j >= i ? q : p, pr.xpa(j));
        rcheck = rcheck + tmp;
      }
      OPA_DISP0(rcheck - R);
      OPA_DISP0(qcheck - Q);
      OPA_DISP0(pt_r);
      OPA_DISP0(pr.eval_batch(rcheck, pt_x));
    }

    REP (i, block_pt_evalx.size()) {
      auto lprod = block_prod.back();
      auto lsum = block_sum.back();
      if (gfp.isZ(q_eval[i])) break;
      block_prod.pb(gfp.mul(lprod, gfp.div(p_eval[i], q_eval[i])));
      block_sum.pb(gfp.add(
        lsum, gfp.mul(lprod, gfp.div(r_eval[i], gfp.div(q_eval[i], q(i * bsize + bsize - 1))))));
    }
    // sum(prod(p(x+i)/q(x+i)))
    // = r(x) / prod(q(x+i))
    // deg(r(x)) ~= bsize
  }

  T query(int x) const {
    int blk = x / bsize;

    T res = block_sum[blk];
    T prod = block_prod[blk];
    int pos = bsize * blk;

    auto tmp = gfp.getZ();
    CumSumP cp, cq;
    cp.setup(p, pos, x);
    cq.setup(q, pos, x);

    FOR (i, blk * bsize, x) {
      res = gfp.add(res, prod);

      if (i != x - 1) prod = gfp.mul(prod, gfp.div(p(i), q(i)));
    }
    return res;
  }
};

struct SolverContext {
  Problem prob;
  s64 iN, i2;

  void read() {
    prob.read();
    if (TEST_RAND) {

    } else {
    }
    iN = gfp.inv(prob.N);
    i2 = gfp.inv(2);
  }

  s64 pn(s64 n) const { return (prob.N - n) * n % mod * i2 % mod * iN % mod * iN % mod; }
  s64 qn(s64 n) const {
    return n * iN % mod * i2 % mod * (1 + (prob.N - n) % mod * iN % mod) % mod;
  }
  F pn2(s64 n) const { return ff.import(prob.N - n, prob.N) * ff.import(n, prob.N * 2); }
  F qn2(s64 n) const {
    return ff.import(n, prob.N * 2) * (ff.import(prob.N - n, prob.N) + ff.import(1));
  }

  F alpha_eval(int x) const {
    F f0 = ff.getZ();
    if (x == 0) return f0;
    F k = ff.getE();
    F v = f0 + k;
    FOR (i, 1, x) {
      k = k * qn2(i) / pn2(i);
      v = v + k;
    }
    return v;
  }

  F phi_eval0(int x) const {
    if (x == prob.N - 1) return ff.getZ();
    F k = -qn2(prob.N - 1) / (F(1) - pn2(prob.N - 1));
    F v = k;
    FORV (i, x + 1, prob.N - 1) {
      k = F(-1) / qn2(i) + k * pn2(i) / qn2(i);
      v = v + k;
    }
    return v;
  }

  F phi_evalN(int x) const {
    if (x == 1) return ff.getZ();
    F k = -qn2(1) / (F(1) - pn2(1));
    F v = k;
    FOR (i, 1, x) {
      k = F(-1) / pn2(i) + k * qn2(i) / pn2(i);
      v = v + k;
    }
    return v;
  }

  F f_eval(int x) const {
    if (x == 0) return ff.getZ();
    F k = ff.getE() * F(2);
    F v = k;
    FOR (i, 1, x) {
      k = k * ff.import(2 * prob.N - i, prob.N - i);
      v = v + k;
    }
    auto conv = gfp.div((v.p % mod).gets32(), (v.q % mod).gets32());
    return v;
  }

  s64 solve() {
    if (prob.N < 10) return solve_dumb();
    PT p = pr.import_vec({ 2 * prob.N - 1, gfp.neg(1) });
    PT q = pr.import_vec({ prob.N - 1, gfp.neg(1) });
    CumSumProd cp;
    cp.setup(p, q, prob.N);
    auto res = cp.query(prob.N);
    for (auto e : prob.entries) res = gfp.sub(res, cp.query(e));
    return gfp.mul(2, res);
  }

  s64 solve_dumb() {
    F res = f_eval(prob.N);
    for (auto e : prob.entries) res = res - f_eval(e);
    auto conv = gfp.div((res.p % mod).gets32(), (res.q % mod).gets32());
    return conv;

    F a0 = alpha_eval(0);
    F aN = alpha_eval(prob.N);
    std::vector<F> p0;
    for (auto e : prob.entries) {
      auto cur = alpha_eval(e);
      p0.pb((cur - aN) / (a0 - aN));
    }

    F p10 = (alpha_eval(1) - aN) / (a0 - aN);
    F e10 = phi_eval0(1) - phi_eval0(0);
    F e1n = phi_evalN(1) - phi_evalN(prob.N);
    OPA_DISP0(e10, e1n);

    auto pall0 = F(1);
    REP (i, prob.entries.size()) {

      auto e = prob.entries[i];
      auto pxN = F(1) - p0[i];
      pall0 = pall0 - pxN;
      res = res + pxN * (phi_evalN(e) - phi_evalN(prob.N));
    }
    auto succ = (F(1) - p10) / F(2);
    auto rem = pall0 * (F(1) + succ * e1n) / (F(1) - succ);
    OPA_DISP0(res, pall0, succ);
    res = res + rem;
    OPA_DISP0(gfp.div(res.p.gets32(), res.q.gets32()));

    return 0;
  }
};

int main(int argc, char **argv) {
  opa::init::opa_init(argc, argv);
  srand(0);
  int tn;

  if (TEST_RAND)
    tn = 10000;
  else
    scanf("%d\n", &tn);

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
      //OPA_DISP0(res, sc.solve_dumb());
    }
  }

  return 0;
}
