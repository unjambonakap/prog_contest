// BEGIN CUT HERE

// END CUT HERE
#line 5 "FoxSearchingRuins.cpp"

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

const int maxn=1024;
const int maxv=1e9;
const ll inf=1e16;

int x[maxn], y[maxn], V[maxn];
int n, m;
int tb[maxn];
int xl[maxn];
int f[maxn][maxn];
int A[2*maxn][maxn+1], B[2*maxn][maxn+1];
int u[maxn][maxn], v[maxn][maxn];

void bit_update(int *a, int p, int v){for (; p<=maxn; p+=p&-p) if (a[p]<v) a[p]=v;} 
int bit_query(int *a, int p){int res=0; for (; p; p-=p&-p) if (res<a[p]) res=a[p]; return res;}

int cmp(int a,int b){return x[a]<x[b];}

void doit(int &a, int v){
    if (a<v) a=v;
    if (a>maxv) a=maxv;
}

class FoxSearchingRuins {
	public:
	long long theMinTime(int W, int H, int jewelCount, int _m, int goalValue, int tx, int ty, vector <int> seeds) {
        n=jewelCount; m=_m;
        ll res=inf;
        x[0]=(1ll*seeds[1]*seeds[0]+seeds[2])%W;
        y[0]=(1ll*seeds[4]*seeds[3]+seeds[5])%H;
        V[0]=(1ll*seeds[7]*seeds[6]+seeds[8])%seeds[9];
        FOR(i, 1, n){
            x[i]=(1ll*seeds[1]*x[i-1]+seeds[2])%W;
            y[i]=(1ll*seeds[4]*y[i-1]+seeds[5])%H;
            V[i]=(1ll*seeds[7]*V[i-1]+seeds[8])%seeds[9];
        }
        set<int> sy; REP(i, n) sy.insert(y[i]);
        memset(A, 0, sizeof(A));
        memset(B, 0, sizeof(B));

        FE(it, sy){
            int na=0;
            REP(i, n) if (y[i]==*it) tb[na++]=i;
            sort(tb,tb+na,cmp);
            REP(i, na) xl[i]=x[tb[i]];
            REP(i, na) memset(u[i], 0, sizeof(int)*(m+1)), memset(v[i], 0, sizeof(int)*(m+1));

            REP(i, na) REP(j, m+1){
                doit(u[i][j], V[tb[i]]+bit_query(A[xl[i]+m-j], xl[i]+1));
                doit(u[i][j], V[tb[i]]+bit_query(B[W-xl[i]+m-j], W-xl[i]));
                if (i&&m-j>=xl[i]-xl[i-1]) doit(u[i][j+xl[i]-xl[i-1]], V[tb[i]]+u[i-1][j]);
            }
            for (int i=na-1; i>=0; --i) REP(j, m+1){
                doit(v[i][j], V[tb[i]]+bit_query(A[xl[i]+m-j], xl[i]+1));
                doit(v[i][j], V[tb[i]]+bit_query(B[W-xl[i]+m-j], W-xl[i]));
                if (i<na-1&&m-j>=xl[i+1]-xl[i]) doit(v[i][j+xl[i+1]-xl[i]], V[tb[i]]+v[i+1][j]);
            }

            REP(i, na) REP(j, m+1){
                int tmp=f[tb[i]][j]=max(u[i][j], v[i][j]);
                bit_update(A[xl[i]+m-j], xl[i]+1, tmp);
                bit_update(B[W-xl[i]+m-j], W-xl[i], tmp);
                if (tmp>=goalValue){
                    checkmin(res, 1ll*j*tx+1ll*ty*y[tb[i]]);
                }
            }

        }
        
        return res==inf?-1:res;
    }

    // BEGIN CUT HERE
    public:
    void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
    private:
    template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
    void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
    void test_case_0() { int Arg0 = 5; int Arg1 = 8; int Arg2 = 5; int Arg3 = 7; int Arg4 = 10; int Arg5 = 3; int Arg6 = 1; int Arr7[] = {979, 777, 878, 646, 441, 545, 789, 896, 987, 10}; vector <int> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); long long Arg8 = 5LL; verify_case(0, Arg8, theMinTime(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)); }
    void test_case_1() { int Arg0 = 7; int Arg1 = 8; int Arg2 = 10; int Arg3 = 3; int Arg4 = 10; int Arg5 = 3; int Arg6 = 10; int Arr7[] = {0, 1, 1, 0, 1, 3, 1011, 3033, 2022, 10}; vector <int> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); long long Arg8 = 29LL; verify_case(1, Arg8, theMinTime(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)); }
    void test_case_2() { int Arg0 = 7; int Arg1 = 8; int Arg2 = 10; int Arg3 = 3; int Arg4 = 14; int Arg5 = 3; int Arg6 = 10; int Arr7[] = {0, 1, 1, 0, 1, 3, 1011, 3033, 2022, 10}; vector <int> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); long long Arg8 = 59LL; verify_case(2, Arg8, theMinTime(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)); }
    void test_case_3() { int Arg0 = 7; int Arg1 = 8; int Arg2 = 10; int Arg3 = 4; int Arg4 = 14; int Arg5 = 3; int Arg6 = 10; int Arr7[] = {0, 1, 1, 0, 1, 3, 1011, 3033, 2022, 10}; vector <int> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); long long Arg8 = 42LL; verify_case(3, Arg8, theMinTime(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)); }
    void test_case_4() { int Arg0 = 497; int Arg1 = 503; int Arg2 = 989; int Arg3 = 647; int Arg4 = 100000; int Arg5 = 13; int Arg6 = 14; int Arr7[] = {7613497, 5316789, 1334537, 2217889, 6349551, 978463, 1234567, 2345678, 3456789, 1000}; vector <int> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); long long Arg8 = -1LL; verify_case(4, Arg8, theMinTime(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)); }
    void test_case_5() { int Arg0 = 1000; int Arg1 = 749613275; int Arg2 = 1000; int Arg3 = 1000; int Arg4 = 7500000; int Arg5 = 97; int Arg6 = 6; int Arr7[] = {224284427, 617001937, 294074399, 606566321, 202762619, 419798101, 200613401, 640663967, 417565817, 170000}; vector <int> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); long long Arg8 = 3780225876LL; verify_case(5, Arg8, theMinTime(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)); }

    // END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
    FoxSearchingRuins ___test; 
    ___test.run_test(-1); 
} 
// END CUT HERE
