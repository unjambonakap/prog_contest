// BEGIN CUT HERE

// END CUT HERE
#line 5 "PawnsAndKings.cpp"

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
inline int get_fb(int n){return n-(n&(n-1));}




int cost[66][66];
int dp[two(10)][64];
int dpa[two(10)][10];
vector<int> kl, pl;
int n, m;

int proc(int p, int s){
	if (s==0)return 0;

	int &r=dp[s][p];
	if (r!=-1)return r;

	r=10000;
	for (int i=0; i<SZ(pl); ++i)
		if (s&two(i))
			r=min(r, cost[p][pl[i]]+proc(pl[i], s-two(i)));
	return r;
}

int proca(int p, int s){
	if (p==n)return 1;
	int &r=dpa[s][p];
	if (r!=-1)return r;

	int i, j, k, l;
	r=10000;
	if (p==n-1)return r=proc(kl[p], s);

	for (i=0; i<two(count_bit(s)); ++i){
		k=l=0;
		for (j=0; j<m; ++j)
			if (s&two(j)){
				if (i&two(k))l+=two(j);
				++k;
			}
		
		r=min(r, proc(kl[p], l)+proca(p+1, s-l));
		assert(r>=count_bit(s));
	}
	assert(r>=0);
	return r;


}

class PawnsAndKings {
	public:
	int minNumberOfMoves(vector <string> board) {

		int i, j, k;
		CLR(kl); CLR(pl);

		for (i=0; i<8; ++i)
			for (j=0; j<8; ++j){
				if (board[i][j]=='K')
					kl.pb(i*8+j);
				else if (board[i][j]=='P')
					pl.pb(i*8+j);

			}
		
		n=SZ(kl), m=SZ(pl);
		for (i=0; i<64; ++i)
			for (j=0; j<64; ++j)
				cost[i][j]=max(abs(i/8-j/8), abs(i%8-j%8));
		
		memset(dp, -1, sizeof(dp));
		memset(dpa, -1, sizeof(dpa));
		FE(it, kl)
			proc(*it, two(m)-1);
		return proca(0, two(m)-1);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {".PPPPKP.", 
 "........", 
 "........", 
 "........", 
 "........", 
 "........", 
 "........", 
 "........"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; verify_case(0, Arg1, minNumberOfMoves(Arg0)); }
	void test_case_1() { string Arr0[] = {"P......P", 
 "........", 
 "........",
 "........",
 "...KK...",
 "........",
 "........",
 "P......P"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 20; verify_case(1, Arg1, minNumberOfMoves(Arg0)); }
	void test_case_2() { string Arr0[] = {".....P.P",
 "..K....P",
 "....K...",
 "..PP...P",
 "...K..KK",
 "........",
 "K.......",
 "KP.K...."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 9; verify_case(2, Arg1, minNumberOfMoves(Arg0)); }
	void test_case_3() { string Arr0[] = {"PK...KPK",
 "......K.",
 "...K....",
 "..KPK...",
 "...K....",
 "........",
 "........",
 "K..P.K.P"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8; verify_case(3, Arg1, minNumberOfMoves(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  PawnsAndKings ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
