#include <opa/math/common/bignum.h>
#include <opa/utils/hash.h>
#include <opa_common.h>

using namespace std;

template <class T> class CombHelper {
public:
  CombHelper(int n = -1) { this->init(n); }
  void init(int n) {
    if (n == -1) return;
    fact.resize(n + 1);
    fact[0] = 1;
    REP (i, n)
      fact[i + 1] = fact[i] * (i + 1);
  }

  T cnk(int n, int k) const {
    if (n < k) return 0;
    if (k < 0) return 0;
    OPA_CHECK0(n < fact.size());
    return fact[n] / fact[k] / fact[n - k];
  }

  T ank(int n, int k) const {
    if (n < k) return 0;
    if (k < 0) return 0;
    return fact[n] / fact[n - k];
  }

  std::vector<T> fact;
};

CombHelper<OPA_BG> ch;
int n, d, r;

typedef std::pair<double, double> Res;
class Helper {
public:
  opa::utils::MemoizeHelperClass<OPA_BG, Helper, int, int> go_mem;
  opa::utils::MemoizeHelperClass<OPA_BG, Helper, int, int> go_w2_mem;
  opa::utils::MemoizeHelperClass<OPA_BG, Helper, int> go_s1_mem;
  opa::utils::MemoizeHelperClass<OPA_BG, Helper, int> go_s2_mem;
  opa::utils::MemoizeHelperClass<OPA_BG, Helper, int, int> go_ai_mem;
#define go_call(...) CALL1(Helper, go, __VA_ARGS__)
#define go_w2_call(...) CALL1(Helper, go_w2, __VA_ARGS__)
#define go_s1_call(...) CALL1(Helper, go_s1, __VA_ARGS__)
#define go_s2_call(...) CALL1(Helper, go_s2, __VA_ARGS__)
#define go_ai_call(...) CALL1(Helper, go_ai, __VA_ARGS__)

  OPA_BG go_(int n, int d) const {
    if (n <= r) return ch.cnk(n + d - 1, n - 1) * (r + d);
    if (d == 0) return r;
    OPA_BG res = 0;

    res += ch.cnk(n + d - 1, n - 1) * r;
    FOR (i, 1, n + 1) {
      if (i > d) break;
      res += ch.cnk(n, i) * go_call(i, d - i);
    }
    return res;
  }

  OPA_BG go_w2_(int nx, int v) const {
    OPA_BG sgn = 1;
    OPA_BG res = 0;
    FOR (i, nx, n + 1) {
      if (i * (v - 1) > d) break;
      OPA_BG ai = ch.cnk(d - i * (v - 1) + n - 1, n - 1) * ch.cnk(n, i);
      res += sgn * ch.cnk(i, nx) * ai;
      sgn *= -1;
    }
    return res;
  }

  OPA_BG go_ai_(int i, int v) const {
    return ch.cnk(d - i * (v - 1) + n - 1, n - 1) * ch.cnk(n, i);
  }

  OPA_BG go_s1_(int nn) const {
    OPA_BG sgn = 1;
    OPA_BG res = 0;
    REP (i, r) {
      res += sgn * ch.cnk(nn, i) * i;
      sgn *= -1;
    }
    return res;
  }

  OPA_BG go_s2_(int nn) const {
    OPA_BG sgn = r & 1 ? -1 : 1;
    OPA_BG res = 0;
    FOR (i, r, n + 1) {
      res += sgn * ch.cnk(nn, i) * r;
      sgn *= -1;
    }
    return res;
  }
};

OPA_BG solve3() {
  Helper helper;
  helper.go_ai_mem.init(&helper);
  helper.go_s1_mem.init(&helper);
  helper.go_s2_mem.init(&helper);

  OPA_BG res = 0;
  FOR (i, 1, n + 1) {
    FOR (j, 1, d + 2) {
      OPA_BG tmp2 =
        helper.go_ai_call(i, j) * (helper.go_s2_call(i) + helper.go_s1_call(i));
      tmp2 *= (i & 1 ? -1 : 1);
      res += tmp2;
    }
  }
  return res;
}

OPA_BG solve1() {
  Helper helper;
  helper.go_mem.init(&helper);
  OPA_BG res = helper.go_call(n, d);
  return res;
}

OPA_BG solve2() {
  Helper helper;
  helper.go_w2_mem.init(&helper);

  OPA_BG res = 0;
  FOR (i, 1, n + 1) {
    FOR (j, 1, d + 2) {
      if (i * (j - 1) > d) break;
      OPA_BG tmp2 = (helper.go_w2_call(i, j)) * std::min(r, i);
      res += tmp2;
    }
  }
  return res;
}

int main(int argc, char **argv) {
  opa::init::opa_init(argc, argv);
  ch.init(1111);
  scanf("%d%d%d", &n, &d, &r);

  OPA_BG res = solve3();

  double mul = 1e9;
  res *= int(mul);
  res /= ch.cnk(n + d - 1, n - 1);
  double ans = res.gets64() / mul;

  printf("%.15lf\n", ans);

  return 0;
}
