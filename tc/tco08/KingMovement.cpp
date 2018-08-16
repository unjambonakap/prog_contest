// BEGIN CUT HERE

// END CUT HERE
#line 5 "KingMovement.cpp"

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




class KingMovement {
	public:
	string finalPosition(string sap, string sop, vector <string> m) {
		int xa, ya, xo, yo;
		xa=sap[0]-'A', ya=sap[1]-'1';
		xo=sop[0]-'A', yo=sop[1]-'1';
		FE(it, m){
			int nx, ny;
			int vx, vy;
			vx=vy=0;
			FE(ita, *it)
				if (*ita=='L')--vx;
				else if (*ita=='R')++vx;
				else if (*ita=='T')++vy;
				else if (*ita=='B')--vy;
			nx=xa+vx; ny=ya+vy;
			if (nx<0 || ny<0 || nx>=8 || ny>=8)continue;
			if (nx==xo && ny==yo){
				nx+=vx, ny+=vy;
				if (nx<0 || ny<0 || nx>=8 || ny>=8)continue;
				xo=nx, yo=ny;
			}

			xa+=vx; ya+=vy;
		}
		string s="aa,aa";
		s[0]=xa+'A';
		s[1]=ya+'1';
		s[3]=xo+'A';
		s[4]=yo+'1';
		return s;

	}

	// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "A1"; string Arg1 = "H8"; string Arr2[] = {"T"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "A2,H8"; verify_case(0, Arg3, finalPosition(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arg0 = "A1"; string Arg1 = "A2"; string Arr2[] = {"T"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "A2,A3"; verify_case(1, Arg3, finalPosition(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arg0 = "A1"; string Arg1 = "A2"; string Arr2[] = {"T", "R"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "B2,A3"; verify_case(2, Arg3, finalPosition(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arg0 = "A1"; string Arg1 = "A2"; string Arr2[] = {"B", "L", "LB", "RB", "LT"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "A1,A2"; verify_case(3, Arg3, finalPosition(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arg0 = "A8"; string Arg1 = "B7"; string Arr2[] = {"RB", "RB", "RB", "RB", "RB", "RB", 
		"RB", "RB", "RB", "RB", "RB", "RB", 
		"RB", "RB", "RB", "RB", "RB", "RB"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "G2,H1"; verify_case(4, Arg3, finalPosition(Arg0, Arg1, Arg2)); }
	void test_case_5() { string Arg0 = "C1"; string Arg1 = "B1"; string Arr2[] = {"L", "T", "LB"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "B2,A1"; verify_case(5, Arg3, finalPosition(Arg0, Arg1, Arg2)); }

	// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	KingMovement ___test; 
	___test.run_test(-1); 
} 
// END CUT HERE
