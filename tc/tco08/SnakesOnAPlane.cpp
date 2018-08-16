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



const int maxn=300;
int w, h;
int graph[maxn][maxn];
int rn[maxn][maxn];
int parent[maxn];
int visited[maxn];
int s, t, nv;
int gid[15][15];

int va[maxn];
int vb[maxn];
int na, nb;
int ea, eb;
int vx[]={0, 1, -1, 0};
int vy[]={1, 0, 0, -1};

int dfs(int p){
	if (p==t)return 1;
	if (visited[p])return 0;
	visited[p]=1;
	REP(i, nv) if (graph[p][i]>0 && dfs(i)){parent[i]=p;return 1;}
	return 0;

}

int max_flow(){
	int ret=0;

	while(1){
		memset(parent, -1, sizeof(parent));
		memset(visited, 0, sizeof(visited));
		if (!dfs(s))break;
		int p=t;
		while(p!=s){
			assert(parent[p]!=-1);
			--graph[parent[p]][p]; ++graph[p][parent[p]];
			p=parent[p];
		}
		++ret;

	}
	return ret;
	

}

class SnakesOnAPlane {
	public:
		int snakes(vector <string> grid) {
			w=grid[0].length();
			h=grid.size();
			ea=eb=na=nb=0;
			memset(gid, -1, sizeof(gid));
			REP(i, h) REP(j, w) if (grid[i][j]=='.'){
				if (i+j&1) ea+=va[gid[i][j]=na++]=(i==0 || j==0 || i==h-1 || j==w-1);
				else eb+=vb[gid[i][j]=nb++]=(i==0 || j==0 || i==h-1 || j==w-1);
			}

			int c=0;
			s=na+nb, t=s+1;
			nv=t+3;
			while(1){
				int ca, cb;
				ca=2*(na-min(na, nb))+c; cb=2*(nb-min(na, nb))+c;
                printf("<< try %d %d\n", ca, cb);
				if (ca>ea || cb>eb)break;

				memset(graph, 0, sizeof(graph));
				memset(rn, 0, sizeof(rn));
				REP(i, na) graph[s][i]=2-va[i];
				REP(i, nb) graph[na+i][t]=2-vb[i];
				REP(i, h) REP(j, w) if (gid[i][j]!=-1 && i+j&1) REP (k, 4) if (i+vx[k]>=0 && i+vx[k]<h && j+vy[k]>=0 && j+vy[k]<w && gid[i+vx[k]][j+vy[k]]!=-1) 
					graph[gid[i][j]][na+gid[i+vx[k]][j+vy[k]]]=1;

				REP(i, na) if (va[i]) graph[t+1][i]=1;
				REP(i, nb) if (vb[i]) graph[na+i][t+2]=1;
				graph[s][t+1]=ea-ca;
				graph[t+2][t]=eb-cb;

				int ret=max_flow();
				if (ret==2*na-ca) return (ca+cb)/2;
				

				++c;
			}



			return -1;

		}

		// BEGIN CUT HERE
	public:
		void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); }
	private:
		template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
		void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
		void test_case_0() { string Arr0[] = {
			"..",
			"..",
			".#" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(0, Arg1, snakes(Arg0)); }

//		void test_case_0() { string Arr0[] = { "......",
//			".#.##.",
//			".#....",
//			"....#.",
//			".##.#.",
//			"......" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(0, Arg1, snakes(Arg0)); }
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
				void test_case_5() { string Arr0[] = { ".....", ".#.#.", ".....", ".#.#.", "....." }
					; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(5, Arg1, snakes(Arg0)); }
					void test_case_6() { string Arr0[] = { ".", "." }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(6, Arg1, snakes(Arg0)); }
					void test_case_7() { string Arr0[] = {"............", "............", "............", "............", "....#.#.....", "............", "....#.#.....", "............", "............", "............", "............", "............"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(7, Arg1, snakes(Arg0)); }

					// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	SnakesOnAPlane ___test; 
	___test.run_test(0); 
} 
// END CUT HERE
