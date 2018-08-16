// BEGIN CUT HERE

// END CUT HERE
#line 5 "KingdomAndCities.cpp"

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


const int mod=1e9+7;
const int maxn=55;
int dp[4][maxn][maxn];
int cnk[maxn*maxn][maxn];
int add[]={0,1,2,2};

int go2(int n, int m, int f);

int go1(int n, int m, int f){
    if (m<0) return 0;
    if (n==1) return 0;
    
    int &r=dp[f][n][m];
    if (r!=-1) return r;

    ll x=0;
    if (f!=2) FOR(i,1,n) REP(j,m+1) x+=1ll*cnk[n-1][i]*cnk[i*(i-1)/2][j]%mod*go2(n-i,m-j,f)%mod;
    else{
        FOR(i,1,n) REP(j,m+1) x+=1ll*cnk[n-2][i-1]*cnk[i*(i+1)/2][j]%mod*go2(n-i,m-j,1)%mod;
        FOR(i,1,n-1) REP(j,m+1) x+=1ll*cnk[n-2][i]*cnk[i*(i-1)/2][j]%mod*go2(n-i,m-j,2)%mod;
    }

    return r=x%mod;
}


int go2(int n, int m, int f){ return m<0?0:(mod+cnk[(n+add[f])*(n+add[f]-1)/2][m]-go1(n,m,f))%mod; }


class KingdomAndCities {
	public:
	int howMany(int N, int M, int K) {
        memset(dp,-1,sizeof(dp));
        REP(i,maxn*maxn) cnk[i][0]=1;
        REP(i,maxn) cnk[i][i]=1;
        FOR(i,1,maxn*maxn) FOR(j,1,min(i,maxn)) cnk[i][j]=(cnk[i-1][j]+cnk[i-1][j-1])%mod;


        ll res=0;
        if (!M) res=go2(N,K,0);
        else if (M==1) res=1ll*(N-1)*(N-2)/2*go2(N-2,K-2,1);
        else{
            REP(ia,N) REP(ja,ia) REP(ib,N) REP(jb,ib) if (ja!=0 && jb!=1 && ib!=1){
                if (ja==1 || jb==0){
                    if (jb!=0 || ja!=1) continue;
                    if (ia==ib) res+=go2(N-2,K-3,0);
                    else res+=go2(N-3,K-3,1);
                }else{
                    int nc=(ia==ib)+(ja==ib)+(ia==jb)+(ja==jb);
                    if (nc==1) res+=go2(N-4,K-4,3);
                    else if (nc==2) res+=go2(N-3,K-4,1);
                    else res+=go2(N-4,K-4,2);
                }
            }
        }
        return res%mod;
    }

    // BEGIN CUT HERE
    public:
    void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
    private:
    template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
    void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
    //void test_case_0() { int Arg0 = 3; int Arg1 = 0; int Arg2 = 3; int Arg3 = 1; verify_case(0, Arg3, howMany(Arg0, Arg1, Arg2)); }
    void test_case_0() { int Arg0 = 4; int Arg1 = 2; int Arg2 = 3; int Arg3 = 1; verify_case(0, Arg3, howMany(Arg0, Arg1, Arg2)); }
    void test_case_1() { int Arg0 = 4; int Arg1 = 1; int Arg2 = 4; int Arg3 = 9; verify_case(1, Arg3, howMany(Arg0, Arg1, Arg2)); }
    void test_case_2() { int Arg0 = 5; int Arg1 = 2; int Arg2 = 11; int Arg3 = 0; verify_case(2, Arg3, howMany(Arg0, Arg1, Arg2)); }
    void test_case_3() { int Arg0 = 5; int Arg1 = 0; int Arg2 = 8; int Arg3 = 45; verify_case(3, Arg3, howMany(Arg0, Arg1, Arg2)); }
    void test_case_4() { int Arg0 = 10; int Arg1 = 2; int Arg2 = 20; int Arg3 = 150810825; verify_case(4, Arg3, howMany(Arg0, Arg1, Arg2)); }

    // END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
    KingdomAndCities ___test; 
    ___test.run_test(4);
} 
// END CUT HERE
