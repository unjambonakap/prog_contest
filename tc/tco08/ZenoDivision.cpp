// BEGIN CUT HERE

// END CUT HERE
#line 5 "ZenoDivision.cpp"

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
inline int ctz(ull n){return n==1?0:ctz(n>>1)+1;}



ull strToull(const string &s){
	stringstream ss(s);
	ull a;
	ss>>a;
	return a;
}

string ulltostr(ull a){
	ostringstream os;
	os<<a;
	return os.str();
}


class ZenoDivision {
	public:
	string cycle(string _a, string _b) {
		ull a, b;
		a=strToull(_a), b=strToull(_b);
		int i, j;

		FOR (i, 1, 60){
			if ((twoll(i)-1)%b)continue;
			string s;
			a*=(twoll(i)-1)/b;
			for (j=0; j<i; ++j)
				s=(a&twoll(j)?"*":"-")+s;
			return s;

		}
		return "impossible";

	}

	// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "2"; string Arg1 = "3"; string Arg2 = "*-"; verify_case(0, Arg2, cycle(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "5"; string Arg1 = "7"; string Arg2 = "*-*"; verify_case(1, Arg2, cycle(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "0"; string Arg1 = "1"; string Arg2 = "-"; verify_case(2, Arg2, cycle(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "5"; string Arg1 = "9"; string Arg2 = "*---**"; verify_case(3, Arg2, cycle(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "1"; string Arg1 = "2"; string Arg2 = "impossible"; verify_case(4, Arg2, cycle(Arg0, Arg1)); }
	void test_case_5() { string Arg0 = "76861433640456464"; string Arg1 = "76861433640456465"; string Arg2 = "********************************************************----"; verify_case(5, Arg2, cycle(Arg0, Arg1)); }

	// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	ZenoDivision ___test; 
	___test.run_test(-1); 
} 
// END CUT HERE
