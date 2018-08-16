// BEGIN CUT HERE

// END CUT HERE
#line 5 "DominoesFinding.cpp"

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

int mp[9][8];
int visited[8][8];
int used[8][8];

int cnt;

void solve(int x, int y){
    if (y==7) ++x, y=0;
    if (x==8){ ++cnt; return; }
    if (visited[x][y]) return solve(x, y+1);
    int a=mp[x][y];
    int b=mp[x][y+1];
    if (y<6 && !visited[x][y+1] && !used[a][b]){
        used[b][a]=used[a][b]=1;
        visited[x][y]=visited[x][y+1]=1;
        solve(x, y+1);
        visited[x][y+1]=0;
        used[b][a]=used[a][b]=0;
    }
    b=mp[x+1][y];
    if (x<7 && !visited[x+1][y] && !used[a][b]){
        used[b][a]=used[a][b]=1;
        visited[x][y]=visited[x+1][y]=1;
        solve(x, y+1);
        visited[x+1][y]=0;
        used[b][a]=used[a][b]=0;
    }
    visited[x][y]=0;


}

class DominoesFinding {
	public:
	int getPossibilities(vector <string> board) {
        REP(i, 8) REP(j, 7) mp[i][j]=board[i][j]-'0';
        memset(visited, 0, sizeof(visited));
        memset(used, 0, sizeof(used));
        cnt=0;
        solve(0, 0);
		
        return cnt;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"0000000",
 "0123456",
 "1111112",
 "1234562",
 "2222333",
 "3456345",
 "3444556",
 "6456566"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 60; verify_case(0, Arg1, getPossibilities(Arg0)); }
	void test_case_1() { string Arr0[] = {"1111111","1111111","1111111","1111111","1111111","1111111","1111111","1111111"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(1, Arg1, getPossibilities(Arg0)); }
	void test_case_2() { string Arr0[] = {"0054450",
 "6645056",
 "0151226",
 "6522303",
 "0246343",
 "6411432",
 "0324531",
 "6215131"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(2, Arg1, getPossibilities(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  DominoesFinding ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
