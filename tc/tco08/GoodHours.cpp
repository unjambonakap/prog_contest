// BEGIN CUT HERE

// END CUT HERE
#line 5 "GoodHours.cpp"

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




class GoodHours {
	public:
	int howMany(string bt, string at) {
		int a, b, c, d, ta, tb;
		at[2]=bt[2]=' ';
		istringstream ss(bt), sa(at);
		ss>>a>>b; sa>>c>>d;
		int p=1440;
		
		ta=a*60+b; tb=c*60+d;
		if (tb<ta)tb+=p;
		int n=0;
		FOR(i, ta, tb){
			int ni=i%p;
			a=ni/60;
			c=ni%60;
			b=a%10;
			a/=10;
			d=c%10;
			c/=10;
			if (a==b*c*d || a*b==c*d || a*b*c==d)++n;
		}
		return n;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "11:11"; string Arg1 = "11:11"; int Arg2 = 1; verify_case(0, Arg2, howMany(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "00:56"; string Arg1 = "12:32"; int Arg2 = 164; verify_case(1, Arg2, howMany(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "00:00"; string Arg1 = "00:59"; int Arg2 = 60; verify_case(2, Arg2, howMany(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "10:10"; string Arg1 = "10:20"; int Arg2 = 2; verify_case(3, Arg2, howMany(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "23:10"; string Arg1 = "01:23"; int Arg2 = 75; verify_case(4, Arg2, howMany(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  GoodHours ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
