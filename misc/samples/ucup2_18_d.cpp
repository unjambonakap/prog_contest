#include <algorithm>
#include <range/v3/view/transform.hpp>
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

template <class TData> struct SegTree {
  struct Node {
    Node *l, *r;
    int a, b;
    TData data;
  };

  void norm(Node *node) {
    if (node->l == nullptr) return;
    node->l->data.push(node->data);
    node->r->data.push(node->data);
    node->data.reset();
  }

  void add(Node *node, int low, int high, TData nd) {
    if (low > node->b || high < node->a) return;
    if (low <= node->a && node->b <= high) {
      node->data.push(nd);
      return;
    }
    norm(node);
    add(node->l, low, high, nd);
    add(node->r, low, high, nd);
    recomp(node);
  }

  void recomp(Node *node) {
    if (node->l) {
      node->data.init_empty();
      node->data.agg(node->l->data);
      node->data.agg(node->r->data);
    }
  }

  void query(Node *node, int low, int high, TData &cur) {
    if (high < node->a || low > node->b) return;
    norm(node);
    recomp(node);
    if (low <= node->a && node->b <= high)
      cur.agg(node->data);
    else {
      query(node->l, low, high, cur);
      query(node->r, low, high, cur);
    }
  }

  void update() {}

  std::deque<Node> nodes;
  Node *root;
  int n;
  Node *build1(int a, int b) {
    if (a > b) return nullptr;
    nodes.emplace_back();
    Node *cur = &nodes.back();
    cur->a = a;
    cur->b = b;
    if (a == b) return cur;
    int m = (a + b) / 2;
    cur->l = build1(a, m);
    cur->r = build1(m + 1, b);
    cur->recomp();
    return cur;
  }

  TData query(int low, int high) {
    TData cur;
    cur.init_empty();
    checkmin(high, n - 1);
    if (low > high) return cur;

    root->query(low, high, cur);
    return cur;
  }
  void build(int n) {
    root = build1(0, n - 1);
    this->n = n;
  }
};


struct Problem {
  int n;
  int nq;
  std::vector<int> al;
  std::vector<pii> ql;
  void read() {
    g_reader.readline() >> n;
    g_reader.readline();
    al = g_reader.read_list<int>(n);
    g_reader.readline() >> nq;
    g_reader.readline();
    ql = g_reader.read_list<pii>(nq, ReaderHelper::kNewLine);
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

  ResT solve() {
    struct Data {
      int cnt;
      pii best;
    };
    auto st = SegmentTree<Data>();

    auto ql = prob.ql;
    std::sort(ALL(ql));
    std::vector<pii> intervals;
    for (auto e : ql) {
      e = e - MP(1, 1);
      if (intervals.empty())
        intervals.pb(e);
      else {
        if (e.ST == intervals.back().ST)
          checkmax(intervals.back().ND, e.ND);
        else if (e.ND > intervals.back().ND)
          intervals.pb(e);
      }
    }
    auto intervals_rl = intervals | STD_TSFX(MP(x.ND, x.ST)) | STD_VEC;
    auto mapper_l = [&](int a) {
      return std::lower_bound(ALL(intervals), MP(a, -1)) - intervals.begin();
    };
    auto mapper_r = [&](int a) {
      return std::lower_bound(ALL(intervals_rl), MP(a, -1)) - intervals_rl.begin();
    };

    st.setup({ .n = (int)intervals.size(),
               .invalid = Data{ .cnt = 0, .best = MP(-1, -1) },
               .data = LQ::enumerate(intervals) |
                       STD_TSFTUPLE((Data{ .cnt = 0, .best = MP(0, p0) })) | STD_VEC,
               .f_update =
                 [&](const Data &a, const Data &b) {
                   return Data{ .cnt = 0, .best = std::max(a.best, b.best) };
                 },
               .f_norm =
                 [](Data &cur, Data &l, Data &r) {
                   l.cnt += cur.cnt;
                   l.best.first += cur.cnt;
                   r.best.first += cur.cnt;
                   r.cnt += cur.cnt;
                   cur.cnt = 0;
                 } });

    std::vector<pii> als = LQ::enumerate(prob.al) | STD_TSFTUPLE(pii(p1, p0)) | STD_VEC;
    std::sort(ALL(als));

    s64 ans = 0;
    for (auto x : als | LQ::reverse) {
      int l = std::max<int>(0, mapper_r(x.second + 1) - 1);
      int r = mapper_l(x.second + 1) - 1;
      auto resv = st.query(l, r);
      st.push(l, r, [&](Data &a) {
        a.cnt += 1;
        a.best.ST += 1;
      });
      checkmax(ans, (s64)resv.best.first * x.first);
    }
    return ans;
  }

  ResT solve_dumb() { return {}; }
};

int main(int argc, char **argv) {
  opa::init::opa_init(argc, argv);
  srand(0);
  int tn;
  freopen("./prog_contest/misc/samples/ucup2_18_d.in", "r", stdin);

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
