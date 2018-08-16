// BEGIN CUT HERE

// END CUT HERE
#line 5 "Spacetsk.cpp"

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



const int maxn=2002;
const int mod=1e9+7;
const int maxp=2500000;

int cnk[maxn][maxn];
int gcd(int a, int b){ return b?gcd(b,a%b):a;}
int A[maxp],B[maxp];
int np=0;

class Spacetsk {
	public:
	int countsets(int L, int H, int K) {
        REP(i,maxn) cnk[i][0]=cnk[i][i]=1;
        FOR(i,1,maxn) FOR(j,1,i) cnk[i][j]=(cnk[i-1][j-1]+cnk[i-1][j])%mod;

        np=0;
        FOR(i,1,maxn) FOR(j,1,maxn) if (gcd(max(i,j),min(i,j))==1) A[np]=i, B[np++]=j;



        ++L; ++H;
        int res=0;
        int vert=1ll*cnk[H][K]*L%mod;

        if (K>1) REP(i,np){
            int ua=A[i], ub=(H-1)/B[i]+1;
            //if (min(ub,(L-1)/ua+1)<K) continue;
            int have=1;
            for (int j=0; j<L; j+=ua){
                int diff=min(L-j,ua);
                res=(res+1ll*diff*cnk[have][K])%mod;
                have=min(have+1,ub);
            }
        }
        res=res*2%mod;
        return (res+vert)%mod;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2000; int Arg1 = 2000; int Arg2 = 1000; int Arg3 = 4; verify_case(0, Arg3, countsets(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 1; int Arg3 = 4; verify_case(1, Arg3, countsets(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 1; int Arg3 = 9; verify_case(2, Arg3, countsets(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 2; int Arg3 = 23; verify_case(3, Arg3, countsets(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 5; int Arg1 = 5; int Arg2 = 3; int Arg3 = 202; verify_case(4, Arg3, countsets(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arg0 = 561; int Arg1 = 394; int Arg2 = 20; int Arg3 = 786097180; verify_case(5, Arg3, countsets(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
  Spacetsk ___test; 
        ___test.run_test(0); 
        } 
// END CUT HERE
