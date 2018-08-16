// BEGIN CUT HERE

// END CUT HERE
#line 5 "DengklekCountingFormations.cpp"

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

const int maxn=11, maxnm=maxn*(maxn-1)/2;
const int maxm=55, maxk=111;
const int mod=1e9+7;

int M, K;
int dpa[maxn][maxm][maxk];//n similar rows, ncolumn, color remaining
int dpb[maxn][maxm];//number of connected graph with vertices,edges
int dpc[maxn][maxm][maxn][maxm];//val for graph with vertices, edges, last number of vertices used, last number of edge used
int cnk[maxk][maxk];
int ifact[maxn];

int inv(int a, int p=mod-2){
    int x=1;
    for (; p; p>>=1, a=1ll*a*a%mod) if (p&1) x=1ll*x*a%mod;
    return x;
}

int pw(int v, int p){
    int x=1;
    REP(i,p) x=1ll*x*v%mod;
    return x;
}

int go1(int a, int b, int c){
    if (!b) return 1; 
    if (!c) return 0;
    int &r=dpa[a][b][c];
    if (r!=-1) return r;
    r=0;
    REP(i,b+1) r=(r+1ll*go1(a,b-i,c-1)*pw(cnk[b][i],a)%mod)%mod;
    return r;
}


int go2(int a, int b){
    if (a==1) return !b;
    if (b<a-1) return 0;
    int &r=dpb[a][b];
    if (r!=-1) return r;

    ll tot=cnk[a*(a-1)/2][b];
    FOR(i,1,a){
        int na=(a-i)*(a-i-1)/2;
        REP(j,b+1) tot-=1ll*cnk[a-1][i-1]*cnk[na][b-j]%mod*go2(i,j)%mod;
    }
    r=(mod+tot%mod)%mod;
    return r;
}

int go3(int a, int b, int c, int d){
    if (!a) return !b;
    if (d>b|| c*(c-1)/2<d) d=c++;
    if (a<c||b<d) return 0;
    int &r=dpc[a][b][c][d];
    if (r!=-1) return r;
    r=go3(a,b,c,d+1);

    int x=1ll*go1(c,M,K)*go2(c,d)%mod;
    int v=1;
    REP(i,a/c) if ((i+1)*d<=b){
        v=1ll*v*x%mod*cnk[a-i*c][c]%mod;
        r=(r+1ll*v*ifact[i+1]%mod*go3(a-c*(i+1),b-d*(i+1),c,d+1)%mod)%mod;
    }
    return r%=mod;
}


class DengklekCountingFormations {
	public:
	int numFormations(int N, int _M, int _K) {
        M=_M; K=_K;
        memset(dpa,-1,sizeof(dpa)); memset(dpb,-1,sizeof(dpb)); memset(dpc,-1,sizeof(dpc));
        ifact[0]=1; FOR(i,1,maxn) ifact[i]=1ll*inv(i)*ifact[i-1]%mod;

        REP(i,maxk) cnk[i][0]=cnk[i][i]=1;
        FOR(i,1,maxk) FOR(j,1,i) cnk[i][j]=(cnk[i-1][j-1]+cnk[i-1][j])%mod;

        ll res=0;
        int sgn=1;
        REP(i,N*(N-1)/2+1){ 
            res=(res+mod+sgn*go3(N,i,1,0))%mod, sgn*=-1;
        }
        return res;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 2; int Arg3 = 10; verify_case(0, Arg3, numFormations(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 58; int Arg3 = 58; verify_case(1, Arg3, numFormations(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 5; int Arg1 = 3; int Arg2 = 2; int Arg3 = 0; verify_case(2, Arg3, numFormations(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 3; int Arg1 = 5; int Arg2 = 7; int Arg3 = 894953467; verify_case(3, Arg3, numFormations(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 7; int Arg1 = 47; int Arg2 = 74; int Arg3 = 778075142; verify_case(4, Arg3, numFormations(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
  DengklekCountingFormations ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
