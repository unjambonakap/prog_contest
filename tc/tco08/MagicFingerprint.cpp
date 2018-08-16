// BEGIN CUT HERE

// END CUT HERE
#line 5 "MagicFingerprint.cpp"

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

int n;
set<int> dp[10];
void dfs(int p, int c, int s, const vi &from, int nb){
	if (c<0 || c>=10)return;

	if (p==0){
		dp[nb].insert(s);
		return;
	}

	if (p-1>=from.size())
		return dfs(p-1, c, s*10+c, from, nb);
	//c-x or x-c=from[p-1]
	int nc=0;
	for (int i=-1; i<=1; i+=2){
		nc=c+from[p-1]*i;
		dfs(p-1, nc, s*10+nc, from, nb);
	}
}

void rec(int p){
	int i, j, k;
//	printf("%d to %d\n", p, n);
	if (p==n-1)return;
	for (i=0; i<=p; ++i){
		FE(it, dp[i]){
			k=0;
			j=*it;
			vi from;
			while(j!=0)from.pb(j%10), j/=10;
			for (j=1; j<10; ++j)
				dfs(p+1, j, j, from, p+1);
		}
	}
	rec(p+1);

}


int solve(int a){
	if (a<7)return 0;
	if (a==1000000000)--a;
	int i, j, k;
	REP(i, 10)
		CLR(dp[i]);
	dp[0].insert(7);
	j=a, n=0;
	while(j>0)j/=10, ++n;
	rec(0);

	int c=0;
	for (i=0; i<=n; ++i)
		FE(it, dp[i])
			if (*it<=a)++c;
//	printf("%d => %d\n", a, c);
	return c;

}


class MagicFingerprint {
	public:
	int countLuckyNumbers(int A, int B) {
		return solve(B)-solve(A-1);
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 9; int Arg2 = 1; verify_case(0, Arg2, countLuckyNumbers(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 1; int Arg1 = 100; int Arg2 = 6; verify_case(1, Arg2, countLuckyNumbers(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 1198; int Arg1 = 1198; int Arg2 = 1; verify_case(2, Arg2, countLuckyNumbers(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 1223; int Arg1 = 1299; int Arg2 = 0; verify_case(3, Arg2, countLuckyNumbers(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 999999930; int Arg1 = 1000000000; int Arg2 = 2; verify_case(4, Arg2, countLuckyNumbers(Arg0, Arg1)); }
	void test_case_5() { int Arg0 = 100000; int Arg1 = 1000000000; int Arg2 = 159720; verify_case(5, Arg2, countLuckyNumbers(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  MagicFingerprint ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
