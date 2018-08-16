// BEGIN CUT HERE

// END CUT HERE
#line 5 "MonstersAndBunnies.cpp"

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



#define REP(i,n) for(i = 0; i < (n); i++)

#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define FOR(i, a, b) for(i = (a); i <= (b); i++)
#define FORV(i, a, b) for(i = (a); i >= (b); i--)

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();i++)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();i++)

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


double dp[1001][1001];
double solve(int a, int b){
	if (b==0)return 1.;

	double &r=dp[b][a];

	if (r>-0.5)return r;
	int s=a+b+1;

	double p;
	
	p=s*(s-1);

	double sa=0.;
	if (b>=2)sa+=b*(b-1)/p;
	if (a>=2)sa+=a*(a-1)/p;
	if (b>=1 && a>=1)sa+=b*a/p+a*b/p;
	
	if (b>=1)sa+=2*b/p;
	if (a>=1)sa+=2*a/p;

	r=0.;
	if (b>=2)
		r+=solve(a, b-2)*b*(b-1)/p;
	if (b>=1 && a>=1)
		r+=solve(a-1, b)*(2*a*b/p);
	assert(sa+10e-5>=1.);

	double c=1.;
	if (a>=2)
		c-=a*(a-1)/p;

	if (a>=1){
		double tr;
		tr=(r+solve(a-1, b)*2*a/p)/c;
		c-=a/p;
		r=max(r/c, tr);
	}else
		r/=c;
	
	return r;
}



class MonstersAndBunnies {
	public:
	double survivalProbability(int M, int B) {
		int i, j;
		
		REP(i, M+1)
			REP(j, B+1)
				dp[i][j]=-1.;
		return solve(B, M);
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 4; int Arg1 = 1; double Arg2 = 1.0; verify_case(0, Arg2, survivalProbability(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 0; int Arg1 = 47; double Arg2 = 1.0; verify_case(1, Arg2, survivalProbability(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 1; int Arg1 = 0; double Arg2 = 0.0; verify_case(2, Arg2, survivalProbability(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 1; int Arg1 = 47; double Arg2 = 0.0; verify_case(3, Arg2, survivalProbability(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 2; int Arg1 = 0; double Arg2 = 0.3333333333333333; verify_case(4, Arg2, survivalProbability(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  MonstersAndBunnies ___test; 
        ___test.run_test(0); 
        } 
// END CUT HERE
