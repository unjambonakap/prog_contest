// BEGIN CUT HERE

// END CUT HERE
#line 5 "ColorfulBalls.cpp"

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

#define SZ(a) (int((a).size()))
#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()


#define pb push_back
#define PF push_front
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;

inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}


class ColorfulBalls {
	public:
	double expectedStepCount(string colors) {
		int n=colors.length();
		if (n==1)return 0.;
		double store[10003][26];
		double ans=0.;
		REP(i, 26){
			int cnt=0;
			REP(j, n) if (colors[j]==i+'A')++cnt;
			if (cnt==0)continue;
			memset(store, 0, sizeof(store));
			store[0][cnt]=1.;

			REP(j, 10000) FOR(k, 0, n){
				double p=double(k)*(n-k)/n/(n-1);
				store[j+1][k]+=(1.-2*p)*store[j][k];
				if (k>0)store[j+1][k-1]+=p*store[j][k];
				if (k<n)store[j+1][k+1]+=p*store[j][k];
			}
			double tans=0.;
			REP(j, 10000)
				tans+=(j+1)*(store[j+1][n]-store[j][n]);
			ans+=tans;

		}
		return ans;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "AB"; double Arg1 = 1.0; verify_case(0, Arg1, expectedStepCount(Arg0)); }
	void test_case_1() { string Arg0 = "Q"; double Arg1 = 0.0; verify_case(1, Arg1, expectedStepCount(Arg0)); }
	void test_case_2() { string Arg0 = "AAAAAAA"; double Arg1 = 0.0; verify_case(2, Arg1, expectedStepCount(Arg0)); }
	void test_case_3() { string Arg0 = "ZCZ"; double Arg1 = 3.0; verify_case(3, Arg1, expectedStepCount(Arg0)); }
	void test_case_4() { string Arg0 = "KLM"; double Arg1 = 4.0; verify_case(4, Arg1, expectedStepCount(Arg0)); }
	void test_case_5() { string Arg0 = "AAABB"; double Arg1 = 11.666666666666668; verify_case(5, Arg1, expectedStepCount(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  ColorfulBalls ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
