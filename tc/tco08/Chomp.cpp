// BEGIN CUT HERE

// END CUT HERE
#line 5 "Chomp.cpp"

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


const int MAX_N=101;

int visited[MAX_N][MAX_N][MAX_N];
int dp[MAX_N][MAX_N][MAX_N];
int sgn(int a){return a<0?-1:1;}

int solve(int a, int b, int c){
	if (b==0 && a==1)return -1;
	if (visited[a][b][c])return dp[a][b][c];
	visited[a][b][c]=1;


	int i, j, k, r;
	int res=-1;
	REP(i, c){
		r=-solve(a, b, i);
		//printf("on %d %d %d => c %d >> %d\n", a, b, c, i, r);
		if (r<0){
			if (res<0)res=min(res, r);
		}else{
			if (res<0)res=r;
			else
				res=min(res, r);
		}
	}
	REP(i, b){
		r=-solve(a, i, min(i, c));
		//printf("on %d %d %d => b %d >> %d\n", a, b, c, i, r);
		if (r<0){
			if (res<0)res=min(res, r);
		}else{
			if (res<0)res=r;
			else
				res=min(res, r);
		}
	}

	FOR(i, 1, a-1){
		r=-solve(i, min(i, b), min(i, c));
		//printf("on %d %d %d => a %d >> %d\n", a, b, c, i, r);
		if (r<0){
			if (res<0)res=min(res, r);
		}else{
			if (res<0)res=r;
			else
				res=min(res, r);
		}
	}

	return dp[a][b][c]=res+sgn(res);


}

class Chomp {
	public:
	int moves(int N) {
		memset(dp, -1, sizeof(dp));
		memset(visited, 0, sizeof(visited));
		int s=solve(N, N, N);
		return s;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 2; verify_case(0, Arg1, moves(Arg0)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 6; verify_case(1, Arg1, moves(Arg0)); }
	void test_case_2() { int Arg0 = 4; int Arg1 = 8; verify_case(2, Arg1, moves(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  Chomp ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
