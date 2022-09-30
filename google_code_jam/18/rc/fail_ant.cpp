#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
//#include <ext/hash_map>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <functional>
#include <random>
#include <unordered_map>
#include <unordered_set>

#ifndef DEBUG
#define DEBUG_PRINT 0
#else
#define DEBUG_PRINT 1
#endif

// clang-format off
#define OPA_XSTR(x) OPA_STR(x)
#define OPA_STR(x) #x

#define VA_NUM_ARGS_IMPL(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...) N
#define VA_NUM_ARGS(...)                                                       \
  VA_NUM_ARGS_IMPL(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
#define OPA_DISPATCH(func, ...) OPA_DISPATCH_(func, VA_NUM_ARGS(__VA_ARGS__))
#define OPA_DISPATCH_(func, nargs) OPA_DISPATCH__(func, nargs)
#define OPA_DISPATCH__(func, nargs) func##nargs

#if DEBUG
#define OPA_DISP(msg, ...)                                                     \
  (std::cout << msg << ": " << RAW_OPA_DISP_VARS(__VA_ARGS__) << std::endl)
#define OPA_DISP0(...) OPA_DISP_VARS(__VA_ARGS__)
#else
#define OPA_DISP(msg, ...)                                                     \
  
#define OPA_DISP0(...)
#endif


#define _OPA_DISP_VAR1(a) #a << "=" << (a) << ","
#define _OPA_DISP_VAR2(a, b) _OPA_DISP_VAR1(a) << _OPA_DISP_VAR1(b)
#define _OPA_DISP_VAR3(a, b, c) _OPA_DISP_VAR2(a, b) << _OPA_DISP_VAR1(c)
#define _OPA_DISP_VAR4(a, b, c, d) _OPA_DISP_VAR3(a, b, c) << _OPA_DISP_VAR1(d)
#define _OPA_DISP_VAR5(a, b, c, d, e)                                          \
  _OPA_DISP_VAR4(a, b, c, d) << _OPA_DISP_VAR1(e)
#define _OPA_DISP_VAR6(a, b, c, d, e, f)                                       \
  _OPA_DISP_VAR5(a, b, c, d, e) << _OPA_DISP_VAR1(f)
#define _OPA_DISP_VAR7(a, b, c, d, e, f, g)                                    \
  _OPA_DISP_VAR6(a, b, c, d, e, f) << _OPA_DISP_VAR1(g)
#define _OPA_DISP_VAR8(a, b, c, d, e, f, g, h)                                 \
  _OPA_DISP_VAR7(a, b, c, d, e, f, g) << _OPA_DISP_VAR1(h)
#define _OPA_DISP_VAR9(a, b, c, d, e, f, g, h, i)                              \
  _OPA_DISP_VAR8(a, b, c, d, e, f, g, h) << _OPA_DISP_VAR1(i)
#define _OPA_DISP_VAR10(a, b, c, d, e, f, g, h, i, j)                          \
  _OPA_DISP_VAR9(a, b, c, d, e, f, g, h, i) << _OPA_DISP_VAR1(j)

#define RAW_OPA_DISP_VARS(...)                                                 \
  std::hex << std::showbase                                                    \
           << OPA_DISPATCH(_OPA_DISP_VAR, __VA_ARGS__)(__VA_ARGS__)

#define OPA_DISP_VARS(...)                                                     \
  (std::cout << RAW_OPA_DISP_VARS(__VA_ARGS__) << std::endl)

#define OPA_DISP_VARSERR(...)                                                  \
  (std::cerr << RAW_OPA_DISP_VARS(__VA_ARGS__) << std::endl)
#define OPA_DISPERR(msg, ...)                                                  \
  (std::cerr << msg << ": " << RAW_OPA_DISP_VARS(__VA_ARGS__) << std::endl)
#define OPA_DISP0ERR(...) OPA_DISP_VARSERR(__VA_ARGS__)

#define OPA_DISPL0(...)                                                        \
  (std::cout << OPA_LINE_INFO << ": " << RAW_OPA_DISP_VARS(__VA_ARGS__)        \
             << std::endl)
#define OPA_DISPL(msg, ...)                                                    \
  (std::cout << OPA_LINE_INFO << "msg:" << msg << ": "                         \
             << RAW_OPA_DISP_VARS(__VA_ARGS__) << std::endl)

#define OPA_STREAM_STR(a)                                                      \
  ((static_cast<std::ostringstream &>(std::ostringstream() << a)).str())

#define OPA_DISP_VARS1(a) (std::cout << _OPA_DISP_VAR1(a) << std::endl)
#define OPA_DISP_VARS2(a, b) (std::cout << _OPA_DISP_VAR2(a, b) << std::endl)
#define OPA_DISP_VARS3(a, b, c)                                                \
  (std::cout << _OPA_DISP_VAR3(a, b, c) << std::endl)
#define OPA_DISP_VARS4(a, b, c, d)                                             \
  (std::cout << _OPA_DISP_VAR4(a, b, c, d) << std::endl)
#define OPA_DISP_VARS5(a, b, c, d, e)                                          \
  (std::cout << _OPA_DISP_VAR5(a, b, c, d, e) << std::endl)
#define OPA_DISP_VARS6(a, b, c, d, e, f)                                       \
  (std::cout << _OPA_DISP_VAR6(a, b, c, d, e, f) << std::endl)
#define OPA_DISP_VARS7(a, b, c, d, e, f, g)                                    \
  (std::cout << _OPA_DISP_VAR7(a, b, c, d, e, f, g) << std::endl)
#define OPA_DISP_VARS8(a, b, c, d, e, f, g, h)                                 \
  (std::cout << _OPA_DISP_VAR8(a, b, c, d, e, f, g, h) << std::endl)
#define OPA_DISP_VARS9(a, b, c, d, e, f, g, h, i)                              \
  (std::cout << _OPA_DISP_VAR9(a, b, c, d, e, f, g, h, i) << std::endl)
#define OPA_DISP_VARS10(a, b, c, d, e, f, g, h, i, j)                          \
  (std::cout << _OPA_DISP_VAR10(a, b, c, d, e, f, g, h, i, j) << std::endl)
#define OPA_DISP_STR(...) (OPA_STREAM_STR(RAW_OPA_DISP_VARS(__VA_ARGS__)))


#define REP(i,n) for(int i = 0; i < int(n); ++i)
#define REPV(i, n) for (int i = (n) - 1; (int)i >= 0; --i)
#define FOR(i, a, b) for(int i = (int)(a); i < (int)(b); ++i)

#define FE(i,t) for (__typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (__typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

#define two(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()


#define pb push_back
#define ST first
#define ND second
#define MP(x,y) std::make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef std::pair<int,int> pii;
typedef std::vector<int> vi;
typedef std::vector<std::string> vs;
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef signed long long s64;
typedef unsigned long long u64;


namespace std {
template <class T1, class T2>
std::ostream &operator<<(std::ostream &os, const std::pair<T1, T2> &a) {
  os << "(";
  os << a.ST << ", " << a.ND;
  os << ")";
  return os;
}

template <class T, class L>
std::ostream &operator<<(std::ostream &os, const std::unordered_set<T, L> &a) {
  os << "(";
  for (auto &x : a) os << x << ",";
  os << ")";
  return os;
}

template <class A, class B, class L>
std::ostream &operator<<(std::ostream &os,
                         const std::unordered_map<A, B, L> &a) {
  os << "(";
  for (auto &x : a) os << x << ",";
  os << ")";
  return os;
}

template <std::size_t N, typename... Args> class Opa_os_tuple_pipe {
public:
  static std::ostream &os_pipe_tuple(std::ostream &os,
                                     const std::tuple<Args...> &a) {
    Opa_os_tuple_pipe<N - 1, Args...>::os_pipe_tuple(os, a);
    os << "," << std::get<N>(a);
    return os;
  }
};

template <typename... Args> class Opa_os_tuple_pipe<0, Args...> {
public:
  static std::ostream &os_pipe_tuple(std::ostream &os,
                                     const std::tuple<Args...> &a) {
    os << std::get<0>(a);
    return os;
  }
};

template <typename... Args>
std::ostream &operator<<(std::ostream &os, const std::tuple<Args...> &a) {
  os << "<";
  Opa_os_tuple_pipe<sizeof...(Args) - 1, Args...>::os_pipe_tuple(os, a);
  os << ">";
  return os;
}

template <class T>
std::ostream &operator<<(std::ostream &os, const std::initializer_list<T> &a) {
  os << "(";
  for (auto &x : a) os << x << ",";
  os << ")";
  return os;
}

template <class T, size_t N>
std::ostream &operator<<(std::ostream &os, const std::array<T, N> &a) {
  os << "(";
  for (auto &x : a) os << x << ",";
  os << ")";
  return os;
}

template <class T, class L>
std::ostream &operator<<(std::ostream &os, const std::set<T, L> &a) {
  os << "(";
  for (auto &x : a) os << x << ",";
  os << ")";
  return os;
}

template <class A, class B, class L>
std::ostream &operator<<(std::ostream &os, const std::map<A, B, L> &a) {
  os << "(";
  for (auto &x : a) os << x << ",";
  os << ")";
  return os;
}

template <class T>
std::ostream &operator<<(std::ostream &os, const std::deque<T> &a) {
  os << "(";
  REP (i, a.size())
    os << a[i] << (i == a.size() - 1 ? "" : ",");
  os << ")";
  return os;
}

template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &a) {
  os << "(";
  REP (i, a.size())
    os << a[i] << (i == a.size() - 1 ? "" : ",");
  os << ")";
  return os;
}

template <class A, class B>
std::pair<A, B> operator+(const std::pair<A, B> &a, const std::pair<A, B> &b) {
  return MP(a.ST + b.ST, a.ND + b.ND);
}

template <class A, class B>
std::pair<A, B> operator-(const std::pair<A, B> &a, const std::pair<A, B> &b) {
  return MP(a.ST - b.ST, a.ND - b.ND);
}
}


template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){if (!DEBUG_PRINT) return ;REP(i, n)std::cout<<t[i]<<" "; std::cout<<std::endl;}
template<class T> void out(const std::vector<T>& t, int n=-1){ if (!DEBUG_PRINT) return; for (int i=0; i<(n==-1?t.size():n); ++i) std::cout<<t[i]<<" "; std::cout<<std::endl;
}
inline int count_bit(int n){return (n==0)?0:1+count_bit(n&(n-1));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(std::string s){int a; std::istringstream(s)>>a; return a;}
std::string toStr(int a){std::ostringstream os; os<<a; return os.str();}

// clang-format on

namespace treap {
std::mt19937 gen(0);
struct Node {
  int id;
  Node *l = nullptr, *r = nullptr;
  int d;
  int dd = 0;
  s64 cost = 0, dcost = 0;
  Node(int d, s64 cost) : d(d), cost(cost) { id = gen(); }

  bool normed() { return dd == 0 && dcost == 0; }
  void norm() {
    d += dd;
    cost += dcost;
    if (l) l->shift(dd, dcost);
    if (r) r->shift(dd, dcost);
    dd = 0;
    dcost = 0;
  }

  void shift(int dd, s64 dcost) {
    this->dd += dd;
    this->dcost += dcost;
  }
};

Node *join(Node *l, Node *r) {
  if (l == nullptr) return r;
  if (r == nullptr) return l;
  l->norm();
  r->norm();

  if (l->id > r->id) {
    r->l = join(l, r->l);
    return r;
  } else {
    l->r = join(l->r, r);
    return l;
  }
}

void setr(Node *p, Node *x) { p->r = x; }

void setl(Node *p, Node *x) { p->l = x; }

Node *fix(Node *x) {
  if (x == nullptr) return x;
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
  root->norm();
  if (root->d > x->d)
    setl(root, insert1(root->l, x));
  else
    setr(root, insert1(root->r, x));
  return fix(root);
}

Node *remove(Node *root, Node *x) {
  root->norm();
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

Node *prev(Node *root, Node *x) { return find_le(root, x->d - 1); }

Node *next(Node *root, Node *x) { return find_ge(root, x->d + 1); }

enum SearchRes {
  This,
  Left,
  Right,
};

Node *search(Node *x, const std::function<SearchRes(Node *)> &f,
             bool lower_bound) {
  Node *last = nullptr;
  while (x != nullptr) {
    x->norm();
    auto res = f(x);
    if (res == SearchRes::This)
      return x;
    else if (res == SearchRes::Left) {
      if (!lower_bound) last = x;
      x = x->l;
    } else {
      if (lower_bound) last = x;
      x = x->r;
    }
  }
  return last;
}

void _cut_le(Node *x, int splitpos, Node *&l, Node *&r) {
  if (x == nullptr) return;
  x->norm();

  if (x->d > splitpos) {
    auto ln = x->l;
    x->l = nullptr;
    r = join(x, r);
    _cut_le(ln, splitpos, l, r);

  } else {
    auto rn = x->r;
    x->r = nullptr;
    l = join(l, x);
    _cut_le(rn, splitpos, l, r);
  }
}
void cut_le(Node *x, int splitpos, Node *&l, Node *&r) {
  l = r = nullptr;
  _cut_le(x, splitpos, l, r);
}

void dfs(Node *x, std::vector<Node *> &res) {
  if (x == nullptr) return;
  x->norm();
  dfs(x->l, res);
  res.pb(x);
  dfs(x->r, res);
}

std::vector<treap::Node *> get_list(Node *x) {
  std::vector<treap::Node *> lst;
  treap::dfs(x, lst);
  return lst;
}

void disp(Node *y) {
  auto lst = get_list(y);
  OPA_DISP("Treap ", lst.size());
  for (auto x : lst) OPA_DISP0(x->d, x->cost);
}

void release(Node *n) {
  std::vector<Node *> lst;
  dfs(n, lst);
  for (auto &x : lst) delete x;
}

} // namespace treap

struct Score {
  treap::Node *root = nullptr;
  treap::Node *make(int n, int w) const {
    auto res = new treap::Node(n, w);
    return res;
  }

  Score() { root = make(0, 0); }

  ~Score() { release(root); }

  void add(int w) {
    treap::Node *l, *r;
    int lim = 6 * w;
    auto *can = treap::search(
      root,
      [&](treap::Node *n) {
        if (n->cost >= lim + 1)
          return treap::SearchRes::Left;
        else
          return treap::SearchRes::Right;
      },
      false);

    if (can == nullptr)
      l = root, r = nullptr;
    else
      treap::cut_le(root, can->d - 1, l, r);
    auto *cutp = treap::search(
      l,
      [&](treap::Node *n) {
        auto nn = treap::next(l, n);
        if (nn == nullptr) return treap::SearchRes::Left;
        int diff = nn->cost - n->cost;
        if (diff > w)
          return treap::SearchRes::Left;
        else
          return treap::SearchRes::Right;
      },
      false);

    printf("Push %d %d\n", w, can == nullptr);
    assert(cutp != nullptr);
    treap::Node *ll, *lr;
    treap::disp(l);
    treap::disp(r);
    treap::cut_le(l, cutp->d - 1, ll, lr);
    treap::disp(ll);
    treap::disp(lr);
    assert(lr != nullptr);
    auto rmin = treap::min(r);
    auto lrmax = treap::max(lr);
    auto lrmin = treap::min(lr);
    auto lrminclone = new treap::Node(lrmin->d, lrmin->cost);

    if (rmin != nullptr && lrmax->cost + w < rmin->cost) {
      OPA_DISP("REmove >> ", rmin->d, rmin->cost);
      treap::disp(r);
      r = treap::remove(r, rmin);
    }
    ll = treap::insert1(ll, lrminclone);

    puts("SHIFT >> ");
    treap::disp(lr);
    lr->shift(1, w);
    puts("JOIN");
    treap::disp(ll);
    treap::disp(lr);
    treap::disp(r);
    root = treap::join(treap::join(ll, lr), r);
    treap::disp(root);
    puts("");

    auto lst = treap::get_list(root);
    int df = -1;
    REP(i, lst.size()-1){
      assert(lst[i]->d+1 == lst[i+1]->d);
      assert(lst[i]->d+1 == lst[i+1]->d);
      int ndf = lst[i+1]->cost -  lst[i]->cost;
      OPA_DISP0(i, ndf);
      assert(ndf >= df);
      df = ndf;
    }
  }

  int get_res() const { return treap::max(root)->d; }
};

const int maxn = 111111;
int n;
int wl[maxn];

int solve() {
  Score sc;
  REP (i, n)
    sc.add(wl[i]);
  return sc.get_res();
}
#ifndef TEST_RAND
#define TEST_RAND 0
#endif

int main() {
  srand(0);
  int tn;
#if TEST_RAND
  tn = 1;
#else
  scanf("%d", &tn);
#endif

  REP (ti, tn) {
#if TEST_RAND
    n = rand() % 100 + 10;
    REP (i, n)
      wl[i] = rand() % 10 + 3;
#else
    scanf("%d", &n);
    REP (i, n)
      scanf("%d", wl + i);
#endif

    printf("Case #%d: ", ti + 1);
    printf("%d", solve());
    puts("");
    break;
  }

  return 0;
}

