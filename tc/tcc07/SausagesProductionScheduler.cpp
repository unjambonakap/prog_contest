// BEGIN CUT HERE

// END CUT HERE
#line 5 "SausagesProductionScheduler.cpp"

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
inline int ctz(int n){return (n==0?-1:(n==1?0:ctz(n>>1)+1));}

const int maxn=55;

vi lim;
int ub[maxn][2], lb[maxn][2];
int n;

char dp[maxn][maxn*100];

class SausagesProductionScheduler {
	public:
	int maxCount(vector <string> lp, vector <string> up, vi _limits) {
		lim=_limits;
		n=lp.size();
		REP(i, n) istringstream(lp[i])>>lb[i][0]>>lb[i][1];
		REP(i, n) istringstream(up[i])>>ub[i][0]>>ub[i][1];

		REP(i, n) lb[i][0]=max((char)lb[i][0], char(100-ub[i][1])), ub[i][0]=min((char)ub[i][0], char(100-lb[i][1]));
		memset(dp, 0, sizeof(dp));
		dp[0][0]=1;
		REP(i, n)  FORV(k, i, 0) FOR(j, 0, n*100) if (dp[k][j]) FOR(u, lb[i][0], ub[i][0]) if (j+u<=n*100)dp[k+1][j+u]=1;

		FORV(i, n, 1) FOR(k, max(0, i*100-lim[1]), min(i*100, lim[0])) if (dp[i][k])return i;

		
		
		
		return 0;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	//{, , }
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"50 50"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"50 50"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {100, 100}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1; verify_case(0, Arg3, maxCount(Arg0, Arg1, Arg2)); }
//{, , }
	void test_case_1() { string Arr0[] = {"22 7", "4 2", "1 5", "4 1", "8 2", "17 7", "2 11", "16 1", "19 17", "5 15", "18 19", "1 4", "7 1", "3 6", "3 15", "3 25", "2 12", "5 2", "5 5", "2 3", "9 11", "19 3", "8 1", "10 4", "5 2", "19 1", "13 2", "9 8", "7 6", "23 4", "2 2", "2 8", "39 9", "17 2", "5 2", "3 18", "10 2", "2 3", "3 9", "16 4", "4 1", "6 9", "7 6", "6 2", "6 3", "7 16", "4 7", "20 12", "11 5", "3 6"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"25 20", "9 8", "38 7", "21 28", "32 15", "35 14", "12 22", "28 18", "27 38", "48 29", "21 23", "37 9", "11 9", "16 32", "28 26", "14 39", "15 40", "5 55", "20 27", "15 11", "10 29", "70 27", "9 1", "13 6", "9 66", "48 30", "43 10", "15 19", "16 11", "40 4", "14 3", "9 19", "50 10", "22 5", "19 6", "10 28", "16 12", "5 18", "31 17", "20 28", "16 17", "11 13", "24 30", "18 40", "17 8", "11 16", "15 24", "46 35", "16 11", "4 13"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {4945, 4849}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 0; verify_case(1, Arg3, maxCount(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"40 21", "6 10"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"89 71", "87 62"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {54, 69}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1; verify_case(2, Arg3, maxCount(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"66 11", "9 11", "13 4"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"85 70", "28 41", "29 88"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {280, 190}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; verify_case(3, Arg3, maxCount(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arr0[] = {"39 19", "6 68", "62 28"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"64 78", "41 86", "72 98"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {230, 232}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 3; verify_case(4, Arg3, maxCount(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  SausagesProductionScheduler ___test; 
       ___test.run_test(3);
        } 
// END CUT HERE
