// BEGIN CUT HERE

// END CUT HERE
#line 5 "BinaryMatrix.cpp"

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



int dp[41][21][21][21][21];//completely define a possible state
int mp[40][5];
int state[5];
int cor[4];
int n;
vi col;
int INF=100000;

int solve(int p){
	int i, j, k;
	REP(i, 5) if (state[i]>col[i] || state[i]+(n-p)<col[i])return INF;
	/*max(0, col[i]-(n-p))<=state[i]<=min(p, col[i])
	  col[i]<n/2  or p<n/2=> obvious
	  col[i]>n/2, p>n/2, 
	  p>col[i} =>>>>col[i]-col[i]+(n-p)=n-p<=n/2
	  p<col[i] =>><>p-col[i]+(n-p)=n-col[i]<=n/2
	 */

	if (p==n)return 0;

	REP(i, 4) cor[i]=state[i]-max(0, col[i]-(n-p)), assert(cor[i]<=20);
	int &r=dp[p][cor[0]][cor[1]][cor[2]][cor[3]];
	if (r!=-1)return r;

	r=INF;
	REP(i, 5){
		REP(j, 5) state[(i+j)%5]+=mp[p][j];
		r=min(r, solve(p+1)+i);
		REP(j, 5) state[(i+j)%5]-=mp[p][j];
	}
	return r;
}

class BinaryMatrix {
	public:
		vector <string> getMaximalLexicographically(vector <string> matrix, vector <int> columns, int mc) {
			n=matrix.size();
			int i, j, k;
			col=columns;
			REP(i, n) REP(j, 5) mp[i][j]=matrix[i][j]-'0';

			memset(dp, -1, sizeof(dp));
			vs res;
			memset(state, 0, sizeof(state));
			if (solve(0)>mc)return res;

			res=vs(n);
			REP(i, n){ 
				string pa, npa(5, 0);
				int bestj=-1;
				REP(j, 5){

					REP(k, 5) npa[(j+k)%5]=matrix[i][k];
					REP(k, 5) state[k]+=npa[k]-'0';
					int cost=solve(i+1);
					REP(k, 5) state[k]-=npa[k]-'0';
					if (cost>mc-j)continue;
					if (bestj==-1 || npa>pa)pa=npa, bestj=j;
				}

				assert(bestj!=-1);
				mc-=bestj;
				res[i]=pa;
				REP(k, 5)state[k]+=pa[k]-'0';
			}
			return res;


		}

		// BEGIN CUT HERE
	public:
		void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
		template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
		void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
		void test_case_0() { string Arr0[] = {"01000", "10000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,1,0,0,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; string Arr3[] = {"10000", "01000" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(0, Arg3, getMaximalLexicographically(Arg0, Arg1, Arg2)); }
		void test_case_1() { string Arr0[] = {"01000", "10000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,1,0,0,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 4; string Arr3[] = {"01000", "10000" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(1, Arg3, getMaximalLexicographically(Arg0, Arg1, Arg2)); }
		void test_case_2() { string Arr0[] = {"00100", "10000", "00010", "00001", "01000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,1,1,1,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 7; string Arr3[] = {"10000", "01000", "00010", "00001", "00100" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(2, Arg3, getMaximalLexicographically(Arg0, Arg1, Arg2)); }
		void test_case_3() { string Arr0[] = {"00011","00010","11000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,1,2,2,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 9; string Arr3[] = {"01100", "00010", "00110" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(3, Arg3, getMaximalLexicographically(Arg0, Arg1, Arg2)); }
		void test_case_4() { string Arr0[] = {"00000","11111"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {5,0,0,0,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 160; string Arr3[] = { }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(4, Arg3, getMaximalLexicographically(Arg0, Arg1, Arg2)); }
		void test_case_5() { string Arr0[] = {"00011"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,1,0,1,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 160; string Arr3[] = { }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(5, Arg3, getMaximalLexicographically(Arg0, Arg1, Arg2)); }

		// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	BinaryMatrix ___test; 
	___test.run_test(-1); 
} 
// END CUT HERE
