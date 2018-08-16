// BEGIN CUT HERE

// END CUT HERE
#line 5 "CubeOfDice.cpp"

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




class CubeOfDice {
	public:
	long long minimumSum(int N, vector <int> values) {
		int minl[3];
		int sum=0;
		ll s=0;
		ll n=N;
		int i, j, k;
		for (i=0; i<6; ++i)
			sum+=values[i];
		int icomp[]={5, 4, 3, 2, 1, 0};
		minl[0]=*min_element(ALL(values));
		minl[1]=INT_MAX;

		for (i=0; i<6; ++i)
			for (j=0; j<6; ++j){
				if (j==i || j==6-i-1)continue;
				minl[1]=min(minl[1], values[i]+values[j]);
			}
		
		minl[2]=INT_MAX;
		REP(i, 6) REP(j, 6) REP(k, 6){
			if (j==i || j==k || i==k)continue;
			if (j==5-i || k==5-i || k==5-j)continue;
			minl[2]=min(minl[2], values[i]+values[j]+values[k]);
		}



		if (n==1)return sum-*max_element(ALL(values));

		s+=((n-2)*(n-2)*5+(n-2)*4)*minl[0];
		s+=((n-2)*8+4)*minl[1];
		s+=4*minl[2];
		return s;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arr1[] = {1,2,3,4,5,6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 36LL; verify_case(0, Arg2, minimumSum(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 3; int Arr1[] = {1,2,3,4,5,6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 69LL; verify_case(1, Arg2, minimumSum(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 1000000; int Arr1[] = {50,50,50,50,50,50}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 250000000000000LL; verify_case(2, Arg2, minimumSum(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 10; int Arr1[] = {1,1,1,1,50,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 500LL; verify_case(3, Arg2, minimumSum(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  CubeOfDice ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
