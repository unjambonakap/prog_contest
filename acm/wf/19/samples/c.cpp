#include <opa_common.h>

using namespace std;

DEFINE_bool(checkit, false, "");
const int maxn = 255555 * 2;
struct HLNode;
const int kSource = 0;
const int kSink = 1;
const int oo = 2e9;

int n;
std::vector<pii> e[maxn];
std::vector<pii> oe[maxn];

HLNode *hl_node[maxn];
int hl_pos[maxn];

int par[maxn];
int par_cost[maxn];
int par_cnt[maxn];
int want[maxn];
int child_size[maxn];

struct SSCnd {
  int from = -1;
  s64 cost;
  void make_invalid() { from = -1; }

  void update(const SSCnd &x) {
    if (x.from == -1) return;
    if (from == -1 || x.cost < cost) cost = x.cost, from = x.from;
  }

  SSCnd recomp(s64 addc) const {
    SSCnd x = *this;
    x.cost += addc;
    return x;
  }

  void reset(const SSCnd &a, const SSCnd &b) {
    *this = a;
    this->update(b);
  }
  OPA_DECL_COUT_OPERATOR2(SSCnd, a.from, a.cost);
};

SSCnd node_sscnd[maxn][2];

struct Cnd {
  std::array<int, 2> ss;
  s64 cost;
  void *owner;
  Cnd() { make_invalid(); }
  Cnd(int a, int b, s64 c) {
    ss[0] = a;
    ss[1] = b;
    cost = c;
  }
  OPA_DECL_COUT_OPERATOR2(Cnd, a.ss, a.cost, a.owner);

  bool valid() const { return ss[0] != -1 && ss[1] != -1; }
  void make_invalid() {
    ss[0] = -1;
    ss[1] = -1;
  }
  void update(const Cnd &a) {
    if (a.valid() && (!valid() || a.cost < cost)) *this = a;
  }

  Cnd sel_best(const Cnd &peer) const {
    Cnd res = *this;
    res.update(peer);
    return res;
  }

  void reset(const Cnd &a, const Cnd &b) {
    make_invalid();
    update(a);
    update(b);
  }

  Cnd &addc(s64 c) {
    cost += c;
    return *this;
  }
  bool operator<(const Cnd &a) const {
    OPA_LT_OP(a, cost, ss[0], ss[1], owner);
  }
};

Cnd make_cnd(const SSCnd &a, const SSCnd &b, int a_sink) {
  if (a_sink) return make_cnd(b, a, 0);
  return Cnd(a.from, b.from, a.cost + b.cost);
}

struct CumSum {
  void init(int n) { data.resize(n + 1); }

  int get(int a) const { return data[a + 1] - data[a]; }
  int get(int a, int b) const { return data[b + 1] - data[a]; }
  void set(int a, int v) { data[a + 1] = v; }
  void compute() {
    data[0] = 0;
    REP (i, data.size() - 1)
      data[i + 1] += data[i];
  }

  std::vector<s64> data;
};

struct BestTracker {

  bool has() const { return stuff.size() > 0; }

  Cnd top() {
    Cnd res = *stuff.begin();
    return res;
  }

  void add(const Cnd &cnd) {
    if (cnd.valid()) stuff.insert(cnd);
  }

  void remove(const Cnd &cnd) {
    if (cnd.valid()) stuff.erase(cnd);
  }

  std::set<Cnd> stuff;
};

BestTracker tracker;

struct SSCndPair {
  SSCnd tb[2];
};

struct UpDownData {
  int child_min_count = 0;
};

struct SegTree {

  struct SegData {
    SSCndPair up, down;
    Cnd best;
    int min_count = 0;
  };
  struct SegNode {
    SegNode *l = nullptr, *r = nullptr;
    SegNode *p = nullptr;
    int T, H;
    s64 base_cost;
    s64 cost0 = 0, costplus = 0, costminus = 0;
    bool has0 = false;
    SSCnd base_cnd[2][2];

    std::array<SegData, 3> dx; // normal, with up inverted, down inverted
    std::array<UpDownData, 2> ud;
    int flow_count = 0;

    Cnd &get_best(int wh) { return dx[wh].best; }
    Cnd &get_final_best(int wh) {
      if (wh == 0) {
        if (flow_count == 0) return get_best(0);
        return flow_count > 0 ? get_best(1) : get_best(2);
      } else {
        return get_best(nwh(wh));
      }
    }

    SSCnd &get_best_up(int wh, int sink) { return dx[wh].up.tb[sink]; }
    SSCnd &get_best_down(int wh, int sink) { return dx[wh].down.tb[sink]; }
    int nfc(int wh) const { return flow_count + (wh == 1 ? 1 : -1); }
    int nwh(int wh) const {
      int x = nfc(wh);
      return x == 0 ? 0 : x > 0 ? 1 : 2;
    }
    SSCnd &get_final_best_up(int wh, int sink) {
      if (wh == 0) {
        if (flow_count == 0) return get_best_up(0, sink);
        return flow_count > 0 ? get_best_up(1, sink) : get_best_up(2, sink);
      } else {
        return get_best_up(nwh(wh), sink);
      }
    }

    SSCnd &get_final_best_down(int wh, int sink) {
      if (wh == 0) {
        if (flow_count == 0) return get_best_down(0, sink);
        return flow_count > 0 ? get_best_down(1, sink) : get_best_down(2, sink);
      } else {
        return get_best_down(nwh(wh), sink);
      }
    }

    s64 get_cost(int wh, int sink) const {
      if (wh == 0) {
        if (sink) {
          s64 x = costminus - costplus;
          if (flow_count > 0)
            x -= cost0;
          else
            x += cost0;
          return x;
        } else {
          s64 x = costplus - costminus;
          if (flow_count < 0)
            x -= cost0;
          else
            x += cost0;
          return x;
        }
      } else {
        s64 x = costplus - costminus;
        int u = nfc(wh);
        if (sink) x = -x, u = -u;
        if (u > 0)
          x += cost0;
        else
          x -= cost0;
        return x;
      }
    }

    void update(int a, int sink, const SSCnd &cnd) {
      if (a < T || a - 1 > H) return;
      this->normalize(false);
      if (l == nullptr) {
        // OPA_DISP("update >> ", sink, cnd, a, T, H);
        base_cnd[a == T][sink] = cnd;
      } else {
        l->update(a, sink, cnd);
        r->update(a, sink, cnd);
      }
      recompute();
    }

    void update_best_ud() {

      REP (sink, 2) {
        REP (wh, 3) {
          // OPA_DISP("on >> ", wh, get_cost(wh, sink), get_cost(wh, sink^1));
          // if (wh!=0) continue;
          get_best_up(wh, sink).make_invalid();
          get_best_down(wh, sink).make_invalid();

          REP (f, 2) {
            auto &cx = base_cnd[f][sink];
            if (f) {
              get_best_up(wh, sink).update(cx);
              get_best_down(wh, sink).update(cx.recomp(get_cost(wh, sink ^ 1)));
            } else {
              get_best_down(wh, sink).update(cx);
              get_best_up(wh, sink).update(cx.recomp(get_cost(wh, sink)));
            }
            // OPA_DISP0(a, T, f, sink, cx);
          }
        }
      }
    }

    void mark_path(bool a_sink, int a, int b) {
      if (b <= T) return;
      if (a > H) return;

      if (a <= T && H < b) {
        flow_count += OPA_BITSIGN(a_sink);
        normalize(false);

      } else {
        normalize(false);
        l->mark_path(a_sink, a, b);
        r->mark_path(a_sink, a, b);
      }
      if (0) {
        puts("");
        OPA_DISP("On mark path ", a_sink, a, b, T, H, flow_count);
      }
      recompute();

      if (0) {
        OPA_DISP0(a, b, T, H, flow_count, get_cost(0, 0), get_cost(0, 1));
        // OPA_DISP0(ud[0].child_min_count, ud[1].child_min_count);
        // OPA_DISP0(cost0, costplus, costminus, base_cost);
        // OPA_DISP0(get_best_up(0, 0), get_best_up(0, 1));
        // OPA_DISP0(get_best_down(0, 0), get_best_down(0, 1));
        // OPA_DISP0(get_best_up(2, 0), get_best_up(2, 1));
        // OPA_DISP0(get_best_down(2, 0), get_best_down(2, 1));
        REP (f, 3)
          OPA_DISP0(f, get_best(f));
        if (l) {
          OPA_DISP0(l->flow_count, r->flow_count);
          OPA_DISP0(l->ud[0].child_min_count, l->ud[1].child_min_count);
          OPA_DISP0(r->ud[0].child_min_count, r->ud[1].child_min_count);
          OPA_DISP0(l->cost0, l->costminus, l->costplus);
          OPA_DISP0(r->cost0, r->costminus, r->costplus);
          REP (f, 3)
            OPA_DISP0(l->get_final_best(f), r->get_final_best(f));
          REP (f, 3)
            OPA_DISP0(l->get_final_best_up(f, 0), l->get_final_best_up(f, 1));
          REP (f, 3)
            OPA_DISP0(r->get_final_best_up(f, 0), r->get_final_best_up(f, 1));
          REP (f, 3)
            OPA_DISP0(r->get_final_best_down(f, 0), r->get_final_best_up(f, 1));
          REP (f, 3)
            OPA_DISP0(l->get_cost(f, 0), l->get_cost(f, 1));
          REP (f, 3)
            OPA_DISP0(r->get_cost(f, 0), r->get_cost(f, 1));
        }
      }
    }

    void recompute() {
      cost0 = 0;
      costplus = 0;
      costminus = 0;
      has0 = false;

      if (!l) {

        if (flow_count > 0)
          costplus += base_cost;
        else if (flow_count < 0)
          costminus += base_cost;
        else
          cost0 += base_cost, has0 = true;

        update_best_ud();
      } else {

        ud[0].child_min_count = oo;
        ud[1].child_min_count = oo;

        for (auto &u : { l, r }) {
          REP (f, 2) {
            int v =
              u->ud[f].child_min_count + u->flow_count * OPA_BITSIGN(f ^ 1);
            if (v > 0) {
              ud[f].child_min_count = std::min(ud[f].child_min_count, v);
            }
          }
          if (u->has0 && u->flow_count > 0)
            ud[0].child_min_count = u->flow_count;
          if (u->has0 && u->flow_count < 0)
            ud[1].child_min_count = -u->flow_count;

          if (u->flow_count == 0)
            cost0 += u->cost0;
          else if (u->flow_count > 0)
            costplus += u->cost0;
          else
            costminus += u->cost0;

          costplus += u->costplus;
          costminus += u->costminus;
          has0 |= u->flow_count == 0 && u->has0;
        }

        // puts("");
        // OPA_DISP0(T, H, flow_count);
        // OPA_DISP0(ud[0].child_min_count, ud[1].child_min_count,
        // l->flow_count,
        //          r->flow_count);
        // OPA_DISP0(l->get_cost(0, 0), r->get_cost(0, 0));
        // OPA_DISP0(l->get_cost(0, 1), r->get_cost(0, 1));
        REP (wh, 3) {
          // if (wh != 0) continue;

          REP (sink, 2) {

            get_best_up(wh, sink).reset(
              l->get_final_best_up(wh, sink),
              r->get_final_best_up(wh, sink).recomp(l->get_cost(wh, sink)));
            get_best_down(wh, sink).reset(
              r->get_final_best_down(wh, sink),
              l->get_final_best_down(wh, sink).recomp(
                r->get_cost(wh, sink ^ 1)));

            // OPA_DISP0(sink, l->get_cost(wh, sink), r->get_cost(wh, sink ^ 1),
            // l->cost0, l->costplus, l->costminus, l->flow_count);
            // OPA_DISP0(r->get_best_down(wh, sink), r->get_best_up(wh, sink));
            // OPA_DISP0(l->get_best_down(wh, sink), l->get_best_up(wh, sink));
            // puts("xxxxxxxxxxxxxx");
          }
          // OPA_DISP0(get_best_up(wh, kSource), get_best_up(wh, kSink));
          // puts("");
        }
      }
      compute_best();
    }

    void compute_best() {
      // OPA_DISP("Best of ", T, H, flow_count);
      if (l) {
        // OPA_DISP0(l->get_cost(0, 0), l->get_cost(0, 1));
        // OPA_DISP0(r->get_cost(0, 0), r->get_cost(0, 1));
        // OPA_DISP0(l->ud[0].child_min_count, r->ud[0].child_min_count);
        // OPA_DISP0(l->ud[1].child_min_count, r->ud[1].child_min_count);
        // OPA_DISP0(l->flow_count, r->flow_count);
      }
      REP (wh, 3) {
        // if (wh != 0) continue;
        get_best(wh).make_invalid();
        if (l) {
          REP (sink, 2) {
            get_best(wh).update(make_cnd(l->get_final_best_down(wh, sink),
                                         r->get_final_best_up(wh, sink ^ 1),
                                         sink));
            // OPA_DISP0(wh, sink, l->get_final_best_down(wh, sink),
            // r->get_final_best_up(wh, sink^1), get_best(wh));
          }
          // OPA_DISP("inter >> ", get_best(wh), l->get_best(wh),
          // r->get_best(wh));
          get_best(wh).update(l->get_final_best(wh));
          get_best(wh).update(r->get_final_best(wh));
        }
        REP (sink, 2) {
          get_best(wh).update(
            make_cnd(get_best_up(wh, sink), get_best_up(wh, sink ^ 1), sink));
          // OPA_DISP("now > ", get_best(wh), sink, get_best_up(wh, sink),
          // get_best_up(wh, sink^1));
        }
        // OPA_DISP0(wh, get_best(wh));
      }
      if (l) {
        for (auto &u : { l, r }) {
          if (u->flow_count > 0)
            get_best(0).update(u->get_best(1));
          else if (u->flow_count < 0)
            get_best(0).update(u->get_best(2));
        }
      }
      // OPA_DISP0(get_best(0), get_best_up(0, 0), get_best_up(0, 1),
      //          get_best_down(0, 0), get_best_down(0, 1));
    }

    void normalize(bool recomp = true) {
      if (l && flow_count != 0) {
        // OPA_DISP("Child min >> ", T, H, flow_count, ud[0].child_min_count,
        //         ud[1].child_min_count);
        l->flow_count += flow_count;
        r->flow_count += flow_count;
        if (flow_count == ud[1].child_min_count ||
            -flow_count == ud[0].child_min_count) {
          // OPA_DISP0("normalize down");
          l->normalize();
          r->normalize();
        }
        flow_count = 0;
      }
      if (recomp) recompute();
    }
  };

  SegNode *root() { return &nodes[0]; }
  void init(int n, int *tb) { build(0, n - 1, tb); }

  SegNode *build(int T, int H, int *tb) {
    nodes.emplace_back();
    SegNode *cur = &nodes.back();
    cur->T = T;
    cur->H = H;
    cur->has0 = true;

    int M = (T + H) / 2;
    cur->base_cost = tb[T];
    cur->cost0 = cur->base_cost;

    if (T == H) {
      return cur;
    }

    cur->l = build(T, M, tb);
    cur->l->p = cur;
    cur->r = build(M + 1, H, tb);
    cur->r->p = cur;
    cur->recompute();
    cur->base_cost = cur->l->base_cost + cur->r->base_cost;

    return cur;
  }

  void update(int a, int sink, const SSCnd &cnd) {
    root()->update(a, sink, cnd);
  }

  std::deque<SegNode> nodes;
};

struct HLNode {
  int root;
  std::deque<HLNode> children;
  std::vector<pii> heavy_path;
  SegTree path_tree;
  Cnd old_best;
  std::vector<std::vector<HLNode *> > path_children;
  int depth = 0;

  const SSCnd get_sscnd(int sink) {
    return path_tree.root()->get_best_up(0, sink);
  }

  void build(int a) {
    root = a;

    heavy_path.emplace_back(a, 0);
    int cur = a;
    while (true) {
      pii heavy = { -1, -1 };
      hl_node[cur] = this;
      hl_pos[cur] = heavy_path.size() - 1;
      path_children.emplace_back();

      std::vector<pii> sz_and_eid;
      REP (i, e[cur].size()) {
        auto &x = e[cur][i];
        sz_and_eid.emplace_back(child_size[x.first], i);
      }
      std::sort(ALL(sz_and_eid), std::greater<pii>());
      // if (child_size[x.first] > child_size[cur] / 2) {
      //  heavy = e[cur][i];
      //  std::swap(e[cur][i], e[cur].back());
      //  e[cur].pop_back();
      //  --i;

      //} else {
      //  children.emplace_back();
      //  auto &child = children.back();
      //  child.depth = depth + 1;
      //  child.build(x.first);
      //  path_children.back().push_back(&child);
      //}
      // if (heavy.first == -1) break;
      if (sz_and_eid.empty()) break;
      heavy = e[cur][sz_and_eid[0].second];
      FOR (i, 1, sz_and_eid.size()) {
        children.emplace_back();
        auto &child = children.back();
        child.depth = depth + 1;
        child.build(e[cur][sz_and_eid[i].second].first);
        path_children.back().push_back(&child);
      }

      heavy_path.push_back(heavy);
      cur = heavy.first;
    }
    // OPA_DISP0(heavy_path);

    std::vector<int> costs;
    FOR (i, 1, heavy_path.size())
      costs.push_back(heavy_path[i].second);
    if (costs.size() == 0) costs = { 0 };
    path_tree.init(costs.size(), costs.data());

    for (auto &child : children) {
      REP (sink, 2) {
        SSCnd x = child.get_sscnd(sink);
        if (x.from == -1) continue;
        path_tree.update(hl_pos[par[child.root]], sink,
                         x.recomp(par_cost[child.root]));
      }
    }

    REP (i, heavy_path.size()) {
      int x = heavy_path[i].first;
      SSCnd u;
      u.cost = 0;
      u.from = x;

      if (want[x] > 0) {
        node_sscnd[x][kSink] = u;
        path_tree.update(i, kSink, u);
      }
      if (want[x] < 0) {
        node_sscnd[x][kSource] = u;
        path_tree.update(i, kSource, u);
      }
    }
    update_tracker();
  }

  void update_tracker() {
    tracker.remove(old_best);
    old_best = path_tree.root()->get_best(0);
    old_best.owner = this;
    // OPA_DISP("adding to tracker", path_tree.root()->get_best(0));
    tracker.add(old_best);
  }

  int get_par_cost(int a, int sink) const {
    int mul = OPA_BITSIGN(par_cnt[a] == 0 ? 1 : (par_cnt[a] > 0) ^ sink);
    return par_cost[a] * mul;
  }

  void update(int pos, int sink) {
    SSCnd nbest = node_sscnd[heavy_path[pos].first][sink];
    for (auto &child : path_children[pos]) {
      // OPA_DISP0(pos, child->root, sink, par_cnt[child->root],
      // get_par_cost(child->root, sink));
      nbest.update(
        child->get_sscnd(sink).recomp(get_par_cost(child->root, sink)));
    }
    path_tree.update(pos, sink, nbest);
    update_tracker();
    int u = this->root;
    int nu = par[u];
    // OPA_DISP("Res update >>> ", u, pos, sink, nbest);
    if (nu != -1) {
      hl_node[nu]->update(hl_pos[nu], sink);
    }
  }

  void mark_path(bool a_sink, int a) {
    par_cnt[this->root] += OPA_BITSIGN(a_sink ^ 1);
    return mark_path(1 ^ a_sink, 0, a);
  }

  void mark_path(bool a_sink, int a, int b) {
    if (b < a) return mark_path(!a_sink, b, a);
    if (a == b) return;
    // OPA_DISP("mark path ", a_sink, a, b);
    path_tree.root()->mark_path(a_sink, a, b);
    // update_tracker();
  }
};

int dfs_make_binary(int a, int p = -1) {
  // OPA_DISP("edge ", p, a, n);
  par[a] = p;
  int sz = 1;
  std::vector<pii> children;
  for (auto &x : oe[a]) {
    if (e[x.first].size() > 0) {
      continue;
    }
    children.push_back(x);
  }

  while (children.size() + (want[a] != 0) > 2) {
    std::vector<pii> rem;
    REP (i, children.size() / 2) {
      int cur = n++;
      want[cur] = 0;
      OPA_CHECK0(n < maxn);
      oe[cur].clear();
      e[cur].clear();
      oe[cur].emplace_back(children[2 * i]);
      oe[cur].emplace_back(children[2 * i + 1]);
      // OPA_DISP0(cur, oe[cur]);
      rem.emplace_back(cur, 0);
    }
    if (children.size() & 1) rem.push_back(children.back());
    children = rem;
  }

  e[a].clear();
  for (auto &x : children) {
    // OPA_DISP("Edgec", a, x);
    par_cost[x.first] = x.second;
    par_cnt[x.first] = 0;
    e[a].push_back(x);
    sz += dfs_make_binary(x.first, a);
  }
  // OPA_DISP0(a, e[a]);
  child_size[a] = sz;
  return sz;
}

u64 solve() {
  u64 res = 0;
  REP (i, n)
    e[i].clear();
  dfs_make_binary(0);
  HLNode root;
  REP (i, n)
    REP (f, 2)
      node_sscnd[i][f].make_invalid();
  root.build(0);

  int roundid = 0;
  while (tracker.has()) {
    Cnd best = tracker.top();
    ++roundid;
    // if (roundid >= 4) break;


    // out(want, n);
    int s = best.ss[kSource];
    int t = best.ss[kSink];

    if (0) {
      puts("");
      puts("");
      puts("====================");
      OPA_DISP("Got kappa ", roundid, best.ss, best.cost, want[s], want[t], s, t);
    }
    int cnt = std::min(-want[s], want[t]);
    OPA_CHECK0(cnt > 0);
    cnt = 1;

    want[s] += cnt;
    want[t] -= cnt;
    // OPA_DISP0(want[s], want[t]);
    res += 1ull * best.cost * cnt;
    int os = s;
    int ot = t;
    if (want[s] == 0) {
      node_sscnd[s][kSource] = SSCnd();
    }

    if (want[t] == 0) {
      node_sscnd[t][kSink] = SSCnd();
      // OPA_DISP("updating ", hl_pos[t]);
    }
    while (hl_node[s]->depth != hl_node[t]->depth) {
      if (hl_node[s]->depth < hl_node[t]->depth) {
        hl_node[t]->mark_path(kSink, hl_pos[t]);
        t = par[hl_node[t]->root];
      } else {
        hl_node[s]->mark_path(kSource, hl_pos[s]);
        s = par[hl_node[s]->root];
      }
    }
    while (hl_node[s] != hl_node[t]) {
      hl_node[t]->mark_path(kSink, hl_pos[t]);
      t = par[hl_node[t]->root];
      hl_node[s]->mark_path(kSource, hl_pos[s]);
      s = par[hl_node[s]->root];
    }
    // OPA_DISP("mark path", hl_pos[s], hl_pos[t]);
    hl_node[t]->mark_path(kSource, hl_pos[s], hl_pos[t]);

    REP (f, 2) {
      // OPA_DISP("Updating here kappa", f, os, ot, hl_node[os], hl_node[ot]);
      hl_node[os]->update(hl_pos[os], f);
      hl_node[ot]->update(hl_pos[ot], f);
    }
  }

  return res;
}

namespace slow {
int to[maxn];
int from[maxn];
int prev[maxn];
int last[maxn];
int cnt[maxn];
int cost[maxn];
int ne;
int want2[maxn];
int vis[maxn];
int vcost[maxn];
int epar[maxn];

void adde(int a, int b, int c) {
  int i = ne++;
  to[i] = b;
  from[i] = a;
  prev[i] = last[a];
  last[a] = i;
  cnt[i] = 0;
  cost[i] = c;
  if (a < b) adde(b, a, c);
}

u64 solve() {
  ne = 0;
  u64 res = 0;
  REP (i, n)
    last[i] = -1;
  REP (i, n) {
    // OPA_DISP0(i, oe[i]);
    for (auto &e : oe[i]) {
      if (i < e.first) adde(i, e.first, e.second);
    }
  }
  REP (i, n)
    want2[i] = want[i];

  int visid = 0;
  while (1) {
    ++visid;
    std::priority_queue<pii> q;
    bool fd = false;
    REP (i, n) {
      vcost[i] = oo;
      if (want2[i] < 0) {
        q.emplace(0, i);
        vcost[i] = 0;
      } else if (want2[i] > 0)
        fd = true;

      epar[i] = -1;
    }

    if (!fd) break;

    fd = false;
    while (!q.empty()) {
      pii x = q.top();
      q.pop();
      x.first = -x.first;
      int a = x.second;
      if (vcost[a] != x.first) continue;
      // OPA_DISP0(x);

      if (want2[a] > 0) {
        res += x.first;
        OPA_DISP0(x.first, a);
        --want2[a];
        while (epar[a] != -1) {
          int e = epar[a];
          cnt[e]++;
          cnt[e ^ 1]--;
          a = from[e];
        }
        OPA_DISP0(a);
        puts("");
        ++want2[a];
        fd = true;
        break;
      }

      for (int e = last[a]; e != -1; e = prev[e]) {
        int b = to[e];
        int ce = cost[e];
        if (cnt[e] < 0) ce *= -1;
        int nc = x.first + ce;
        // OPA_DISP0(a, b, nc, vcost[b]);
        if (nc < vcost[b]) {
          q.emplace(-nc, b);
          vcost[b] = nc;
          epar[b] = e;
        }
      }
    }
    OPA_CHECK0(fd);
  }

  return res;
}
} // namespace slow

void checkit() {
  srand(0);
  FOR (nn, 4, 10) {
    REP (i, 100000) {
      n = nn;
      int s1 = 0, s2 = 0;
      REP (i, n) {
        oe[i].clear(), want[i] = rand() % 10 - 5;
        if (want[i] < 0)
          s1 += -want[i];
        else
          s2 += want[i];
      }
      if (s2 > s1) continue;

      REP (i, n - 1) {
        int a = i + 1;
        int b = rand() % (i + 1);
        int c = rand() % 10;
        oe[a].emplace_back(b, c);
        oe[b].emplace_back(a, c);
      }
      // if (nn != 8 || i != 0x50b0) continue;
      // if (nn != 4 || i != 0x57) continue;

      REP (i, n)
        OPA_DISP0(i, oe[i], want[i]);
      s64 a2 = slow::solve();
      s64 a1 = solve();
      OPA_DISP0(nn, i, a1, a2);
      OPA_CHECK_EQ0(a1, a2);
    }
  }
}

int main(int argc, char **argv) {
  opa::init::opa_init(argc, argv);
  if (FLAGS_checkit) {
    checkit();
    return 0;
  }
  scanf("%d", &n);

  REP (i, n - 1) {
    int u, v, c;
    scanf("%d%d%d", &u, &v, &c);
    --u;
    --v;
    oe[u].emplace_back(v, c);
    oe[v].emplace_back(u, c);
  }

  REP (i, n) {
    int a, b;
    scanf("%d%d", &a, &b);
    want[i] = b - a;
    // OPA_DISP0(want[i], a, b);
  }
  u64 res = solve();
  REP (i, n)
    OPA_CHECK0(want[i] <= 0);
  printf("%lu\n", res);

  return 0;
}
