#include "opa/algo/base.h"
#include <algorithm>
#include <opa/algo/graph.h>
#include <opa/math/game/base.h>
#include <opa/math/game/conf.h>

#include <glm/geometric.hpp>
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
namespace std {
std::istream &operator>>(std::istream &is, opa::Pos &p) {
  is >> p.x >> p.y >> p.z;
  return is;
}
} // namespace std

namespace prob {

Pos to_pos(const std::vector<double> &vec) {
  OPA_CHECK0(vec.size() == 3);
  return { vec[0], vec[1], vec[2] };
}

std::vector<double> to_vec(const opa::Pos &vec) { return { vec[0], vec[1], vec[2] }; }

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

struct Problem {
  double R;
  int n;
  std::vector<opa::Pos> pl;

  void read() {
    g_reader.readline() >> n >> R;
    g_reader.readline();
    pl = g_reader.read_list<opa::Pos>(n, ReaderHelper::kNewLine);
  }
};

struct SolverContext {
  Problem prob;
  typedef s64 ResT;
  RealDouble field{ 1e-7 };
  struct Point {
    opa::Pos pos;
    Pos dir_front;
    Pos dir_right;
    Pos dir_up;
    double cos_angle;
    Pos c0;
    double nr;
    OPA_DECL_COUT_OPERATOR2(Point, a.pos, a.dir_front, a.cos_angle);
  };
  struct IntersectionPoint {
    Pos pt;
    int id;
    vi srcs;
    std::array<double, 2> angs;
    OPA_DECL_COUT_OPERATOR2(IntersectionPoint, a.pt, a.id, a.srcs, a.angs);
  };
  std::vector<Point> data;

  Point make_point(opa::Pos x) {
    auto front = -glm::normalize(x);
    auto vr = math::game::vec_ortho_rand(front);

    x = x / prob.R;
    double cos_angle = std::cos(std::asin(1 / std::sqrt(glm::dot(x, x))));
    auto c0 = front * cos_angle;
    double nr = std::sqrt(1 - cos_angle * cos_angle);
    return Point{
      .pos = x,
      .dir_front = front,
      .dir_right = vr,
      .dir_up = glm::cross(vr, front),
      .cos_angle = cos_angle,
      .c0 = c0,
      .nr = nr,
    };
  };

  bool is_vis(int pt, Pos p) const {
    // p is on circle
    return std::acos(glm::dot(p, data[pt].dir_front)) > std::acos(data[pt].cos_angle) - 1e-5;
  }

  double proj_ang(const Point &x, const Pos &p) const {
    Pos dx = (p - x.c0) / x.nr;
    double ang = std::acos(glm::dot(dx, x.dir_right));
    if (glm::dot(dx, x.dir_up) < 0) ang = -ang;
    return ang;
  }

  Pos iproj(const Point &x, const double &p) const {
    return x.c0 + (x.dir_right * std::cos(p) + x.dir_up * std::sin(p)) * x.nr;
  }

  std::vector<Pos> get_intersections(const Point &a, const Point &b) {

    /*
      x.x = 1
      x.ti = fi
      */

    Matrix<double> mat;
    mat.initialize(&field, 2, 3);
    mat.set_row(0, to_vec(a.dir_front));
    mat.set_row(1, to_vec(b.dir_front));
    auto res = mat.solve_eq();
    if (res.KernelBasis.n != 1) return {};
    auto dv = to_pos(res.KernelBasis.get_row(0).tovec());
    auto v0 = to_pos(
      (res.ImageBasis.transpose() * (res.Inv * mat.fromvec({ a.cos_angle, b.cos_angle }))).tovec());

    auto sol = solve_quadratic(glm::dot(dv, dv), 2 * glm::dot(v0, dv), glm::dot(v0, v0) - 1, kEps);
    if (sol.size() != 2) return {}; // angle stability
    auto s0 = v0 + dv * sol[0];
    auto s1 = v0 + dv * sol[1];

    OPA_DISP0(v0, dv, sol);
    OPA_DISP0(std::abs(glm::dot(s0, s0) - 1));
    OPA_DISP0(std::abs(glm::dot(s1, s1) - 1));
    OPA_CHECK0(std::abs(glm::dot(s0, s0) - 1) < 1e-5);
    OPA_CHECK0(std::abs(glm::dot(s1, s1) - 1) < 1e-5);
    OPA_DISP0(mat);
    OPA_DISP0(res.KernelBasis, res.Inv, res.ImageBasis);
    OPA_DISP0(glm::dot(s0, a.dir_front), a.cos_angle);
    OPA_DISP0(glm::dot(dv, a.dir_front), a.cos_angle);
    OPA_DISP0(glm::dot(v0, a.dir_front), a.cos_angle);
    OPA_CHECK0(std::abs(glm::dot(s0, a.dir_front) - a.cos_angle) < 1e-5);
    OPA_CHECK0(std::abs(glm::dot(s0, b.dir_front) - b.cos_angle) < 1e-5);
    OPA_CHECK0(std::abs(glm::dot(s1, a.dir_front) - a.cos_angle) < 1e-5);
    OPA_CHECK0(std::abs(glm::dot(s1, b.dir_front) - b.cos_angle) < 1e-5);
    return { s0, s1 };
  }

  ResT solve() {
    OPA_DISP0(prob.pl, prob.n);
    if (prob.n <= 1) return 1;

    std::vector<IntersectionPoint> inters;
    data = prob.pl | STD_TSFX(make_point(x)) | STD_VEC;
    auto ids = STD_RANGE(0, prob.n) | STD_VECT(int);

    auto p0 = data[0];

    bool has_inter = false;
    for (auto p2 : combinations<int, 2>(ids)) {
      auto &a = data[p2[0]];
      auto &b = data[p2[1]];

      auto ix = get_intersections(a, b);
      if (ix.size() != 2) continue;
      has_inter = true;
      REP (k, 2) {
        inters.emplace_back(IntersectionPoint{ .pt = ix[k],
                                               .id = int(inters.size()),
                                               .srcs = { p2[0], p2[1] },
                                               .angs = {
                                                 proj_ang(a, ix[k]),
                                                 proj_ang(b, ix[k]),
                                               } });
      }
    }
    if (inters.size() == 0) return has_inter ? 0 : 1;
    OPA_DISP0(inters);

    std::vector<std::vector<std::pair<double, int> > > entries(prob.n);
    REP (k, 2) STD_FOREACHX(inters, (entries[x.srcs[k]].emplace_back(x.angs[k], x.id)));
    std::vector<std::pair<pii, bool> > edges;

    REP (i, prob.n) {
      auto &l = entries[i];
      if (l.empty()) continue;
      OPA_CHECK0(l.size() >= 2);
      std::sort(ALL(l));
      l.pb(l[0] + MP(2 * OPA_PI, 0));
      REP (j, l.size() - 1) {
        auto &a = inters[l[j].second];
        auto &b = inters[l[j + 1].second];
        double mid = (l[j].first + l[j + 1].first) / 2;
        auto pt = iproj(data[i], mid);
        OPA_CHECK0(is_vis(i, pt));
        bool vis = std::all_of(ALL(ids), [&](auto id) { return is_vis(id, pt); });
        edges.emplace_back(MP(a.id, b.id), vis);
      }
    }
    if (std::all_of(ALL(edges), [](auto x){ return !x.second; })) return 0;
    OPA_DISP0(edges);
    opa::algo::UnionJoin uj_all{ (int)inters.size() };
    opa::algo::UnionJoin uj1{ (int)inters.size() };

    std::map<int,int> degs;
    for (auto x : edges) {
      if (x.second){
        ++degs[x.first.first];
        ++degs[x.first.second];

        uj1.merge(x.first.first, x.first.second);
      }
      uj_all.merge(x.first.first, x.first.second);
    }
    OPA_DISP0(degs);

    std::unordered_map<int, int> cnt;
    for (auto &x : uj1.get_groups_map())
      if (x.second.size() > 1) cnt[uj_all.root(x.first)]++;
    int res = 1;
    OPA_DISP0(uj1.get_groups_map());
    OPA_DISP0(uj_all.get_groups_map(), cnt);
    for (auto kv : cnt) {
      res += kv.second - 1;
    }
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

  if (TEST_RAND)
    tn = 10000;
  else {
    freopen("./prog_contest/misc/samples/ucup2_20_d.in", "r", stdin);
    scanf("%d\n", &tn);
    // tn = 1;
  }

  REP (ti, tn) {

    prob::SolverContext sc;
    sc.read();
    if (ti!=2) continue;
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
