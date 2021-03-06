// BEGIN CUT HERE

// END CUT HERE
#line 5 "MultiplayerBattleships.cpp"

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


int mp[7][7];
int r, c;
int vx[]={1, 0}, vy[]={0, 1};

int dp[200000][16];
int mul[20];
int l[20];

int n, np;
int solve(int s, int p){

	if (s==0)return 0;
	int &r=dp[s][p];
	if (r!=-1)return r;

	int best=-1, bv=-1;
	for (int i=0; i<n; ++i){
		int c;
		if ((c=s/mul[i]%(l[i]+1))==0)continue;
		int v=solve(s-mul[i], np-1)+(c==1?l[i]:1);
		if (best==-1 || v>bv)best=i, bv=v;
	}//choose po best choice
	
	return r=p==0?bv:solve(s-mul[best], (np+p-1)%np);
}

class MultiplayerBattleships {
	public:
	int getFirstPlayerScore(vector <string> field, int playerCount) {
		int i, j, k;

		np=playerCount;
		r=field.size(), c=field[0].length();

		memset(mp, -1, sizeof(mp));

		n=0;
		REP(i, r) REP(j, c) if (field[i][j]=='X'){
			if (mp[i][j]==-1)mp[i][j]=n, l[n++]=1;
			REP(k, 2) if (i+vx[k]<r && j+vy[k]<c && field[i+vx[k]][j+vy[k]]=='X') mp[i+vx[k]][j+vy[k]]=mp[i][j], ++l[mp[i][j]];
		}
		REP(i, n+1)
			mul[i]=i==0?1:mul[i-1]*(l[i-1]+1);
		memset(dp, -1, sizeof(dp));
		return solve(mul[n]-1, 0);
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"XX.XX.X", ".......", "XX.XX.X", ".......", "XX.XX.X", ".......", "XX.XX.X"};
 vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 1; verify_case(0, Arg2, getFirstPlayerScore(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {".XXXX.."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 5; verify_case(1, Arg2, getFirstPlayerScore(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {".XX",
 "...",
 "XXX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 6; verify_case(2, Arg2, getFirstPlayerScore(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"XXXX",
 "....",
 "XXXX",
 "....",
 "XXXX", 
 "....",
 "XXXX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 12; verify_case(3, Arg2, getFirstPlayerScore(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  MultiplayerBattleships ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
