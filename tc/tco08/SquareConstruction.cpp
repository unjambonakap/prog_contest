// BEGIN CUT HERE

// END CUT HERE
#line 5 "SquareConstruction.cpp"

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


string intToStr(int a){
	ostringstream os;
	os<<a;
	return os.str();

}


class SquareConstruction {
	public:

	vector <string> construct(int n, int a, int b, int c, int d) {
		int mp[n][n];
		int i, j, k, step, na;
		memset(mp, -1, sizeof(mp));
		step=0;
		i=j=0;
		na=1;
		while(1){
			if (mp[i][j]!=-1)
				i=(i+c)%n, j=(j+d)%n;
			if (mp[i][j]==-1){
				mp[i][j]=na++;
				i=(i+a)%n, j=(j+b)%n;
			}else break;

		}
		vs res(n);
		REP(i, n)
			REP(j, n)
				res[i]+=intToStr(mp[i][j])+(j==n-1?"":" ");
		return res;
				
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arg0 = 5; int Arg1 = 0; int Arg2 = 0; int Arg3 = 0; int Arg4 = 0; string Arr5[] = {"1 -1 -1 -1 -1", "-1 -1 -1 -1 -1", "-1 -1 -1 -1 -1", "-1 -1 -1 -1 -1", "-1 -1 -1 -1 -1" }; vector <string> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); verify_case(0, Arg5, construct(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { int Arg0 = 5; int Arg1 = 1; int Arg2 = 1; int Arg3 = 2; int Arg4 = 2; string Arr5[] = {"1 -1 -1 -1 -1", "-1 2 -1 -1 -1", "-1 -1 3 -1 -1", "-1 -1 -1 4 -1", "-1 -1 -1 -1 5" }; vector <string> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); verify_case(1, Arg5, construct(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { int Arg0 = 5; int Arg1 = 1; int Arg2 = 1; int Arg3 = 1; int Arg4 = 0; string Arr5[] = {"1 22 18 14 10", "6 2 23 19 15", "11 7 3 24 20", "16 12 8 4 25", "21 17 13 9 5" }; vector <string> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); verify_case(2, Arg5, construct(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { int Arg0 = 5; int Arg1 = 0; int Arg2 = 1; int Arg3 = 2; int Arg4 = 3; string Arr5[] = {"1 2 3 4 5", "17 18 19 20 16", "8 9 10 6 7", "24 25 21 22 23", "15 11 12 13 14" }; vector <string> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); verify_case(3, Arg5, construct(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_4() { int Arg0 = 6; int Arg1 = 1; int Arg2 = 2; int Arg3 = 2; int Arg4 = 2; string Arr5[] = {"1 -1 15 -1 11 -1", "12 -1 2 -1 16 -1", "17 -1 7 -1 3 -1", "4 -1 18 -1 8 -1", "9 -1 5 -1 13 -1", "14 -1 10 -1 6 -1" }; vector <string> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); verify_case(4, Arg5, construct(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_5() { int Arg0 = 1; int Arg1 = 0; int Arg2 = 0; int Arg3 = 0; int Arg4 = 0; string Arr5[] = {"1" }; vector <string> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); verify_case(5, Arg5, construct(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  SquareConstruction ___test; 
        ___test.run_test(2); 
        } 
// END CUT HERE
