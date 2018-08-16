// BEGIN CUT HERE

// END CUT HERE
#line 5 "PreciousStones.cpp"

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

void checkmin(int &a, int b){if (b<a)a=b;}
void checkmax(int &a, int b){if (b>a)a=b;}

const double EPS=10e-9;


int dp[51][10100];

class PreciousStones {
	public:
	double value(vector <int> ta, vector <int> tb) {
		int n=ta.size();
		int i, j, k;


		double res=0.;
		REP(i, n){
			vi na, nb;
			int sa=0;

			REP(j, n) if (j!=i)na.pb(ta[j]), nb.pb(tb[j]), sa+=ta[j];

			memset(dp, -1, sizeof(dp));
			int mid=5020;

			dp[0][mid]=0;
			REP(j, n-1) REP(k, 10100) if (dp[j][k]!=-1){
				checkmax(dp[j+1][k+na[j]], dp[j][k]+na[j]);
				checkmax(dp[j+1][k-nb[j]], dp[j][k]);
			}

			REP(k, 10100) if (dp[n-1][k]!=-1){
				int ca, cb;
				ca=dp[n-1][k], cb=mid-k+ca;
				if (ca+ta[i]<cb || cb+tb[i]<ca)continue;
				double v=double(cb-ca+tb[i])/(ta[i]+tb[i]);
				
				res=max(res, ca+ta[i]*v);

			}


		}
		return res;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = { 10, 6 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 3, 10 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 10.0; verify_case(0, Arg2, value(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = { 30 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 15 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 10.0; verify_case(1, Arg2, value(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = { 0, 0 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 10, 11 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.0; verify_case(2, Arg2, value(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = { 3, 5, 4 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 3, 5, 4 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 6.0; verify_case(3, Arg2, value(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = { 1, 2, 3 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 2, 2, 2 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 3.5; verify_case(4, Arg2, value(Arg0, Arg1)); }
	void test_case_5() { int Arr0[] = { 11, 9, 13, 10 }
; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 8, 14, 17, 21 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 28.304347826086957; verify_case(5, Arg2, value(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  PreciousStones ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE
