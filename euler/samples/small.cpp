#include <opa/math/common/FractionField.h>
#include <opa/math/common/Matrix.h>
#include <opa/math/common/PR_ring.h>
#include <opa/math/common/RealField.h>
#include <opa/math/common/Types.h>
#include <opa/math/common/Utils.h>
#include <opa/math/common/UtilsPoly.h>
#include <opa/math/common/Zn.h>
#include <opa/math/common/ZnForDiv.h>
#include <opa/math/common/algo.h>
#include <opa/math/common/base.h>
#include <opa/math/common/float.h>
#include <opa_common.h>

#include <glib/gtl/map_util.h>
#include <opa/algo/base.h>
#include <opa/algo/graph.h>
#include <opa/algo/graph_util.h>
#include <opa/math/game/base.h>
#include <opa/or/grid_search.h>
#include <opa/or/search.h>
#include <opa/utils/DataStruct.h>
#include <opa/utils/hash.h>
#include <opa/utils/misc.h>

using namespace std;
using namespace opa;
using namespace opa::math;
using namespace opa::math::common;
using namespace opa::utils;
using namespace opa::algo;
using namespace opa::math::game;

DEFINE_string(action, "", "");
DEFINE_string(tempfile, "/tmp/euler.out", "");

std::unordered_map<s64, int> collatz;

template <int mod> class CombHelper {
public:
  CombHelper(int n = 0) { this->init(n); }
  void init(int n) {
    fact.resize(n + 1);
    ifact.resize(n + 1);
    fact[0] = 1;
    REP (i, n)
      fact[i + 1] = 1ull * fact[i] * (i + 1) % mod;
    ifact[0] = 1;
    REP (i, n + 1)
      ifact[i] = u32_faste(fact[i], mod - 2, mod);
  }

  u32 cnk(int n, int k) const {
    if (n < k) return 0;
    if (k < 0) return 0;
    return 1ull * fact[n] * ifact[k] % mod * ifact[n - k] % mod;
  }

  std::vector<int> fact;
  std::vector<int> ifact;
};

class CombHelperForMod {
public:
  void init(const ZnForDiv *zn, int n) {
    m_zn = zn;
    m_n = n;
    fact.resize(n + 1);
    fact[0] = m_zn->importu32(1);
    REP (i, n)
      fact[i + 1] = m_zn->mul(fact[i], m_zn->importu32(i + 1));
  }

  u32 cnk(int n, int k) const {
    if (n < k) return 0;
    if (k < 0) return 0;
    return m_zn->to_u32(m_zn->div(fact[n], m_zn->mul(fact[k], fact[n - k])));
  }

  u32 arrangement(int n, int k) const {
    OPA_CHECK(n <= m_n, n);
    OPA_CHECK(k <= m_n, k);
    u32 res = m_zn->to_u32(m_zn->div(fact[n], fact[k]));
    OPA_DISP0(n, k, fact[n], fact[k], res);
    return res;
  }

  const ZnForDiv *m_zn;
  int m_n;
  std::vector<NumForDiv> fact;
};

s64 next_collatz(s64 v) { return (v & 1) ? 3 * v + 1 : v >> 1; }

int get_collatz(s64 v) {
  if (v == 1) return 0;
  int &x = collatz[v];
  if (x == 0) {
    x = 1 + get_collatz(next_collatz(v));
  }
  return x;
}

void p7() {
  int n = 101;
  REP (i, n)
    printf("%d\n", pl[i]);
}

void p10() {
  bignum s = 0;
  for (auto &p : pl) {
    if (p > 2e6) break;
    s += p;
  }
  cout << s.str(10) << endl;
}

bignum count_divisors(const bignum &v) {
  bignum rem, res;
  auto factors = factor_small(v, rem);
  res = 1;
  if (rem != 1) res = 2;
  for (auto &factor : factors) res *= (1 + factor.second);
  return res;
}

void p12() {

  int n = 2;
  for (s64 i = 2;; ++i) {
    s64 v = i * (i + 1) / 2;

    bignum cnt = count_divisors(v);
    printf(">> %Ld %s\n", i, cnt.str(10).c_str());
    if (cnt > 500) {
      printf("%Ld\n", v);
      break;
    }
  }
}

void p14() {
  int best = 1;
  MaxFinderPair<s64, int> finder;
  FOR (i, 1, 1e6) { finder.update(get_collatz(i), i); }
  printf("%d\n", finder.get());
}

namespace n_p537 {
const int mod = 1004535809;
const int n = 20000;
const int maxn = n + 10;
std::map<std::tuple<int, int, int>, int> dp; // prime_id, n, k

CombHelper<mod> helper(maxn);

int bad(int prime_id, int n, int k) { return (n < k * prime_id); }

int rec(int prime_id, int n, int k) {
  if (n == 0 || k == 0) return n == 0 && k == 0;
  if (bad(prime_id, n, k)) return 0;
  auto key = std::make_tuple(prime_id, n, k);

  if (dp.count(key)) return dp[key];
  int nv = pl[prime_id] - 1 - (prime_id == 0 ? 0 : pl[prime_id - 1]);
  int &r = dp[key];
  u64 tmp = 0;
  REPV (i, k + 1)
    if (i > 0) {
      if (bad(prime_id + 1, n - i * prime_id, k - i)) break;
      tmp += rec(prime_id + 1, n - i * prime_id, k - i) * helper.cnk(k, i) %
             mod * u32_faste(nv, i, mod) % mod;
    }
  tmp += rec(prime_id + 1, n, k);
  r = tmp % mod;
  return r;
}

inline int rmp(int n, int k) { return k * maxn + n; }

// ou are given T(10,10) = 869 985 and T(103,103) ≡ 578 270 566 (mod 1 004 535
// 809).
// Find T(20 000, 20 000) mod 1 004 535 809.
int solve2() {
  int N = (maxn + 10) * (maxn + 10);
  int *t1 = new int[N];
  memset(t1, 0, sizeof(int) * N);
  t1[rmp(n, n)] = 1;
  REP (i, n + 1) {
    int nv = pl[i] - (i == 0 ? 1 : pl[i - 1]);
    vector<int> vals;
    REP (k, n + 1)
      vals.push_back(u32_faste(nv, k, mod));

    printf("%d / %d , p=%d\n", i, n, pl[i]);
    REP (j, n + 1) {
      int maxk = n / 1;
      REP (k, maxk + 1) {
        int cur = t1[rmp(j, k)];
        if (cur == 0) continue;
        int mk = std::max(k - j, 0);
        t1[rmp(j, k)] = 0;
        FOR (take, mk, k + 1) {
          int &target = t1[rmp(j - (k - take), k - take)];
          int v = 1ull * vals[take] * helper.cnk(k, take) % mod * cur % mod;
          target = (target + v) % mod;
        }
      }
    }
  }

  int res = t1[rmp(0, 0)];
  delete[] t1;
  return res;
}
}

void p537() {
  // int res = n_p537::rec(0, 20000, 20000);
  int res = n_p537::solve2();
  printf("%d\n", res);
}

std::vector<std::vector<std::vector<int> > >
list_selections(const std::vector<int> &counts) {
  struct Rec {
    std::vector<int> counts;
    std::vector<std::vector<std::vector<int> > > res;
    std::vector<std::vector<int> > cur;

    bool is_done() const {
      for (auto &c : counts)
        if (c != 0) return false;
      return true;
    }

    void solve(const std::vector<int> &counts) {
      this->counts = counts;
      cur.emplace_back();
      rec(0);
    }

    void rec(int pos) {
      if (counts.size() == pos) {
        if (cur.size() >= 2) {
          if (cur[cur.size() - 1] < cur[cur.size() - 2]) return;
        }

        if (is_done()) {
          res.push_back(cur);
        } else {
          cur.emplace_back();
          rec(0);
          cur.pop_back();
        }
        return;
      }

      if (counts[pos] == 0) return rec(pos + 1);
      int old_count = counts[pos];
      REP (j, old_count + 1) {
        if (cur.back().empty() && j == 0) continue;
        if (j != 0) cur.back().push_back(pos);
        counts[pos] = old_count - j;
        rec(pos + 1);
      }
      REP (j, old_count)
        cur.back().pop_back();
      counts[pos] = old_count;
    }
  };

  Rec r;
  r.solve(counts);
  return r.res;
}
std::vector<std::vector<u64> > list_divisors_split(const u64 n) {
  bignum rem;
  auto factors = factor_small(n, rem);
  if (rem != 1) factors.emplace_back(rem.getu64(), 1);

  std::vector<int> counts;
  for (auto &factor : factors) counts.push_back(factor.second);
  OPA_DISP0(counts);
  auto selections = list_selections(counts);
  OPA_DISP0(selections);

  std::vector<std::vector<u64> > res;
  for (auto &selection : selections) {
    std::vector<u64> entry;
    for (auto &s : selection) {
      u64 v = 1;
      for (auto &c : s) {
        v *= factors[c].first;
      }
      entry.push_back(v);
    }
    res.push_back(entry);
  }
  return res;
}

u64 count_p233(const std::vector<u64> &good, s64 lim, s64 pval) {
  s64 tmp = lim / pval;

  s64 res = 0;
  vector<s64> good2;
  for (auto &entry : good) {
    if (entry > tmp) break;
    good2.push_back(entry);
  }

  opa::OR::SubsetSelector<s64> ss(good2, [&](const std::vector<int> &ids) {
    s64 f = 1;
    s64 x = 1;
    for (auto &id : ids) {
      x *= good2[id];
      if (x > tmp) return {false, true};
      f *= -1;
    }
    s64 v = (tmp / x) * (tmp / x + 1) / 2 * x;
    res += v * f;
    //  res += tmp / x * f;
    return {false, false};
  });
  return res * pval;
  return res;
}

void p233() {
  vector<u64> good;
  auto divs = list_divisors_split(105);

  for (auto &p : pl) {
    if (p % 4 == 1) good.push_back(p);
  }
  s64 lim = 1e11;
  bignum plim = bignum(lim);
  s64 cnt = 0;
  s64 cnt2 = 0;

  // 158618179044151376
  // 271204031455541309
  // 158618179044151376

  for (auto &div_set : divs) {
    std::sort(ALL(div_set));
    std::reverse(ALL(div_set));
    for (auto &k : div_set) k = (k - 1) / 2;
    OPA_DISP0("ON DIVSET >> ", div_set);
    REP (i, good.size()) {
      bignum p = good[i];
      p = p.pow(div_set[0]); // only have even solutions
      if (p > lim) break;
      if (div_set.size() == 1) {
        cnt += count_p233(good, lim, p.gets64());
        continue;
      }

      REP (j, good.size()) {
        if (i == j) continue;
        bignum p2 = p * bignum(good[j]).pow(div_set[1]);
        if (p2 > lim) break;
        if (div_set.size() == 2) {
          cnt += count_p233(good, lim, p2.gets64());
          continue;
        }

        REP (k, good.size()) {
          if (i == k || j == k) continue;
          bignum p3 = p2 * bignum(good[k]).pow(div_set[2]);
          if (p3 > lim) break;

          if (div_set.size() == 3) {
            cnt += count_p233(good, lim, p3.gets64());
            continue;
          }
        }
      }
    }
  }
  OPA_DISP0(plim.str(10));
  OPA_DISP0(bignum(cnt).str(10));
  OPA_DISP0(bignum(cnt * 2).str(10));
}

namespace n201 {
const int maxn = 50;
const int maxv = 100;
}

void p201() {
  using namespace n201;
  int stride = maxv * maxv * maxn + 1;
  int sz = stride * (maxn + 1) + 10;
  u8 *t1 = new u8[sz];

  vector<int> elems;
  REP (i, 100)
    elems.push_back((i + 1) * (i + 1));
  // elems = {1,3,6,8,10,11};

  memset(t1, 0, sz);
  t1[0] = 1;
  REP (i, elems.size()) {
    int v = elems[i];
    OPA_DISP0(i, v);
    REPV (k, maxn) {
      REPV (j, stride) {
        if (t1[k * stride + j]) {
          t1[(k + 1) * stride + j + v] =
            std::min(2, t1[k * stride + j] + t1[(k + 1) * stride + j + v]);
        }
      }
    }
  }

  u64 res = 0;
  REP (i, stride)
    if (t1[maxn * stride + i] == 1) {
      OPA_DISP0(i);
      res += i;
    }
  printf("%Ld\n", res);
}

namespace n269 {

const int maxdeg = 16;
struct data_t {
  std::vector<int> vals;

  bool operator<(const data_t &x) const { OPA_LT_OP(x, vals); }
  bool operator==(const data_t &x) const { OPA_EQ_OP(x, vals); }
};

struct SolverCtx {
  std::map<data_t, s64> dp[maxdeg];
  std::vector<int> roots;
  int nr;

  s64 solve(const std::vector<int> roots) {
    this->roots = roots;
    nr = roots.size();
    s64 res = 0;
    std::vector<int> start(roots.size(), 0);
    return rec(data_t{ start }, maxdeg - 1);
  }

  s64 rec(const data_t &data, int deg) {
    if (deg == -1) {
      for (auto &d : data.vals)
        if (d != 0) return 0;
      return 1;
    }
    if (dp[deg].count(data)) return dp[deg][data];
    s64 &res = dp[deg][data];
    data_t ndata = data;

    REP (i, nr) { ndata.vals[i] *= -roots[i]; }
    res = 0;
    REP (v, 10) {
      bool bad = false;
      REP (i, nr) {
        if (abs(ndata.vals[i] * roots[i]) > 40) {
          bad = true;
          break;
        }
      }
      if (v == 0 && deg == 0) bad = true; // force non x factor
      if (!bad) {
        res += rec(ndata, deg - 1);
      }
      REP (i, nr)
        ndata.vals[i]++;
    }

    return res;
  }
};

struct Solver2 {
  std::vector<std::pair<std::set<int>, s64> > counts;
  std::map<int, s64> mem;

  s64 get() {
    s64 res = 0;
    REP (i, counts.size()) {
      s64 have = get1(i);
      res += have;
      OPA_DISP0(counts[i], have);
    }
    return res;
  }

  s64 get1(int id) {
    if (mem.count(id)) return mem[id];
    s64 &r = mem[id];
    auto &cur = counts[id];
    r = cur.second;

    REP (other_id, counts.size()) {
      auto &other = counts[other_id];

      if (other.first.size() <= cur.first.size()) continue;
      bool contained = true;
      for (auto &x : cur.first)
        if (!other.first.count(x)) {
          contained = false;
          break;
        }
      if (!contained) continue;
      s64 rem = get1(other_id);
      r -= rem;
    }
    return r;
  }
};

void p269() {
  std::vector<int> cnds;
  FOR (i, 1, 10)
    cnds.push_back(i);

  std::vector<std::pair<std::set<int>, s64> > counts;
  opa::OR::SubsetSelector<int> ss(cnds, [&](const std::vector<int> &ids) {
    if (ids.size() == 0) return {false, false};
    int prod = 1;
    std::vector<int> roots;
    for (auto &id : ids) {
      roots.push_back(cnds[id]);
      prod *= cnds[id];
    }
    if (prod >= 10) return {false, true};

    SolverCtx solver;
    s64 res = solver.solve(roots);
    OPA_DISP0(roots, res);
    counts.emplace_back(std::set<int>(ALL(roots)), res);
    return {false, false};
  });

  Solver2 s2;
  s2.counts = counts;
  s64 res = s2.get() + bignum(10).pow(maxdeg - 1).gets64();
  printf(">> %Ld\n", res);
}
}

template <class T> class FastBinaryTree {
public:
  FastBinaryTree(int n) {
    this->n = n;
    d = log2_high_bit(n - 1) + 1;
    N = 1 << d;
    N2 = 2 * N;
    data.resize(N2);
  }

  void add(int p, T v) {
    p += N;
    v += data[p];
    while (p) {
      data[p] = std::max(data[p], v);
      p >>= 1;
    }
  }

  void update(int p, T v) {
    p += N;
    while (p) {
      data[p] = std::max(data[p], v);
      p >>= 1;
    }
  }

  T get(int p) {
    p += N;
    T res = data[p];
    while (p > 1) {
      if (p & 1) res = std::max(res, data[p ^ 1]);
      p >>= 1;
    }
    return res;
  }

  int d;
  int n;
  int N;
  int N2;
  std::vector<T> data;
};

namespace n411 {

class Solver {
public:
  int n;
  std::vector<pii> points;

  Solver(int n) {
    this->n = n;
    int x = 1 % n, y = 1 % n;
    REP (i, 2 * n + 1) {
      points.emplace_back(x, y);
      x = 2 * x % n;
      y = 3 * y % n;
    }
    sort(ALL(points));
    make_unique(points);
    OPA_DISP0(points);
  }

  s64 get() {
    s64 res = 0;
    FastBinaryTree<int> bt(n + 1);

    for (auto &pt : points) {
      bt.update(pt.second, bt.get(pt.second) + 1);
    }
    res = bt.data[1];
    return res;
  }
};

void solve() {
  s64 res = 0;
  // OPA_DISP0(Solver(10000).get());
  // return;
  FOR (k, 1, 31) {
    int k5 = k * k * k * k * k;
    Solver solver(k5);
    s64 cur = solver.get();
    OPA_DISP0(k, cur);
    OPA_CHECK(cur <= k5 * 2, cur, k5, k);
    res += cur;
  }
  printf(">> %Ld\n", res);
}
}

namespace n575 {
const int n = 1000;

Float get(bool v1, int nround = 1000) {
  std::vector<Float> ta, tb;
  Float iv = Float(1) / (n * n);
  tb.resize(n * n, iv);
  ta.resize(n * n, iv);

  int vd[] = { 1, 0, -1, 0, 1 };
  vector<std::pair<Float, vector<int> > > ntb;
  REP (i, n * n) {
    vector<int> neighbors;
    int x = i / n;
    int y = i % n;
    REP (k, 4) {
      int nx = x + vd[k];
      int ny = y + vd[k + 1];
      if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
      neighbors.push_back(nx * n + ny);
    }
    Float coef = Float(0.5) / neighbors.size();

    if (v1) {
      neighbors.push_back(i);
      coef = Float(1) / neighbors.size();
    }

    ntb.emplace_back(coef, neighbors);
  }

  bool first = true;
  Float last;

  for (int nt = 0;; ++nt) {
    if (nt % 200 == 0) OPA_DISP0(nt);
    REP (i, tb.size()) {
      if (v1) {
        tb[i] = 0;
      } else {
        tb[i] = ta[i] / 2;
      }
    }
    REP (i, ta.size()) {
      for (auto &nxt : ntb[i].second) tb[nxt] += ta[i] * ntb[i].first;
    }

    std::swap(ta, tb);

    bool compute = nt >= nround && nt % 10 == 0;
    if (compute) {
      Float res = 0;
      FOR (i, 1, n + 1) {
        int target = i * i - 1;
        res += ta[i];
      }
      if (!first) {
        Float diff = (last - res).abs();
        OPA_DISP0(v1, diff.to_str(20));
        if (diff * Float(10).pow(20) < 1) {
          if (1) {
            REP (i, n) {
              REP (j, n) { printf("%s ", ta[i * n + j].to_str(14).c_str()); }
              puts("");
            }
          }
          return res;
        }
      }
      last = res;
      first = false;
    }
  }
}

int get_cat(int x, int y) {
  bool bx = x == 0 || x == n - 1;
  bool by = y == 0 || y == n - 1;
  if (bx && by) return 0;
  if (bx || by) return 1;
  return 2;
}

Float get2(bool v1) {
  RealF R;
  Matrix<Float> m;
  m.initialize(&R, 3, 3);

  int vd[] = { 1, 0, -1, 0, 1 };
  vector<std::pair<Float, vector<int> > > ntb;
  vector<pii> cats = { { 0, 0 }, { 0, 1 }, { 1, 1 } };
  REP (i, 3) {
    vector<int> neighbors;
    int x = cats[i].first;
    int y = cats[i].second;
    REP (k, 4) {
      int nx = x + vd[k];
      int ny = y + vd[k + 1];
      if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
      neighbors.push_back(nx * n + ny);
    }
    Float selfc = Float(0.5);
    Float coef = Float(0.5) / neighbors.size();

    if (v1) {
      neighbors.push_back(x * n + y);
      coef = Float(1) / neighbors.size();
      selfc = 0;
    }
    m(i, i) = selfc;
    for (auto nxt : neighbors) {
      int x = nxt / n;
      int y = nxt % n;
      m(i, get_cat(x, y)) += coef;
    }
  }

  printf(" >>> ON %d >>>>>\n", v1);
  Matrix<Float> im;
  im = m.faste(3000);
  int counts[] = { 4, 4 * n - 8, (n - 2) * (n - 2) };
  Float norm = 0;
  REP (i, 3)
    norm += im(0, i) * counts[i];
  im.scmul(Float(1) / norm);
  OPA_DISP0(m, im);
  OPA_DISP0(m.mul(m.fromvec({ Float(0.025), Float(0.0375), Float(0.05) })));

  Float res = 0;
  FOR (i, 1, n + 1) {
    int target = i * i - 1;
    res += im(0, get_cat(target / n, target % n));
  }
  return res;
}

Float get3(bool v1) {
  std::vector<std::pair<Float, Float> > tsf;
  for (auto nn : { 2, 3, 4 }) {
    if (v1) {
      Float v = Float(1) / (nn + 1);
      tsf.emplace_back(v, v);
    } else {
      tsf.emplace_back(Float(1) / 2, Float(1) / 2 / nn);
    }
  }

  int counts[] = { 4, 4 * n - 8, (n - 2) * (n - 2) };
  RealF R(Float(1. / 10).pow(20));
  Matrix<Float> m;
  m.initialize(&R, 6, 3);
  int nn = n * n;
  m.setRow(0, { tsf[0].first - 1, tsf[1].second * 2, 0 });
  m.setRow(
    1,
    { tsf[0].second, tsf[1].first + tsf[1].second * 1 - 1, tsf[2].second * 1 });
  m.setRow(
    2, { Float(0), tsf[1].first + tsf[1].second * 2 - 1, tsf[2].second * 1 });
  m.setRow(
    3, { Float(0), tsf[1].second * 2, tsf[2].first + tsf[2].second * 2 - 1 });
  m.setRow(
    4, { Float(0), tsf[1].second * 1, tsf[2].first + tsf[2].second * 3 - 1 });
  m.setRow(5, { (double)counts[0], (double)counts[1], (double)counts[2] });

  OPA_DISP0(m);
  auto mres = m.solve({ Float(0), Float(0), 0, 0, 0, 1 });
  OPA_DISP0(mres);
  OPA_CHECK0(mres.size() == m.getM());
  Float res = 0;
  FOR (i, 1, n + 1) {
    int target = i * i - 1;
    res += mres[get_cat(target / n, target % n)];
  }
  return res;
}

void solve() {
  // Float res0 = (get(false) + get(true)) / 2;
  // Float res = (get2(false) + get2(true)) / 2;
  Float res = (get3(false) + get3(true)) / 2;
  OPA_DISP0(res.to_str(12));
}
}

namespace n289 {
// want c <= r for better path decomposition
// L(10,10) = 9369513298
const int r = 10;
const int c = 10;
const int n = (r + 1) * (c + 1);
std::vector<std::pair<pii, std::set<int> > > path_decomposition;
const s64 mod = 1e10;
typedef std::vector<pii> pairing_t;

FastGraph graph;
FastGraph edge_graph;

Remapper<pii, std::map<pii, int> > rmp;
TwoWayRemapper<pii, pii, std::map<pii, pii>, std::map<pii, pii> > rmp_edge;
std::map<int, std::vector<pairing_t> > allowed_pairings;

bool is_boundary(int i, int j) { return i == 0 || i == r || j == 0 || j == c; }

struct state_t {
  pairing_t pairing; // pair of edges connected together, connected to
                     // later vertices in the path decomposition
  OPA_DECL_EQ_OPERATOR(state_t, pairing);
  OPA_DECL_LT_OPERATOR(state_t, pairing);
};
std::map<state_t, s64> mem[n];

s64 rec(int id, const state_t &state) {
  if (id == n) return state.pairing.size() == 0;

  if (mem[id].count(state)) return mem[id][state];
  s64 &r = mem[id][state];
  const auto &entry = path_decomposition[id].first;
  const auto &s = path_decomposition[id].second;
  std::map<int, int> pairing_remap;
  REP (i, state.pairing.size()) {
    pairing_remap[state.pairing[i].first] = state.pairing[i].second;
    pairing_remap[state.pairing[i].second] = state.pairing[i].first;
  }

  std::set<int> to_remove_edges;
  for (const auto &p : allowed_pairings[id][0]) {
    if (pairing_remap.count(p.first)) to_remove_edges.insert(p.first);
    if (pairing_remap.count(p.second)) to_remove_edges.insert(p.second);
  }

  for (const auto &pairing : allowed_pairings[id]) {
    state_t nstate;
    bool ok = true;
    std::map<int, int> pairing_remap2 = pairing_remap;
    for (const auto &p : pairing) {
      int p1 = glib::gtl::FindWithDefault(pairing_remap2, p.first, -1);
      int p2 = glib::gtl::FindWithDefault(pairing_remap2, p.second, -1);

      if (p1 == -1 && p2 == -1) {
        nstate.pairing.push_back(p);
      } else if (p1 == -1) {
        pairing_remap2[p.first] = p2;
        pairing_remap2[p2] = p.first;
        pairing_remap2.erase(p.second);
      } else if (p2 == -1) {
        pairing_remap2[p.second] = p1;
        pairing_remap2[p1] = p.second;
        pairing_remap2.erase(p.first);
      } else {

        if (p1 == p.second) {
          pairing_remap2.erase(p1);
          pairing_remap2.erase(p2);
          if (id == n - 1) continue;
          // Don't close loop (last vertex does not go through here
          ok = false;
          break;
        }
        pairing_remap2[p1] = p2;
        pairing_remap2[p2] = p1;
        pairing_remap2.erase(p.first);
        pairing_remap2.erase(p.second);

        // nstate.pairing.emplace_back(p1, p2);
      }
    }

    for (auto &e : pairing_remap2) {
      if (e.first > e.second) continue;
      nstate.pairing.push_back(e);
    }
    std::sort(ALL(nstate.pairing));

    if (!ok) continue;
    r += rec(id + 1, nstate);
  }
  // OPA_DISP0(id, state.pairing, r, to_remove_edges);
  r %= mod;
  return r;
}

bool is_overlapping_pairing(const pairing_t &pairing) {
  REP (i, pairing.size()) {
    REP (j, i) {
      auto a = pairing[i];
      auto b = pairing[j];
      if (a.first < b.first && (a.second < b.first || b.second < a.second))
        continue;
      std::swap(a, b);
      if (a.first < b.first && (a.second < b.first || b.second < a.second))
        continue;
      return true;
    }
  }
  return false;
}

struct PairingListing {
  std::vector<int> tb;
  std::vector<pairing_t> res;
  std::vector<int> used;
  pairing_t cur;
  int n;
  PairingListing(int n) {
    REP (i, n)
      tb.push_back(i);
    this->n = n;
    used.resize(n, 0);
  }

  PairingListing &get() {
    rec(0);
    return *this;
  }

  PairingListing &get_no_overlap() {
    rec(0);
    res.resize(std::remove_if(ALL(res), is_overlapping_pairing) - res.begin());
    return *this;
  }
  void rec(int p) {
    if (p == n) {
      res.push_back(cur);
      return;
    }
    if (used[p]) return rec(p + 1);
    FOR (i, p + 1, n) {
      if (used[i]) continue;
      used[i] = 1;
      cur.emplace_back(p, i);
      rec(p + 1);
      cur.pop_back();
      used[i] = 0;
    }
  }
};

void solve() {
  graph.reset(n, algo::Mode::MULTIGRAPH);
  edge_graph.reset(0, algo::Mode::DYNAMIC_SIZE);

  int vd[] = { 1, 0, -1, 0, 1 };
  std::set<int> decomposition;
  std::map<int, std::vector<pairing_t> > deg_to_pairing;

  REP (i, r + 1) {
    REP (j, c + 1) {
      int a = rmp.get2(i, j);
      pii entry(a, -1);
      if (i != 0) {
        entry.second = rmp.get2(i - 1, j);
        decomposition.erase(entry.second);
      }
      decomposition.insert(a);
      path_decomposition.emplace_back(entry, decomposition);

      std::vector<pii> edges;
      REP (k, 4) {
        int ni = i + vd[k];
        int nj = j + vd[k + 1];
        if (ni < 0 || nj < 0 || ni >= r + 1 || nj >= c + 1) continue;
        int b = rmp.get2(ni, nj);
        if (a < b) {
          int c1 = graph.add_bidirectional(a, b);
          int c2 = -1;
          // edge to edge
          if ((i == ni && (i == 0 || i == r)) ||
              (j == nj && (j == 0 || j == c)))
            ;
          else {
            c2 = graph.add_bidirectional(a, b);
          }
          // OPA_DISP0(i, j, ni, nj, c1, c2);
          rmp_edge.add(MP(a, b), MP(c1, c2));
        }
        auto tmp_edges = graph.get_edges2(a, b);
        if (b < a && tmp_edges.size() == 2)
          std::swap(tmp_edges[0], tmp_edges[1]);
        for (auto &edge : tmp_edges) {
          int id = graph.get_edge_id(edge.id);
          edges.emplace_back(b, id);
        }
      }

      // OPA_DISP0(edges);
      // for (auto &edge : edges) edge.second = abs(edge.second);
      int ne = edges.size();
      if (deg_to_pairing.count(ne) == 0) {
        deg_to_pairing[ne] = PairingListing(ne).get_no_overlap().res;
        OPA_DISP("Allowed pairings >> ", ne, deg_to_pairing[ne]);
      }

      /*
         General case: list all perfect matchings
      REP (k, edges.size()) {
        int k2 = (k + 1) % ne;
        edge_graph.add_bidirectional(edges[k].second, edges[k2].second);
        OPA_DISP0(i, j, rmp.rget(edges[k].first), rmp.rget(edges[k2].first));
      }
      */

      for (auto &pairing_base : deg_to_pairing[ne]) {
        pairing_t pairing;
        for (auto &entry : pairing_base)
          pairing.emplace_back(edges[entry.first].second,
                               edges[entry.second].second);
        allowed_pairings[a].push_back(pairing);
      }
      // OPA_DISP0(a, allowed_pairings[a]);
    }
  }

  // OPA_DISP0(edge_graph.str());
  // OPA_DISP0(rmp.mp());
  s64 res = rec(0, state_t());
  printf(">> %Ld\n", res);
}
}

namespace n490 {
const int mod = 1e9;
const int maxd = 3;
const s64 L = 12;
Zn zn(mod);

struct state_t {
  std::vector<std::pair<int, int> > transition;
  OPA_DECL_EQ_OPERATOR(state_t, transition);
  OPA_DECL_LT_OPERATOR(state_t, transition);
};
state_t start;

Remapper<state_t, std::map<state_t, int> > state_rmp;
Remapper<int> used_rmp;
std::map<pii, int> tsf;
std::map<int, int> deg;

bool is_valid(const state_t &state) {
  for (auto &e : state.transition)
    if (e.first >= 3) return false;
  return true;
}

bool dfs(const state_t &state) {
  int cur = state_rmp.get(state);
  if (deg.count(cur)) return true;
  deg[cur] = 0;
  OPA_DISP("Got state ", cur, state.transition);

  state_t nstate = state;
  std::vector<int> forward, backward;
  IdGenerator idgen;
  idgen.block(0);

  REP (i, nstate.transition.size()) {
    auto &e = nstate.transition[i];
    e.first += 1;
    idgen.block(abs(e.second));
    if (e.second < 0)
      backward.push_back(i);
    else
      forward.push_back(i);
  }

  std::vector<state_t> next_list;
  {
    int blkid = idgen.get_new();
    nstate.transition.emplace_back(0, blkid);
    nstate.transition.emplace_back(0, -blkid);
    next_list.push_back(nstate);
    nstate.transition.pop_back();
    nstate.transition.pop_back();
  }

  for (auto &e : nstate.transition) {
    int old = e.first;
    e.first = 0;
    next_list.push_back(nstate);
    e.first = old;
  }

  for (auto &fwd : forward) {
    for (auto &bwd : backward) {
      // no inner loop allowed
      if (nstate.transition[fwd].second == -nstate.transition[bwd].second)
        continue;

      state_t tmp;
      REP (i, nstate.transition.size()) {
        if (i == fwd || i == bwd) continue;
        tmp.transition.push_back(nstate.transition[i]);
      }
      next_list.push_back(tmp);
    }
  }
  for (auto &next : next_list) {
    if (!is_valid(next)) continue;
    std::sort(ALL(next.transition));
    Remapper<int> rmp_id;
    for (auto &x : next.transition) {
      x.second = (rmp_id.get(abs(x.second)) + 1) * OPA_SIGN(x.second);
    }

    if (dfs(next)) {
      int nid = state_rmp.get(next);
      ++tsf[MP(cur, nid)];
      ++deg[cur];
    }
  }
  return deg[cur] > 0;
}

int startp;
std::vector<std::vector<int> > paths;
Matrix<u32> transfer_mat;
std::vector<int> cur_path;
void list_paths(int pos, int e) {
  if (pos == L) {
    if (e == startp) paths.push_back(cur_path);
    return;
  }

  REP (i, transfer_mat.m) {
    if (transfer_mat(e, i) != 0) {
      cur_path.push_back(i);
      list_paths(pos + 1, i);
      cur_path.pop_back();
    }
  }
}

Matrix<u32> build_transfer_mat() {
  start.transition.emplace_back(0, 1);
  dfs(start);
  OPA_DISP0(deg[state_rmp.get(start)]);
  for (auto &x : deg) {
    if (x.second > 0) {
      used_rmp.get(x.first);
    }
  }
  startp = used_rmp.get(state_rmp.get(start));
  printf("MAT >> %d %d\n", state_rmp.size(), used_rmp.size());

  Matrix<u32> res;
  res.initialize(&zn, used_rmp.size(), used_rmp.size());
  for (auto &e : tsf) {
    if (!used_rmp.has(e.first.first)) continue;
    if (!used_rmp.has(e.first.second)) continue;
    res(used_rmp.get(e.first.first), used_rmp.get(e.first.second)) = e.second;
  }
  return res;
}

void solve() {
  transfer_mat = build_transfer_mat();

  if (0) {
    list_paths(1, startp);
    for (auto &path : paths) {
      printf("\n==== new path\n");
      for (auto &e : path) {
        OPA_DISP0(state_rmp.rget(used_rmp.rget(e)).transition);
      }
    }
  }
  OPA_DISP0(transfer_mat);
  typedef Fraction<bignum> Q_e;

  FractionField<bignum> Q(&Ring_Z);
  Matrix<bignum> mat_q(&Ring_Z, transfer_mat.n, transfer_mat.m);
  REP (i, mat_q.n)
    REP (j, mat_q.m)
      mat_q(i, j) = bignum(transfer_mat(i, j));

  std::vector<u32> lst;
  std::vector<u32> lst2;
  bignum sum = 0;
  int md = 400;
  REP (i, md) {
    bignum p = mat_q.faste(i + 1)(startp, startp);
    sum += p * p * p;
    lst.emplace_back((p % (s32)mod).getu32());
    lst2.emplace_back(zn.import((p * p * p % mod).getu32()));
  }

  auto rel2 = findMinLinearRecursion_Slow(zn, lst2, 130);
  OPA_DISP0(rel2, rel2.size());
  return;
  // rel2 = findMinLinearRecursion_Massey(gfp, lst2, md);
  // OPA_DISP0(rel2, rel2.size());

  return;

  auto rel = findMinLinearRecursion_Slow(zn, lst, 10);
  OPA_DISP0(rel, rel.size());

  auto res = transfer_mat.faste(L - 1);
  OPA_DISP0(res);
  printf(">>> %d\n", res(startp, startp));
}
}

namespace n328 {
const int N = 2e3;

int dp[N][N];
std::pair<pii, pii> split[N][N];

int rec(int p, int k) {
  if (k == 0) return 0;
  if (k == 1) return 0;
  if (k == 2) return p + 1;
  int &r = dp[p][k];
  if (r != -1) return r;
  utils::MinFinderPair<int, int> mf;
  FOR (j, 1, k - 1) {
    int cost = p + j + 1 + std::max(rec(p, j), rec(p + j + 1, k - 1 - j));

    mf.update(cost, j);
  }
  r = mf.get_cost();
  split[p][k].first = MP(p, mf.get());
  split[p][k].second = MP(p + mf.get() + 1, k - 1 - mf.get());

  return r;
}

void disp(int p, int k) {
  if (dp[p][k] == -1) return;
  printf("%d %d >> cost=%d, split=%d, costl=%d, costr=%d\n", p, k, dp[p][k],
         p + split[p][k].first.second + 1,
         rec(split[p][k].first.first, split[p][k].first.second),
         rec(split[p][k].second.first, split[p][k].second.second));
  disp(split[p][k].first.first, split[p][k].first.second);
  disp(split[p][k].second.first, split[p][k].second.second);
}

int c(int n) {
  std::queue<int> q;
  REP (i, n)
    q.push(i + 1);
  return 0;
}

void solve() {
  memset(dp, -1, sizeof(dp));
  int mx = 18;
  int c1 = rec(0, mx);
  disp(0, mx);
  printf(">> %d %d\n", c(mx), c1);
}
}

namespace n553 {
const int maxn = 11111;
const int n = 4;
const int k = 2;
const int mod = 1e9 + 7;

CombHelper<mod> helper(maxn);

void solve1() {
  GF_p gfp(mod);
  typedef Poly<u32> Poly_t;
  PolyRing<u32> pr;
  pr.init(&gfp);

  Poly_t modp = pr.xpw(k + 1);

  PR_ring<u32> ringp;
  ringp.init(&gfp, modp, 0);

  Poly_t p1 = pr.x() + pr.constant(1) + pr.x() * pr.x();
  p1 = ringp.import(p1);
  auto res = ringp.faste(p1, n);
  printf(">>> %d\n", res.get_safe(k));
}

class Solver {
public:
  utils::MemoizeHelperClass<int, Solver, int, int> ck_mem;
  utils::MemoizeHelperClass<int, Solver, int, int> final_ck_mem;
  utils::MemoizeHelperClass<int, Solver, int> call_mem;
  utils::MemoizeHelperClass<int, Solver, int> c1_mem;

#define s_call(...) CALL1(Solver, call, __VA_ARGS__)
#define s_ck(...) CALL1(Solver, ck, __VA_ARGS__)
#define s_c1(...) CALL1(Solver, c1, __VA_ARGS__)
#define s_final_ck(...) CALL1(Solver, final_ck, __VA_ARGS__)

  Solver() {
    ck_mem.init(this);
    final_ck_mem.init(this);
    call_mem.init(this);
    c1_mem.init(this);
  }

  int call_(int n) const {
    int pn = u32_faste(2, n, mod - 1) - 1;
    return u32_faste(2, pn, mod) - 1;
  }

  int c1_(int n) const {
    if (n == 1) return 1;
    s64 x = s_call(n) - s_call(n - 1);
    REP (i, n - 1) {
      x = (x -
           1ll * helper.cnk(n - 1, i) * s_c1(i + 1) % mod *
             (1 + s_call(n - 1 - i)) % mod) %
          mod;
    }
    return (mod + x) % mod;
  }

  int ck_(int n, int k) const {
    if (n < k) return 0;
    if (k == 1) return s_c1(n);
    s64 x = 0;
    REP (i, n - k + 1) {
      x = (x +
           1ull * helper.cnk(n - 1, i) * s_c1(i + 1) % mod *
             s_ck(n - i - 1, k - 1) % mod) %
          mod;
    }
    return x;
  }

  int final_ck_(int n, int k) const {
    if (n < k) return 0;
    s64 x = 0;
    FOR (i, k, n + 1) {
      x = (x + 1ull * s_ck(i, k) * helper.cnk(n, i) % mod) % mod;
    }
    return x;
  }
};

GF_p gfp(mod);
PolyRing<u32> pr(&gfp);
Solver solver;
typedef Poly<u32> P;

class BoundingPolyRing : public PolyRing<u32> {
public:
  void init(const Field<u32> *field, int cutpw) {
    PolyRing<u32>::init(field);
    m_cutpw = cutpw;
    m_planner.init(field, 2 * cutpw, false, false);
  }

  virtual Poly<u32> mul(const Poly<u32> &a, const Poly<u32> &b) const {
    std::vector<u32> res =
      m_planner.main_executor->multiply(a.to_vec(), b.to_vec());
    if (res.size() > m_cutpw) res.resize(m_cutpw);
    return this->import(res);
  }

private:
  PolyFFTPlanner<u32> m_planner;
  int m_cutpw;
};

int get2(int n, int k) {

  std::vector<u32> entry = { 0 };
  REP (i, n)
    entry.push_back(1ll * solver.s_c1(i + 1) * helper.ifact[i + 1] % mod);
  OPA_DISP0(entry);

  P res;

  if (0) {
    P p0 = pr.import(entry);
    res = pr.faste(p0, k);
    OPA_DISP0(res);
  }

  BoundingPolyRing bpr;
  bpr.init(&gfp, n + 1);
  P p0 = bpr.import(entry);
  res = bpr.faste(p0, k);
  OPA_DISP0(res);

  int tot = 0;
  FOR (i, k, n + 1) {
    int n1 = res.get_safe(i);
    int cur = 1ll * n1 * helper.cnk(n, i) % mod * helper.fact[i] % mod;
    tot = (cur + tot) % mod;
  }
  tot = 1ll * tot * helper.ifact[k] % mod;
  return tot;
}

void solve2() {
  OPA_DISP0(get2(2, 1));
  OPA_DISP0(get2(3, 1));
  OPA_DISP0(get2(4, 2));
  OPA_DISP0(get2(3, 3));
  OPA_DISP0(get2(5, 3));
  OPA_DISP0(get2(5, 5));
  OPA_DISP0(get2(10, 5));
  OPA_DISP0(get2(100, 10));
  OPA_DISP0(get2(10000, 10));
}

void solve() {
  // solve1();
  solve2();
  Solver solver;
  OPA_DISP0(solver.s_final_ck(4, 2));
  OPA_DISP0(solver.s_final_ck(2, 1));
  OPA_DISP0(solver.s_final_ck(3, 1));
  OPA_DISP0(solver.s_final_ck(3, 3));
  OPA_DISP0(solver.s_final_ck(5, 3));
  OPA_DISP0(solver.s_final_ck(5, 5));
  OPA_DISP0(solver.s_final_ck(10, 5));
  OPA_DISP0(solver.s_final_ck(100, 10));
  return;
  OPA_DISP0(solver.s_call(200));
  OPA_DISP0(solver.s_c1(100));
  OPA_DISP0(solver.s_ck(100, 10));
  OPA_DISP0(helper.cnk(100, 10));
  OPA_DISP0(solver.s_final_ck(10000, 10));
  OPA_DISP0(solver.s_call(3));
  // 360209555
  //  39123900237
  //  728209718
}
}

namespace n275 {

typedef int BaseType;

const int maxn = 22;
int N = 10;
u64 nstates = 0;
typedef std::vector<BaseType> partition_t;
typedef std::vector<partition_t> partitions_t;
const bool track_solutions = false;

utils::Remapper<partitions_t, std::map<partitions_t, int> > partitions_rmp;

utils::Remapper<std::deque<BaseType>, std::map<std::deque<BaseType>, int> >
  deq_u8_rmp;

struct StateKey {
  int partitions_id;
  int cl_prev_id;
  int cl_cur_id;
  s16 xsum = 0;    // current sum
  BaseType yp = 0; // processing y position
  BaseType n;      // number of remaining tiles
  BaseType xp;
  bool sym = false;
  OPA_DECL_LT_OPERATOR(StateKey, xsum, partitions_id, cl_prev_id, cl_cur_id);
  OPA_DECL_COUT_OPERATOR2(StateKey, a.xsum, (int)a.yp, (int)a.n, (int)a.xp,
                          a.sym, a.partitions_id, a.cl_prev_id, a.cl_cur_id);
};

typedef std::vector<pii> solution_t;

std::map<StateKey, u64> dp[2][maxn][maxn][maxn]; // sym, n, yp, xp
std::map<StateKey, std::vector<solution_t> > sols[2][maxn][maxn][maxn]; // sym,
                                                                        // n,
                                                                        // yp,
                                                                        // xp
#define get_dp_entry(tb, skey) tb[skey.sym][skey.n][skey.yp][skey.xp + maxn / 2]

struct State {
  StateKey key;
  partitions_t partitions;
  std::deque<BaseType> cl_prev;
  std::deque<BaseType> cl_cur;

  void pack() {
    key.cl_prev_id = deq_u8_rmp.get(cl_prev);
    key.cl_cur_id = deq_u8_rmp.get(cl_cur);
    key.partitions_id = partitions_rmp.get(partitions);
  }

  const StateKey &get_key() {
    pack();
    return key;
  }

  void unpack() {
    cl_prev = deq_u8_rmp.rget(key.cl_prev_id);
    cl_cur = deq_u8_rmp.rget(key.cl_cur_id);
    partitions = partitions_rmp.rget(key.partitions_id);
  }

  bool change_row(bool insert) {
    OPA_CHECK(cl_prev.size() == 0 || cl_prev.front() >= key.yp, *this);
    bool removing = cl_prev.size() > 0 && cl_prev.front() == key.yp;
    key.xsum += key.xp * insert;
    if (insert) --key.n;

    std::vector<std::vector<BaseType> > npartitions;

    std::vector<BaseType> with_new;
    const int below_idx = (cl_cur.size() > 0 && cl_cur.back() == key.yp - 1)
                            ? cl_prev.size() + cl_cur.size() - 1
                            : -1;
    if (removing) cl_prev.pop_front();
    if (insert) cl_cur.push_back(key.yp);
    const int new_idx = cl_cur.size() + cl_prev.size() - 1;

    for (auto &oldp : this->partitions) {
      std::vector<BaseType> np;
      bool has_removed = false;
      bool has_below = false;
      for (auto &x : oldp) {
        if (removing && x == 0)
          has_removed = true;
        else
          np.push_back(x - removing);

        if (insert && x == below_idx) has_below = true;
      }

      if (insert && (has_below || has_removed))
        with_new.insert(with_new.end(), ALL(np));
      else {
        if (np.size() == 0) return false;
        npartitions.push_back(np);
      }
    }

    if (insert) {
      with_new.push_back(new_idx);
      std::sort(ALL(with_new));
      npartitions.push_back(with_new);
    }
    std::sort(ALL(npartitions));
    this->partitions = npartitions;

    int cnt = 0;
    for (auto &x : partitions) cnt += x.size();
    OPA_CHECK0(cnt == cl_prev.size() + cl_cur.size());
    ++key.yp;
    return true;
  }

  bool change_col() {
    if (key.n == 0) return false;
    key.xp += 1;
    if (key.xp == 0 && key.sym) {
      if (N < 2 * (N - key.n) + 1)
        return false; // 1 because of the mandatory block on (0,0)
      key.n = N - 2 * (N - key.n);
      key.xsum = 0;
    }
    key.yp = 0;
    int decv = cl_prev.size();
    cl_prev = cl_cur;
    cl_cur.clear();
    std::vector<std::vector<BaseType> > npartitions;

    for (auto &oldp : this->partitions) {
      std::vector<BaseType> np;
      for (auto &x : oldp) {
        if (x - decv >= 0) np.push_back(x - decv);
      }
      if (np.size() == 0) return false;
      npartitions.push_back(np);
    }

    this->partitions = npartitions;
    return true;
  }
  OPA_DECL_COUT_OPERATOR2(State, a.key, a.cl_cur, a.cl_prev, a.partitions);
};

void check_key(const StateKey &skey) {

  OPA_CHECK(skey.n >= 0 && skey.n < maxn, int(skey.n));
  OPA_CHECK(skey.yp >= 0 && skey.yp < maxn, skey.yp);
  OPA_CHECK(skey.xp + maxn / 2 >= 0 && skey.xp + maxn / 2 < maxn, skey.xp);
}

std::pair<u64 &, bool> get_entry(const StateKey &s) {
  check_key(s);
  auto it = get_dp_entry(dp, s).emplace(s, 0);
  return MP(std::ref(it.first->second), it.second);
}

u64 rec(const StateKey &skey);

u64 compute(const State &state) {
  u64 res = 0;
  ++nstates;
  bool should_stop = false;
  if (state.key.xsum + state.key.n * state.key.xp > 0) return 0;

  if (state.key.n == 0) {
    bool ok = state.key.xsum == 0 && state.partitions.size() == 1;
    if (ok && track_solutions) {
      get_dp_entry(sols, state.key)[state.key] = { {} };
    }
    return ok;
  }
  int merge_count = 2 * state.partitions.size() - 1;
  if (state.cl_cur.size() > 0 && state.cl_cur.back() == state.key.yp - 1) {
    merge_count--;
    if (state.cl_prev.size() > 0 && state.cl_prev.front() == state.key.yp)
      --merge_count;
  }

  int transition_count = state.key.n - merge_count;
  int min_sum = state.key.xsum;
  min_sum +=
    transition_count * (transition_count + 1) + transition_count * state.key.xp;
  min_sum += merge_count * (state.key.xp + transition_count);
  if (min_sum < 0) return 0;
  if (transition_count < 0) return 0;

  MinFinder<int> min_req;
  int closest_cur = state.cl_cur.size() > 0 ? state.cl_cur.back() : 0;
  min_req.update(state.key.yp - closest_cur + 1);
  if (closest_cur == state.key.yp - 1) min_req.update(0);
  if (state.cl_prev.size() > 0) min_req.update(0);
  if (min_req.get() > state.key.n - 1) should_stop = true;
  if (state.key.yp > N) return 0;
  if (should_stop) return 0;

  int max_sum = state.key.xsum + (int)state.key.n * (state.key.n - 1) / 2 +
                (int)state.key.n * state.key.xp;
  if (max_sum < 0) return 0;
  std::vector<solution_t> cur_sols;

  REP (should_insert, 2) {
    if (should_insert == 0 && state.key.yp == 0 && state.key.xp == 0) continue;

    State nstate = state;
    if (!nstate.change_row(should_insert)) continue;
    u64 nx = rec(nstate.get_key());
    if (nx > 0 && track_solutions) {
      auto lst = get_dp_entry(sols, nstate.key)[nstate.key];
      for (auto &sol : lst) {
        cur_sols.push_back(sol);
        if (should_insert)
          cur_sols.back().emplace_back(state.key.xp, state.key.yp);
      }
    }

    res += nx;
    if (should_insert && nstate.change_col()) {
      nx = rec(nstate.get_key());
      if (nx && track_solutions) {
        auto lst = get_dp_entry(sols, nstate.key)[nstate.key];
        for (auto &sol : lst) {
          cur_sols.push_back(sol);
          if (should_insert)
            cur_sols.back().emplace_back(state.key.xp, state.key.yp);
        }
      }
      res += nx;
    }
  }
  if (track_solutions) {
    get_dp_entry(sols, state.key).emplace(state.key, cur_sols);
  }
  return res;
}

u64 rec(const StateKey &skey) {
  // recursive call preserving references due to the array parementers for the
  // map
  auto cur = get_entry(skey);
  if (cur.second) {
    State state;
    state.key = skey;
    state.unpack();
    cur.first = compute(state);
    // OPA_DISP0(state, cur.first);
  }
  return cur.first;
}

void display_sols(const std::vector<solution_t> &tb) {
  for (auto &sol : tb) {
    int mid = (N - 1) / 2;
    fflush(stdout);
    REPV (i, N) {
      REP (j, N) {
        bool has = false;
        for (auto &e : sol)
          if (e == pii(j - mid, i)) has = true;
        putchar(" *"[has]);
      }
      puts("");
    }
    puts("=======");
  }
}

u64 query(int n) {
  N = n;
  nstates = 0;
  u64 tot = 2; // vertical bar;
  FOR (i, 1, (n - 1) / 2 + 1) {
    State st;
    st.key.xp = -i;
    // st.cl_cur.push_back(0);
    st.key.xsum = 0;
    st.key.yp = 0;
    // st.partitions.push_back(std::vector<int>{ 0 });
    st.key.n = n;

    st.key.sym = false;

    u64 v1 = rec(st.get_key());
    puts("solution ====== ");
    if (track_solutions) {
      OPA_DISP0("Whaterversym solutions", i);
      display_sols(get_dp_entry(sols, st.key)[st.key]);
    }
    st.key.sym = true;
    u64 v2 = rec(st.get_key()); // now also double count symmetric
    if (track_solutions) {
      OPA_DISP0("Symmetric solutions", i);
      display_sols(get_dp_entry(sols, st.key)[st.key]);
    }
    OPA_DISP0(i, v1, v2, nstates);
    tot += v1 + v2;
  }
  tot /= 2;
  return tot;
}

void solve() {

  if (0) {
    //    N = 6;
    //    State st;
    //    st.xp = 1;
    //    st.cl_prev.push_back(0);
    //    st.cl_prev.push_back(1);
    //    st.xsum = -2;
    //    st.yp = 0;
    //    //st.partitions.push_back(std::vector<u8>{ 0, 1 });
    //    st.n = 2;
    //    st.sym = false;
    //
    //    u64 v1 = rec(st);
    //    return;
  }
  OPA_DISP0(query(18));
  OPA_DISP0(partitions_rmp.size(), deq_u8_rmp.size());
}
/*
solution ======
i=1,v1=11c87a,v2=4c7,nstates=c4d2a6,
  solution ======
  i=2,v1=a3c152,v2=143d,nstates=2b68d48,
  solution ======
  i=3,v1=b47da1,v2=1597,nstates=4b46349,
  solution ======
  i=4,v1=4e33ef,v2=d5c,nstates=5d334e5,
  solution ======
  i=5,v1=108385,v2=553,nstates=6411a48,
  solution ======
  i=6,v1=1a075,v2=149,nstates=65c9d10,
  solution ======
  i=7,v1=1010,v2=29,nstates=6602d85,
  solution ======
  i=8,v1=22,v2=2,nstates=6604062,
  query(18)=e55924,
*/
}

namespace n262 {

int LOW = 0;
int HIGH = 1600;
const Range1D window{ 0, 1600 };
const double eps = 1e-9;
const double c1 = 0.000001;
const double c2 = 0.0015;
const double c3 = 0.7;
const Pos2 startp = { 200, 200 };
const Pos2 endp = { 1400, 1400 };

const double c4 = 5000;
const double c5 = 0.005;
const double c6 = 12.5;
const int vd[] = { 1, 0, -1, 0, 1 };

#define MAP2D_def(name, xhigh)                                                 \
  int map_##name(const int x, const int y) { return ((x) + (y) * (xhigh)); }

#define IMAP2D_def(name, xhigh)                                                \
  std::pair<int, int> imap_##name(int v) {                                     \
    return { (v) % (xhigh), (v) / (xhigh) };                                   \
  }
MAP2D_def(1, HIGH);
IMAP2D_def(1, HIGH);

inline double g(const Pos2 &pos) {
  return c1 * (pos.x * pos.x + pos.y * pos.y) - c2 * (pos.x + pos.y) + c3;
}

inline double ff(const Pos2 &pos) { return std::exp(-std::abs(g(pos))); }

inline double f(const Pos2 &pos) {
  return (c4 - c5 * (pos.x * pos.x + pos.y * pos.y + pos.x * pos.y) +
          c6 * (pos.x + pos.y)) *
         ff(pos);
}
inline double f_xy(double x, double y) { return f(Pos2(x, y)); }

Pos2 gradient(const Pos2 &pos) {
  double tg = g(pos);
  if (std::abs(tg) < eps) {
    OPA_CHECK(false, pos);
    return Pos2(0);
  }
  Pos2 dg = pos * c1 * 2 - Pos2(c2);
  if (tg < 0) dg = -dg;

  double t1 = ff(pos);
  double t2 = f(pos);
  Pos2 dd = Pos2(t2) * dg;
  Pos2 dd2 = Pos2(t1 + c6) + (pos * 2 + pos.yx()) * c5;

  return dd + dd2;
}

struct PointData {
  double v;
  Pos2 p;
  Pos2 dp;
  bool ok;

  void setup(const Pos2 &p) {
    this->p = p;
    v = f(p);
    dp = gradient(p);
  }
};

bool checkit(const double v) {
  int np = 1600;
  auto range = window.linspace(np).tb();
  int n_base = HIGH * HIGH;
  auto base_uj = UnionJoin(n_base);
  std::vector<PointData> pts(n_base);

  utils::MinFinderPair<double, int> start_finder;
  utils::MinFinderPair<double, int> end_finder;
  REP (xp, np)
    REP (yp, np) {
      const double x = range[xp];
      const double y = range[yp];
      int id = map_1(xp, yp);
      Pos2 p(x, y);
      pts[id].setup(p);
      start_finder.update(glm::length(p - startp), id);
      end_finder.update(glm::length(p - endp), id);
      pts[id].ok = pts[id].v <= v;
    }

  REP (xp, np)
    REP (yp, np) {
      int nx, ny;
      int id = map_1(xp, yp);
      const PointData &cur = pts[id];
      if (!cur.ok) continue;
      REP (k, 4) {
        nx = xp + vd[k];
        ny = yp + vd[k + 1];
        if (nx < 0 || ny < 0 || nx >= np || ny >= np) continue;
        int nid = map_1(nx, ny);
        const PointData &next = pts[nid];
        if (!next.ok) continue;
        Pos2 dir = next.p - cur.p;
        ;
        int b1 = std::signbit(glm::dot(dir, cur.dp));
        int b2 = std::signbit(glm::dot(dir, next.dp));
        if (b1 != b2) continue;
        base_uj.merge(id, nid);
      }
    }

  int startid = start_finder.get();
  int endid = end_finder.get();
  if (base_uj.same(startid, endid)) return true;
  return false;
}

std::pair<double, double>
do_ternary_search(const Range1D &range,
                  const std::function<double(double)> &func, int niter) {
  double T = range.low;
  double H = range.high;
  REP (i, niter) {
    double L = (2 * T + H) / 3;
    double R = (T + 2 * H) / 3;
    double vl = func(L);
    double vr = func(R);
    if (vl < vr)
      T = L;
    else
      H = R;
  }
  double ans = (T + H) / 2;
  return { ans, func(ans) };
}

Pos2 do_newton(const Pos2 &startp, double level, double stop_cond = 1e-6,
               int nsteps = -1) {
  Pos2 cur = startp;
  Pos2 other = startp;
  double vcur = f(cur) - level;

  while (true) {
    double v = f(other) - level;
    if (std::signbit(vcur) != std::signbit(v)) break;
    Pos2 grad = gradient(other);
    Pos2 dir = glm::normalize(grad);
    double coeff = v / glm::length(grad);
    const double minv = 1e-3;
    if (std::abs(coeff) < minv) coeff = OPA_SIGN(coeff) * minv;
    Pos2 next = other - dir * coeff;
    OPA_DISP0(v, vcur, cur, other, next, coeff);
    usleep(1e3);
    other = next;
  }

  if (f(cur) < f(other)) std::swap(cur, other);

  REP (step, 30) {
    Pos2 mid = (cur + other) / 2;
    if (f(mid) > level)
      cur = mid;
    else
      other = mid;
  }
  return cur;
}

Point2Vec level_to_polyline(const Pos2 &pt, double precision) {
  double level = f(pt);
  Point2Vec res;
  Pos2 dir = vec2_orth(gradient(pt));
  const Pos2 start_dir = dir;
  double stop_cond = 1e-6;
  Pos2 cur = pt;
  while (true) {
    res.push_back(cur);
    Pos2 dir = vec2_orth(gradient(cur));
    Pos2 next = cur + glm::normalize(dir) * precision;
    OPA_DISP0(cur, res.size());
    next = do_newton(next, level);
    if (glm::length(cur - pt) < precision * 1.01 &&
        std::signbit(glm::dot(cur - pt, dir)) !=
          std::signbit(glm::dot(next - pt, dir)))
      break;
    cur = next;
    OPA_CHECK0(res.size() < 1e6);
  }

  return res;
}

double compute_path(double level) {
  Point2Vec tb;
  double res = -1;
  Pos2 startp = do_newton(Pos2(), level);
  OPA_DISP("start point ", startp);
  Point2Vec polyline = level_to_polyline(startp, 0.1);
  OPA_DISP0(startp, polyline.size());
  return res;
}

void solve() {
  int np = 1600;
  auto range = window.linspace(np).tb();
  utils::MinFinder<double> minf;
  utils::MaxFinder<double> maxf;
  for (const double x : range)
    for (const double y : range) {
      double v = f_xy(x, y);
      minf.update(v);
      maxf.update(v);
    }

  double vlow = minf.get();
  double vhigh = maxf.get();
  OPA_DISP0(vlow, vhigh);
  OPA_DISP0(
    do_ternary_search(window, std::bind(f_xy, LOW, std::placeholders::_1), 30));
  OPA_DISP0(
    do_ternary_search(window, std::bind(f_xy, std::placeholders::_1, LOW), 30));
  OPA_DISP0(do_ternary_search(
    window, std::bind(f_xy, HIGH, std::placeholders::_1), 30));
  OPA_DISP0(do_ternary_search(
    window, std::bind(f_xy, std::placeholders::_1, HIGH), 30));

  int nstep = 30;
  REP (step, nstep) {
    double v = (vlow + vhigh) / 2;
    if (checkit(v))
      vhigh = v;
    else
      vlow = v;
  }
  OPA_DISP0("cAN  >> ", vhigh);
  printf("%.10lf\n", vhigh);
  return;
  double res = compute_path(vhigh);
  OPA_DISP0(res, vhigh);
}
}

namespace n416 {
constexpr int maxd = 3;
constexpr int maxskip = 1;
constexpr int m = 10;
constexpr int M = m * 2;
constexpr int mod = 1e9;
UPTR(ZnForDiv) zndiv;
UPTR(Zn) zn;
CombHelperForMod math_helper;

void init() {
  zndiv.reset(new ZnForDiv(mod));
  zn.reset(new Zn(mod));

  math_helper.init(zndiv.get(), M);
}

struct State {
  std::array<int, maxd> sx = { 0 };
  int skipped = 0;
  OPA_DECL_LT_OPERATOR(State, sx, skipped);
  OPA_DECL_COUT_OPERATOR2(State, a.sx, a.skipped);
  OPA_DECL_EQ_OPERATOR(State, sx, skipped);
};

struct State2 {
  std::vector<int> split;
  int tot;
  int ways = 1;
};

std::vector<State2> list_split(int tot, int split_repartition) {

  typedef OR::Search_bfs<State2> Search_t;

  Search_t search;
  Search_t::SearchParams params;
  bool found = true;
  std::vector<State2> res;
  params.func = [&](OR::Search<State2> *self, const State2 &state) {
    if (state.split.size() == split_repartition) {
      if (state.tot == 0) res.push_back(state);
      return;
    }
    OPA_CHECK0(state.tot >= 0);

    REP (i, state.tot + 1) {
      State2 ns = state;
      ns.ways = zn->mul(ns.ways, math_helper.cnk(ns.tot, i));
      ns.split.push_back(i);
      ns.tot -= i;
      self->add(ns);
    }
  };

  OPA_CHECK0(found == true);
  State2 s0;
  s0.tot = tot;
  search.init(params);
  search.add(s0);
  search.start();
  return res;
}

std::vector<std::pair<State, int> > explore_state(const State &state) {
  State ns;
  ns.skipped = state.skipped;
  REP (i, maxd - 1)
    ns.sx[i] = state.sx[i + 1];

  if (state.sx[0] == 0) {
    ++ns.skipped;
    if (ns.skipped > maxskip) return {};
    return { { ns, 1 } };
  }

  std::vector<std::pair<State, int> > res;
  auto splits = list_split(state.sx[0], maxd);
  for (auto &e : splits) {
    State ns2 = ns;
    REP (i, e.split.size())
      ns2.sx[i] += e.split[i];
    if (ns2.sx[0] == 0 && ns2.skipped == maxskip) continue;
    res.emplace_back(ns2, e.ways);
  }
  return res;
}

template <class T> class TransitionMatrixBuilder {
public:
  void build(const T &state,
             const std::function<std::vector<std::pair<T, int> >(const T &)>
               &next_func) {
    this->next_func = next_func;
    rec(state);
  }

  void rec(const T &state) {
    int rid = rmp.get(state);
    if (vis.count(rid)) return;
    vis.insert(rid);
    std::vector<std::pair<T, int> > next = this->next_func(state);
    auto &v = transitions[rid];
    for (auto &e : next) {
      v.emplace_back(rmp.get(e.first), e.second);
    }
    for (auto &e : next) rec(e.first);
  }

  Matrix<u32> get_mat(const Ring<u32> *ring) {
    Matrix<u32> res;
    res.initialize(ring, rmp.size(), rmp.size());
    for (auto &e : transitions) {
      for (auto &x : e.second) {
        res(x.first, e.first) = x.second;
      }
    }
    return res;
  }

  std::function<std::vector<std::pair<T, int> >(const T &)> next_func;
  utils::Remapper<T, std::map<T, int> > rmp;
  std::set<int> vis;
  std::map<int, std::vector<pii> > transitions;
};

void solve() {
  init();
  TransitionMatrixBuilder<State> builder;
  State s0;
  s0.sx[0] = M;
  puts("Build states");
  builder.build(s0, explore_state);
  puts("get mat");
  Matrix<u32> mat = builder.get_mat(zn.get());
  s64 n = 1e12;
  puts("faste");
  OPA_DISP0(mat.n, n);
  Matrix<u32> res = mat.faste(n - 1);
  int id0 = builder.rmp.get(s0);
  OPA_DISP0(mat);
  puts("");
  OPA_DISP0(res);

  int sum = 0;
  REP (i, maxskip + 1) {
    State s1;
    s1.sx[0] = M;
    s1.skipped = i;
    int id1 = builder.rmp.get(s1);
    int curv = res(id1, id0);
    OPA_DISP0(s1, curv);
    sum = zn->add(sum, curv);
  }
  for (auto &x : builder.rmp.mp()) OPA_DISP0(x);

  OPA_DISP("Running with ", n, m);
  OPA_DISP0(sum);
}
}

namespace n488 {

const int U = 3;
class Solver {
public:
  typedef std::vector<int> State;
  utils::MemoizeHelperClass<bool, Solver, State> query_mem;

  void init() { query_mem.init(this); }

  bool is_valid(const State &st) const {
    REP (j, U - 1)
      if (st[j] == st[j + 1]) return false;
    return true;
  }

  bool normalize(State &st) const {
    std::sort(ALL(st));
    return is_valid(st);
  }

  bool query_(const State &st) const {
    if (st.back() == U - 1) return false;
    REP (i, U) {
      REP (j, st[i]) {
        State ns = st;
        ns[i] = j;
        if (normalize(ns)) {
          if (!get_query(ns)) {
            return true;
          }
        }
      }
    }
    return false;
  }

  bool get_query(const State &st) const { return CALL1(Solver, query, st); }

  void build_graph(const State &s) {
    int a = rmp.get(s);
    if (vis.count(a)) return;
    vis.insert(a);
    REP (i, U) {
      REP (j, s[i]) {
        State ns = s;
        ns[i] = j;
        if (normalize(ns)) {
          int b = rmp.get(ns);
          graph.adde(a, b);
          build_graph(ns);
        }
      }
    }
  }

  FastGraph graph =
    FastGraph(0, algo::Mode::DYNAMIC_SIZE | algo::Mode::DIGRAPH);
  utils::Remapper<State, std::map<State, int> > rmp;
  std::set<int> vis;
};

const int mod = 1e9 + 7;
s64 get_at_max(s64 n) {
  s64 res = 0;
  res += n * n;
  res += (n - 1) * (n - 2) / 2;
  res %= mod;
  return res;
}

s64 get(s64 n) {
  FOR (i, 3, n)
    OPA_DISP0(i, get_at_max(i));
  n -= 1;
  n %= mod;
  s64 v = n * (n + 1) / 2 % mod;
  v -= 2 * n;
  v %= mod;
  v = (v + mod) % mod;
  return v;
}

void solve() {
  s64 n = 8;
  OPA_DISP0(get(n));

  Solver solver;
  solver.init();

  int mv = n - 1;
  Solver::State s0;
  REPV (j, U)
    s0.push_back(mv - j);
  solver.build_graph(s0);
  DigraphComputation<int> grundy(solver.graph, grundy_comp);
  DigraphComputation<int> dist(solver.graph, dist_comp);
  int count = 0;
  for (auto &x : solver.rmp.remap()) {
    if (x.first[0] == 0) continue;
    int y = grundy.get(x.second);
    int d = dist.get(x.second);
    if (0) {
      if (d <= 2) {
        OPA_DISP0(x.first, y, d);
      }
    } else {
      if (y == 0) {
        ++count;
        OPA_DISP0(x.first, y, d);
      }
    }
  }
  OPA_DISP0(count);
  return;

  REP (i, 20)
    REP (j, i)
      REP (k, j) {
        Solver::State is;
        is.resize(3);
        is[0] = k;
        is[1] = j;
        is[2] = i;
        bool win = solver.get_query(is);
        if (!win) OPA_DISP0(i, j, k, k ^ (j - 1) ^ (i - 2));
      }
}
}

namespace n559 {
constexpr int mod = 1000000123;
constexpr int maxn = 55555;

class Solver {
public:
  CombHelper<mod> comb;
  int r, n;

  Solver(int r, int n) : r(r), n(n) {
    comb.init(n+1);
    for (auto &v : comb.fact) v = u32_faste(v, r, mod);
    for (auto &v : comb.ifact) v = u32_faste(v, r, mod);
  }

  s64 get_k(int k) {
    std::vector<int> tb;
    tb.push_back(comb.fact[n]);

    for (int i = 0; i * k < n; ++i) {
      int curw = std::min<int>(n - i * k, k);
      int last = i * k + curw;
      s64 curv = 1ull * tb.back() * comb.ifact[curw] %
                 mod; // only one order for ascent segment
      REPV (j, i) {
        s64 val = 1ull * tb[j] * comb.ifact[(i - j) * k + curw] %
                  mod; // order from j * k to last
        if (i - j & 1) val = (mod - val);
        curv += val;
      }
      curv %= mod;
      tb.push_back(curv);
    }

    return tb.back();
  }

  s64 get() {
    s64 res = 0;
    FOR (i, 1, n + 1) { res += get_k(i); }
    res %= mod;
    return res;
  }
};

void solve() {
  OPA_DISP0(Solver(2, 3).get_k(1));
  OPA_DISP0(Solver(4, 6).get_k(2));
  OPA_DISP0(Solver(5, 30).get_k(7));
  OPA_DISP0(Solver(5, 5).get());
  OPA_DISP0(Solver(50, 50).get());
  OPA_DISP0(Solver(50000, 50000).get());
}
}

int main(int argc, char **argv) {
  opa::init::opa_init(argc, argv);
  typedef void (*action_func)();
  std::unordered_map<string, action_func> actions;

  actions["p7"] = p7;
  actions["p10"] = p10;
  actions["p12"] = p12;
  actions["p14"] = p14;
  actions["p537"] = p537;
  actions["p233"] = p233;
  actions["p201"] = p201;
  actions["p269"] = n269::p269;
  actions["p411"] = n411::solve;
  actions["p575"] = n575::solve;
  actions["p289"] = n289::solve;
  actions["p490"] = n490::solve;
  actions["p328"] = n328::solve;
  actions["p553"] = n553::solve;
  actions["p262"] = n262::solve;
  actions["p275"] = n275::solve;
  actions["p416"] = n416::solve;
  actions["p488"] = n488::solve;
  actions["p559"] = n559::solve;

  string action = FLAGS_action;
  OPA_CHECK0(!action.empty());
  OPA_CHECK0(actions.count(action));
  actions[action]();
  return 0;
}
