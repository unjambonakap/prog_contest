#include <opa_common.h>

using namespace std;
const int maxn = 555;

int _gcd(int a, int b) { return b == 0 ? a : _gcd(b, a % b); }
int gcd(int a, int b) { return _gcd(std::max(a, b), std::min(a, b)); }
// const int V = 32 * 3;
const int V = 32 * 27 * 5 * 7;
const int MAXX = 99;
constexpr int MV = V * MAXX;
// const int V = 3;

int n;

struct BitSet {
  u32 tb[MV / 32+5];
  BitSet() { memset(tb, 0, sizeof(tb)); }

  u32 get(u32 a) { return tb[a / 32] >> (a & 0x1f) & 1; }
  void set(u32 a, u32 i) { tb[a/32] = tb[a/32] | i << (a&0x1f);}
  void do_and(const BitSet &peer) {
    REP (i, MV / 32)
      tb[i] &= peer.tb[i];
  }
};

struct Entry {
  int t0;
  int n0;
  int n;
  OPA_DECL_COUT_OPERATOR2(Entry, a.t0, a.n0, a.n);
  mutable int p = 0;

  void reset() const { p = (n - t0) % n; }

  inline int next() const {
    int v = !(p < n0);
    ++p;
    if (p==n) p=0;
    return v;
  }

  Entry inv() const {
    Entry res;
    res.n = n;
    res.t0 = (t0 + n0) % n;
    res.n0 = n - n0;
    return res;
  }

  int get_nn() const { return n / gcd(n, V); }
};

Entry tb[maxn];

struct ResCnd {
  std::vector<double> tb;
  static ResCnd Ident() {
    ResCnd res;
    res.tb.clear();
    res.tb.resize(V, 1);
    return res;
  }

  void merge(const ResCnd &peer) {
    REP (i, V)
      tb[i] *= peer.tb[i];
  }

  double val() {
    double res = 0;
    REP (i, V)
      res += tb[i];
    res /= V;
    return res;
  }
};

struct Seq {
  Seq(const Entry &e) {
    n = e.get_nn();
    OPA_CHECK0(n < MAXX);
    e.reset();
    int nx = n* V;
    int n0 = e.n0;
    int n1=  e.n - n0;
    int i=0;
    if (n1==0) return;
    if (n0==0){
      memset(b.tb, -1, sizeof(b.tb));
      return;
    }

    while(e.p != 0){
      b.set(i++,  e.next());
    }
    for (; i<nx; ){
      i+=n0;
      REP(j,n1)b.set(i++, 1);
    }
  }

  void merge(const Seq &peer) {
    res.release();
    b.do_and(peer.b);
  }

  const ResCnd &get_res() {
    if (!res) {
      res.reset(new ResCnd());
      REP (i, V) {
        int s = 0;
        REP (j, n)
          s += b.get(i + j * V);
        res->tb.pb(1. * s / n);
      }
    }
    return *res;
  }

  std::unique_ptr<ResCnd> res;
  BitSet b;
  int n;
  int gcdx;
};

struct State {
  std::map<int, std::unique_ptr<Seq> > t2entries;

  double eval(const Entry &e) {
    std::unique_ptr<Seq> s0 = std::make_unique<Seq>(e);
    ResCnd res = ResCnd::Ident();

    for (auto &x : t2entries) {
      if (x.first == s0->n) {
        s0->merge(*x.second);
        res.merge(s0->get_res());
      } else
        res.merge(x.second->get_res());
    }
    if (!t2entries.count(s0->n)) {
      res.merge(s0->get_res());
    }
    return res.val();
  }

  void push(const Entry &e) {
    std::unique_ptr<Seq> s0 = std::make_unique<Seq>(e);
    if (!t2entries.count(s0->n))
      t2entries[s0->n].reset(s0.release());
    else
      t2entries[s0->n]->merge(*s0);
  }
};

int main(int argc, char **argv) {
  opa::init::opa_init(argc, argv);
  scanf("%d", &n);

  REP (i, n) {
    auto &e = tb[i];
    int x, r, g;
    scanf("%d%d%d", &x, &r, &g);
    e.n = r + g;
    e.n0 = r;
    e.t0 = (e.n - x % e.n) % e.n;
  }

  State state;
  REP (i, n) {
    printf("%.12lf\n", state.eval(tb[i].inv()));
    state.push(tb[i]);
  }

  Entry e0;
  e0.n = 1;
  e0.n0 = 0;
  e0.t0 = 0;
  printf("%.12lf\n", state.eval(e0));

  return 0;
}

