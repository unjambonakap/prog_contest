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

#include "contest_base.h"
#include <opa/algo/graph.h>
#include <opa/utils/hash.h>


using namespace opa::math::common;
using namespace opa::algo;

std::mt19937 rng(0);
ReaderHelper g_reader;

constexpr int mod = 998244353;
typedef GF_pMod<998244353> GFP;

struct Problem {
  int K;
  std::vector<std::string> data;
  int xn, yn;
  std::vector<std::vector<bool> > map;
  pii p0;

  void read() {
    g_reader.readline() >> K;
    while (true) {
      data.emplace_back();
      g_reader.readline() >> data.back();
      if (data.back().size() == 0) {
        data.pop_back();
        break;
      }
    }

    xn = data.size();
    yn = data[0].size();
    map.resize(xn, std::vector<bool>(yn, false));
    REP (i, xn)
      REP (j, yn) {
        map[i][j] = data[i][j] == '#';
        if (data[i][j] == 'S') p0 = MP(i, j);
      }
  }
};

struct SolverContext {
  Problem prob;
  typedef s64 ResT;

  void read() {
    prob.read();
    if (TEST_RAND) {

    } else {
    }
  }
  int toid(int x, int y) const { return x * prob.yn + y; }

  ResT solve() {
    FastGraph fg(prob.xn * prob.yn, Mode::NONE);
    const int vx[] = { 0, 1, 0 };
    REP (i, prob.xn)
      REP (j, prob.yn)
        if (!prob.map[i][j]) {
          REP (k, 2) {
            int nx = i + vx[k];
            int ny = j + vx[k + 1];
            if (std::min(nx, ny) < 0 || nx >= prob.xn || ny >= prob.yn) continue;
            if (!prob.map[nx][ny]) fg.adde(toid(i, j), toid(nx, ny));
          }
        }

    auto do_step = [&](const std::set<int> &s) {
      std::set<int> res;
      for (auto x : s) {
        auto nh = fg.get_neighbours(x);
        res.insert(ALL(nh));
      }
      return res;
    };

    std::set<int> cur = { toid(prob.p0.ST, prob.p0.ND) };
    std::set<std::set<int> > seen;
    int cnt = 0;
    while (true) {
      if (seen.count(cur)) break;
      seen.insert(cur);
      ++cnt;
      cur = do_step(cur);
    }
    OPA_DISP0(cnt);

    return {};
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
      std::cout << res << std::endl;
      // std::cout << std::dec;
      // for (auto x : res) std::cout << x << ' ';
      // std::cout << std::endl;
      //  OPA_DISP0(res, sc.solve_dumb());
    }
  }

  return 0;
}
