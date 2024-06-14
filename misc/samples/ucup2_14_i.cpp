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

constexpr int M = 6;
constexpr int D = 10;
typedef std::array<int, M> cube_t;
struct Problem {
  int n, k;
  std::vector<cube_t> lst;

  void read() {
    g_reader.readline() >> n >> k;
    g_reader.readline();
    lst = g_reader.read_list<cube_t>(n, ReaderHelper::kNewLine);
  }
};

struct SolverContext {
  Problem prob;
  typedef std::vector<std::vector<int> > ResT;
  typedef std::array<int, D> CountT;
  std::vector<int> mp;
  std::vector<int> f;
  std::vector<std::vector<int> > states;

  void generate(CountT &cur, int pos, int rem, bool flag, std::vector<CountT> &res) {
    if (!flag && *std::min_element(ALL(states[pos])) >= rem) return;

    if (pos == D - 1) {
      cur[pos] = rem;
      res.pb(cur);
      return;
    }
    bool nflag = flag;
    REP (take, rem + 1) {
      cur[pos] = take;
      if (!flag) {
        REP (i, 1 << (D - pos - 1))
          states[pos + 1][i] = std::min(states[pos][i << 1], states[pos][(i << 1) | 1] - take);
        nflag = *std::min_element(ALL(states[pos + 1])) < 0;
        states[pos+1][0] = 1e9;
      }
      generate(cur, pos + 1, rem - take, nflag, res);
    }
  }

  ResT solve() {
    ResT res;
    mp.clear();
    for (auto x : prob.lst) {
      int v = 0;

      for (auto y : x) v |= 1 << y;
      mp.pb(v);
    }

    std::unordered_map<int, std::vector<int> > rmp;

    f.resize(1 << D);
    FOR (i, 1, 1 << D) {
      int cnt = 0;
      REP (j, prob.n) cnt += bool(mp[j] & i);
      f[i] = cnt;
      rmp[cnt].pb(i);
    }
    states.resize(D);
    f[0] = 1e9;
    REP (i, D) states[i].resize(1 << (D - i));
    REP (i, 1 << D) states[0][i] = f[i];
    int mv = *min_element(ALL(f));

    std::vector<int> current;
    for (int v = mv; res.size() < prob.k; ++v) {

      int need = prob.k - res.size();
      if (res.size() == prob.k) break;
      std::vector<CountT> tmp;
      CountT ct;
      generate(ct, 0, v, false, tmp);

      ResT current;
      {
        // tmp to current
        for (auto sel : tmp) {
          std::vector<std::vector<std::vector<int> > > cnks(D);
          int rem = v;
          REP (i, D) {
            cnks[i] = combinations2<int>(STD_RANGE(0, rem) | STD_VECT(int), sel[i]);
            rem -= sel[i];
          }

          for (auto e : product(cnks)) {
            if (e[0].size() > 0 && e[0][0] == 0) continue;
            vi pos = STD_RANGE(0, v) | STD_VECT(int);
            vi cur(v);
            REP (i, D) {
              vi npos;
              int xp = 0;
              for (auto x : pos) {
                if (xp < e[i].size() && pos[e[i][xp]] == x) {
                  cur[x] = i;
                  ++xp;
                } else
                  npos.pb(x);
              }
              std::swap(pos, npos);
            }

            current.pb(cur);
          }
        }
      }

      std::sort(ALL(current));
      res.insert(res.end(), ALL(current));
    }
    res.resize(prob.k);
    return res;
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
    freopen("./prog_contest/misc/samples/ucup2_14_i.in", "r", stdin);
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
      for (auto x : res) {
        auto tmp = x | STD_TSFX(char(x + '0')) | STD_VEC;
        std::string s{ ALL(tmp) };

        std::cout << s << ' ';
      }
      std::cout << std::endl;
      // OPA_DISP0(res, sc.solve_dumb());
    }
  }

  return 0;
}
