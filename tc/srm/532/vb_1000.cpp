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

const int mod=1e9+7;
const int maxn=55;
const int maxm=11;
const int maxk=111;

int cnk[maxn][maxn];
int dp[maxm][maxn][maxn][maxk];//nrow,ncolumn remain, last asst, num color

int go(int m, int n, int last, int k){
    if (!m) return 1;
    if (!n) return m==1;
    if (last>n) return 0;
    if (!k) return 0;
    int &r=dp[m][n][last][k];
    if (r!=-1) return r;
    r=0;
    int pw=1;

    REP(i,m+1) r=(r+1ll*pw*go(i,n-last,0,k-1)%mod*go(m-i,n,last+1,k)%mod*cnk[m][i]%mod)%mod, pw=1ll*pw*cnk[n][last]%mod;
    return r;

}


class DengklekCountingFormations {
	public:
	int numFormations(int M, int N, int K) {
        REP(i,maxn) cnk[i][i]=cnk[i][0]=1;
        FOR(i,1,maxn) FOR(j,1,i) cnk[i][j]=(cnk[i-1][j-1]+cnk[i-1][j])%mod;

        memset(dp,-1,sizeof(dp));
        return go(M,N,0,K);
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
