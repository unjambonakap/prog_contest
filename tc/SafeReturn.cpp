// BEGIN CUT HERE

// END CUT HERE
#line 5 "SafeReturn.cpp"

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
const int inf=1e6;

int g[maxn][maxn];
int ng[maxn][maxn];
int n,N;

int G[maxn][maxn];
int vis[maxn];
int peer[maxn];
int step;

int dfs(int a){
    if (vis[a]==step) return 0;
    vis[a]=step;
    REP(i,N) if (G[a][i]&&(peer[i]==-1||dfs(peer[i]))){
        peer[i]=a;
        return 1;
    }
    return 0;
}



class SafeReturn {
	public:
	int minRisk(int _N, vector <string> u) {
        N=_N;
        n=u.size();
        REP(i,n) REP(j,n) ng[i][j]=g[i][j]=u[i][j]=='-'?inf:u[i][j]-'0';
        REP(i,n) ng[i][i]=0;
        REP(k,n) REP(i,n) REP(j,n) checkmin(ng[i][j],ng[i][k]+ng[k][j]);
        memset(G,0,sizeof(G));
        step=0;
        REP(i,N) REP(j,N) if (i!=j&&ng[0][i+1]==ng[0][j+1]+ng[j+1][i+1]) G[i][j]=1;
        
        int res=0;
        memset(vis,0,sizeof(vis));
        memset(peer,-1,sizeof(peer));
        REP(i,N){
            ++step;
            if (!dfs(i)) ++res;
        }
        return res;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; string Arr1[] = {"-234",
 "2---",
 "3---",
 "4---"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(0, Arg2, minRisk(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 2; string Arr1[] = {"-12",
 "1-1",
 "21-"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(1, Arg2, minRisk(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 3; string Arr1[] = {"-----7",
 "--1---",
 "-1-5--",
 "--5-1-",
 "---1-3",
 "7---3-"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(2, Arg2, minRisk(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 2; string Arr1[] = {"-11",
 "1-1",
 "11-"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(3, Arg2, minRisk(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
  SafeReturn ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
