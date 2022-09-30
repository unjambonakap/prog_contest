#include <opa_common.h>

using namespace std;
const int maxn = 555555;
const int ytarget = 0;
const int xmin = -10;
const int xmax = 1e9 + 2;
const int ysrc = 1e9 + 2;
const int yceiling = ysrc + 1e8;
const int yfloor = ytarget - 1e8;

struct Tarp;

namespace treap {
std::mt19937 gen(0);
struct Node {
  int id;
  Node *l = nullptr, *r = nullptr;
  int d, cost;
  int dd = 0, dcost = 0;
  Node(int d, int cost) : d(d), cost(cost) {
    OPA_CHECK0(d >= -1);
    id = gen();
  }

  bool normed(){
    return dd == 0 && dcost == 0;

  }
  void norm() {
    d += dd;
    cost += dcost;
    if (l) l->shift(dd, dcost);
    if (r) r->shift(dd, dcost);
    dd = 0;
    dcost = 0;
  }

  void shift(int dd, int dcost) {
    this->dd += dd;
    this->dcost += dcost;
  }
};

Node *join(Node *a, Node *b) {
  if (a == nullptr) return b;
  if (b == nullptr) return a;
  a->norm();
  b->norm();

  if (a->id > b->id) {
    b->l = join(a, b->l);
    return b;
  } else {
    a->r = join(a->r, b);
    return a;
  }
}

void setr(Node *p, Node *x) { p->r = x; }

void setl(Node *p, Node *x) { p->l = x; }

Node *fix(Node *x) {
  if (x == nullptr) return x;
  OPA_CHECK0(x->normed());
  Node *p = x;
  if (x->l != nullptr && x->l->id < x->id) {
    p = x->l;
    p->norm();
    x->l = p->r;
    p->r = x;
  }

  if (x->r != nullptr && x->r->id < x->id) {
    p = x->r;
    p->norm();
    x->r = p->l;
    p->l = x;
  }
  return p;
}

Node *insert1(Node *root, Node *x) {
  if (root == nullptr) return x;
  OPA_CHECK0(x->normed());
  root->norm();
  if (root->d > x->d)
    setl(root, insert1(root->l, x));
  else
    setr(root, insert1(root->r, x));
  return fix(root);
}

Node *remove(Node *root, Node *x) {
  root->norm();
  OPA_CHECK0(x->normed());
  if (root == x) {
    auto xl = x->l;
    auto xr = x->r;
    delete x;
    return join(xl, xr);
  }
  if (x->d < root->d)
    setl(root, remove(root->l, x));
  else
    setr(root, remove(root->r, x));
  return root;
}

Node *max(Node *x) {
  if (x == nullptr) return x;
  x->norm();
  return x->r == nullptr ? x : max(x->r);
}

Node *min(Node *x) {
  if (x == nullptr) return x;
  x->norm();
  return x->l == nullptr ? x : min(x->l);
}

Node *find_le(Node *x, int v) {
  if (x == nullptr) return nullptr;
  x->norm();
  if (x->d == v) return x;

  if (x->d > v) {
    return find_le(x->l, v);
  } else {
    auto r = find_le(x->r, v);
    return r == nullptr ? x : r;
  }
}
Node *find_ge(Node *x, int v) {
  if (x == nullptr) return nullptr;
  x->norm();
  if (x->d == v) return x;

  if (x->d > v) {
    auto r = find_ge(x->l, v);
    return r == nullptr ? x : r;
  } else {
    return find_ge(x->r, v);
  }
}

void cut_le(Node *x, int splitpos, Node *&l, Node *&r) {
  if (x == nullptr) return;
  x->norm();

  if (x->d > splitpos) {
    auto ln = x->l;
    x->l = nullptr;
    r = join(x, r);
    cut_le(ln, splitpos, l, r);

  } else {
    auto rn = x->r;
    x->r = nullptr;
    l = join(l, x);
    cut_le(rn, splitpos, l, r);
  }
}

void dfs(Node *x, std::vector<Node *> &res) {
  if (x == nullptr) return;
  x->norm();
  dfs(x->l, res);
  res.pb(x);
  dfs(x->r, res);
}
void disp(Node *y) {
  std::vector<treap::Node *> lst;
  treap::dfs(y, lst);
  OPA_DISP("Treap ", lst.size());
  for (auto x : lst) OPA_DISP0(x->d, x->cost);
}

Node *find_by_cost_ge(Node *x, int cost) {
  if (x == nullptr) return nullptr;
  x->norm();
  if (x->cost >= cost) {
    auto r = find_by_cost_ge(x->r, cost);
    return r == nullptr ? x : r;
  }
  return find_by_cost_ge(x->l, cost);
}

} // namespace treap

struct TarpLink {
  int xl, xh;
  int dist;
  Tarp *target = nullptr;
  bool operator<(const TarpLink &peer) const { return dist < peer.dist; }
};

struct TarpScore {
  int d0;
  treap::Node *root;
  void init(int d) {
    this->d0 = d;
    root =
      treap::join(new treap::Node(-1, maxn), new treap::Node(d + 5, -maxn));
  }

  void check() {

    OPA_CHECK0(treap::min(root)->d == -1);
    if (treap::max(root)->d != d0 + 5) {
      treap::disp(root);
      OPA_DISP0(d0);
    }
    OPA_CHECK0(treap::max(root)->d == d0 + 5);
  }

  int query(int d) const { return treap::find_le(root, d)->cost; }
  int query_best() const { return query_prev(d0); }
  int query_prev(int d) const { return treap::find_le(root, d)->cost; }

  void insert(treap::Node *n) {
    auto minn = treap::min(n);
    auto maxn = treap::max(n);
    auto qprev = treap::find_le(root, minn->d);
    OPA_CHECK0(qprev != nullptr);
    treap::Node *sl = 0, *sr = 0;
    treap::cut_le(root, minn->d, sl, sr);

    int minc = minn->cost, mind = minn->d;
    int maxc = maxn->cost, maxd = maxn->d;

    n = remove_cost_ge(n, qprev->cost);
    if (mind == qprev->d && minc < qprev->cost) sl = treap::remove(sl, qprev);
    sr = remove_cost_ge(sr, maxn->cost);

    auto minsr = treap::min(sr);
    if (minsr != nullptr && minsr->d == maxd) {
      n = treap::remove(n, maxn);
    }
    root = join(sl, join(n, sr));
  }

  treap::Node *remove_cost_ge(treap::Node *n, int cost) {
    auto qp = treap::find_by_cost_ge(n, cost);
    if (qp != nullptr) {

      treap::Node *il = 0, *ir = 0;
      treap::cut_le(n, qp->d, il, ir);
      release(il);
      n = ir;
    }
    return n;
  }

  void insert1(int d, int score) {
    root = treap::insert1(root, new treap::Node(d, score));
  }

  treap::Node *extract(int d1, int d2) {
    treap::Node *l = 0, *m = 0, *r = 0, *res = 0;
    treap::cut_le(root, d1 - 1, l, m);
    treap::cut_le(m, d2, res, r);
    root = treap::join(l, r);
    return res;
  }

  void release(treap::Node *n) {
    std::vector<treap::Node *> lst;
    treap::dfs(n, lst);
    for (auto &x : lst) delete x;
  }

  void add(int d, int score) { insert(new treap::Node(d, score)); }
};

struct Tarp {
  int xl, xh, y1, y2;
  int tid;
  double c;
  bool downleft;
  bool is_src = false;

  std::vector<TarpLink> uplinks;
  std::vector<TarpLink> downlinks;
  TarpScore score;
  int deg_seen = 0;
  void setup() {
    if (xl > xh) std::swap(xl, xh), std::swap(y1, y2);
    c = 1. * (y2 - y1) / (xh - xl);
    downleft = y1 < y2;
    score.init(xh - xl);
  }
  void set(int xl, int xh, int y1, int y2) {
    this->xl = xl;
    this->xh = xh;
    this->y1 = y1;
    this->y2 = y2;
    setup();
  }

  float y(int x) const { return 1. * (x - xl) * c + y1; }
  int drill_cost(int x) const { return is_src ? 0 : 1 - falling(x); }
  bool falling(int x) const { return downleft ? x == xl : x == xh; }

  int x2dist(int x) const { return downleft ? xh - x : x - xl; }
  int dist2x(int d) const { return downleft ? xh - d : xl + d; }
  int query(int x) { return score.query(x2dist(x)) + drill_cost(x); }

  void finish_links() {
    std::sort(ALL(uplinks));
    // OPA_DISP0(tid);
    // for (auto &x : uplinks) OPA_DISP0(x.target->tid, x.dist, x.xl, x.xh);
  }

  TarpLink buildlink;

  void push(int x, Tarp *t) {

    // if (t != nullptr) OPA_DISP("Push ", x, tid, t->tid);
    buildlink.xh = x;
    if (buildlink.target != nullptr) {
      TarpLink inv = buildlink;
      inv.target = this;
      buildlink.target->downlinks.pb(inv);

      // OPA_DISP0(buildlink.target->tid);
      OPA_CHECK0(buildlink.xl >= xl && buildlink.xh <= xh);
      OPA_CHECK0(buildlink.target->xl <= buildlink.xl);
      OPA_CHECK(buildlink.target->xh >= x, buildlink.target->tid, t->tid, x,
                tid);
      uplinks.pb(buildlink);
    }
    buildlink.xl = buildlink.xh;
    buildlink.target = t;
  }
};

struct Event {
  int x;
  int tid;
  bool operator<(const Event &p) const { return x < p.x; }
};

int xl, xh, n;
Tarp tarps[maxn];
Tarp *t_ceiling;
Tarp *t_floor;
Tarp *t_target;
Tarp *t_src;
int state_x;

struct State {
  int tid;
  State(int tid) : tid(tid) {}

  bool operator<(const State &peer) const {
    const auto &a = tarps[tid];
    const auto &b = tarps[peer.tid];
    bool res = false;
    if (tid == peer.tid)
      res = false;
    else if (a.xl >= b.xl && a.xl <= b.xh) {
      int xa = a.xl - b.xl;
      int ya = a.y1 - b.y1;

      int xb = b.xh - b.xl;
      int yb = b.y2 - b.y1;
      return 1ll * xb * ya - 1ll * yb * xa < 0;
    } else
      res = !(peer < *this);
    // OPA_CHECK(res == a.y(state_x) < b.y(state_x), a.xl, a.xh, a.y1, a.y2,
    // b.xl,
    //          b.xh, b.y1, b.y2);
    // return a.y(state_x) < b.y(state_x);
    return res;
  }
};

void compute(Tarp *x) {
  for (auto &ul : x->uplinks) {
    int s1 = ul.target->x2dist(ul.xl);
    int s2 = ul.target->x2dist(ul.xh);
    if (s2 < s1) std::swap(s2, s1);

    int sl = ul.target->query(ul.xl);
    int sh = ul.target->query(ul.xh);

    OPA_CHECK0(sl >= 0);
    OPA_CHECK0(sh >= 0);
    x->score.add(x->x2dist(ul.xl), sl);
    x->score.check();
    x->score.add(x->x2dist(ul.xh), sh);
    x->score.check();

    if (!ul.target->is_src && ul.target->downleft != x->downleft) {
      continue;
    }

    int high = x->x2dist(ul.target->dist2x(s1));
    auto nodes = ul.target->score.extract(s1, s2);

    if (nodes == nullptr) continue;
    ul.target->score.check();
    auto mx = treap::max(nodes);
    ul.target->score.insert1(mx->d, mx->cost);
    ul.target->score.check();

    nodes->shift(high - s1, 1);
    x->score.insert(nodes);
    OPA_CHECK0(x->score.query_best() >= 0);
  }
  x->score.check();
}

int main(int argc, char **argv) {
  opa::init::opa_init(argc, argv);
  scanf("%d%d%d", &xl, &xh, &n);

  std::vector<Event> events;
  REP (i, n) {
    auto &t = tarps[i];
    scanf("%d%d%d%d", &t.xl, &t.y1, &t.xh, &t.y2);
  }

  t_target = tarps + n++;
  t_src = tarps + n++;
  t_ceiling = tarps + n++;
  t_floor = tarps + n++;
  t_ceiling->set(xmin, xmax, yceiling, yceiling);
  t_floor->set(xmin, xmax, yfloor, yfloor);
  t_src->set(xl, xh, ysrc, ysrc);
  t_target->set(xl, xh, ytarget, ytarget);
  t_src->is_src = true;

  REP (i, n) {
    tarps[i].tid = i;
    tarps[i].setup();
  }

  REP (i, t_src->tid + 1) {
    auto &t = tarps[i];
    Event ev;
    ev.x = t.xl;
    ev.tid = i;
    events.pb(ev);
    ev.x = t.xh;
    events.pb(ev);
  }

  std::set<State> sl;
  sl.insert(State(t_ceiling->tid));
  sl.insert(State(t_floor->tid));

  std::sort(ALL(events));
  for (auto &ev : events) {
    auto &t = tarps[ev.tid];
    bool low = ev.x == t.xl;
    state_x = ev.x;

    // puts("");
    // OPA_DISP0(ev.x, ev.tid, t.y(state_x));
    // for (auto &k : sl) OPA_DISP0(tarps[k.tid].y(state_x));
    State s(ev.tid);
    if (!low) sl.erase(s);
    auto it = sl.lower_bound(s);
    assert(it != sl.begin());
    assert(it != sl.end());
    auto next = &tarps[it->tid];
    auto prev = &tarps[(--it)->tid];

    if (low) {
      prev->push(ev.x, &t);
      t.push(ev.x, next);
      sl.insert(s);

    } else {
      t.push(ev.x, nullptr);
      prev->push(ev.x, next);
    }
  }

  for (auto &lnk : t_src->downlinks) {
    if (lnk.target->downleft) {
      lnk.target->push(lnk.xl, 0);
      lnk.target->push(lnk.xh, 0);
    }
  }

  REP (i, n)
    tarps[i].finish_links();

  std::queue<Tarp *> q;
  q.push(t_floor);
  std::vector<Tarp *> order;
  while (!q.empty()) {
    auto t = q.front();
    q.pop();
    order.pb(t);
    // OPA_DISP0(t->tid, t->xl, t->y1);

    for (auto &uplink : t->uplinks) {
      auto x = uplink.target;
      if (++x->deg_seen == x->downlinks.size()) q.push(x);
    }
  }
  t_src->score.add(0, 0);
  // OPA_DISP0(t_src->score);
  assert(order.size() == n);
  std::reverse(ALL(order));
  assert(order[0] == t_ceiling);
  // assert(order[1] == t_src);
  assert(order.back() == t_floor);

  OPA_TRACE0;
  FOR (i, 2, order.size() - 1) { compute(order[i]); }

  int res = t_target->score.query_best();
  printf("%d\n", res);
  return 0;
}

