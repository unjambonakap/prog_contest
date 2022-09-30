#include <opa/utils/hash.h>
#include <opa_common.h>

using namespace std;

const int maxm = 1e6 + 11;
int n, m;
u64 k;

struct Edge {
  Edge() {}
  Edge(u64 st) : st(st) {}
  int to;
  u64 st, et;
  double prob;
  bool operator<(const Edge &e) const { return st < e.st; }
};

std::vector<Edge> edges[maxm];
int epos[maxm];

struct State {
  int pos;
  int t;
  State(int pos, int t) : pos(pos), t(t) {}
  bool operator==(const State &s) const { return s.pos == pos && t == s.t; }
  bool operator<(const State &s) const { return t < s.t; }
};

namespace std {
template <> struct hash<State> {
  size_t operator()(State const &tt) const {
    return std::hash<std::pair<int, int> >()(std::make_pair(tt.pos, tt.t));
  }
};
} // namespace std

std::unordered_map<State, double> dp;

double go(const State &state) {
  if ((int)k < state.t) return 0;
  if (state.pos == 1) return 1;
  if (dp.count(state)) return dp[state];

  double &r = dp[state];
  r = 0;
  const auto &ex = edges[state.pos];
  int eid = std::lower_bound(ALL(ex), Edge(state.t + 1)) - ex.begin();
  if (eid == ex.size()) return r;
  int neid = eid;
  double next = go(State(state.pos, ex[eid].st + 1));

  while (neid < ex.size() && ex[neid].st == ex[eid].st) {
    State ns(ex[neid].to, ex[neid].et);
    double p = ex[neid].prob;
    r = std::max(r, go(ns) * p + next * (1 - p));
    ++neid;
  }

  r = std::max(r, next);
  return r;
}

int main(int argc, char **argv) {
  opa::init::opa_init(argc, argv);
  scanf("%d%d%lu", &m, &n, &k);
  std::vector<u64> tlist;
  REP (i, m) {
    Edge e;
    int from;
    scanf("%d%d%lu%lu%lf", &from, &e.to, &e.st, &e.et, &e.prob);
    tlist.push_back(e.st);
    tlist.push_back(e.et);

    edges[from].push_back(e);
  }
  std::sort(ALL(tlist));
  tlist.resize(std::unique(ALL(tlist)) - tlist.begin());
  REP (i, n)
    for (auto &e : edges[i]) {
      e.st = std::lower_bound(ALL(tlist), e.st) - tlist.begin();
      e.et = std::lower_bound(ALL(tlist), e.et) - tlist.begin();
      e.st *= 2;
      e.et *= 2;
    }

  k = std::lower_bound(ALL(tlist), k) - tlist.begin();
  k *= 2;
  std::vector<State> reqs;

  REP (i, n)
    sort(ALL(edges[i]));
  REP (i, n)
    for (auto &e : edges[i]){
      reqs.emplace_back(e.to, e.et);
      reqs.emplace_back(i, e.st+1);
    }
  std::sort(ALL(reqs));
  FEV (it, reqs) go(*it);

  memset(epos, -1, sizeof(epos));
  double res = go(State{ 0, -1 });
  printf("%.9lf\n", res);

  return 0;
}
