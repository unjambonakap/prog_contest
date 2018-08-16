// BEGIN CUT HERE

// END CUT HERE
#line 5 "IncompatibleMice.cpp"

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


const int MAX_N=50;
int n, m;
int maze[MAX_N][MAX_N];
int tpath[MAX_N][MAX_N][3][2];
int path[MAX_N][MAX_N][3];
pii st[3], nd[3];
int vd[]={0, -1, 0, 1};
bool in(int x, int y){return (x>=0 && y>=0 && x<n && y<m);}
int incomp[3][5000];

void bfs(int s, int t, int k, int l){
	vector<pii> q(n*m);
	int qa, qe;
	qe=qa=0;
	q[qe++]=MP(s, 0);
	tpath[s%n][s/n][k][l]=0;
	while(qa<qe){
		pii p=q[qa];
		int nx, ny, c=p.ND;
		++qa;
		if (p.ST==t)break;

		REP(i, 4) if (in(nx=p.ST%n+vd[i], ny=p.ST/n+vd[(i+1)%4]) && tpath[nx][ny][k][l]==-1 && maze[nx][ny]==0) q[qe++]=MP(nx+ny*n, c+1), tpath[nx][ny][k][l]=c+1;
	}

}

void procIncomp(int a, int b){
	REP(i, n) REP(j, m) if (path[i][j][a]>=0 && path[i][j][b]>=0){
		incomp[a][2500+path[i][j][b]-path[i][j][a]]=1;
		REP(k, 4){
			int nx=i+vd[k], ny=j+vd[(k+1)%4];
			if (in(nx, ny) && path[nx][ny][a]>=0 && path[nx][ny][b]>=0 && path[i][j][a]==path[nx][ny][a]-1 && path[i][j][b]==path[nx][ny][b]+1) incomp[a][2500+path[i][j][b]-path[i][j][a]-1]=1;

		}
	}

}

class IncompatibleMice {
	public:
		int totalTime(vector <string> ms) {
			memset(maze, 0, sizeof(maze));
			memset(path, -1, sizeof(path));
			memset(tpath, -1, sizeof(tpath));
			n=ms.size(), m=ms[0].length();

			REP(i, n) REP(j, m){
				char c=ms[i][j];
				if (c=='#')maze[i][j]=1;
				else if (c=='.');
				else if (c>='a')st[c-'a']=MP(i, j);
				else nd[c-'A']=MP(i, j);
			}

			REP(k, 3){
				bfs(st[k].ST+st[k].ND*n, nd[k].ST+nd[k].ND*n, k, 0);
				int c;
				if ((c=tpath[nd[k].ST][nd[k].ND][k][0])==-1)return -1;
				bfs(nd[k].ST+nd[k].ND*n, st[k].ST+st[k].ND*n, k, 1);
				

				REP(i, n) REP(j, m) if (tpath[i][j][k][0]>=0 && tpath[i][j][k][0]+tpath[i][j][k][1]==c) path[i][j][k]=tpath[i][j][k][0];
			//	printf("from %d %d to %d %d\n", st[k].ST, st[k].ND, nd[k].ST, nd[k].ND);
			//	REP(i, n) {
			//		REP(j, m) printf("%d ", path[i][j][k]);
			//		printf("\n");
			//	}
			//	printf("\n\n");
			}
			memset(incomp, 0, sizeof(incomp));
			procIncomp(0, 1);
			procIncomp(1, 2);
			procIncomp(2, 0);
			int ea, eb, ec;
			ea=path[nd[0].ST][nd[0].ND][0];
			eb=path[nd[1].ST][nd[1].ND][1];
			ec=path[nd[2].ST][nd[2].ND][2];
			
			//printf("ici %d %d %d\n", ea, eb, ec);
			int res=INT_MAX;
			REP(j, 5000) REP(k, 5000){
				if ((j>=2500 || !incomp[0][2500-j]) && (k>=2500 || !incomp[2][2500+k]) && (abs(j-k)>=2500 || !incomp[1][2500+j-k]))
					res=min(res, max(ea, max(j+eb, k+ec)));
				//printf("%d %d %d\n",incomp[0][2500+j], incomp[1][2500-k], incomp[2][2500+k-j]);
				if ((j>=2500 || !incomp[0][2500+j]) && (k>=2500 || !incomp[1][2500-k]) && (abs(j-k)>=2500 || !incomp[2][2500+k-j]))
					res=min(res, max(eb, max(j+ea, k+ec)));
				if ((j>=2500 || !incomp[2][2500-j]) && (k>=2500 || !incomp[1][2500+k]) && (abs(j-k)>=2500 || !incomp[0][2500+j-k]))
					res=min(res, max(ec, max(j+ea, k+eb)));
			}


			return res;


		}

		// BEGIN CUT HERE
	public:
		void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
		template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
		void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
//		void test_case_0() { string Arr0[] = { "########",
//			"###a####",
//			"##...###",
//			"#b...B##",
//			"##...###",
//			"###A#cC#",
//			"########" }
		void test_case_0() { string Arr0[] = {"#...C...b.", "..a...#...", "..#c..A#..", "#.#....#..", ".B..#....#"};

			; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(0, Arg1, totalTime(Arg0)); }
			void test_case_1() { string Arr0[] = { "A##.##B",
				".......",
				"b#####a",
				"#.c.C.#" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 15; verify_case(1, Arg1, totalTime(Arg0)); }
			void test_case_2() { string Arr0[] = { "##.#...#.##",
				"##...#...##",
				"a..#...#..A",
				"##...#...##",
				"b..#...#..B",
				"##...#...##",
				"c..#...#..C",
				"##...#...##",
				"##.#...#.##" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 16; verify_case(2, Arg1, totalTime(Arg0)); }
			void test_case_3() { string Arr0[] = { "....b....",
				".........",
				"..a......",
				".........",
				"c.......C",
				".........",
				"......A..",
				".........",
				"....B...." }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; verify_case(3, Arg1, totalTime(Arg0)); }
			void test_case_4() { string Arr0[] = { "aB........Ab.cC" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 20; verify_case(4, Arg1, totalTime(Arg0)); }
			void test_case_5() { string Arr0[] = { "...a...",
				".#####.",
				"Bc...bC",
				"###.###",
				"###A###" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 13; verify_case(5, Arg1, totalTime(Arg0)); }
			void test_case_6() { string Arr0[] = { ".a.A.#...",
				".b...#.B.",
				".c.C.#..." }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(6, Arg1, totalTime(Arg0)); }

			// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	IncompatibleMice ___test; 
	___test.run_test(0); 
} 
// END CUT HERE
