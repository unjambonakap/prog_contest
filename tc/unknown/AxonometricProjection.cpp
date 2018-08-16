// BEGIN CUT HERE

// END CUT HERE
#line 5 "AxonometricProjection.cpp"

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
#define REPV(i, n) for (int i = (n) - 1; (int)i >= 0; --i)
#define FOR(i, a, b) for(int i = (int)(a); i <= (int)(b); ++i)
#define FORV(i, a, b) for(int i = (int)(a); i >= (int)(b); --i)

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

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
typedef vector<string> vs;

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

const int maxn=55;
const int mod=1e9+9;
const int maxh=11111;

ll A[maxn][maxn];
int X[maxn][maxn];
int n, m, ox, oy, x, y, H;
ll cnk[maxn][maxn];



ll fast_exp(ll a, int p){
    ll x=1;
    while(p){
        if (p&1) x=a*x%mod;
        p>>=1;
        a=a*a%mod;
    }
    return x;
}

ll proc(int a, int b){
    if (y==oy && a==ox) return 1;
    if (a==n) return b==oy;
    ll &r=A[a][b];
    if (r!=-1) return r;
    r=0;
    REP(i, oy-b+1) if (H||i==oy-b){
        r=(r+proc(a+1, b+i)*cnk[oy-b][i]%mod*
                fast_exp(H, oy-b-i)%mod*
                fast_exp(H+1, (a<ox?m:oy)-(oy-b)-y)%mod
          )%mod;

    }
    if (H && a<ox) r=(r+mod-proc(a+1, b)*fast_exp(H, m-y)%mod)%mod;
    return r;
}


class AxonometricProjection {
	public:
	int howManyWays(vector <int> ha, vector <int> hb) {
        REP(i, maxn) cnk[i][0]=cnk[i][i]=1;
        REP(i, maxn) REP(j, i) if (i&&j) cnk[i][j]=(cnk[i-1][j]+cnk[i-1][j-1])%mod;

        sort(ALL(ha)); sort(ALL(hb));
        n=ha.size(); m=hb.size();
        REP(i, n) REP(j, m) X[i][j]=min(ha[i], hb[j]);
        REP(i, n) if (X[i][m-1]<ha[i]) return 0;
        REP(i, m) if (X[n-1][i]<hb[i]) return 0;

        x=n, y=m;
        ll ans=1;
        while(1){
            if (!x && !y) break;
            ox=x, oy=y;
            if (x&&y){
                if (x==n) --x, --y;
                else if (X[x-1][y]==X[x][y-1]) --x, --y;
                else if (X[x-1][y]<X[x][y-1]) --y;
                else --x;

            }else if (x) --x; 
            else  --y;
            for (; x && X[x][y]==X[x-1][y]; --x);
            for (; y && X[x][y]==X[x][y-1]; --y);
            H=X[x][y];
            memset(A, -1, sizeof(A));
            ans=proc(x, y)*ans%mod;

        }
        return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 7; verify_case(0, Arg2, howManyWays(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {50,50,50,50,524}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {524,524}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 104060401; verify_case(1, Arg2, howManyWays(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {1,2,3,4,5,6,7,8,9,10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,3,4,5,6,7,8,9,10,11}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(2, Arg2, howManyWays(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {5,2,4,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {5,2,4,0,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 429287; verify_case(3, Arg2, howManyWays(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {5,2,4,52,24,524}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,4,20,24,500,504,520,524}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 97065655; verify_case(4, Arg2, howManyWays(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  AxonometricProjection ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE
