// BEGIN CUT HERE

// END CUT HERE
#line 5 "OptimalPlay.cpp"

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


const int maxn=51;


class OptimalPlay {
	public:
	double winnings(vector <double> betProb, vector <double> callProb) {
		int n=betProb.size();

		double p=1./n;
		double res=0.;
		REP(i, n){
			double t=0.;
			double pa, pb, pc;
			//p1 bets
			pa=pb=pc=0.;
			FOR(j, 0, i-1)pa+=betProb[j];
			FOR(j, i+1, n-1)pc+=betProb[j];
			pb=betProb[i];
			res+=max(0., (2*pa+0.5*pb-pc)*p);

			//now p1 checks 
			//p2 checks
			t=((i-pa)*1+0.5*(1-pb))*p;
			//p2 bets
			double ta, tb, tc;
			ta=tb=tc=0.;
			FOR(j, 0, i-1)ta+=callProb[j];
			FOR(j, i+1, n-1)tc+=callProb[j];
			tb=callProb[i];
			t=max(t, (ta*2+(i-ta-pa)+
					tb*0.5+(1-tb-pb)+
					(n-i-1-tc-pc)-tc)*p);
			res+=t;
		}
		return res*p;
		
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { double Arr0[] = {0,0}; vector <double> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arr1[] = {0,0}; vector <double> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 1.0; verify_case(0, Arg2, winnings(Arg0, Arg1)); }
	void test_case_1() { double Arr0[] = {1,1,1}; vector <double> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arr1[] = {0,0,0}; vector <double> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.6666666666666666; verify_case(1, Arg2, winnings(Arg0, Arg1)); }
	void test_case_2() { double Arr0[] = {0.5,0,1}; vector <double> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arr1[] = {0,1,0}; vector <double> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.5833333333333334; verify_case(2, Arg2, winnings(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  OptimalPlay ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE
