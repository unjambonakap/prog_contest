// BEGIN CUT HERE

// END CUT HERE
#line 5 "CuttingGlass.cpp"

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

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:(n==1?0:ctz(n>>1)+1));}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

struct edge{
	int xa, ya, xb, yb;
	bool operator<(const edge &e)const{
		if (xa!=e.xa) return xa<e.xa;
		if (xb!=e.xb) return xb<e.xb;
		if (ya!=e.ya) return ya<e.ya;
		if (yb!=e.yb) return ya<e.yb;
		return 0;

	}
	string str()const{
		ostringstream os;
		os<<xa<<" "<<ya<<"//"<<xb<<" "<<yb;
		return os.str();

	}
};

int vx[]={0, 1, -1, 0};
int vy[]={-1, 0, 0, 1};

const int maxw=1010;
int proc[maxw][maxw];
int w, h;
set<edge> e;

int in(int a, int b){return a>=0 && b>=0 && a<w && b<h;}
void bfs(int i, int j){
	int nx, ny;
	queue<pii> q;
	q.push(MP(i, j));
	while(!q.empty()){
		pii p=q.front();
		q.pop();
		if (proc[p.ST][p.ND])continue;
		proc[p.ST][p.ND]=1;

		REP(k, 4) if (in(nx=p.ST+vx[k], ny=p.ND+vy[k]) && !proc[nx][ny] && !e.count((edge){p.ST,p.ND,nx,ny})) q.push(MP(nx, ny));
	}
}
class CuttingGlass {
	public:
		int pieces(int W, int H, int sx, int sy, vector <string> program) {
			int nx, ny;
			string s="";
			w=W, h=H;
			FE(it, program)s+=*it;
			e.clear();
			REP(i, s.length()){
				nx=sx; ny=sy;
				if (s[i]=='L'){
					--nx;
					e.insert((edge){nx, ny, nx, ny-1});
					e.insert((edge){nx, ny-1, nx, ny});
				}
				if (s[i]=='D'){
					e.insert((edge){nx, ny, nx-1, ny});
					e.insert((edge){nx-1, ny, nx, ny});
					++ny;
				}
				if (s[i]=='U'){
					--ny;
					e.insert((edge){nx, ny, nx-1, ny});
					e.insert((edge){nx-1, ny, nx, ny});
				}
				if (s[i]=='R'){
					e.insert((edge){nx, ny, nx, ny-1});
					e.insert((edge){nx, ny-1, nx, ny});
					++nx;
				}
				sx=nx, sy=ny;
			}
			memset(proc, 0, sizeof(proc));
			int cnt=0;
			REP(i, w) REP(j, h) if (!proc[i][j]) bfs(i, j), ++cnt;

			return cnt;

		}

		// BEGIN CUT HERE
	public:
		void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
		template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
		void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
		//void test_case_0() { int Arg0 = 100; int Arg1 = 100; int Arg2 = 50; int Arg3 = 50; string Arr4[] = {"ULDR"}; vector <string> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arg5 = 2; verify_case(0, Arg5, pieces(Arg0, Arg1, Arg2, Arg3, Arg4)); }
		void test_case_0() { int Arg0 = 1000; int Arg1 = 1000; int Arg2 = 597; int Arg3 = 184; string Arr4[] = {"LLURDDLDLDRURURRURRULDDLDLDDRDRURRDLDLURUULDLULLLD", "DLDRRRDRDLULUULDDRDDRRDLUULLLDDLURRDLDRDDLURRRDLLD", "DRDLULUULLDLLDDDLUULLUURRULLDLURULDLDLUULDRRURULDL", "URULLULULURULDLLULDDRULLLDLLLURDDDDRRRDDLDLUUUUURU", "RDDRDDLLDLLURRUUURRDRURULDLULUURURDRULUUUURUULLURU", "RULDLLURRURULURUURRRRURRDLUURDRDLDRURDDRRDLDRDLLUL", "DDRULLUULDLULLURULUURULDLLLURDDLULDRDRRRDLUUUULULL", "ULLUULLDLDDDLLULLDRRDDLLURUUULLDLDRRDLLULUULUUUUUL", "URURRULLULLLURDDDDRURULUULULDLDLLDDDRULLDLLDRRDRRD", "RRRURULDLURULUURRDLLLLULLDLDDDLULULUULURURUURRDRUL", "UURDDRDRRDLUURDRULURDRULURDRURDRRUURURULUUULDLDDRD", "LULLULLULDDRULLUULDDDRDLLLUUURRRRUURDLLUULDLLUULDL", "URURRUUUURRRDDLULUURUUUURURRDRULUURDLLULLLLULULLDL", "DLUULUULLULLULULDLDDDLLDRRURDLDLDLLUUURURRRURRDDLD", "DLLDDDDLLLLULDDLLDRRRUULLDDDRRURDLDLDLLLLDDLULULDL", "LDLULULURURDDDRURDDLDRRDRDDLURRDRRDLUURRDLUUURRULL", "LDDRRRURDRDLDDLLURULUUUUUURRUUURRRDRUUURRDDLLLUURU", "URRDRURDRUUUURDRURRRDRULULLUUURULUUURRRULUULLULULL", "UURULDLDRRURDRRRDRUURRRRUURURRDLDLLLLDDRDLLLDLDRDR", "URDLDRDRDDRRRULLLLULULULLLDRDDLLURULULDDDLULLDDRDR", "RURULDLULDRDDLULULDLLULLDRRDLLDDRRDDDDLDDLDLUUULUR", "UUURDRUUUUUURRULDDRURRRUURRRDLLUURULUULDDDDLDLULLD", "LUULURDRDLLDRDLULLDRRDLLULUURULLDLDRRRURULULLLULDL", "LLLLURURRDRRURULLUURRDDRDRRDDRULLUUUULDLLDDLDDDRUR", "DDLURRUULURDRDDDLDDRDLDRDRUULDRRUUUURULURURDRURDDD", "DRDDLDDRURDRDRRUURURRRDRDLULUURUULUUUURDLLUUULURRD", "RUULURRRRRDDDDRRRRULLDDLLDLDRRRDLLUURDDDDRRRDRUULL", "LLLLURDDRDDDLLUULULDRDDRDRDLDDDRURRDDDDDDRULLUULUL", "ULURRURUURDDDRUULLLDLLULDDRULLLULLLDRDDLULDLDRRDDR", "RRDLUULLLLULLDDRURDRRDRDRULUUURDRRULUUULLUUURDLLLD", "DDLLLDRUUULDLLULLLUURDLLDLLDLLDLDLDLDDRUURDRRDDDLL", "ULLDDDDDLURRRURRUURRRUULLUUULDDRRRDRRDLLLUUUUURUUR", "DLLUULDLURULDLDLLURUURRDLLLUURUUULUULDDDLUUURUURUU", "URURRULDDLDLLLULUUUURRDDLLLDDLDLLDLDRRDRULULDDDDDD", "LDLLDLLUURDRULUURDRRDLLULLLLURDDLLLLLURRUURULUURDL", "LDLULLLDDRURUULURURULLULULULDLUURRURRDLLDRUUUUULDL", "ULLUUURULDLLLLLULDRDLLDLLLUUURULDLUURDLLLURDDRDDRR", "RRURDDLDRURRDDLDDRURDLDDLDRDLULURUULULURDRRURURUUU", "UUULLUURDDDLLLULDRDLDLLDDDRUUUUUUURDLLURURURDDRRRR", "RRRURDRRURURDLDDDDLULLLUURDRRURRURDRUULURULDLLLDLU", "RURRDDRDRRURDRDDLULDRDRRDRULULDDRDDLULDLLDRUURURDR", "RURULUULUURRRRDDDRDDRRRDRRULDDDLDLLURURDLDDDDRDRDR", "ULURUUUULDRRURDRUUUUUURRRRULLDDRDDLDDDLULLULDLURUR", "DRRDRRRUUUURRRRULULDDDDLLLDDDLDDRRUURDLLURURUUUUUR", "RDDDLDLLLLLULLULDLDLLULLLDLURULDLLDLDDRRDDDRRURRRR", "UULDRRRDLLDLUULLDDRDRDDRULLULLDRDRULUULDLLLLULLUUR", "DLLLLULULDRDLULLLDLDRURRUURULURDRDRDRRUUURDLLDDDDR", "DLLLLDLLDRRDLUUURULURDRDDDLURRRRDLDRRUULURDRRRUULU", "RRRURURDLDLDDDLUULUUUULLDRDLULURURURURDDDLURRDDRUR", "ULDLLDRDLLLDLDDDDLLDDDRRDRDLULUUURURRURDRURDLDLULD"}; vector <string> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arg5 = 2; verify_case(0, Arg5, pieces(Arg0, Arg1, Arg2, Arg3, Arg4)); }
		void test_case_1() { int Arg0 = 10; int Arg1 = 10; int Arg2 = 3; int Arg3 = 4; string Arr4[] = {"UDUDUDUDUDU"}; vector <string> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arg5 = 1; verify_case(1, Arg5, pieces(Arg0, Arg1, Arg2, Arg3, Arg4)); }
		void test_case_2() { int Arg0 = 3; int Arg1 = 3; int Arg2 = 0; int Arg3 = 0; string Arr4[] = {"RDDDUUU","RDDDUUU","R","DLLLRRR","DLLL"}; vector <string> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arg5 = 9; verify_case(2, Arg5, pieces(Arg0, Arg1, Arg2, Arg3, Arg4)); }
		void test_case_3() { int Arg0 = 5; int Arg1 = 3; int Arg2 = 5; int Arg3 = 3; string Arr4[] = {"LULLULLU"}; vector <string> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arg5 = 2; verify_case(3, Arg5, pieces(Arg0, Arg1, Arg2, Arg3, Arg4)); }

		// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	CuttingGlass ___test; 
	___test.run_test(-1); 
} 
// END CUT HERE
