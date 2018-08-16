// BEGIN CUT HERE

// END CUT HERE
#line 5 "FuzzyLife.cpp"

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


const int maxn=57;
int state[maxn][maxn];
int proc[maxn][maxn];
int n, m;
int cnt[maxn][maxn];
int vx[]={1, 1, 1, 0, -1, -1, -1, 0};
int vy[]={-1, 0, 1, 1, 1, 0, -1, -1};

int in(int a, int b){ return a>=0 && b>=0 && a<n && b<m; }

class FuzzyLife {
	public:
	int survivingCells(vector <string> grid) {
		n=grid.size()+2; m=grid[0].length()+2;
		memset(state, 0, sizeof(state));
		REP(i, n-2) REP(j, m-2) state[i+1][j+1]=(grid[i][j]=='?'?2:grid[i][j]-'0');

		vector<pii> lst;
		memset(cnt, 0, sizeof(cnt));
		REP(i, n) REP(j, m){
			if (state[i][j]==2) lst.pb(MP(i, j));
			REP(k, 8) if (in(i+vx[k], j+vy[k]) && state[i+vx[k]][j+vy[k]]==1) ++cnt[i][j];
		}

		int res=0;
		memset(proc, 0, sizeof(proc));
		FE(it, lst){
			int na=0;
			int x=it->ST, y=it->ND;
			proc[x][y]=1;
			REP(i, 2){
				int tmp=0;
				REP(k, 8){
					int nx=x+vx[k], ny=y+vy[k];
					if (in(nx, ny)){
						proc[nx][ny]=1;
						assert(state[nx][ny]!=2);
						if (state[nx][ny]==0 && cnt[nx][ny]+i==3) ++tmp;
						else if (state[nx][ny] && cnt[nx][ny]+i>=2 && cnt[nx][ny]+i<=3) ++tmp;
					}
				}
				checkmax(na, tmp+(cnt[x][y]==3 || (i==1 && cnt[x][y]==2)?1:0));
			}
			res+=na;
		}
		REP(i, n) REP(j, m) if (!proc[i][j] && (cnt[i][j]==3 || (state[i][j]==1 && cnt[i][j]==2))) ++res;
		return res;
		
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"011",
 "0?1",
 "100"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(0, Arg1, survivingCells(Arg0)); }
	void test_case_1() { string Arr0[] = {"101",
 "0?0",
 "101"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(1, Arg1, survivingCells(Arg0)); }
	void test_case_2() { string Arr0[] = {"11",
 "11"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(2, Arg1, survivingCells(Arg0)); }
	void test_case_3() { string Arr0[] = {"111",
 "1?1",
 "111"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8; verify_case(3, Arg1, survivingCells(Arg0)); }
	void test_case_4() { string Arr0[] = {"?11?",
 "0110",
 "1001",
 "?11?"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 12; verify_case(4, Arg1, survivingCells(Arg0)); }
	void test_case_5() { string Arr0[] = {"00100",
 "01010",
 "10?01",
 "01010",
 "00100"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 12; verify_case(5, Arg1, survivingCells(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  FuzzyLife ___test; 
        ___test.run_test(4); 
        } 
// END CUT HERE
