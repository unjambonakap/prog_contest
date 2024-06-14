#include <algorithm>
#include <numeric>
#include <range/v3/view/enumerate.hpp>
#include <range/v3/view/transform.hpp>
#include <unordered_set>
#include <vector>

#include "opa/math/common/FFT.h"
#include "opa/math/common/FractionField.h"
#include "opa/math/common/Matrix.h"
#include "opa/math/common/Types.h"
#include "opa/math/common/Utils.h"
#include "opa/math/common/Z.h"
#include "opa/math/common/matrix_utils.h"
#include "opa_common_base.h"
#include <Eigen/Dense>
#include <algorithm>
#include <opa/math/common/crt_fft.h>
#include <opa/math/game/base.h>
#include <opa/math/game/conf.h>
#include <opa/utils/range.h>
#include <opa_common.h>
#include <sstream>

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

#define pb push_back
#define ST first
#define ND second
#define MP(x, y) std::make_pair(x, y)

#define MAKE_ARRAY(t, rep, expr)                                                                   \
  STD_EXPR({                                                                                       \
    std::array<t, rep> res;                                                                        \
    REP (i, rep) {                                                                                 \
      res[i] = expr;                                                                               \
    }                                                                                              \
    return res;                                                                                    \
  })

#define STD_PARTIAL_SUM(tb_op)                                                                     \
  STD_EXPR({                                                                                       \
    auto tb = tb_op | STD_VEC;                                                                     \
    auto res = tb;                                                                                 \
    std::partial_sum(ALL(tb), res.begin());                                                        \
    return res;                                                                                    \
  })

#define STD_PARTIAL_SUM_OP(tb_op, op)                                                              \
  STD_EXPR({                                                                                       \
    auto tb = tb_op | STD_VEC;                                                                     \
    auto res = tb;                                                                                 \
    std::partial_sum(ALL(tb), res.begin(), op);                                                    \
    return res;                                                                                    \
  })

#define STD_EXPR(expr) ([&]() { expr; }())

template <class T> T _gcd(T a, T b) { return b == 0 ? a : _gcd(b, a % b); }
template <class T> T gcd(T a, T b) { return _gcd(std::max(a, b), std::min(a, b)); }
template <class T> int sign(T a) { return a > 0 ? 1 : (a < 0 ? -1 : 0); }

namespace OPA_NM = opa::math::common;

#if !LOCAL
namespace std {
s128 abs(s128 x) { return x < 0 ? -x : x; }
template <> struct hash<u128> {
  size_t operator()(const u128 &x) const {
    size_t h1 = std::hash<u64>{}((u64)x);
    size_t h2 = std::hash<u64>{}((u64)(x >> 64));
    return (h1 * int(1e9 + 7) + h2) ^ h1;
  }
};

template <> struct hash<s128> {
  size_t operator()(const s128 &x) const { return std::hash<u128>{}(x); }
};
} // namespace std
#endif

namespace std {
std::istream &operator>>(std::istream &is, opa::Pos &p) {
  is >> p.x >> p.y >> p.z;
  return is;
}
} // namespace std
opa::Pos to_pos(const std::vector<double> &vec) {
  OPA_CHECK0(vec.size() == 3);
  return { vec[0], vec[1], vec[2] };
}

std::vector<double> to_vec(const opa::Pos &vec) { return { vec[0], vec[1], vec[2] }; }

template <class T> Eigen::VectorXd to_evec(const T &vec) {
  Eigen::VectorXd res = Eigen::VectorXd(vec.size());
  REP (i, res.size()) res[i] = vec[i];
  return res;
}
template <class T> std::vector<T> to_vec(const Eigen::VectorX<T> &vec) {
  std::vector<T> res(vec.size());
  REP (i, res.size()) res[i] = vec[i];
  return res;
}

template <class T, int N> std::array<T, N> to_array(const Eigen::VectorX<T> &vec) {
  std::array<T, N> res;
  REP (i, N) res[i] = vec[i];
  return res;
}

template <class T> struct frac {
  T p, q;
  frac() {}
  frac(T p) : p(p), q(1) {}
  frac(const std::pair<T, T> &px) : frac(px.first, px.second) {}

  frac(T p, T q) : p(p), q(q) {
    T d = gcd(std::abs(p), std::abs(q));
    if (this->q < 0) this->p = -this->p, this->q = -this->q;
    this->p /= d;
    this->q /= d;
  }
  template <typename U> frac<U> as() const { return frac<U>(p, q); }
  T floor() const { return p / q; }
  T rem() const { return p % q; }
  T ceil() const { return (p + q - 1) / q; }

  std::pair<T, T> as_pair() const { return MP(p, q); }
  frac operator+(const frac &peer) const { return frac(p * peer.q + peer.p * q, peer.q * q); }
  frac operator-(const frac &peer) const { return frac(p * peer.q - peer.p * q, peer.q * q); }
  frac operator*(const frac &peer) const { return frac(p * peer.p, peer.q * q); }
  frac operator/(const frac &peer) const { return frac(p * peer.q, q * peer.p); }
  frac operator/(T d) const { return frac(p, q * d); }
  bool operator<(const frac &peer) const { return (p * peer.q - peer.p * q) < 0; }
  bool operator>(const frac &peer) const { return (p * peer.q - peer.p * q) > 0; }
  bool operator<=(const frac &peer) const { return (p * peer.q - peer.p * q) <= 0; }
  bool operator==(const frac &peer) const { return p == peer.p && q == peer.q; }
  bool operator!=(const frac &peer) const { return p != peer.p || q != peer.q; }
};

template <class T> struct Point {
  T x, y;
  Point() {}
  Point(T x, T y) : x(x), y(y) {}
  Point operator-(const Point &peer) const { return Point(x - peer.x, y - peer.y); }
  Point operator+(const Point &peer) const { return Point(x + peer.x, y + peer.y); }
  bool operator<(const Point &peer) const { return as_pair() < peer.as_pair(); }
  bool operator==(const Point &peer) const { return x == peer.x && y == peer.y; }
  bool operator!=(const Point &peer) const { return x != peer.x || y != peer.y; }
  Point abs() const { return Point(std::abs(x), std::abs(y)); }
  T cross(const Point &peer) const { return x * peer.y - y * peer.x; }
  template <typename T2> Point<T2> as() const { return Point<T2>(x, y); }
  T dot(const Point &peer) const { return x * peer.x + y * peer.y; }
  std::pair<T, T> as_pair() const { return MP(x, y); }
  T atan2() const { return std::atan2(y, x); }
  std::array<T, 2> as_array() const { return std::array<T, 2>{ x, y }; }
  std::vector<T> as_vec() const { return { x, y }; }

  Point simplify() const {
    T d = gcd(std::abs(x), std::abs(y));
    if (d == 0) return *this;
    if (y < 0) d = -d;
    return Point(x / d, y / d);
  }

  OPA_DECL_COUT_OPERATOR2(Point, a.x, a.y)
  OPA_DECL_CIN_OPERATOR2(Point, a.x, a.y)
};
typedef struct Point<s64> P64;

template <class T> struct Segment {
  Point<T> a, b;
  Segment(Point<T> _a, Point<T> _b) : a(_a), b(_b) {}

  bool different_side(const Segment &peer) const {
    auto v = b - a;
    return sign(v.cross(peer.a - a)) != sign(v.cross(peer.b - a));
  }

  bool intersects(const Segment &peer) const {
    if (parallel(peer)) return false;
    return different_side(peer) && peer.different_side(*this);
  }
  template <typename T2> Segment<T2> as() const {
    return Segment<T2>(a.template as<T2>(), b.template as<T2>());
  }
  frac<T> slope() const { return frac<T>(b.y - a.y, b.x - a.x); }

  frac<s128> eval(const T &x) const { return frac<s128>(b.y - a.y, b.x - a.x) * (x - a.x) + a.y; }

  bool vertical() const { return a.x == b.x; }
  bool parallel(const Segment &peer) const { return (b - a).cross(peer.b - peer.a) == 0; }
  Point<T> dir() const { return b - a; }
  Point<T> orth_dir() const {
    auto d = dir();
    return Point<T>(-d.y, d.x);
  }
  T signed_dist(const Point<T> &p) const { return (b - a).cross(p - a); }
  bool ccw(const Point<T> &p) const { return dir().cross(p - a) > 0; }

  Point<frac<T> > inter_point(const Segment<T> &peer) const {
    auto v1 = orth_dir();
    auto v2 = peer.orth_dir();
    auto d = v1.cross(v2);
    auto p1 = v1.dot(a);
    auto p2 = v2.dot(peer.a);

    auto xx = p1 * v2.y - p2 * v1.y;
    auto yy = v1.x * p2 - v2.x * p1;
    return Point<frac<T> >(frac<T>(xx, d), frac<T>(yy, d));
  }
};

namespace std {
template <class T> std::ostream &operator<<(std::ostream &os, const Point<T> &a) {
  return os << a.as_pair();
}
template <class T> std::ostream &operator<<(std::ostream &os, const frac<T> &a) {
  return os << MP(a.p, a.q);
}
template <class T> std::ostream &operator<<(std::ostream &os, const Segment<T> &a) {
  return os << "Seg(" << a.a << ", " << a.b << ")";
}

template <typename T> struct hash<frac<T> > {
  size_t operator()(const frac<T> &x) const { return std::hash<std::pair<T, T> >{}(x.as_pair()); }
};
template <typename T> struct hash<Point<T> > {
  size_t operator()(const Point<T> &x) const { return std::hash<std::pair<T, T> >{}(x.as_pair()); }
};
} // namespace std

template <int mod> class CombHelper {
public:
  CombHelper(int n = 0) { this->init(n); }
  void init(int n) {
    fact.resize(n + 1);
    ifact.resize(n + 1);
    fact[0] = 1;
    REP (i, n) fact[i + 1] = 1ull * fact[i] * (i + 1) % mod;
    ifact[0] = 1;
    REP (i, n + 1) ifact[i] = inv(fact[i]);
  }

  u32 faste(s64 x, s64 pw) const {
    return opa::math::common::u32_faste(x % mod, pw % (mod - 1), mod);
  }
  u32 inv(int x) const { return faste(x, mod - 2); }

  u32 cnk(int n, int k) const {
    if (n < k) return 0;
    if (k < 0) return 0;
    return 1ull * fact[n] * ifact[k] % mod * ifact[n - k] % mod;
  }

  u32 dispatch(int n, int k) const {
    if (n < 0) return 0;
    if (n == 0) return k == 0 ? 1 : 0;
    return cnk(n + k - 1, n - 1);
  }

  std::vector<int> fact;
  std::vector<int> ifact;
};
s64 invmod(s64 x, s64 mod) { return opa::math::common::u32_faste(x % mod, mod - 2, mod); }

class CombHelper2 {
public:
  int mod;

  CombHelper2(int mod, int n = 0) { this->init(mod, n); }
  void init(int mod, int n) {
    this->mod = mod;
    fact.resize(n + 1);
    ifact.resize(n + 1);
    fact[0] = 1;
    REP (i, n) fact[i + 1] = 1ull * fact[i] * (i + 1) % mod;
    ifact[0] = 1;
    REP (i, n + 1) ifact[i] = inv(fact[i]);
  }

  u32 faste(s64 x, s64 pw) const {
    return opa::math::common::u32_faste(x % mod, pw % (mod - 1), mod);
  }
  u32 inv(int x) const { return faste(x, mod - 2); }

  u32 cnk(int n, int k) const {
    if (n < k) return 0;
    if (k < 0) return 0;
    return 1ull * fact[n] * ifact[k] % mod * ifact[n - k] % mod;
  }

  std::vector<int> fact;
  std::vector<int> ifact;
};
template <typename T>
typename std::enable_if<std::is_same<T, pii>::value, T>::type read_t(std::istringstream &iss) {
  pii res;
  iss >> res.ST >> res.ND;
  return res;
}

template <typename T>
typename std::enable_if<not std::is_same<T, pii>::value, T>::type read_t(std::istringstream &iss) {
  T res;
  iss >> res;
  return res;
}

struct ReaderHelper {
  mutable char buf[111111];
  mutable bool eof = false;
  static constexpr bool kNewLine = false;

  mutable std::istringstream iss;
  std::istringstream &readline() const {
    std::fgets(buf, sizeof(buf) - 1, stdin);
    eof = std::feof(stdin);
    if (eof) buf[0] = 0;
    iss = std::istringstream(buf);
    return iss;
  }
  template <typename T> T read_t() const { return ::read_t<T>(iss); }

  template <class T> std::vector<T> read_list(int cnt, bool newline = !kNewLine) const {
    std::vector<T> res(cnt);
    REP (i, cnt) {
      if (i != 0 && newline == kNewLine) this->readline();
      res[i] = this->read_t<T>();
    }
    return res;
  }

  template <class T, size_t K> std::array<T, K> read_array(bool newline = !kNewLine) const {
    auto tmp = this->read_list<T>(K, newline);
    std::array<T, K> res;
    REP (i, K) res[i] = tmp[i];
    return res;
  }
};

template <class T> struct SegmentTree {

  std::vector<T> nodes;
  int n;
  int nb;
  SegmentTree() {}
  typedef std::function<T(const T &, const T &)> f_update_t;
  typedef std::function<void(T &, T &, T &)> f_norm_t;
  typedef std::function<void(T &)> f_push_t;

  T invalid;
  f_norm_t f_norm;
  f_update_t f_update;
  const T &root() const { return nodes[1]; }

  struct SetupParams {
    int n;
    T invalid;
    const std::vector<T> &data;
    const f_update_t &f_update;
    std::function<void(T &, T &, T &)> f_norm;
  };

  void setup(const SetupParams &params) {
    this->n = params.n;
    this->invalid = params.invalid;
    this->f_norm = params.f_norm;
    this->f_update = params.f_update;
    nb = 1;
    while (nb < n) nb <<= 1;
    nodes.resize(2 * nb);
    assert(params.data.size() == params.n);

    REP (i, nb) nodes[nb + i] = i < n ? params.data[i] : invalid;

    FORV (p, 1, nb) {
      auto &nx = nodes[p];
      nx = params.f_update(nodes[2 * p], nodes[2 * p + 1]);
    }
  }

  inline int high(int node) const { return low(node) + sz(node) - 1; }
  inline int low(int node) const { return sz(node) * (node ^ (1 << log2_high_bit(node))); }
  inline int sz(int node) const { return nb >> log2_high_bit(node); }

  T query(int a, int b) {
    T res = invalid;
    _query(1, a, b, res);
    return res;
  }
  void push(int a, int b, const f_push_t &f_push) { _push(1, a, b, f_push); }

  void _push(int p, int a, int b, const f_push_t &f_push) {
    if (a > b) return;
    int lp = low(p);
    int hp = high(p);
    if (b < lp) return;
    if (a > hp) return;
    auto &nx = nodes[p];

    if (a <= lp && hp <= b) {
      f_push(nx);
    } else {
      f_norm(nx, nodes[2 * p], nodes[2 * p + 1]);
      _push(2 * p, a, b, f_push);
      _push(2 * p + 1, a, b, f_push);
      nx = f_update(nodes[2 * p], nodes[2 * p + 1]);
    }
  }
  void _query(int p, int a, int b, T &res) {
    if (a > b) return;
    int lp = low(p);
    int hp = high(p);
    if (b < lp) return;
    if (a > hp) return;
    auto &nx = nodes[p];

    if (a <= lp && hp <= b) {
      res = f_update(res, nx);
    } else {
      f_norm(nx, nodes[2 * p], nodes[2 * p + 1]);
      _query(2 * p, a, b, res);
      _query(2 * p + 1, a, b, res);
      // nx = f_update(nodes[2 * p], nodes[2 * p + 1]);
    }
  }
};

template <typename T> class Mutator {
public:
  Mutator(T &t, T value) : m_t(t) {
    orig = t;
    t = value;
  }

  ~Mutator() { m_t = orig; }
  T orig;
  T &m_t;
};

template <class T> struct LinkCutTree {

  struct Node {
    int l, r, p, path;
    bool rev = false;
    T data;
    OPA_DECL_COUT_OPERATOR2(Node, a.l, a.r, a.p, a.path, a.data);
  };

  inline void norm(int aid) {
    if (aid == pNull) return;
    auto &a = nodes[aid];
    OPA_CHECK0(aid != a.l);
    OPA_CHECK0(aid != a.r);
    op(a.data, nodes[a.l].data, nodes[a.r].data);
    if (a.rev) a.rev = 0, nodes[a.l].rev ^= 1, nodes[a.r].rev ^= 1, std::swap(a.l, a.r);
  }

  std::vector<Node> nodes;
  typedef std::function<void(T &, T &, T &)> op_t;
  typedef std::function<void(T &)> mut_op_t;
  int pNull;
  op_t op;

  void init(int n) {

    pNull = n;
    nodes.resize(n + 1, Node{ .l = pNull, .r = pNull, .p = pNull, .path = pNull });
  }

  inline void rotate(int aid) {
    if (aid == pNull) return;
    auto &a = nodes[aid];
    if (a.p == pNull) return;
    int xid = a.p;
    auto &x = nodes[a.p];

    if (x.l == aid) {
      a.p = x.p;
      x.l = a.r;
      nodes[a.r].p = xid;
      a.r = xid;
      x.p = aid;
    } else {
      a.p = x.p;
      x.r = a.l;
      nodes[a.l].p = xid;
      a.l = xid;
      x.p = aid;
    }
    a.path = x.path;
    x.path = pNull;
    if (nodes[a.p].l == xid)
      nodes[a.p].l = aid;
    else
      nodes[a.p].r = aid;
    OPA_CHECK0(a.path != aid);
    OPA_CHECK0(a.p != aid);
    OPA_CHECK0(a.l != aid);
    OPA_CHECK0(a.r != aid);
    refresh(xid);
    refresh(aid);
  }

  inline void refresh(int aid) {
    if (aid == pNull) return;
    auto &a = nodes[aid];
    op(a.data, nodes[a.l].data, nodes[a.r].data);
  }

  inline void splay(int aid) {
    int k = 0;
    int tmp = aid;
    vi lst;
    while (tmp != pNull) {
      lst.pb(tmp);
      tmp = nodes[tmp].p;
    }
    for (auto x : lst | LQ::reverse) norm(x);

    while (true) {
      auto &a = nodes[aid];
      if (a.p == pNull) break;
      auto &ap = nodes[a.p];
      if (ap.p == pNull)
        rotate(aid);
      else {
        if ((ap.l == aid) == (nodes[ap.p].l == a.p))
          rotate(a.p), rotate(aid);
        else
          rotate(aid), rotate(aid);
      }
    }
  }

  void access(int aid) {
    int oaid = aid;
    int rp = pNull;

    while (aid != pNull) {
      splay(aid);
      auto &a = nodes[aid];

      if (a.r != pNull) {
        nodes[a.r].path = aid;
        nodes[a.r].p = pNull;
        a.r = pNull;
      }

      a.r = rp;
      nodes[rp].p = aid;
      refresh(aid);

      rp = aid;
      aid = a.path;
    }
    splay(oaid);
    nodes[oaid].path = pNull;
  }

  void make_root(int aid) {
    access(aid);
    auto &a = nodes[aid];
    a.reverse = true;
    a.path = pNull;
    assert(a.p == pNull);
  }

  void link(int aid, int bid) {
    make_root(bid);
    assert(nodes[bid].path == pNull);
    assert(nodes[bid].p == pNull);
    nodes[bid].path = aid;
  }

  void cut(int aid, int bid) {
    make_root(aid);
    splay(bid);
    assert(nodes[bid].path == aid);
    assert(nodes[bid].p == pNull);
    nodes[bid].path = pNull;
  }

  int get_root(int aid) {
    access(aid);
    while (nodes[aid].l != pNull) aid = nodes[aid].l;
    access(aid);
    return aid;
  }

  int lca(int aid, int bid) {
    access(aid);
    access(bid);
    splay(aid);
    if (nodes[aid].path == pNull) return aid;
    return nodes[aid].path;
  }

  T do_path_query(int aid, int bid) {

    T res;
    int cid = lca(aid, bid);
    access(aid);
    splay(cid);
    T v1, v2;
    {
      Mutator mt(nodes[cid].l, pNull);
      norm(cid);
      v1 = nodes[cid].data;
    }
    norm(cid);

    if (bid != cid) {
      access(bid);
      splay(cid);
      norm(nodes[cid].r);
      v2 = nodes[nodes[cid].r].data;
    }
    op(res, v1, v2);
    return res;
  }

  void do_node_op(int aid, mut_op_t mut_op) {
    access(aid);
    mut_op(nodes[aid].data);
    refresh(aid);
  }
  void do_path_op(int aid, int bid, mut_op_t mut_op) {
    int cid = lca(aid, bid);
    access(aid);
    splay(cid);
    {
      Mutator mt(nodes[cid].l, pNull);
      mut_op(nodes[cid].data);
      norm(cid);
    }
    norm(cid);

    if (bid == cid) return;

    access(bid);
    splay(cid);
    OPA_CHECK0(nodes[cid].r != pNull);
    norm(nodes[cid].r);
    mut_op(nodes[nodes[cid].r].data);
    norm(nodes[cid].r);
    refresh(cid);
  }

  T get_data(int aid) {
    access(aid);
    return nodes[aid].data;
  }
};

std::vector<double> solve_quadratic(double a, double b, double c, double eps = 1e-9) {
  double d = b * b - 4 * a * c;
  if (d < -eps) return {};
  if (d < eps) return { -b / (2 * a) };
  d = std::sqrt(d);
  return { (-b - d) / (2 * a), (-b + d) / (2 * a) };
}

template <class T>
std::vector<std::vector<T> > product(const std::vector<std::vector<T> > &tb, int k = -1) {
  if (k == -1) k = tb.size();
  if (k == 0) return { {} };
  std::vector<std::vector<T> > res;
  for (auto e : product(tb, k - 1)) {
    for (auto x : tb[k - 1]) {
      res.pb(e);
      res.back().pb(x);
    }
  }
  return res;
}

template <class T> std::vector<std::vector<T> > product2(const std::vector<T> &tb, int k) {
  if (k == 0) return { {} };
  std::vector<std::vector<T> > res;
  for (auto e : product2(tb, k - 1)) {
    for (auto x : tb) {
      res.pb(e);
      res.back().pb(x);
    }
  }

  return res;
}

template <class T> std::vector<std::vector<T> > combinations2(const std::vector<T> &tb, int K) {
  int n = tb.size();
  if (K > n) return {};
  if (K == 0) {

    return { {} };
  } else {

    if (K == tb.size()) {
      return { tb };
    }

    std::vector<std::vector<T> > res;
    auto copy = tb;
    REP (i, n - K + 1) {
      auto last = copy.back();
      copy.pop_back();

      for (auto x : combinations2<T>(copy, K - 1)) {
        res.pb(x);
        res.back().pb(last);
      }
    }
    return res;
  }
}
template <class T, int K> std::vector<std::array<T, K> > combinations(const std::vector<T> &tb) {
  int n = tb.size();
  if (K > n) return {};
  if constexpr (K == 0) {

    return { {} };
  } else {

    if (K == tb.size()) {
      std::array<T, K> u;
      REP (i, K) u[i] = tb[i];
      return { u };
    }

    std::vector<std::array<T, K> > res;
    auto copy = tb;
    REP (i, n - K + 1) {
      auto last = copy.back();
      copy.pop_back();

      for (auto x : combinations<T, K - 1>(copy)) {
        res.emplace_back();
        REP (i, K - 1) res.back()[i] = x[i];
        res.back()[K - 1] = last;
      }
    }
    return res;
  }
}

struct Tree {
  std::vector<vi> edges;
  std::vector<int> par;
  std::vector<int> depth;
  int n;

  void init(const std::vector<pii> &init_edges) {
    n = init_edges.size() + 1;

    depth.resize(n, 0);
    par.resize(n, -1);
    edges.resize(n);
    for (auto x : init_edges) edges[x.ST].pb(x.ND), edges[x.ND].pb(x.ST);
    dfs(0);
  }

  void dfs(int a, int p = -1) {
    par[a] = p;
    depth[a] = p == -1 ? 0 : depth[p] + 1;
    for (auto &b : edges[a])
      if (b != p) dfs(b, a);
  }

  int lca(int a, int b) const {
    if (a == b) return a;
    int da = depth[a], db = depth[b];
    return lca((da >= db ? par[a] : a), (db >= da ? par[b] : b));
  }

  vi path(int a, int b) const {
    vi p2 = {};
    vi p1 = {};

    int c = lca(a, b);
    while (b != c) p2.pb(b), b = par[b];
    while (a != c) p1.pb(a), a = par[a];
    p1.pb(c);
    return LQ::concat(p1, p2 | LQ::reverse) | STD_VEC;
  }
};

struct Generator {
  std::mt19937 rng{ 0 };
  bool check_colinear(Point<s32> pt, const std::vector<Point<s32> > &lst) {
    std::unordered_set<pii> mp;
    for (auto &e : lst) {
      if (pt == e) return false;
      if (!mp.insert((e - pt).simplify().as_pair()).second) return false;
    }
    return true;
  }

  std::vector<double> generate_vec(int nd, int lim) {
    std::uniform_real_distribution<double> dis(-lim, lim);
    return STD_RANGE(0, nd) | STD_TSFX(dis(rng)) | STD_VEC;
  }

  std::vector<pii> generate_points(int n, int lim) {
    std::uniform_int_distribution<> dis(-lim, lim);
    std::unordered_set<int> seen;
    std::vector<Point<s32> > pts;
    if (TEST_LARGE) {
      double pi = acos(-1.);
      int r = std::uniform_int_distribution<>(lim / 2, lim)(rng);
      std::uniform_int_distribution<> d2(-(lim * 2 * pi / n / 10 + 1), lim * 2 * pi / n / 10 + 1);

      REP (i, n) {
        double ang = 2 * pi / n * (i + 0.5);
        double x = cos(ang) * r + d2(rng) * 1;
        double y = sin(ang) * r + d2(rng) * 1;
        pts.emplace_back(x, y);
      }

    } else {

      REP (i, n) {
        while (true) {
          Point<s32> p(dis(rng), dis(rng));
          if (seen.count(p.x)) continue;
          if (check_colinear(p, pts)) {
            pts.pb(p);
            seen.insert(p.x);
            break;
          }
        }
      }
    }

    std::vector<pii> res;
    for (auto &x : pts) res.pb(x.as_pair());
    return res;
  }

  std::vector<pii> generate_tree(int n) {
    vi par(n, -1);
    std::function<int(int)> root;
    root = [&](int x) { return par[x] == -1 ? x : par[x] = root(par[x]); };
    std::vector<pii> res;
    while (res.size() != n - 1) {
      int a = rng() % n, b = rng() % n;
      if (a != b && root(a) != root(b)) {
        res.emplace_back(a, b);
        par[root(a)] = root(b);
      }
    }
    return res;
  }
};

namespace std {

template <typename A, typename B> std::istream &operator>>(std::istream &is, std::pair<A, B> &p) {

  is >> p.first >> p.second;
  return is;
}
template <typename A, long unsigned int N>
std::istream &operator>>(std::istream &is, std::array<A, N> &p) {

  REP (i, N) is >> p[i];
  return is;
}
} // namespace std

namespace hull {

struct TNode {
  int left_bridge = -1;
  int right_bridge = -1;
  int cnt = 0;
};

struct DynamicHull {
  const int lowerhull = 1;
  const int upperhull = 0;
  std::vector<Point<s64> > pts;
  std::unordered_map<Point<s64>, int> rmp;
  std::vector<TNode> segtrees[2];
  std::vector<Point<s64> > ptsf[2];
  std::vector<int> highbit;
  int pw;
  int n;
  int count(int f) const { return segtrees[f][1].cnt; }

  void setup(const std::vector<Point<s64> > &points) {
    pts = points;
    std::sort(ALL(pts));
    n = pts.size();
    REP (i, n) rmp[pts[i]] = i;
    REP (i, n) ptsf[0].emplace_back(pts[i]);
    REP (i, n) ptsf[1].emplace_back(pts[i].x, -pts[i].y);

    pw = 1;
    while (pw < n) pw <<= 1;
    REP (f, 2) segtrees[f].resize(2 * pw);
    highbit.resize(2 * pw);

    highbit[0] = -1;
    FOR (i, 1, highbit.size()) highbit[i] = highbit[i >> 1] + 1;
  }

  int start_node_id(int pos) const {
    int hg = highbit[pos];
    return (pos ^ (1 << hg)) * (pw >> hg);
  }
  int node_size(int pos) const { return pw >> highbit[pos]; }

  void normalize(int f, int p) {
    if (p >= pw) return;
    auto &l = segtrees[f][2 * p];
    auto &r = segtrees[f][2 * p + 1];
    segtrees[f][p].cnt = l.cnt + r.cnt;
  }

  int only_child(int f, int pos) const {
    while (pos < pw) {

      if (segtrees[f][2 * pos].cnt == 0)
        pos = 2 * pos + 1;
      else if (segtrees[f][2 * pos + 1].cnt == 0)
        pos = 2 * pos;
      else
        break;
    }
    return pos;
  }

  void update_bridge(int f, int pos) {
    int lp = pos * 2;
    int rp = pos * 2 + 1;
    auto &vx = segtrees[f];
    auto &nx = vx[pos];

    if (nx.cnt == 0 || vx[lp].cnt == 0 || vx[rp].cnt == 0) {
      nx.left_bridge = nx.right_bridge = -1;
      return;
    }

    while (true) {
      if (vx[lp].cnt > 0) {
        lp = only_child(f, lp);
      }

      if (vx[rp].cnt > 0) {
        rp = only_child(f, rp);
      }
      assert(lp < 2 * pw);
      assert(rp < 2 * pw);
      if (lp >= pw && rp >= pw) break;
      auto &l = vx[lp];
      auto &r = vx[rp];
      auto &tb = ptsf[f];
      int llb = l.left_bridge == -1 ? lp - pw : l.left_bridge;
      int lrb = l.right_bridge == -1 ? lp - pw : l.right_bridge;
      int rlb = r.left_bridge == -1 ? rp - pw : r.left_bridge;
      int rrb = r.right_bridge == -1 ? rp - pw : r.right_bridge;
      int rid = start_node_id(rp);
      int lid = start_node_id(lp) + node_size(lp) - 1;
      int action =
        compute_action(tb[llb], tb[lrb], tb[rlb], tb[rrb], frac<s64>(pts[lid].x + pts[rid].x, 2));
      if (action < 2)
        lp = 2 * lp + action;
      else
        rp = 2 * rp + action - 2;
    }

    if (vx[lp].cnt > 0 && vx[rp].cnt > 0) {
      nx.left_bridge = lp - pw;
      nx.right_bridge = rp - pw;
    } else {

      nx.left_bridge = -1;
      nx.right_bridge = -1;
    }
  }

  int compute_action(const Point<s64> &ll, const Point<s64> &lr, const Point<s64> &rl,
                     const Point<s64> &rr, frac<s64> midpoint) {
    if (ll == lr) {
      return (rl - ll).cross(rr - ll) > 0 ? 3 : 2;
    }
    if (rl == rr) {
      return (ll - rl).cross(lr - rl) > 0 ? 0 : 1;
    }

    {
      auto v = lr - ll;
      auto v1 = rl - ll;
      auto v2 = rr - ll;
      bool s1 = v.cross(v1) > 0;
      bool s2 = v.cross(v2) > 0;
      if (s1 || s2) return 0;
    }

    {
      auto v = rl - rr;
      auto v1 = lr - rr;
      auto v2 = ll - rr;
      bool s1 = v.cross(v1) < 0;
      bool s2 = v.cross(v2) < 0;
      if (s1 || s2) return 3;
    }
    auto segl = Segment<s64>(ll, lr).as<s128>();
    auto segr = Segment<s64>(rl, rr).as<s128>();
    auto interpoint = segl.inter_point(segr);

    if (interpoint.x < midpoint.as<s128>()) return 1;
    return 2;
  }

  void update(const Point<s64> &p, bool remove_node) {
    REP (f, 2) update(p, remove_node, f);
  }

  void update(const Point<s64> &p, bool remove_node, int f) {
    assert(rmp.count(p));
    int pid = rmp[p];
    assert(pid < n);

    int pos = pid + pw;
    auto &nx = segtrees[f][pos];
    if (remove_node) {
      nx.cnt = 0;
      nx.left_bridge = -1;
      nx.right_bridge = -1;
    } else {
      nx.cnt = 1;
      nx.left_bridge = -1;
      nx.right_bridge = -1;
    }

    for (; pos > 1; pos >>= 1) {
      int np = pos >> 1;

      normalize(f, np);
      auto &node = segtrees[f][np];
      bool do_update = false;
      if (remove_node)
        do_update |= node.left_bridge == pid || node.right_bridge == pid || true;
      else {
        if (node.left_bridge == -1 || node.right_bridge == -1)
          do_update = true;
        else {
          auto seg = Segment<s64>(ptsf[f][node.left_bridge], ptsf[f][node.right_bridge]);
          do_update |= pid < node.left_bridge || pid > node.right_bridge || seg.ccw(ptsf[f][pid]);
        }
      }
      if (do_update) update_bridge(f, np);
    }
  }

  void fill_hull(int f, int pos, std::vector<int> &hull, int l, int r) const {
    auto &x = segtrees[f][pos];
    if (x.cnt == 0) return;
    int ln = start_node_id(pos);
    int rn = ln + node_size(pos) - 1;
    if (l > rn || r < ln) return;
    int nr = r;
    if (x.left_bridge != -1) checkmin(nr, x.left_bridge - 1);
    fill_hull(f, 2 * pos, hull, l, nr);
    if (x.left_bridge != -1 && x.left_bridge >= l && x.left_bridge <= r) hull.pb(x.left_bridge);
    if (x.right_bridge != -1 && x.right_bridge >= l && x.right_bridge <= r) hull.pb(x.right_bridge);

    if (pos >= pw && pos - pw >= l && pos - pw <= r) hull.pb(pos - pw);
    int nl = l;
    if (x.right_bridge != -1) checkmax(nl, x.right_bridge + 1);
    fill_hull(f, 2 * pos + 1, hull, nl, r);
  }

  std::vector<int> extract_hull(int f) const {
    std::vector<int> res;
    fill_hull(f, 1, res, 0, n);
    return res;
  }

  std::vector<int> compute_hull_dumb(int f) const {
    std::vector<int> tb;
    REP (i, n) {
      if (segtrees[f][i + pw].cnt == 0) continue;

      auto &a = ptsf[f][i];
      while (tb.size() >= 2) {
        int nx = tb.size();
        if ((ptsf[f][tb[nx - 1]] - a).cross(ptsf[f][tb[nx - 2]] - a) < 0)
          tb.pop_back();
        else
          break;
      }
      tb.pb(i);
    }
    return tb;
  }
  typedef std::function<bool(const Segment<s64> &)> FindF;
  typedef std::function<bool(int lb, int rb)> SearchF;

  int search(int f, const SearchF &func) const {
    int pos = 1;
    while (true) {
      pos = only_child(f, pos);
      if (pos >= pw) break;
      auto &node = segtrees[f][pos];
      if (func(node.left_bridge, node.right_bridge))
        pos = 2 * pos + 1;
      else
        pos = 2 * pos;
    }
    return pos - pw;
  }

  int find(int f, const FindF &func) const {
    int pos = 1;
    while (true) {
      pos = only_child(f, pos);
      if (pos >= pw) break;
      auto &node = segtrees[f][pos];
      if (func(Segment<s64>(pts[node.left_bridge], pts[node.right_bridge])))
        pos = 2 * pos + 1;
      else
        pos = 2 * pos;
    }
    return pos - pw;
  }

  int prev(int f, int p) const {
    int best = -1;
    search(f, [&](int a, int b) {
      if (a < p) checkmax(best, a);
      if (b < p) checkmax(best, b);
      return a < p;
    });
    return best;
  }
  int next(int f, int p) const {
    int best = INT_MAX;
    search(f, [&](int a, int b) {
      if (a > p) checkmin(best, a);
      if (b > p) checkmin(best, b);
      return b <= p;
    });
    return best == INT_MAX ? -1 : best;
  }

  int max(int f) const {
    return search(f, [](int a, int b) {
      (void)a;
      (void)b;
      return true;
    });
  }
  int min(int f) const {
    return search(f, [](int a, int b) {
      (void)a;
      (void)b;
      return false;
    });
  }
};

template <typename T> std::vector<int> compute_hull(const std::vector<Point<T> > &pts, bool upper) {
  int n = pts.size();
  vi tb;
  REP (i, n) tb.pb(i);
  std::sort(ALL(tb), [&](int a, int b) { return pts[a].x < pts[b].x; });
  vi res;

  for (auto i : tb) {
    auto &a = pts[i];
    while (res.size() >= 2) {
      int nx = res.size();
      if (((pts[res[nx - 2]] - a).cross(pts[res[nx - 1]] - a) > 0) ^ !upper)
        res.pop_back();
      else
        break;
    }
    res.pb(i);
  }
  return res;
}

template <typename T> std::vector<int> compute_hull_full(const std::vector<Point<T> > &pts) {
  int n = pts.size();
  OPA_CHECK0(n >= 2);

  vi tb;
  REP (i, n) tb.pb(i);
  constexpr double eps = 1e-9;
  std::sort(ALL(tb), [&](int a, int b) {
    return pts[a].x + eps < pts[b].x ||
           (std::abs(pts[a].x - pts[b].x) < eps && pts[a].y < pts[b].y);
  });

  auto compute = [&](bool upper) {
    vi res;

    for (auto i : tb) {
      auto &a = pts[i];
      while (res.size() >= 2) {
        int nx = res.size();
        if (((pts[res[nx - 2]] - a).cross(pts[res[nx - 1]] - a) > 0) ^ !upper)
          res.pop_back();
        else
          break;
      }
      res.pb(i);
    }
    return res;
  };
  auto lh = compute(false);
  auto uh = compute(true);
  uh.pop_back();
  std::reverse(ALL(uh));
  uh.pop_back();
  return LQ::concat(lh, uh) | STD_VEC;
}

struct SidedHull {
  DynamicHull *dh;
  bool lower;
  SidedHull(DynamicHull *dh, bool lower) : dh(dh), lower(lower) {}

  struct Iterator {
    const SidedHull *sh;
    int v;
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = int;
    using pointer = int *;         // or also value_type*
    using reference = const int &; // or also value_type&
    reference operator*() const { return v; }
    Point<s64> pt() const { return sh->dh->pts[v]; }

    Iterator operator-(int a) const { return *this + (-a); }
    Iterator operator+(int a) const {
      auto res = *this;
      if (a >= 0)
        REP (i, a) ++res;
      else
        REP (i, -a) --res;
      return res;
    }

    // Prefix increment
    Iterator &operator--() {
      if (v == -1)
        v = sh->dh->max(sh->lower);
      else
        v = sh->dh->prev(sh->lower, v);
      assert(v != -1);
      return *this;
    }

    Iterator &operator++() {
      assert(v != -1);
      v = sh->dh->next(sh->lower, v);
      return *this;
    }

    // Postfix increment
    Iterator operator--(int) {
      Iterator tmp = *this;
      --(*this);
      return tmp;
    }
    Iterator operator++(int) {
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }
  };

  Iterator begin() const {
    Iterator res;
    res.sh = this;
    res.v = dh->min(lower);
    return res;
  }
  Iterator end() const {
    Iterator res;
    res.sh = this;
    res.v = -1;
    return res;
  }

  friend bool operator==(const Iterator &a, const Iterator &b) {
    return a.sh == b.sh && a.v == b.v;
  }

  friend bool operator!=(const Iterator &a, const Iterator &b) { return !(a == b); }
};

template <typename T> struct IncrementalHull {
  struct PointCompare {
    const IncrementalHull &ih;
    PointCompare(IncrementalHull &ih) : ih(ih) {}
    bool operator()(const int &a, const int &b) const {
      if (a == -1)
        return !ih.search(b);
      else if (b == -1)
        return ih.search(a);
      return ih.tb[a].x < ih.tb[b].x;
    }
  };
  std::vector<Point<T> > tb;
  PointCompare pc;
  std::set<int, PointCompare> hull;
  std::vector<int> next;
  bool upper;
  int n;

  typedef std::function<bool(const Segment<T> &)> SearchF;
  mutable const SearchF *_searchF;

  IncrementalHull() : pc(*this), hull(pc) {}

  bool search(int v) const {
    if (next[v] == -1) return false;
    return (*_searchF)(Segment<T>(tb[v], tb[next[v]]));
  }

  void setup(const std::vector<Point<T> > &startpoints, bool upper) {
    tb = startpoints;
    this->upper = upper;
    auto hull = compute_hull(startpoints, upper);
    n = startpoints.size();
    next.resize(n, -1);
    REP (i, hull.size() - 1) next[hull[i]] = hull[i + 1];
    this->hull.insert(ALL(hull));
  }

  int find(const SearchF &func) const {
    OPA_DISP0(hull.size());
    if (hull.size() == 0) return -1;
    if (hull.size() == 1) return *hull.begin();
    _searchF = &func;
    auto it = hull.lower_bound(-1);
    _searchF = nullptr;
    OPA_DISP0(*it);
    return *it;
  }

  bool push(Point<T> pt) {
    int id = tb.size();
    OPA_DISP("PUsh ", pt, id);
    next.pb(-1);
    tb.pb(pt);
    auto it = hull.lower_bound(id);
    if (it != hull.begin()) {
      auto p1 = it;
      --p1;
      while (p1 != hull.begin()) {
        auto p2 = p1;
        --p2;
        if (!can_remove(*p2, *p1, id)) break;
        OPA_DISP("Remove 1", *p2, *p1, id);
        next[*p1] = -1;
        hull.erase(p1);
        p1 = p2;
      }
      it = ++p1;
    }

    while (it != hull.end()) {
      auto nit = it;
      ++nit;
      if (nit == hull.end()) break;
      if (!can_remove(id, *it, *nit)) break;
      OPA_DISP("Remove 1", id, *it, *nit);
      next[*it] = -1;
      it = hull.erase(it);
    }
    bool insert = false;
    OPA_DISP0(it == hull.end(), it == hull.begin());
    if (it == hull.end() || it == hull.begin())
      insert = true;
    else {
      auto prev = it;
      --it;
      insert = !can_remove(*prev, id, *it);
    }
    OPA_DISP0(id, insert);
    if (insert) {
      auto it = hull.insert(id).first;
      if (it != hull.begin()) {
        auto prev = it;
        next[*--prev] = id;
      }

      auto nit = ++it;
      if (nit != hull.end()) next[id] = *nit;
    }
    return insert;
  }

  bool can_remove(int a, int b, int c) const {
    auto pa = tb[a];
    auto pb = tb[b];
    auto pc = tb[c];
    return Segment<T>(pa, pb).ccw(pc) ^ !upper;
  }
};

} // namespace hull
struct MinEnclosingBall {
  typedef std::vector<double> point_t;
  typedef Eigen::VectorXd ipoint_t;
  std::vector<point_t> points;
  std::vector<ipoint_t> ipoints;
  mutable std::mt19937 rng{ 0 };
  static constexpr double eps = 1e-7;
  OPA_NM::RealDouble field{ eps };

  mutable std::vector<int> ord;
  struct CircleSpec {
    ipoint_t p;
    double r;
  };

  bool inside(const CircleSpec &c, int p) const {
    return (c.p - ipoints[p]).squaredNorm() < c.r * c.r + eps;
  }

  __attribute__((force_align_arg_pointer)) CircleSpec rec(int pos,
                                                          const std::vector<int> &boundary) const {
    if (pos == 1 && boundary.size() == 0) return rec(0, { 0 });

    if (pos == 0) {
      int nn = boundary.size();
      if (nn == 1) return CircleSpec{ .p = ipoints[boundary[0]], .r = 0 };
      auto pts = OPA_NM::Matrix<double>::fromvecs(&field, boundary | STD_TSFX(points[x]) | STD_VEC,
                                                  OPA_NM::VecType::Row);

      auto mat = OPA_NM::Matrix<double>::fromvecs(
        &field,
        boundary | LQ::drop(1) | STD_TSFX(to_vec<double>(ipoints[x] - ipoints[boundary[0]])) |
          STD_VEC,
        OPA_NM::VecType::Row);
      auto r = mat.zeroes(nn - 1, nn);
      std::vector<double> b(nn - 1);
      REP (i, nn - 1) {
        r(i, i) = -1;
        r(i, i + 1) = 1;
        auto pa = ipoints[boundary[i]];
        auto pb = ipoints[boundary[i + 1]];
        b[i] = (pb - pa).dot((pa + pb) / 2 - ipoints[boundary[0]]);
      }

      OPA_NM::gram_schmidt_real(mat);
      auto A = (r * pts) * mat.transpose();
      OPA_DISP0(points, boundary, pts);
      OPA_DISP0(mat);
      OPA_DISP0(A, b);
      auto rv = A.solve(b);
      auto cx = mat.evalT(rv);
      Eigen::VectorXd cc = to_evec(cx) + ipoints[boundary[0]];
      auto dists = boundary | STD_TSFX((ipoints[x] - cc).norm()) | STD_VEC;
      OPA_DISP0(cc, dists, cx, to_evec(cx), ipoints[boundary[0]], rv);
      OPA_DISP0(cc - ipoints[boundary[0]]);
      if (boundary.size() == 2) OPA_DISP0((ipoints[boundary[0]] - ipoints[boundary[1]]).norm());
      puts("\n\n\n\n");
      return CircleSpec{ .p = cc, .r = (ipoints[boundary[0]] - cc).norm() };
    }

    auto res = rec(pos - 1, boundary);
    if (!inside(res, pos - 1))
      return rec(pos - 1, LQ::concat(boundary, STD_SINGLEV(int(pos - 1))) | STD_VEC);
    return res;
  }

  std::pair<double, point_t> compute() {
    ord = STD_RANGE(0, points.size()) | STD_VECT(int);
    std::shuffle(ALL(ord), rng);
    ipoints = points | STD_TSFX(to_evec(x)) | STD_VEC;
    auto c = rec(points.size(), {});
    return MP(c.r, to_vec(c.p));
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

enum TreapRangeExpl {
  Stop = 0,
  Continue = 1,
  Contained = 2,
};

template <class T> struct Treap {
  typedef int node_id_t;
  typedef int key_t;
  struct Node {
    int l, r, p;
    int id;
    T data;
    OPA_DECL_COUT_OPERATOR2(Node, a.l, a.r, a.p, a.data);
  };

  inline void norm(int aid) {
    if (aid == pNull) return;
    auto &a = nodes[aid];
    OPA_CHECK0(aid != a.l);
    OPA_CHECK0(aid != a.r);
    op(a.data, nodes[a.l].data, nodes[a.r].data);
  }

  std::mt19937 rng{ 0 };
  std::vector<Node> nodes;
  int n;
  int nb;
  typedef std::function<void(T &, T &, T &)> op_t;
  typedef std::function<void(T &)> mut_op_t;
  typedef std::function<TreapRangeExpl(const T &)> range_expl_op_t;
  int pNull;
  op_t op;

  void init(int n) { pNull = 0; }

  Treap() {}
  typedef std::function<T(const T &, const T &)> f_update_t;
  typedef std::function<void(T &, T &, T &)> f_norm_t;
  typedef std::function<void(T &)> f_push_t;

  int join(int aid, int bid) {
    norm(aid);
    norm(bid);
    if (aid == pNull) return bid;
    if (bid == pNull) return aid;
    auto &a = nodes[aid];
    auto &b = nodes[bid];

    if (a.id > b.id) {
      b.l = join(aid, b.l);
      b->update();
      return bid;
    } else {
      a.r = join(a.r, b);
      a->update();
      return aid;
    }
  }

  int fix(int xid) {
    if (xid == pNull) return xid;

    auto &x = nodes[xid];
    int pid = xid;
    if (x.l != pNull && nodes[x.l].id < x.id) {
      pid = x.l;
      auto &p = nodes[pid];
      norm(pid);
      x.l = p.r;
      p.r = xid;
    }

    if (x.r != pNull && nodes[x.r].id < x.id) {
      pid = x.r;
      auto &p = nodes[pid];
      norm(pid);
      x.r = p.l;
      p.l = xid;
    }
    norm(xid);
    norm(pid);
    return pid;
  }

  key_t key(node_id_t id) const { return nodes[id].data.key; }

  int insert1(int rid, int xid) {
    if (rid == pNull) return xid;
    norm(rid);

    if (key(rid) > key(xid))
      nodes[rid].l = insert1(nodes[rid].l, xid);
    else
      nodes[rid].r = insert1(nodes[rid].r, xid);
    return fix(rid);
  }

  int remove(int rid, int xid) {
    norm(rid);
    if (rid == xid) {
      return join(nodes[rid].l, nodes[rid].r);
    }
    if (key(xid) < key(rid))
      nodes[rid].l = remove(nodes[rid].l, xid);
    else
      nodes[rid].r = remove(nodes[rid].r, xid);
    norm(rid);
    return rid;
  }

  node_id_t find_le(node_id_t xid, key_t v) {
    if (xid == pNull) return pNull;
    norm(xid);
    int kv = key(xid);
    if (kv == v) return xid;

    if (kv > v) {
      return find_le(nodes[xid].l, v);
    } else {
      auto r = find_le(nodes[xid].r, v);
      return r == pNull ? xid : r;
    }
  }

  node_id_t find_ge(node_id_t xid, key_t v) {
    if (xid == pNull) return pNull;
    norm(xid);
    int kv = key(xid);
    if (kv == v) return xid;

    if (kv > v) {
      auto r = find_ge(nodes[xid].l, v);
      return r == pNull ? xid : r;
    } else {
      return find_ge(nodes[xid].r, v);
    }
  }

  void cut_le(node_id_t xid, key_t splitpos, node_id_t &out_lid, node_id_t &out_rid) {
    if (xid == pNull) return;
    norm(xid);

    if (splitpos < key(xid)) {
      int lid = nodes[xid].l;
      nodes[xid].l = pNull;
      out_rid = join(xid, out_rid);
      cut_le(lid, splitpos, out_lid, out_rid);

    } else {
      int rid = nodes[xid].r;
      nodes[xid].r = pNull;
      out_lid = join(xid, out_lid);
      cut_le(rid, splitpos, out_lid, out_rid);
    }
  }

  void mutate_range(int xid, const range_expl_op_t &f, const mut_op_t &mut_op,
                    const mut_op_t &mut_op_range) {
    if (xid == pNull) return;
    norm(xid);
    auto expl_res = f(xid);

    if (expl_res == TreapRangeExpl::Stop) return;
    if (expl_res == TreapRangeExpl::Contained) {
      mut_op_range(xid);
    } else {
      mut_op(xid);
      mutate_range(nodes[xid].l, f, mut_op, mut_op_range);
      mutate_range(nodes[xid].r, f, mut_op, mut_op_range);
    }
  }
};

struct Primes {
  std::vector<u32> pl;
  std::vector<u32> isc;
  int bound;
  typedef std::vector<std::pair<s64, int> > S64Factors;
  inline bool get_isc(u32 x) { return isc[x >> 5] >> (x & 0x1f) & 1; }
  inline void set_isc(u32 x) { isc[x >> 5] |= 1u << (x & 0x1f); }

  void init_primes(int bound) {
    this->bound = bound;
    if (pl.size() > 0) return;
    isc.clear();
    isc.resize(bound / 32 + 1, 0);
    set_isc(0);
    set_isc(1);
    u32 ub = std::sqrt(bound) + 10;
    for (u32 i = 2; i < bound; ++i)
      if (!get_isc(i)) {
        pl.push_back(i);
        if (i < ub)
          for (u32 j = i * i; j < bound; j += i) set_isc(j);
      }
  }

  S64Factors factor(s64 a) const {
    assert(a > 0);

    S64Factors res;
    REP (i, pl.size()) {
      if (a == 1) break;
      if (1ull * pl[i] * pl[i] > a) break;
      int cnt = 0;
      while (a % pl[i] == 0) a /= pl[i], ++cnt;

      if (cnt) res.push_back(MP((s64)pl[i], cnt));
    }
    if (a > 1) res.push_back(MP(a, 1));
    return res;
  }
};

template <class T> struct PersistentArray {
  typedef int id_t;
  static constexpr id_t kNullId = -1;
  struct Node {
    T data;
    id_t l = kNullId, r = kNullId;
    int mid;
  };
  std::vector<Node> nodes;
  int n;

  id_t init(int n) {
    this->n = n;
    nodes.reserve(2 * n);
    return _build(0, n - 1);
  }

  id_t get_new() {
    id_t p = nodes.size();
    nodes.emplace_back();
    return p;
  }

  id_t _build(int l, int r) {
    id_t curid = get_new();
    if (l == r) {
      return curid;
    }
    int mid = (l + r) / 2 + 1;
    id_t il = _build(l, mid - 1);
    id_t ir = _build(mid, r);
    nodes[curid].l = il;
    nodes[curid].r = ir;
    nodes[curid].mid = mid;
    return curid;
  }

  std::pair<id_t, std::reference_wrapper<T> > mutate(id_t root, int pos) {
    auto nid = get_new();
    nodes[nid] = nodes[root];
    if (nodes[root].l == kNullId) {
      return { nid, nodes[nid].data };
    }

    bool is_r = pos >= nodes[nid].mid;
    auto rec = mutate(is_r ? nodes[nid].r : nodes[nid].l, pos);
    (is_r ? nodes[nid].r : nodes[nid].l) = rec.first;
    return { nid, rec.second };
  }

  T get(id_t root, int pos) {
    if (nodes[root].l == kNullId) {
      return nodes[root].data;
    }

    bool is_r = pos >= nodes[root].mid;
    return get(is_r ? nodes[root].r : nodes[root].l, pos);
  }
};

struct PersistentUJ {
  int init(int n) { return pa.init(n); }

  int root(int version, int a) {
    int x = pa.get(version, a).par;
    return x < 0 ? a : root(version, x);
  }
  struct JoinResult {
    bool changes = false;
    int nversion;
    int nroot;
    int new_size;
    int old_s1;
    int old_s2;
  };

  JoinResult join(int version, int a, int b) {
    a = root(version, a);
    b = root(version, b);
    if (a == b) return JoinResult{ .changes = false };
    int sa = -pa.get(version, a).par;
    int sb = -pa.get(version, b).par;
    if (sa < sb) std::swap(sa, sb), std::swap(a, b);

    {
      auto ub = pa.mutate(version, b);
      ub.second.get().par = a;
      version = ub.first;
    }
    auto ua = pa.mutate(version, a);
    ua.second.get().par -= sb;
    return JoinResult{ .changes = true,
                       .nversion = ua.first,
                       .nroot = a,
                       .new_size = sa + sb,
                       .old_s1 = sa,
                       .old_s2 = sb };
  }

  struct UJData {
    int par = -1;
  };
  PersistentArray<UJData> pa;
};
