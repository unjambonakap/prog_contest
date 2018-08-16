// BEGIN CUT HERE

// END CUT HERE
#line 5 "CodeRed.cpp"

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




class CodeRed {
	public:
	int count(string text) {
		int pb, pc;
		int c=0;
		pb=pc=0;
		REP(i, text.length()){
			if (pc){
				pc=0;
			   if(text[i]=='d' || text[i]=='D')++c, pc=0;
			}
			if (pb){
				pb=0;
			   if (text[i]=='e' || text[i]=='E')pc=1, pb=0;
			}
			if (text[i]=='r' || text[i]=='R')pb=1;
		}
		return c;

		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "the detective questioned his credibility"; int Arg1 = 1; verify_case(0, Arg1, count(Arg0)); }
	void test_case_1() { string Arg0 = "Server ERRED in Redirecting Spam"; int Arg1 = 2; verify_case(1, Arg1, count(Arg0)); }
	void test_case_2() { string Arg0 = "  read the RED sign   said fReD"; int Arg1 = 2; verify_case(2, Arg1, count(Arg0)); }
	void test_case_3() { string Arg0 = "pure delight"; int Arg1 = 0; verify_case(3, Arg1, count(Arg0)); }
	void test_case_4() { string Arg0 = "re"; int Arg1 = 0; verify_case(4, Arg1, count(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  CodeRed ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
