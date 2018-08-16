// BEGIN CUT HERE

// END CUT HERE
#line 5 "SweetFruits.cpp"

#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <climits>
//#include <ext/hash_map>


using namespace std;
using namespace __gnu_cxx;



#define REP(i,n) for(int i = 0; i < int(n); ++i)
#define FOR(i, a, b) for(int i = (int)(a); i < (int)(b); ++i)
#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();++i)

#define two(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()


#define pb push_back
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n==0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}


const int maxb=(1<<20)+10;
const int mod=1e9+7;
const int maxn=44;

int sa[maxb], na[maxb];
int sb[maxb], nb[maxb];
int NC, N;
int n;

int ida[maxb], idb[maxb];
int cnt[maxn];
int have[maxn];

int cnk[maxn][maxn];

int cmpa(int a, int b){return sa[a]<sa[b];}
int cmpb(int a, int b){return sb[a]<sb[b];}


int dp[maxn];
int m[maxn][maxn];

int faste(int a, int p=mod-2){int x=1; for (; p; p>>=1, a=1ll*a*a%mod) if (p&1) x=1ll*x*a%mod; return x;}

int solve(){
    int res=1, na=n-1;

    REP(i,na){
        int p=-1;
        FOR(j,i,na) if (m[j][i]){p=j; break;}
        if (p==-1) return 0;
        REP(j,na) swap(m[p][j],m[i][j]);
        res=1ll*res*m[i][i]%mod;

        int x=faste(m[i][i]);
        REP(j,na) m[i][j]=1ll*m[i][j]*x%mod;
        FOR(j,i+1,na) for (int k=na-1; k>=i; --k) m[j][k]=(m[j][k]+1ll*(mod-m[j][i])*m[i][k])%mod;
    }
    assert(res>=0);
    return res;
}

int go(int a){
    int &r=dp[a];
    if (r!=-1) return r;
    r=0;
    REP(i,a) r+=mod-1ll*cnk[a][i]*go(i)%mod, r%=mod;

    memset(m,0,sizeof(m));
    REP(i,a){
        REP(j,a) m[i][j]=mod-1;
        FOR(j,N,n) m[i][j]=mod-1;
        m[i][i]=a+NC-1;
    }
    FOR(i,a,N){
        FOR(j,N,n) m[i][j]=mod-1;
        m[i][i]=NC;
    }
    FOR(i,N,n){
        REP(j,n) m[i][j]=mod-1;
        m[i][i]=n-1;
    }
    r+=solve(); r%=mod;
    assert(r>=0);
    return r;
}


class SweetFruits {
	public:
	int countTrees(vector <int> sn, int ms) {
        n=sn.size();

        REP(i,maxn) cnk[i][i]=cnk[i][0]=1;
        FOR(i,1,maxn) FOR(j,1,i) cnk[i][j]=(cnk[i-1][j]+cnk[i-1][j-1])%mod;

        vi aa;
        REP(i,sn.size()) if (sn[i]!=-1) aa.pb(sn[i]);
        N=aa.size();
        NC=n-N;

        vi l, r;
        REP(i,N) if (i<aa.size()/2) l.pb(aa[i]); else r.pb(aa[i]);

        REP(i,l.size()) sa[1<<i]=l[i];
        int u=1<<l.size();
        FOR(i,1,u) sa[i]=sa[i&(i-1)]+sa[i&-i], na[i]=na[i&(i-1)]+1;

        REP(i,r.size()) sb[1<<i]=r[i];
        int v=1<<r.size();
        FOR(i,1,v) sb[i]=sb[i&(i-1)]+sb[i&-i], nb[i]=nb[i&(i-1)]+1;

        REP(i,u) ida[i]=i; sort(ida,ida+u,cmpa);
        REP(i,v) idb[i]=i; sort(idb,idb+v,cmpb);




        memset(cnt,0,sizeof(cnt));
        memset(have,0,sizeof(have));
        int nl=l.size()+1;
        int j=v-1;
        for (int i=0; i<u; ++i){
            int x=ida[i];
            for (; j>=0 && sa[x]+sb[idb[j]]>ms; --j){
                int y=nb[idb[j]];
                REP(k,nl){
                    cnt[k+y]+=have[k];
                    if (cnt[k+y]>=mod) cnt[k+y]-=mod;
                }
            }
            ++have[na[x]];
        }
        for (; j>=0; --j){
            int y=nb[idb[j]];
            REP(k,nl){
                cnt[k+y]+=have[k];
                if (cnt[k+y]>=mod) cnt[k+y]-=mod;
            }
        }
        cnt[0]=1;

        memset(dp,-1,sizeof(dp));
        ll res=0;
        REP(i,N+1) res+=1ll*cnt[i]*go(i)%mod;
        return res%mod;
    }

    // BEGIN CUT HERE
    public:
    void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
    private:
    template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
    void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
    void test_case_0() { int Arr0[] = {1, 2, -1, 3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 3; verify_case(0, Arg2, countTrees(Arg0, Arg1)); }
    void test_case_1() { int Arr0[] = {1, 2, -1, 3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; int Arg2 = 7; verify_case(1, Arg2, countTrees(Arg0, Arg1)); }
    void test_case_2() { int Arr0[] = {-1, -1, 2, 5, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; int Arg2 = 20; verify_case(2, Arg2, countTrees(Arg0, Arg1)); }
    void test_case_3() { int Arr0[] = {2, 6, 8, 4, 1, 10, -1, -1, -1, -1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 15; int Arg2 = 17024000; verify_case(3, Arg2, countTrees(Arg0, Arg1)); }
    void test_case_4() { int Arr0[] = {1078451, -1, 21580110, 8284711, -1, 4202301, 3427559, 8261270, -1, 16176713,
        22915672, 24495540, 19236, 5477666, 12280316, 3305896, 17917887, 564911, 22190488, 21843923,
        23389728, 14641920, 9590140, 12909561, 20405638, 100184, 23336457, 12780498, 18859535, 23180993,
        10278898, 5753075, 21250919, 17563422, 10934412, 22557980, 24895749, 7593671, 10834579, 5606562}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 245243285; int Arg2 = 47225123; verify_case(4, Arg2, countTrees(Arg0, Arg1)); }

    // END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
    SweetFruits ___test; 
    ___test.run_test(-1); 
} 
// END CUT HERE
