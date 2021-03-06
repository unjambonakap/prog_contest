// BEGIN CUT HERE

// END CUT HERE
#line 5 "MusicalChairs.cpp"

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




class MusicalChairs {
	public:
	string knockedOut(vector <string> pl, string ch, int seconds) {
		int n=pl.size();
		seconds%=pl.size();
		REP(i, n) if (ch[i]=='.'){
			return pl[(n+i-seconds)%n];

		}

		assert(0);
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"Emma Sue", "Billy Bob Thornton", "Joe", "Cassius Clay"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "hh.h"; int Arg2 = 1; string Arg3 = "Billy Bob Thornton"; verify_case(0, Arg3, knockedOut(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"Emma Sue", "Billy Bob Thornton", "Joe", "Cassius Clay"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "hh.h"; int Arg2 = 4; string Arg3 = "Joe"; verify_case(1, Arg3, knockedOut(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"Jack Dempsey", "Joe Louis", "Rocky Marciano",
 "Cassius Clay", "George Foreman", "Mike Tyson"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "h.hhhh"; int Arg2 = 500; string Arg3 = "Mike Tyson"; verify_case(2, Arg3, knockedOut(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"  itchy   ", "SCRATCHY"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = ".h"; int Arg2 = 0; string Arg3 = "  itchy   "; verify_case(3, Arg3, knockedOut(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arr0[] = {"Moe", "Larry", "Curly", "Moe"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "hh.h"; int Arg2 = 2; string Arg3 = "Moe"; verify_case(4, Arg3, knockedOut(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  MusicalChairs ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
