// BEGIN CUT HERE

// END CUT HERE
#line 5 "SnakesOnAPlane.cpp"

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



const int maxn=12;
const int inf=5000;
int dp[maxn][maxn][two(maxn)][2];
int seen[maxn][maxn][two(maxn)][2];
int mp[maxn][maxn];
int w, h;


int solve(int a, int b, int p, int l){
	if (b==w)return min(solve(a+1, 0, p, 0), solve(a+1, 0, p, 1));
	if (a==h)return 0;

	int &r=dp[a][b][p][l];
	if (seen[a][b][p][l])return r;
	seen[a][b][p][l]=1;
	r=inf;

	int t;
	int np=(p^two(b))&p;
	if (mp[a][b])
		return r=(l||(p&two(b)))?inf:solve(a, b+1, np, 0);
	
	if (b==0){
		if (a==0){
			if (l&&(p&two(b)))return r=inf;
			if (l){
				if (b!=w-1)r=1+solve(a, b+1, np, 1);
				if (a!=h-1)r=min(r, 1+solve(a, b+1, np|two(b), 0));
				return r;
			}
			if (p&two(b)){
				if (a!=h-1)r=1+solve(a, b+1, np|two(b), 0);
			   	if (b!=w-1)r=min(r, 1+solve(a, b+1, np, 1));
				return r;
			}
			return r=(b==w-1 && a==h-1)?inf:1+solve(a, b+1, np|two(b), 1);
		}
		if (a==h-1){
			if (l&&(p&two(b)))return r=solve(a, b+1, np, 0);
			if (l){ 
				if (b!=w-1)r=1+solve(a, b+1, np, 1);
				return r;
			}
			if (p&two(b))return r=min(solve(a, b+1, np|two(b), 0), solve(a, b+1, np, 1));
			if (b!=w-1) r=1+solve(a, b+1, np|two(b), 1);
			return r;
		}
		if (l&&(p&two(b)))return r=solve(a, b+1, np, 0);
		if (l){
			if (b!=w-1) r=1+solve(a, b+1, np, 1);
		   	r=min(r, 1+solve(a, b+1, np|two(b), 0));
			return r;
		}
		if (p&two(b))return r=min(solve(a, b+1, np|two(b), 0), solve(a, b+1, np, 1));
		return r=(b==w-1)?inf:1+solve(a, b+1, np|two(b), 1);
	}if (b==w-1){
		if (a==0){
			if (l&&(p&two(b)))return r=solve(a, b+1, np, 0);
			if (l)return r=min(solve(a, b+1, np, 1), solve(a, b+1, np|two(b), 0));
			if (p&two(b)){
				if (a!=h-1) r=1+solve(a, b+1, np|two(b), 0);
				return r;
			}
			if (a!=h-1) r=1+solve(a, b+1, np|two(b), 1);
			return r;
		}if (a==h-1){
			if (l&&(p&two(b)))return r=solve(a, b+1, np, 0)-1;
			if (l)return r=min(solve(a, b+1, np, 1), solve(a, b+1, np|two(b), 0));
			if (p&two(b))return r=min(solve(a, b+1, np|two(b), 0), solve(a, b+1, np, 1));
			return r=inf;
		}
		if (l&&(p&two(b)))return r=solve(a, b+1, np, 0)-1;
		if (l)return r=min(solve(a, b+1, np, 1), solve(a, b+1, np|two(b), 0));
		if (p&two(b))return r=min(solve(a, b+1, np|two(b), 0), solve(a, b+1, np, 1));
		return r=1+solve(a, b+1, np|two(b), 1);
	}if (a==0){
		if (l&&(p&two(b)))return r=solve(a, b+1, np, 0);
		if (l)return r=min(solve(a, b+1, np, 1), solve(a, b+1, np|two(b), 0));
		if (p&two(b)){
			if (a!=h-1) r=1+solve(a, b+1, np|two(b), 0);
			r=min(r, 1+solve(a, b+1, np, 1));
			return r;
		}
		return r=1+solve(a, b+1, np|two(b), 1);

	}if (a==h-1){
		if (l&&(p&two(b)))return r=solve(a, b+1, np, 0)-1;
		if (l)return r=min(solve(a, b+1, np, 1), solve(a, b+1, np|two(b), 0));
		if (p&two(b))return r=min(solve(a, b+1, np|two(b), 0), solve(a, b+1, np, 1));
		return r=1+solve(a, b+1, np|two(b), 1);
	}

	if (l&&(p&two(b)))return r=solve(a, b+1, np, 0)-1;
	if (l)return r=min(solve(a, b+1, np, 1), solve(a, b+1, np|two(b), 0));
	if (p&two(b))return r=min(solve(a, b+1, np|two(b), 0), solve(a, b+1, np, 1));
	return r=1+solve(a, b+1, np|two(b), 1);
}

class SnakesOnAPlane {
	public:
		int snakes(vector <string> grid) {
			w=grid[0].length();
			h=grid.size();


			REP(i, h) REP(j, w) mp[i][j]=(grid[i][j]=='#');
			memset(seen, 0, sizeof(seen));

			int r=inf;
			REP(i, two(w)) REP(j, 2)
			   	r=min(r, solve(0, 0, i, j));
			
			assert(r>=0);

			return (r>=100)?-1:r;

		}

		// BEGIN CUT HERE
	public:
		void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); }
	private:
		template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
		void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
		void test_case_0() { string Arr0[] = { "......",
			".#.##.",
			".#....",
			"....#.",
			".##.#.",
			"......" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(0, Arg1, snakes(Arg0)); }
		void test_case_1() { string Arr0[] = { "###.###",
			"###.###",
			".......",
			"###.###",
			"###.###" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(1, Arg1, snakes(Arg0)); }
		void test_case_2() { string Arr0[] = { "#.....##",
			"...#....",
			"........",
			"..#.#.#.",
			"......#.",
			"...#..#.",
			"#......." }
			; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(2, Arg1, snakes(Arg0)); }
			void test_case_3() { string Arr0[] = { "###########",
				"#......#...",
				"#.####.#...",
				"#.#..#.####",
				"#.#..#.####",
				"#.####.#..#",
				"#......#..#",
				"###########" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(3, Arg1, snakes(Arg0)); }
			void test_case_4() { string Arr0[] = { "####.######",
				"#.........#",
				"..........#",
				"#..........",
				"#.........#",
				"#####.#####" }
				; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(4, Arg1, snakes(Arg0)); }
				void test_case_5() { string Arr0[] = { "##",
					"#." }
					; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(5, Arg1, snakes(Arg0)); }
					void test_case_6() { string Arr0[] = { ".", "." }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(6, Arg1, snakes(Arg0)); }
					void test_case_7() { string Arr0[] = { "#."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(7, Arg1, snakes(Arg0)); }

					// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	SnakesOnAPlane ___test; 
	___test.run_test(7); 
} 
// END CUT HERE
