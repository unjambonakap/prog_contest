// BEGIN CUT HERE

// END CUT HERE
#line 5 "GogoXMarisaKirisima.cpp"

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
#define FOR(i, a, b) for(int i = (int)(a); i < (int)(b); ++i)
#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();++i)

#define two(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()


#define pb push_back
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n==0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=55;
int g[maxn][maxn];
int vis[maxn];
int can[maxn];
int n;


void dfs(int a){
    if (vis[a]) return;
    vis[a]=1;
    REP(i, n) if (g[a][i]) dfs(i);
}
void dfsb(int a){
    if (vis[a]) return;
    vis[a]=1;
    REP(i, n) if (g[i][a]) dfsb(i);

}


class GogoXMarisaKirisima {
	public:
	int solve(vector <string> choices) {
        n=choices.size();
        REP(i, n) REP(j, n) g[i][j]=choices[i][j]=='Y';

        memset(vis, 0, sizeof(vis));
        memset(can, 1, sizeof(can));
        dfs(0);
        REP(i, n) if (!vis[i]) can[i]=0;
        memset(vis, 0, sizeof(vis));
        dfsb(n-1);
        REP(i, n) if (!vis[i]) can[i]=0;
        if (!can[n-1]) return 0;
        int cnt=0;
        REP(i, n) if (can[i]){
            --cnt;
            REP(j, n) if (g[i][j] && can[j]) ++cnt;
        }
        return cnt+2;

	
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
    	void test_case_0() { string Arr0[] = {"NNNYNNYNNNNYNNNNYNYNNNNNYNNNNYNNNYNNNNNNNNNNNNNYNN","YNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNYNNNNYNNNNYNYNYNNN","YYNNNNNNNNNNNNYNNNNNNYNYNYYNNNNNNYNNYNNNNNNNYNNNNN","NNNNNNYNNNNNNNNNNNNNNNNNNNNYNNNNNNYNNNNNNNNNNNNNNN","NNNNNNNNNNNNNYNNNYNNYNNNNNNNNNNNNNNYYNNNYNNNNYNNNY","NNYNYNYNNNNNNYNNYNNNNNYNNNNNNNNNNNNNNNNNYNNNNNNNYN","NNNNNNNNNNYNYYYYNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNN","NYYNNYNNNNNNNNNNNNYYNNNNNYYNNYYYNNNNNYNYNNNNYYNNNY","NNNNNNNYNNNNYNYNYNNNYNYNNNNYNNNNYNNNYYNYNNNNNNYNNN","NYNNNNNNNNNNNYNNNNNNNYNYNNNNNNNNNNNNNYNNNYNYNNNNNN","NNNNNNNNNYNNYNNNNNNYYNNNYNNNNNNNNNNNYYNNNNNNNNNNNN","NNNYYNYNNNNNNNNNNNNYNNNNYNNNYNNNNYNNNNNNNNNNYNNNNN","NNNYNNNNNNNNNNNYNNYNYNNYYYNNNNNNNYNNNNNYNYYNYNNNNN","NNNYNNNNNNNNNNNYYNNNNNNNNYNNNNYNYNNNNYNNNNNNNNNNNN","NNNNNNNNYYNYNNNNNNNNYNNNNNNNYNNNNNNNNNNNNNNNNNNNNN","NNYNNNNNNYNYNYYNNNNNYNNNNNNNYNYNNNNNNNNNYYNNYYNNNY","NNNYNNNNNNNYNNNYNYYNYNNNNNNNNYNNYNYNNNNNYNYNNNNYNN","NNNNNYNNNYNNNNNNYNNNNNYYNNNNNNNNNNNNYNNNNNNNNNNNNY","YNNYYNNNNYNNNYNNNNNNYNNNNNNYNNNNNNNYNNYNNYNNNNNNNY","NNNNNNYNNNNNNNNNNNYNYNYNNNNNNNNNNNYNNNNYNNNYNYNNNN","YNNNYNYNNNNNNYNNNNYNNNNNYNNNNNNNNNNNNNYYNNNNNNNNNN","NYYNYYYNNYYNYYYNNYYNNNNNYNNNYYNNNNNNNNYNNNNYYNNNNY","NNNNNNNYYNNNNNNNNYNNNNNNNYYNNYNYYNNNNNYNNNNNNYNNNY","NNNYNNYNNNNYNNNNNNNNNNNNNNNNYNNNYNYYYNNNNNNNNNNNYN","NNYNNNNNNNNNNYYNNYNNNNNNNNNNNNNNNYNNNNNNYNNNNYNNNY","NYNNNNNNNNNNNNNNYNYNNNNNYNNNNNNYNNNNNNNYNYNNNNNNYN","NNNNNYNNYNNNNNNNYNNNNNNYNYNNNNNNNYNNNNNYNNNNNNNYNN","YNNNNNNNYYYNNYYNNNNYYNYNYNNNNNNNNNNNNNYNNNNNNNYNYN","NYNNNNNNNNNYNNYYYNNNYNNNNNNNNNNNNNYNNNYNNNNNNNYYNN","NNNNYYNNNYYNYNNNNNNNNYNNNNNNNNNNNNNNNNNNNYNNNYNNNN","NNYNYNNNNNNNYNNNNNNYNNNNNNNNNNNNNNNYNNNNNNYNYNNNNN","NNNNNNNNNNNNNNNNYNNNNNNNNNNYYNNNNYYNYNNNNNNNYNNNNN","NNNNNNNYYNNNYYNYNYNNNNNNNYNNNNNNNNNNNYNNYNNYNYNNNN","NNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNYYNNNYNNNNNNNN","NNNNNYNNYNNNNNNNNNNNYYYNNNYNNNYNYNNNNNNNNNNNNNYNNN","NNNNNNNNNYNNNNYNNNYNNNNNNNNNNNNNNNNNNNNYNNNNNNYNNN","NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN","NNYNNNNNNNNNNYNYNYYNNNYNNNNYNNNYNNYNNNNNYNNNNNNNNN","NNYNNNNNNNNNNNNNNYYYNNNNNNNNNNNYNNNNNNNNNNYNNYYYNN","NYNYYYNNNYNNYNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNYN","NNNNYNNNYNNNNNNNNNNNNNNNNNYNYNYNYNNYNNNNNNYNNNNNNN","NNNYNNYNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNYNN","NNNYNYNYNNNNNNYNNNNNNYYNNNYNNYNNNYNYNNNNNNNNNNNYNY","YNNNNNNNNNNYNNNNNNNNNNNNNNYNNYNNNNNYNNYNNNNNNNNNNN","YNNNYNNNNNNNNYNNNNNNNYNNNNYNNNNYNNNNNNNNYNNNNNYNNN","NYNNNYYNNNNNNNNNNNNNYNYYNNYNNNYYYNNNNNNNNYNNNNYNNN","NNNNYNNNNYYNNYNNYNNYNNNYNNNYNNNNNNYYYNNNYNNNNNNNNN","NNNNNYNNNNNNNNNNNYNNNYNNNNNNYNNNYNNNNNNNNYNNNNYNNY","NYNNNNNNNNYNNNNNYYNNNNNNNNNNNNNNYYNYNNNNNYNNNNNNNN","NNNNNNNYNNNNNNYNNNYNNYNNNYNNNNNYNNYNNNNNNNNYNNNNNN"
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(0, Arg1, solve(Arg0)); }
	//void test_case_0() { string Arr0[] = {"NYN" ,"YNY" ,"NNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(0, Arg1, solve(Arg0)); }
	void test_case_1() { string Arr0[] = {"NNY"
,"YNY"
,"YNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(1, Arg1, solve(Arg0)); }
	void test_case_2() { string Arr0[] = {"NN"
,"NN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(2, Arg1, solve(Arg0)); }
	void test_case_3() { string Arr0[] = {"NYYY"
,"NNNY"
,"NNNY"
,"NNNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(3, Arg1, solve(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
  GogoXMarisaKirisima ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
