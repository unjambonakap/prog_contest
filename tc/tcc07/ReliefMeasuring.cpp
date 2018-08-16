// BEGIN CUT HERE

// END CUT HERE
#line 5 "ReliefMeasuring.cpp"

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


const int maxn=26;
const int inf=100000;

int graph[maxn][maxn];
int n, m;
int dp[maxn][maxn][maxn];
int pre[maxn][maxn][maxn][maxn];
int crow;
int solvea(int c, int a, int b){
	if (c==-1 || c==m)return 0;
	int &r=dp[c][a][b];
	if (r!=-1)return r;
	r=inf;
	int p=pre[crow][c][a][b];
	FOR(nb, crow, b) FOR(na, a, crow+(nb==crow))r=min(r, p+solvea(c-1, na, nb));
	
	return r;
}
int solveb(int c, int a, int b){
	if (c==-1 || c==m)return 0;
	int &r=dp[c][a][b];
	if (r!=-1)return r;
	r=inf;
	FOR(nb, crow, b) FOR(na, a, crow+(nb==crow)){
		int p=pre[crow][c][na][nb];
		r=min(r, p+solveb(c+1, na, nb));
	}
	return r;
}
class ReliefMeasuring {
	public:
	int minValuesToFix(vector <string> heights) {
		n=heights.size(), m=heights[0].length();
		REP(i, n) REP(j, m) graph[i][j]=heights[i][j]=='1';
		int c=inf;
		memset(pre, 0, sizeof(pre));
		REP(i, n)  FOR(b, i, n-1) FOR(a, 0, i+(b==i)) REP(j, m) REP(k, n) if (graph[k][j]!=(k>=a && k<=b))++pre[i][j][a][b];

		REP(i, n) REP(j, m){
			memset(dp, -1, sizeof(dp));
			crow=i;
			FOR(b, i, n-1) FOR(a, 0, i+(b==i))c=min(c, solvea(j, a, b)+solveb(j+1, a, b));
			
		}
		return c;
	}
	
// BEGIN CUT HERE
// {}
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {
		"0100",
		"1110",
		"0110",
		"0110"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(0, Arg1, minValuesToFix(Arg0)); }
	void test_case_1() { string Arr0[] = {"00100000000010001010000", "00000000000010101001001", "00000000000000000000010", "00001000010000101000000", "00000000001110010000001", "00000000001010001000000", "00000001010000000000000", "00000000000000000000000", "00000100100001001011000", "10000000000001000001100", "00000000001010011000000", "10010000000000001000001", "00000000010000100011001", "00010100101001100011000", "00000000000000101001010", "01000000000000001000000", "10000000000000000000000", "00001000000000000000001", "00000010000000100000000", "00000000000000000000001", "00000000000000000000000", "00010010000000000001000", "00000000000000000001000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(1, Arg1, minValuesToFix(Arg0)); }
	void test_case_2() { string Arr0[] = {"101", "010", "101"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(2, Arg1, minValuesToFix(Arg0)); }
	void test_case_3() { string Arr0[] = {"0010",
 "0101",
 "0010"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(3, Arg1, minValuesToFix(Arg0)); }
	void test_case_4() { string Arr0[] = {"1010",
 "0101",
 "1010",
 "0101"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(4, Arg1, minValuesToFix(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  ReliefMeasuring ___test; 
        ___test.run_test(1); 
        } 
// END CUT HERE
