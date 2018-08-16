#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <utility>
#include <numeric>
#include <algorithm>
#include <bitset>
#include <complex>

using namespace std;

typedef unsigned uint;
typedef long long Int;
typedef vector<int> vint;
typedef pair<int,int> pint;
#define mp make_pair

template<class T> void pv(T a, T b) { for (T i = a; i != b; ++i) cout << *i << " "; cout << endl; }
template<class T> void chmin(T &t, T f) { if (t > f) t = f; }
template<class T> void chmax(T &t, T f) { if (t < f) t = f; }
int in() { int x; scanf("%d", &x); return x; }

const Int LIM_OVERFLOW = 3037000499LL;
const int LOG = 33;

Int multiply(Int a, Int b, Int m) {
    return (((a << 16) % m) * (b >> 16) + a * (b & 0xffff)) % m;
}
Int gcd(Int a, Int b) {
    return b ? gcd(b, a % b) : a;
}
Int lcm(Int a, Int b) {
    return a / gcd(a, b) * b;
}

#define MAX_LIM_PRIME 100010
const int LIM_PRIME = 100000;
bool isnp[MAX_LIM_PRIME];
int primesLen;
Int primes[MAX_LIM_PRIME];
void preparePrimes() {
    int i, j;
    for (i = 2; i * i < LIM_PRIME; ++i) if (!isnp[i]) for (j = i * i; j < LIM_PRIME; j += i) isnp[j] = 1;
    primesLen = 0;
    for (i = 2; i < LIM_PRIME; ++i) if (!isnp[i]) primes[primesLen++] = i;
}

#define MAX_PW26 0x2000a
const Int MO = 1000000007;
Int pw26Small[MAX_PW26], pw26Large[MAX_PW26];

#define MAX_LR 50010
#define MAX_LEN 15
#define MAX_E 40
Int L, R;
Int LL, RR;
int lens[MAX_LR];
Int pss[MAX_LR][MAX_LEN];
int ess[MAX_LR][MAX_LEN];

#define MAX_PWM 50

Int M;
Int pwMs[MAX_PWM];
int len, len_;
Int *ps, *ps_;
int *es, *es_;
Int os[MAX_LEN][MAX_E];
Int pps_[MAX_E];
Int cSum;

/*
#define MAX_MEM 20000010
const Int LIM_MEM = 20000000;
Int orders[MAX_MEM];
bool memed[MAX_MEM];
*/

Int power2(Int e) {
    Int ret = 1;
    int i;
    for (i = 0; i <= LOG; ++i) if (e & 1LL << i) ret = multiply(ret, pwMs[i], M);
    return ret;
}
void getFactors(Int m) {
    if (LL <= m && m <= RR) {
        len_ = lens[m - LL];
        ps_ = pss[m - LL];
        es_ = ess[m - LL];
    } else {
        int i;
        Int p;
        len_ = 0;
        ps_ = pss[MAX_LR - 1];
        es_ = ess[MAX_LR - 1];
        for (i = 0; i < primesLen && (p = primes[i], p * p <= m); ++i) if (m % p == 0) {
            ps_[len_] = p;
            es_[len_] = 1;
            for (; ; ) {
                m /= p;
                if (m % p != 0) break;
                ++es_[len_];
            }
            ++len_;
        }
        if (m > 1) {
            ps_[len_] = m;
            es_[len_] = 1;
            ++len_;
        }
    }
}
Int getOrder(Int p) {
    int i_, e_;
    Int o = p - 1;
    getFactors(p - 1);
    for (i_ = 0; i_ < len_; ++i_) {
        Int p_ = ps_[i_];
        pps_[0] = 1;
        for (e_ = 1; e_ <= es_[i_]; ++e_) pps_[e_] = pps_[e_ - 1] * p_;
        int lo = 0, ho = es_[i_] + 1;
        for (; lo + 1 < ho; ) {
            int mo = (lo + ho) / 2;
            (power2(o / pps_[mo]) % p == 1) ? (lo = mo) : (ho = mo);
        }
        o /= pps_[lo];
    }
    return o;
}

void dfs(int i, Int h, Int o) {
    if (i == len) {
        cSum += h / o;
        return;
    }
    int e;
    for (e = 0; e <= es[i]; ++e) {
        dfs(i + 1, h, lcm(o, os[i][e]));
        h *= e ? ps[i] : (ps[i] - 1);
    }
}
void dfs() {
    dfs(0, 1, 1);
}

int main() {
    int i, e;
    Int m, n;

    preparePrimes();
    pw26Small[0] = pw26Large[0] = 1;
    for (i = 1; i <= 0x20000; ++i) pw26Small[i] = pw26Small[i - 1] * 26 % MO;
    for (i = 1; i <= 0x20000; ++i) pw26Large[i] = pw26Large[i - 1] * pw26Small[0x20000] % MO;

    for (int TC = in(); TC--; ) {
        scanf("%lld%lld", &L, &R);
        //L= 99950000LL;
        //R=100000000LL;
        LL = max(L - 1, 1LL);
        RR = R + 1;
        memset(lens, 0, (RR - LL + 2) << 2);
        for (i = 0; i < primesLen; ++i) {
            Int p = primes[i];
            for (m = (LL + p - 1) / p * p; m <= RR; m += p) {
                pss[m - LL][lens[m - LL]++] = p;
            }
        }
        for (m = LL; m <= RR; ++m) {
            int &len = lens[m - LL];
            Int *ps = pss[m - LL];
            int *es = ess[m - LL];
            Int mm = m;
            for (i = 0; i < len; ++i) {
                Int p = ps[i];
                es[i] = 1;
                for (; ; ) {
                    mm /= p;
                    if (mm % p != 0) break;
                    ++es[i];
                }
            }
            if (mm > 1) {
                ps[len] = mm;
                es[len] = 1;
                ++len;
            }
        }
        Int ans = 0;
        Int MBef = -1;
        for (n = L; n <= R; ++n) {
            M = (n % 2 != 0) ? n : (n + 1);
            if (MBef != M) {
                MBef = M;
                pwMs[0] = 2;
                for (i = 1; i <= LOG; ++i) pwMs[i] = multiply(pwMs[i - 1], pwMs[i - 1], M);
                len = lens[M - LL];
                ps = pss[M - LL];
                es = ess[M - LL];
                for (i = 0; i < len; ++i) {
                    os[i][0] = 1;
                    os[i][1] = getOrder(ps[i]);
                    Int pp = ps[i];
                    for (e = 2; e <= es[i]; ++e) {
                        pp *= ps[i];
                        os[i][e] = (power2(os[i][e - 1]) % pp == 1) ? os[i][e - 1] : (os[i][e - 1] * ps[i]);
                    }
                }
                cSum = -1;
                dfs();
            }
            if (n % 2 != 0) ++cSum;
            ans += pw26Small[cSum & 0x1ffff] * pw26Large[cSum >> 17];
            ans %= MO;
        }
        printf("%lld\n", ans);
    }

    return 0;
}
