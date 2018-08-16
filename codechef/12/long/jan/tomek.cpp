#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <cassert>
#include <ctime>
#include <queue>
using namespace std;
#define VAR(a,b) __typeof(b) a=(b)
#define REP(i,n) for(int _n=n, i=0;i<_n;++i)
#define FOR(i,a,b) for(int i=(a),_b=(b);i<=_b;++i)
#define FORD(i,a,b) for(int i=(a),_b=(b);i>=_b;--i)
#define FOREACH(it,c) for(VAR(it,(c).begin());it!=(c).end();++it)
#define ALL(c) (c).begin(),(c).end()
#define TRACE(x) cerr << "TRACE(" #x ")" << endl;
#define DEBUG(x) cerr << #x << " = " << x << endl;

typedef long long LL;
typedef unsigned long long ULL;
const int INF = 1000000000; const LL INFLL = LL(INF) * LL(INF);
template<class T> inline int size(const T&c) { return c.size(); }
int rint() { int x; if(scanf("%d",&x)!=1) return -1; return x; }
LL rLL() { LL x; if(scanf("%lld",&x)!=1) return -1; return x; }
//}}}

const int MAX_SMALL_PRIME = 100001;
const LL SMALL_FACTORED = 170000;
const int ORDER_CACHE = 1000000;

vector<int> smallPrimes;

void calcSmallPrimes() {
    smallPrimes.clear();
    vector<bool> pr(MAX_SMALL_PRIME, true);
    FOR(p,2,MAX_SMALL_PRIME) if(pr[p]) {
        smallPrimes.push_back(p);
        for(int q = 2*p; q <= MAX_SMALL_PRIME; q+=p) pr[q]=false;
    }
}

LL gcd(LL a, LL b) {
    int sh = 0;
    if(a==0 || b==0) return a|b;
    if(a|b) while(((a|b)&1)==0) { ++sh; a>>=1; b>>=1; }
    while((a&1)==0) a>>=1;
    while((b&1)==0) b>>=1;
    if(a<b) swap(a,b);
    // b smaller, both odd
    for(;;) {
        a -= b;
        if(!a) break;
        while((a&1)==0) a>>=1;
        if(a<b) swap(a,b);
    }
    return b << sh;
}

LL lcm(LL a, LL b) {
    return a / gcd(a,b) * b;
}

unsigned mypowerModVerySmall(unsigned a, LL b, unsigned m) {
    unsigned res = 1;
    while(b) {
        if(b&1) res = res * a % m;
        b >>= 1;
        if(!b) break;
        a = a * a % m;
    }
    return res;
}

unsigned mypowerModSmall(unsigned a, LL b, unsigned m) {
    unsigned res = 1;
    while(b) {
        if(b&1) res = ULL(res) * ULL(a) % m;
        b >>= 1;
        if(!b) break;
        a = ULL(a) * ULL(a) % m;
    }
    return res;
}

LL mulModBig(LL a, LL b, LL m) {
    ULL aa = a, bb=b, mm=m;
    ULL xx = aa * (bb & 0xffffu) % mm;
    return LL((((aa * (bb>>16) % mm) << 16) + xx) % mm);
}

// m>=3
LL mypowerModBig(LL a, LL b, LL m) {
    if(m < (1LL<<32)) {
        unsigned m2 = unsigned(m);
        if(m2< (1u<<16)) {
            return mypowerModVerySmall(unsigned(a % m2), b, m2);
        } else {
            return mypowerModSmall(unsigned(a % m2), b, m2);
        }
    }
    LL res = 1;
    while(b) {
        if(b&1) res = mulModBig(res, a, m);
        b >>= 1;
        if(!b) break;
        a = mulModBig(a,a,m);
    }
    return res;
}

struct PrimePower {
    LL p;
    int k;
};

class FactoredRange {
    LL a,b;
    vector<vector<PrimePower> > factors;
    public:
    FactoredRange():a(0),b(-1) {}
    void calc(LL A, LL B);
    bool inRange(LL x) { return x>=a && x<=b; }
    vector<PrimePower> get(LL x) { return factors[x-a]; }
};

void FactoredRange::calc(LL A, LL B) {
    a = A; b = B;
    vector<LL> rem(b-a+1);
    factors.clear();
    factors.resize(b-a+1);
    for(LL i=a; i<=b; ++i) rem[i-a] = i;
    FOREACH(it, smallPrimes) {
        int p = *it;
        LL x = a + (p - int(a % p)) % p;
        for(;x <= b; x += p) {
            PrimePower pp;
            pp.p = p;
            pp.k = 1;
            rem[x-a] /= p;
            while(rem[x-a]%p==0) { rem[x-a]/=p; ++pp.k; }
            factors[x-a].push_back(pp);
        }
    }
    for(LL i=a; i<=b; ++i) if(rem[i-a]>1) {
        PrimePower pp;
        pp.p = rem[i-a];
        pp.k = 1;
        factors[i-a].push_back(pp);
    }
}

FactoredRange smallFactoredRange, largeFactoredRange;

LL orderModPrimeCache[ORDER_CACHE];

// p odd prime, p <= 10^10+1
LL calcOrderModuloPrime(LL p, LL n, const vector<PrimePower> &nfactors) {
    if(p<ORDER_CACHE && orderModPrimeCache[p]) return orderModPrimeCache[p];
    vector<PrimePower> factors;
    if(smallFactoredRange.inRange(p-1)) factors = smallFactoredRange.get(p-1);
    else {
        LL x = n - n/p;
        assert(largeFactoredRange.inRange(x));
        vector<PrimePower> f1 = largeFactoredRange.get(x);
        int a=0;
        FOREACH(it, f1) {
            PrimePower pp = *it;
            if(a < size(nfactors) && nfactors[a].p < pp.p) {
                assert(nfactors[a].k==1);
                ++a;
            }
            if(a < size(nfactors) && nfactors[a].p == pp.p) {
                pp.k -= nfactors[a].k - (pp.p==p);
                assert(pp.k >= 0);
                ++a;
            }
            if(pp.k>0) factors.push_back(pp);
        }
        if(a < size(nfactors)) {
            assert(nfactors[a].p==p);
            assert(nfactors[a].k==1);
            ++a;
        }
        assert(a == size(nfactors));
    }
    int k = size(factors);
    FORD(i,k-1,0) {
        LL qq = 1;
        REP(j,k) if(j!=i) REP(b,factors[j].k) qq *= factors[j].p;
        int newk=0;
        LL p2 = mypowerModBig(2, qq, p);
        while(p2 != 1) {
            assert(newk < factors[i].k);
            ++newk;
            p2 = mypowerModBig(p2, factors[i].p, p);
        }
        factors[i].k = newk;
    }
    LL res = 1;
    REP(i,k) REP(j,factors[i].k) res *= factors[i].p;
    if(p<ORDER_CACHE) orderModPrimeCache[p] = res;
    return res;
}

LL calcOrbitsRek(const vector<PrimePower> &factors, const vector<vector<LL> > &orders, int nr, LL phi, LL order) {
    if (nr==size(factors)) {
        return phi==1 ? 0 : phi/order;
    }
    LL res = calcOrbitsRek(factors, orders, nr+1, phi, order);
    LL p = factors[nr].p;
    LL k = factors[nr].k;
    FOR (i,1,k) {
        if (i==1) {
            phi *= p-1;
            order = lcm(order, orders[nr][1]);
        } else {
            phi *= p;
            if (orders[nr][i] > orders[nr][i-1]) order *= p;
        }
        res += calcOrbitsRek(factors, orders, nr+1, phi, order);
    }
    return res;
}

// n odd, n <= 10^10+1
LL calcOrbits(LL n) {
    assert(largeFactoredRange.inRange(n));
    vector<PrimePower> factors = largeFactoredRange.get(n);
    int k = size(factors);
    vector<vector<LL> > orders(k);
    REP(i,k) {
        LL p = factors[i].p;
        int a = factors[i].k;
        orders[i].resize(a+1);
        LL pa = 1; REP(j,a) pa *= p;
        orders[i][0] = 1;
        orders[i][1] = calcOrderModuloPrime(p, n, factors);
        LL x=0; // 2^order mod pa
        LL pj = p;
        FOR(j,2,a) {
            if(j==2) x = mypowerModBig(2, orders[i][1], pa);
            else if(orders[i][j-1]>orders[i][j-2]) x = mypowerModBig(x, p, pa);
            assert(x % pj == 1);
            pj *= p;
            if(x % pj == 1) orders[i][j] = orders[i][j-1];
            else orders[i][j] = orders[i][j-1] * p;
        }
    }
    LL res = calcOrbitsRek(factors, orders, 0, 1, 1);
    return res;
}

int calc(LL L, LL R) {
    largeFactoredRange.calc(max(1LL, L - (R+1)/SMALL_FACTORED), R+1);
    const int MOD = 1000000007;
    LL res = 0;
    while (L <= R) {
        if (L&1) {
            res += mypowerModBig(26, 1 + calcOrbits(L), MOD);
            ++L;
        } else if (L==R) {
            res += mypowerModBig(26, calcOrbits(L+1), MOD);
            ++L;
        } else {
            res += 27 * mypowerModBig(26, calcOrbits(L+1), MOD);
            L += 2;
        }
        res %= MOD;
    }
    return int(res);
}

void go() {
    LL L = rLL();
    LL R = rLL();
    int res = calc(L,R);
    printf("%d\n", res);
}

int main() {
    calcSmallPrimes();
    smallFactoredRange.calc(1, SMALL_FACTORED);
    int ntc = rint();
    REP(tc,ntc) go();
}
