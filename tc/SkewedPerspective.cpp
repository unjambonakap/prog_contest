// BEGIN CUT HERE

// END CUT HERE
#line 5 "SkewedPerspective.cpp"

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
const int maxn=53;
int dp[9][maxn][11][maxn+1][10][2];//col, nA, nB, nhidden, nodd, last


int W, B;
vi cl;
int nc;
int A[maxn][maxn];
int cnk[maxn][maxn];

int proc(int a, int b){
    if (a==cl.size()) return b==0;
    int &r=A[a][b];
    if (r!=-1) return r;
    r=0;

    REP(i,cl[a]+1) if (b>=i) r=(r+1ll*cnk[b][i]*proc(a+1,b-i))%mod;
    
    return r;
}

int go(int col, int nA, int nB, int u, int v, int last){
    int remc=nc-nA-v;
    int remb=B-col-nB;
    if (2*remb+remc<2*u || remb<0||remc<0) return 0;
    assert(nA<=50);
    assert(u<=50);
    assert(col<=9);
    assert(v<=8);

    int &r=dp[col][nA][nB][u][v][last];
    if (r!=-1) return r;
    r=proc(0,nA);//stop here
    r=(r+go(col,nA+1,nB,u,v,0))%mod;
    r=(r+go(col,nA,nB+1,u,v,1))%mod;

    if (!col&&W>1&&!nA&&nB==1) r=(r+go(col+1,nA,nB,0,1,1))%mod;
    
    if (col+1<W && !last){
        int h=nA+col+2*nB-1;
        r=(r+go(col+1,nA,nB,u+h/2,v+(h&1),1))%mod;
    }
    return r;
}

class SkewedPerspective {
    public:
        int countThem(vector <int> cubes, int _B, int _W) {
            W=_W;
            B=_B;
            cl=cubes;
            nc=0;
            REP(i,cl.size()) nc+=cl[i];

            memset(dp,-1,sizeof(dp));
            memset(A,-1,sizeof(A));
            REP(i,maxn) cnk[i][i]=cnk[i][0]=1;
            FOR(i,1,maxn) FOR(j,1,i) cnk[i][j]=(cnk[i-1][j]+cnk[i-1][j-1])%mod;
            return (mod-1+go(0,0,0,0,0,1))%mod;
        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        void test_case_0() { int Arr0[] = {11,9}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; int Arg2 = 1; int Arg3 = 19; verify_case(0, Arg3, countThem(Arg0, Arg1, Arg2)); }
        //void test_case_0() { int Arr0[] = {1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 2; int Arg3 = 19; verify_case(0, Arg3, countThem(Arg0, Arg1, Arg2)); }
        void test_case_1() { int Arr0[] = {1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 2; int Arg3 = 19; verify_case(1, Arg3, countThem(Arg0, Arg1, Arg2)); }
        void test_case_2() { int Arr0[] = {}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; int Arg2 = 5; int Arg3 = 5; verify_case(2, Arg3, countThem(Arg0, Arg1, Arg2)); }
        void test_case_3() { int Arr0[] = {7,7,7}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 8; int Arg3 = 301226488; verify_case(3, Arg3, countThem(Arg0, Arg1, Arg2)); }

        // END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
    SkewedPerspective ___test; 
    ___test.run_test(-1);
} 
// END CUT HERE
