#include "opa/math/common/Utils.h"
#include <algorithm>

#include <glm/geometric.hpp>
#include <iterator>
#include <random>
#include <range/v3/view/enumerate.hpp>
#include <range/v3/view/transform.hpp>
#include <unordered_map>
#include <vector>

#define DEBUG
#define TEST_RAND 1
#define TEST_CHECK 1

#include "contest_base.h"
#include <opa/utils/hash.h>

using namespace opa::math::common;
using namespace opa;

const int maxd = 20;
struct State {
  int run_digits = 0;
  int digits_sum = 0;
  int last_loss_dist = 0;
  OPA_DECL_EQ_OPERATOR(State, run_digits, digits_sum, last_loss_dist);
};

template <> struct std::hash<State> {
  size_t operator()(const State &x) const {
    return (s64)x.run_digits + (maxd * 10) * x.digits_sum +
           (maxd * maxd * 10ll * 10ll) * x.last_loss_dist;
  }
};

namespace prob {

std::mt19937 rng(0);
ReaderHelper g_reader;
constexpr int mod = 1e9 + 7;
typedef GF_pMod<mod> GFP;

typedef Fraction<bignum> F;

typedef u32 T;
typedef Poly<T> PT;

struct Problem {
  s64 n;

  void read() { g_reader.readline() >> n; }
};

struct Precomp {

  std::unordered_map<State, int> dp;
  int query(const State &s) {
    if (s.run_digits == 0) return s.digits_sum >= s.last_loss_dist + 10 ? s.last_loss_dist + 10 : 0;
    if (dp.count(s)) return dp[s];
    int last = s.last_loss_dist;
    REP (j, 10)
      last = query(State{
        .run_digits = s.run_digits - 1, .digits_sum = s.digits_sum + j, .last_loss_dist = last });

    return dp[s] = last;
  }
};
Precomp g_precomp;

struct SolverContext {
  Problem prob;
  typedef bool ResT;

  ResT solve() {
    if (prob.n % 10 != 0) return true;
    s64 x = prob.n / 10;
    vi tb;
    while (x) tb.pb(x % 10), x /= 10;
    int s = tb.back();
    int last = 0;
    REPV (i, tb.size() - 1) {
      REP (j, tb[i]) {
        last =
          g_precomp.query(State{ .run_digits = i, .digits_sum = s + j, .last_loss_dist = last });
      }
      s += tb[i];
    }
    return g_precomp.query(State{ .run_digits = 0, .digits_sum = s, .last_loss_dist = last }) != 0;
  }

  ResT solve_dumb() {
    std::vector<bool> tb;
    tb.resize(prob.n + 1, false);
    tb[0] = false;

    FOR (i, 1, prob.n + 1) {
      int cnt = 0;
      int x = i;
      while (x) cnt += x % 10, x /= 10;
      FOR (j, i - cnt, i)
        if (!tb[j]) {
          tb[i] = true;
          break;
        }
    }
    return tb[prob.n];
  }

  void read() {
    if (TEST_RAND) {
      prob.n = (rng() % 60000+1)  * 10;
    } else {
      prob.read();
    }
  }
};
} // namespace prob

int main(int argc, char **argv) {
  opa::init::opa_init(argc, argv);
  srand(0);
  int tn;

  if (TEST_RAND)
    tn = 10000;
  else {
    freopen("./prog_contest/misc/samples/ucup2_6_a.in", "r", stdin);
    scanf("%d\n", &tn);
    // tn = 1;
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
        OPA_DISP0(r1, r2, sc.prob.n);
        puts("");
        assert(r1 == r2);
      }
    } else {

      auto res = sc.solve();
      std::cout << (res ? "Algosia" : "Bajtek") << std::endl;
      // OPA_DISP0(res, sc.solve_dumb());
    }
  }

  return 0;
}
