#include "contest_base.h"
#include <opa/math/common/crt_fft.h>
#include <opa/utils/hash.h>

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

struct Problem {
  pii start, end;
  int t;
  void read() { g_reader.readline() >> t >> start.ST >> start.ND >> end.ST >> end.ND; }
};

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

int dv[] = { -1, 0, 1, 0, -1 };
std::vector<pii> neighbors(const pii &p) {
  std::vector<pii> res;
  REP (k, 4) res.pb(p + MP(dv[k], dv[k + 1]));
  return res;
}

struct Solver {
  Problem prob;
  int solve() {

    pii diff = prob.end - prob.start;
    int need = std::abs(diff.ST) + std::abs(diff.ND);
    if (need > prob.t || (prob.t - need) % 2 != 0) return 0;
  }
};

struct SolverDumb {
  Problem prob;

  int solve() {

    std::unordered_map<pii, int> q, nq;
    REP (i, prob.t) {
      nq.clear();
      for (auto e : q) {
        if (e.first == prob.end) continue;
        for (auto np : neighbors(e.first)) {
          if (std::min(np.first, np.second) < 0) continue;
          nq[np] = (nq[np] + e.second) % mod;
        }
      }
    }
    return nq[prob.end];
  }
};

int main(int argc, char **argv) {
  opa::init::opa_init(argc, argv);

  return 0;
}
