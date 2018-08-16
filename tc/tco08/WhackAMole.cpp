// BEGIN CUT HERE

// END CUT HERE
#line 5 "WhackAMole.cpp"

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




class WhackAMole {
	public:
	string placeMoles(int numHoles, int numHammers) {
		int best=0;
		REP(i, two(numHoles)){
			REP(j, two(numHoles)) if (count_bit(j)==numHammers){
				bool ok=false;
				REP(k, numHoles) if ((j&((i<<k|i>>(numHoles-k))&two(numHoles)-1))==0){ok=true; break;}
				if (!ok)goto fail;
			}
			if (count_bit(i)>count_bit(best)) best=i;
fail:;
		}
		string s;
		FORV (i, numHoles-1, 0) s+=(best&two(i)?"X":"O");
		return s;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 1; string Arg2 = "O"; verify_case(0, Arg2, placeMoles(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 4; int Arg1 = 2; string Arg2 = "OOOX"; verify_case(1, Arg2, placeMoles(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 5; int Arg1 = 2; string Arg2 = "OOOXX"; verify_case(2, Arg2, placeMoles(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 6; int Arg1 = 2; string Arg2 = "OOXOXX"; verify_case(3, Arg2, placeMoles(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  WhackAMole ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
