// BEGIN CUT HERE

// END CUT HERE
#line 5 "EvenOnes.cpp"

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




class EvenOnes {
	public:
	int minOperations(vector <string> matrix) {
		int i, j;
		int n, m;
		n=matrix.size(); m=matrix[0].length();
		int nr, nc;

		nr=nc=0;
		for (i=0; i<n; ++i){
			int t=0;
			for (j=0; j<m; ++j)
				t+=(matrix[i][j]=='1');
			nr+=t%2;
		}
		for (j=0; j<m; ++j){
			int t=0;
			for (i=0; i<n; ++i)
				t+=(matrix[i][j]=='1');
			nc+=t%2;
		}
		int s=-1, ns;
		int t;

		ns=nr;
		if (ns%2==1)
			t=m-nc;
		else t=nc;
		if (t%2==0)
			if (s==-1 || s>ns+t)s=ns+t;

		ns=n-nr;
		if (ns%2==1)
			t=m-nc;
		else t=nc;
		if (t%2==1)
			if (s==-1 || s>ns+t)s=ns+t;

			

		
		return s;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {
 "111",
 "011",
 "001"
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(0, Arg1, minOperations(Arg0)); }
	void test_case_1() { string Arr0[] = {
  "111",
  "111",
  "111",
  "111",
  "111"
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(1, Arg1, minOperations(Arg0)); }
	void test_case_2() { string Arr0[] = {
  "00000",
  "00000",
  "00000"
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(2, Arg1, minOperations(Arg0)); }
	void test_case_3() { string Arr0[] = {
  "10101",
  "01010",
  "10101",
  "01010",
  "10101"
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(3, Arg1, minOperations(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  EvenOnes ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
