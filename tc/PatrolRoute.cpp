// BEGIN CUT HERE

// END CUT HERE
#line 5 "PatrolRoute.cpp"

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
const int maxv=8001;
int va[maxv], vb[maxv];
ll u[2*maxv];


class PatrolRoute {
	public:
	int countRoutes(int X, int Y, int minT, int maxT) {
        memset(va,0,sizeof(va)); memset(vb,0,sizeof(vb));
        maxT=min(maxT,2*maxv);
        REP(i,X) REP(j,i-1) va[2*(i-j)]+=i-j-1;
        REP(i,Y) REP(j,i-1) vb[2*(i-j)]+=i-j-1;
        int res=0;
        REP(i,maxv) REP(j,maxv) u[i+j]+=1ll*va[i]*vb[j];
        FOR(i,minT,maxT+1) res=(res+u[i])%mod;
        return 6ll*res%mod;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	//void test_case_0() { int Arg0 = 3; int Arg1 = 3; int Arg2 = 1; int Arg3 = 20000; int Arg4 = 6; verify_case(0, Arg4, countRoutes(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_0() { int Arg0 = 4000; int Arg1 = 4000; int Arg2 = 1; int Arg3 = 20000; int Arg4 = 6; verify_case(0, Arg4, countRoutes(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 3; int Arg2 = 4; int Arg3 = 7; int Arg4 = 0; verify_case(1, Arg4, countRoutes(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 4; int Arg1 = 6; int Arg2 = 9; int Arg3 = 12; int Arg4 = 264; verify_case(2, Arg4, countRoutes(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 7; int Arg1 = 5; int Arg2 = 13; int Arg3 = 18; int Arg4 = 1212; verify_case(3, Arg4, countRoutes(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arg0 = 4000; int Arg1 = 4000; int Arg2 = 4000; int Arg3 = 14000; int Arg4 = 859690013; verify_case(4, Arg4, countRoutes(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
  PatrolRoute ___test; 
        ___test.run_test(0);
        } 
// END CUT HERE
