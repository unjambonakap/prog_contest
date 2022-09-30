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
#include <valarray>

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
std::ostream &operator<<(std::ostream &os, const std::valarray<T> &a) {
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
std::string toStr(s64 a){std::ostringstream os; os<<a; return os.str();}

struct hash_t {
  template<typename T1,typename T2> size_t operator()(const std::pair<T1,T2> &x) const {
    size_t h1 = std::hash<T1>{}(x.first);
    size_t h2 = std::hash<T1>{}(x.second);
    return (h1 * 31 + h2) ^ h1;
  }


};

// clang-format on

#ifndef TEST_RAND
#define TEST_RAND 0
#endif

#ifndef TEST_CHECK
#define TEST_CHECK 0
#endif
#ifndef TEST_FMT
#define TEST_FMT 0
#endif

const s64 mod = 1e9 + 7;
const double eps = 1e-9;
const int maxn = 11111;
pii p0(0, 0);
pii p1(0, 1000);
const double pi = acos(-1.0);
std::mt19937 rng(0);

class bignum {
  const u32 INT_MAXL = ll(INT_MAX) + 1;

  const int &operator[](size_t pos) const { return limb.at(pos); }
  int &operator[](size_t pos) { return limb.at(pos); }
  const int &at(size_t pos) const { return limb.at(pos); }
  int &at(size_t pos) { return limb.at(pos); }

  int mul_limb(int *limb, int a, int sz) {
    ll r;
    if (sz == 0) return 0;
    int i, c;
    i = 0;
    r = limb[0] * ll(a);
    c = r / INT_MAXL;
    limb[0] = r % INT_MAXL;
    while (++i < sz) {
      r = limb[i] * ll(a) + c;
      c = r / INT_MAXL;
      limb[i] = r % INT_MAXL;
    }

    if (c != 0) limb[sz++] = c;
    return sz;
  }

  int add_limb(int *limb, int a, int sz) {
    ll r;
    if (sz == 0) {
      limb[0] = a;
      return 1;
    }
    r = limb[0] + ll(a);
    int c = 0;
    limb[0] = r % INT_MAXL;
    c = (r >= INT_MAXL);
    int i = 1;
    while (c && i < sz) c = (++limb[i++] <= 0);
    if (c) limb[sz++] = 1;
    return sz;
  }

public:
  std::vector<int> limb;
  int nlimb = 0;
  int sgn = 0;
  bignum() {
    sgn = 1;
    nlimb = 0;
  }

  s32 to_s32() const {
    if (nlimb == 0) return 0;
    return at(0) * sgn;
  }

  s64 to_s64() const {
    if (nlimb < 2) return to_s32();
    return 1ull * sgn * ((1ull * at(1) << 31) + (nlimb < 3 ? 0 : 1ull * at(2) << 62) + at(0));
  }

  bignum(s64 v) {
    sgn = v < 0 ? -1 : 1;
    v = std::abs(v);
    nlimb = 3;
    limb.resize(nlimb);
    limb[0] = v & (INT_MAXL - 1);
    limb[1] = v >> 31 & (INT_MAXL - 1);
    limb[2] = v >> 62 & (INT_MAXL - 1);
    update();
  }
  // bignum(bignum &&x) {
  //  sgn = x.sgn;
  //  limb = std::move(x.limb);
  //  nlimb = x.nlimb;
  //  x.nlimb = 0;
  //}

  bignum(const std::string &s, int b) { build(s, b); }

  void build(std::string s, int b) {
    int num;
    int sz;
    int bb;
    sgn = 1;
    if (s[0] == '-') sgn = -1, s.erase(0, 1);

    nlimb = ceil(s.length() * 0.69314718055994530942 / log(10.) / 4) + 1;
    if (nlimb == 0) return;
    limb.resize(nlimb, 0);
    sz = 0;

    int cpl = 1;
    bb = b;
    while (ll(bb) * b < INT_MAXL) {
      bb *= b, ++cpl;
    }
    int i;
    for (i = 0; i < int(s.length()) - cpl; i += cpl) {
      num = 0;
      REP (j, cpl)
        num = num * b + s[i + j] - '0';
      sz = mul_limb(limb.data(), bb, sz);
      sz = add_limb(limb.data(), num, sz);
      assert(sz <= nlimb);
    }
    bb = 1;
    num = 0;
    REP (j, s.length() - i)
      bb *= b, num = num * b + s[i + j] - '0';

    sz = mul_limb(limb.data(), bb, sz);
    sz = add_limb(limb.data(), num, sz);

    assert(sz <= nlimb);
    update();
  }
  bool greatereqAbs(const bignum &a) const {
    if (a.nlimb != nlimb) return nlimb > a.nlimb;
    REPV (i, nlimb)
      if (a[i] != at(i)) return at(i) > a[i];
    return 1;
  }

  bool greaterAbs(const bignum &a) const {
    if (a.nlimb != nlimb) return nlimb > a.nlimb;
    REPV (i, nlimb)
      if (a[i] != at(i)) return at(i) > a[i];
    return 0;
  }
  bool greatereqAbs(int a) const { return (nlimb > 1 || (nlimb == 1 && at(0) >= a)); }
  bool greaterAbs(int a) const { return (nlimb > 1 || (nlimb == 1 && at(0) > a)); }

  bool lessAbs(const bignum &a) const {
    if (a.nlimb != nlimb) return nlimb < a.nlimb;
    REPV (i, nlimb)
      if (a[i] != at(i)) return at(i) < a[i];
    return 0;
  }
  void update() {
    assert(sgn != 0);
    assert(nlimb == limb.size());
    assert(nlimb < 10);
    REP (i, nlimb)
      assert(at(i) >= 0);
    while (nlimb > 0 && at(nlimb - 1) == 0) {
      limb.pop_back(), --nlimb;
    }
    if (nlimb == 0) sgn = 1;
  }
  bool operator>(const bignum &a) const {
    if (sgn != a.sgn) return sgn != -1;
    return sgn == 1 ? greaterAbs(a) : lessAbs(a);
  }
  bool operator<(const bignum &a) const {
    if (sgn != a.sgn) return sgn == -1;
    return lessAbs(a);
  }
  bool operator<=(const bignum &a) const { return !(*this > a); }
  bool operator>=(const bignum &a) const { return !(*this < a); }
  bool operator!=(const bignum &a) const { return !(*this == a); }
  bool operator==(const bignum &a) const {
    if (sgn != a.sgn || nlimb != a.nlimb) return false;
    REP (i, nlimb)
      if (at(i) != a[i]) return false;
    return true;
  }

  bignum &sabs() {
    sgn = 1;
    return *this;
  }

  bignum &operator=(const bignum &a) {
    sgn = a.sgn;
    if (this == &a) return *this;
    nlimb = a.nlimb;
    limb = a.limb;
    return *this;
  }

  bignum operator-() const {
    bignum a;
    if ((a.nlimb = nlimb) == 0) {
      a.sgn = 1;
      return a;
    }
    a.sgn = -sgn;
    a.limb = limb;
    return a;
  }

  bignum operator+(const bignum &a) const {

    if (a.nlimb == 0) return *this;
    if (nlimb == 0) return a;

    if (sgn == a.sgn) {
      if (!greatereqAbs(a)) return a + *this;
      int c, i;
      ll r;
      bignum b = *this;
      b.limb.pb(0);
      b.nlimb += 1;
      for (i = 0, c = 0; i < std::max(nlimb, a.nlimb); ++i) {
        r = (s64)b[i] + (i >= a.nlimb ? 0 : a[i]) + c;
        b[i] = r % INT_MAXL, c = r / INT_MAXL;
      }
      b[i] = c;
      b.update();
      return b;

    } else
      return *this - (-a);
  }

  bignum operator-(const bignum &a) const {
    if (a.nlimb == 0) return *this;
    if (nlimb == 0) return -a;

    if (sgn == a.sgn) {
      if (greatereqAbs(a)) {
        int c, i;
        bignum b = *this;
        for (i = 0, c = 0; i < b.nlimb; ++i) {
          b[i] = b[i] - (i < a.nlimb ? a[i] : 0) - c;
          if (b[i] < 0)
            c = 1, b[i] += INT_MAXL;
          else
            c = 0;
        }
        assert(c == 0);
        b.update();
        return b;

      } else
        return -(a - (*this));

    } else
      return *this + (-a);

    assert(0);
  }

  bignum operator*(const bignum &a) const {

    bignum b;
    b.nlimb = a.nlimb + nlimb;

    if (b.nlimb == 0) {
      return b;
    }
    assert(a.sgn != 0);
    assert(sgn != 0);
    b.sgn = a.sgn * sgn;
    b.limb.resize(b.nlimb, 0);

    ll r;
    REP (i, a.nlimb) {
      REP (j, nlimb) {
        r = b[i + j] + ll(a[i]) * at(j);
        b[i + j] = ((u32)r << 1) >> 1;
        // assert(b[i + j + 1] + r / INT_MAXL < INT_MAXL);
        b[i + j + 1] += r >> 31;
      }
    }
    b.update();
    return b;
  }

  bignum operator*(int a) const {

    bignum b;
    b.nlimb = 1 + nlimb;

    if (b.nlimb == 0) {
      return b;
    }
    b.sgn = (a < 0 ? -1 : 1) * sgn;
    a = std::abs(a);
    b.limb.resize(b.nlimb, 0);

    ll r;
    REP (i, nlimb) {
      r = b[i] + ll(a) * at(i);
      b[i] = r % INT_MAXL;
      b[i + 1] += r / INT_MAXL;
    }
    b.update();
    return b;
  }

  bignum operator/(const bignum &a) const {
    bignum b;
    int i, H, M, L;
    if (!greatereqAbs(a)) return b;
    b.sgn = a.sgn * sgn;

    b.nlimb = nlimb - a.nlimb + 1;
    b.limb.resize(b.nlimb, 0);
    for (i = b.nlimb - 1; i >= 0; --i) {
      L = 0, H = INT_MAX;
      int cnt = 0;
      while (L < H) {
        ++cnt;
        assert(cnt < 40);
        M = ceil((ll(L) + H) / 2.);
        b[i] = M;
        bignum c = b * a;
        if (this->greatereqAbs(c))
          L = M;
        else
          H = M - 1;
      }
      b[i] = L;
    }
    b.update();

    return b;
  }

  bignum operator/(int a) const {
    bignum b;
    int i, H, M, L;
    if (a == 0) assert("div0" && 0);
    if (!greatereqAbs(a)) return b;

    b.sgn = (a < 0 ? -1 : 1) * sgn;

    b.nlimb = nlimb;

    b.limb.resize(b.nlimb, 0);
    for (i = b.nlimb - 1; i >= 0; --i) {
      L = 0, H = INT_MAX;
      while (L < H) {
        M = ceil((ll(L) + H) / 2.);
        b[i] = M;
        bignum c = b * bignum(toStr(a), 10);
        if (this->greatereqAbs(c))
          L = M;
        else
          H = M - 1;
      }
      b[i] = L;
    }

    b.update();
    return b;
  }
  bignum operator%(const bignum &a) const { return (*this) - ((*this) / a) * a; }
  int operator%(int a) const {
    assert(sgn != 0);
    bignum d = (*this) / a;

    bignum c = (*this) - ((*this) / a) * a;

    if (c.nlimb == 0) return 0;
    assert(c.nlimb == 1);
    assert(c[0] < a);
    return c[0];
  }

  ~bignum() { limb.clear(); }

  std::string get_str(int b) const {
    bignum a = *this;
    std::string s;
    a.sabs();
    while (a.nlimb) {
      s += (a % b) + '0';
      a = a / b;
    }
    if (s.empty()) return "0";
    if (sgn == -1) s += "-";
    std::reverse(ALL(s));
    return s;
  }
};

namespace std {
bignum abs(const bignum &a) { return bignum(a).sabs(); }
std::ostream &operator<<(std::ostream &os, const bignum &a) {
  os << a.get_str(10);
  return os;
}
} // namespace std

template <typename T> T _gcd(const T &a, const T &b) { return b == 0 ? a : _gcd(b, a % b); }
template <typename T> T gcd(const T &a, const T &b) { return _gcd(std::min(a, b), std::max(a, b)); }

struct Angle {
  bignum d0, d1;
  Angle() {}
  double ang() const { return std::atan2(d1.to_s64(), d0.to_s64()) / 2 / pi; }

  Angle(const bignum &a, const bignum &b, bool unsafe = false) {
    if (unsafe) {
      d0 = a;
      d1 = b;
    } else {
      assert(a != 0 || b != 0);
      bignum d = gcd(std::abs(a), std::abs(b));
      d0 = a / d;
      d1 = b / d;
    }
  }
  Angle rot(const Angle &ang) const {
    return Angle(d0 * ang.d0 + d1 * ang.d1, d0 * -ang.d1 + d1 * ang.d0);
  }

  Angle flipy() const { return Angle(d0, -d1, true); }

  bool cross_sign(const Angle &peer) const {
    auto r0 = d0 * peer.d1 - d1 * peer.d0;
    return r0 >= 0;
  }

  bool operator==(const Angle &peer) const { return d0 == peer.d0 && d1 == peer.d1; }
  bool operator!=(const Angle &peer) const { return !(*this == peer); }
  bool operator<(const Angle &peer) const;
};

struct hash_t2 {
  size_t operator()(const Angle &x) const {
    size_t h1 = x.d0.to_s64();
    size_t h2 = x.d1.to_s64();
    return (h1 * 31 + h2) ^ h1;
  }
};

Angle yvec(0, 1);
Angle nyvec(0, -1);
Angle xvec(1, 0);
Angle nxvec(-1, 0);
bool Angle::operator<(const Angle &peer) const {
  if (*this == peer) return false;
  if (peer == yvec) return false;
  if (*this == yvec) return true;
  bool s1 = yvec.cross_sign(*this);
  bool s2 = yvec.cross_sign(peer);
  if (s1 != s2) return s1;
  return cross_sign(peer);
}

struct Interval {
  Angle a0, a1;
  Interval(Angle x0, Angle x1) : a0(x0), a1(x1) {
    if (a0.cross_sign(a1) == false) std::swap(a0, a1);
  }

  std::vector<Interval> normalize() const {
    std::vector<Interval> res;
    if (yvec.cross_sign(a0) == false && yvec.cross_sign(a1)) {
      res.pb(Interval(a0, yvec));
      res.pb(Interval(yvec, a1));
    } else
      res.pb(*this);
    return res;
  }

  Interval complement() const { return Interval(a0.flipy(), a1.flipy()); }
};

double norm_ang(double ang) {
  while (ang >= 1) ang -= 1;
  while (ang < 0) ang += 1;
  return ang;
}

struct SolverContext {
  int n;
  std::vector<std::pair<double, double> > tl;
  std::vector<std::pair<double, double> > free_covers;
  std::vector<std::pair<double, double> > intervals;
  std::vector<Interval> sym_free_covers;
  std::vector<Interval> sym_choices;
  std::vector<Interval> sym_intervals;
  std::vector<pii> p0l;
  std::vector<pii> p1l;
  Angle sym_free_low = xvec;
  Angle sym_free_high = nxvec;

  void read() {
    std::uniform_int_distribution<> dis(-20000, 20000);
    if (TEST_RAND) {
      n = 10000;
      n = rng() % 10 + 1;
      n = 5;
    } else
      scanf("%d", &n);

    REP (i, n) {
      double ang0, ang1;

      int x0, y0, x1, y1;
      if (TEST_RAND)
        while (true) {
          x0 = dis(rng), y0 = dis(rng), x1 = dis(rng), y1 = dis(rng);
          if (x0 != 0 || y0 < p0.ND || y0 > p1.ND) break;
        }
      else
        scanf("%d%d%d%d", &x0, &y0, &x1, &y1);

      p0l.emplace_back(x0, y0);
      p1l.emplace_back(x1, y1);
      double curAng = std::atan2(y1 - y0, x1 - x0) / (2 * pi);
      ang0 = std::atan2(p0.ND - y0, p0.ST - x0) / (2 * pi);
      ang1 = std::atan2(p1.ND - y0, p1.ST - x0) / (2 * pi);
      ang0 = norm_ang(ang0 - curAng);
      ang1 = norm_ang(ang1 - curAng);

      if (ang1 < ang0) std::swap(ang0, ang1);
      intervals.emplace_back(ang0, ang1);

      if (1) {
        std::valarray<s64> a0(2);
        a0[0] = p0.ST - x0;
        a0[1] = p0.ND - y0;
        std::valarray<s64> a1(2);
        a1[0] = p1.ST - x0;
        a1[1] = p1.ND - y0;
        std::valarray<s64> rot_ang(2);
        rot_ang[0] = x1 - x0;
        rot_ang[1] = y1 - y0;
        std::valarray<s64> a0r(2);
        std::valarray<s64> a1r(2);
        a0r[0] = a0[0] * rot_ang[0] + a0[1] * rot_ang[1];
        a0r[1] = a0[0] * -rot_ang[1] + a0[1] * rot_ang[0];

        a1r[0] = a1[0] * rot_ang[0] + a1[1] * rot_ang[1];
        a1r[1] = a1[0] * -rot_ang[1] + a1[1] * rot_ang[0];
        s64 d0 = gcd(std::abs(a0r[0]), std::abs(a0r[1]));
        s64 d1 = gcd(std::abs(a1r[0]), std::abs(a1r[1]));
        auto ix =
          Interval(Angle(a0r[0] / d0, a0r[1] / d0, true), Angle(a1r[0] / d1, a1r[1] / d1, true));
        sym_intervals.pb(ix);

        // sym_intervals.emplace_back(a0.rot(rot_angle), a1.rot(rot_angle));
        // auto ix = sym_intervals.back();
        auto xi = ix.complement();
        if (ix.a0.cross_sign(xvec) != ix.a1.cross_sign(xvec)) {
          if (ix.a0.cross_sign(xvec)) {
            Angle plow = ix.a1, phigh = xi.a1;
            if (!plow.cross_sign(phigh)) std::swap(plow, phigh);
            if (sym_free_low.cross_sign(plow)) sym_free_low = plow;
            sym_choices.emplace_back(plow, phigh);
          } else {

            Angle plow = ix.a0, phigh = xi.a0;
            if (!plow.cross_sign(phigh)) std::swap(plow, phigh);
            if (!sym_free_high.cross_sign(phigh)) sym_free_high = phigh;
            sym_choices.emplace_back(plow, phigh);
          }

        } else {
          if (ix.a0.cross_sign(xvec))
            sym_choices.pb(xi);
          else
            sym_choices.pb(ix);
        }

        // OPA_DISP0(a1.dp, a1.ang());
        // OPA_DISP0(ix.a0.ang(), ix.a1.ang(), ix.a0.dp, ix.a1.dp, ang0, ang1);
      }

      if (ang1 - ang0 > 0.5) {
        double mx = std::min(1 - ang1, ang0);
        double maxv = std::max(1 - ang1, ang0);

        free_covers.emplace_back(0, mx);
        tl.pb(MP(mx, maxv));
      } else if (ang0 < 0.5 && ang1 > 0.5) {
        double mx = std::min(0.5 - ang0, ang1 - 0.5);
        double maxv = std::max(0.5 - ang0, ang1 - 0.5);

        free_covers.emplace_back(0.5 - mx, 0.5);
        tl.pb(MP(0.5 - maxv, 0.5 - mx));
      } else {
        if (ang0 >= 0.5) {
          ang0 = 1 - ang0, ang1 = 1 - ang1;
          std::swap(ang0, ang1);
        }
        tl.emplace_back(ang0, ang1);
      }
      assert(tl.back().second <= 0.5);
    }
  }

  typedef std::unordered_map<pii, double, hash_t> state_t;

  double solve() {
    state_t states;

    tl.emplace_back(0.5, 0.5);
    tl.emplace_back(0, 0);
    std::sort(ALL(tl));
    std::sort(ALL(free_covers));

    std::vector<Angle> vals;
    for (auto &x : sym_choices) vals.pb(x.a0), vals.pb(x.a1);
    vals.pb(xvec);
    vals.pb(nxvec);
    vals.pb(sym_free_low);
    vals.pb(sym_free_high);

    std::sort(ALL(vals), [](const auto &a, const auto &b) {
      if (a == b) return false;
      if (a == nxvec) return false;
      if (b == nxvec) return true;
      return a.cross_sign(b);
    });

    std::unordered_map<Angle, int, hash_t2> mp;
    for (int i = 0; i < vals.size(); ++i) mp[vals[i]] = i;

    std::vector<pii> intervals;
    for (auto &x : sym_choices) intervals.emplace_back(mp[x.a0], mp[x.a1]);
    std::sort(ALL(intervals));
    int left = mp[sym_free_low];
    int right = mp[sym_free_high];

    intervals.emplace_back(vals.size() - 1, vals.size() - 1);

    states[MP(left, left)] = 1.;
    if (left >= right) return 1;

    for (auto &ix : intervals) {
      state_t nstates;
      if (ix.ST >= right) break;
      for (const auto &s : states) {
        pii ns1 = s.first;
        if (ns1.ST < ix.ST || ns1.ND < ix.ST) continue;
        checkmax(ns1.ST, ix.ND);
        pii ns2 = s.first;
        checkmax(ns2.ND, ix.ND);
        nstates[ns1] += s.second * 0.5;
        nstates[ns2] += s.second * 0.5;
      }
      std::swap(states, nstates);
    }

    double res = 0;
    for (auto &x : states) {
      if (x.first.first >= right && x.first.second >= right) res += x.second;

      // if (s.first != -1 && tl[s.first].second < 0.5) continue;
      // if (s.second != -1 && tl[s.second].second < 0.5) continue;
    }
    return 1 - res;
  }

  double solve_dumb() {
    int res = 0;
    int res2 = 0;
    std::vector<std::vector<Interval> > elems[2];
    REP (i, n) {
      elems[0].pb(sym_intervals[i].normalize());
      elems[1].pb(sym_intervals[i].complement().normalize());
    }

    REP (i, 1 << n) {
      std::vector<Interval> sym_cover;
      sym_cover.reserve(2 * n);
      std::vector<std::pair<double, double> > cover;
      REP (j, n) {
        auto ix = intervals[j];
        if (i >> j & 1) {
          ix = MP(1 - ix.second, 1 - ix.first);
        }

        if (1) {
          const auto &norm = elems[i >> j & 1][j];
          // OPA_DISP0(ix, ix2.a0.ang(), ix2.a1.ang(), norm.size());
          for (auto &x : norm) sym_cover.pb(x);
        }

        if (ix.second - ix.first >= 0.5) {
          cover.emplace_back(0, ix.first);
          cover.emplace_back(ix.second, 1);
        } else
          cover.pb(ix);
      }

      std::sort(ALL(cover));
      sym_cover.pb(Interval(nyvec, nyvec));
      sym_cover.pb(Interval(nxvec, nxvec));
      sym_cover.pb(Interval(xvec, xvec));
      sym_cover.pb(Interval(yvec, yvec));

      std::sort(ALL(sym_cover),
                [](const Interval &i1, const Interval &i2) { return i1.a0 < i2.a0; });
      double last = 0;
      Angle st = yvec;
      Angle nd = yvec;
      sym_cover.pb(Interval(yvec, yvec));

      bool bad = false;
      bool bad0 = false;

      for (int i = 0; i < sym_cover.size() - 1; ++i) {
        auto cur = sym_cover[i];
        auto to = sym_cover[i + 1];

        st = cur.a0;
        assert(st.cross_sign(to.a0));
        if (nd.cross_sign(cur.a1)) nd = cur.a1;
        if (cur.a0 != to.a0) {
          if (st.cross_sign(to.a0) && to.a0.cross_sign(nd))
            ;
          else {
            bad = true;
            break;
          }
        }
      }

      for (int i = 0; i < cover.size(); ++i) {
        auto &k = cover[i];
        if (k.first > last + eps) {
          last = -1;
          bad0 = true;
          break;
        }
        checkmax(last, k.second);
      }

      if (!bad) ++res2;

      bad0 |= last + eps < 1;
      if (!bad0) {
        ++res;
      } else {
        // OPA_DISP0(i, cover);
      }
      if (TEST_CHECK) assert(bad == bad0);
    }

    if (TEST_CHECK) assert(res == res2);
    return 1 - 1. * res2 / (1 << n);
  }
};

int main() {
  srand(0);
  int tn;

  if (TEST_RAND)
    tn = 1000000;
  else
    scanf("%d", &tn);

  REP (ti, tn) {

    SolverContext sc;
    sc.read();
    // if (ti != 120) continue;

    if (TEST_CHECK) {
      auto r1 = sc.solve();
      auto r2 = sc.solve_dumb();
      printf("%lf %lf\n", r1, r2);
      assert(std::abs(r1 - r2) < 1e-6);
      if (TEST_RAND && r1 == 1) continue;
      // OPA_DISP0(sc.intervals, sc.free_covers, sc.tl);
      printf("Case #%d: ", ti + 1);
      OPA_DISP0(r1, r2);
    } else {

      printf("Case #%d: ", ti + 1);
      auto res = sc.solve();
      printf("%.8lf", res);
    }
    puts("");
  }

  return 0;
}

