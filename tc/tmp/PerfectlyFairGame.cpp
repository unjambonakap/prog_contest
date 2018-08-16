// BEGIN CUT HERE

// END CUT HERE
#line 5 "PerfectlyFairGame.cpp"

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

const int maxn=22;
const int mod=44*maxn;
int mp[maxn][maxn];
double dp[2*maxn][mod];
int vis[2*maxn][mod];
int r, c;
int n;

double solve(int p, int a){
    if (p==2*n) return !a?0.5:a>0;

    double &rx=dp[p][(mod+a)%mod];
    if (vis[p][(mod+a)%mod]) return rx;
    vis[p][(mod+a)%mod]=1;

    rx=0.;
    FOR(i, 1, r-1) FOR(j, 1, c-1){
        double ans=0.;
        for (int dr=-1; dr<=1; ++dr) for (int dc=-1; dc<=1; ++dc) ans+=1-solve(p+1, -(a+mp[i+dr][j+dc]))/9;
        checkmax(rx, ans);
    }
    
    return rx;
}

class PerfectlyFairGame {
	public:
	double winChance(vector <string> board, int darts) {
        r=board.size(); c=board[0].length();
        REP(i, r) REP(j, c) mp[i][j]=board[i][j]-'0';
        memset(vis, 0, sizeof(vis));
        n=darts;

        return 1-solve(0, 0);

		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"123","456","789"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; double Arg2 = 0.5; verify_case(0, Arg2, winChance(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"55555","55555","55555","55555","55555"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 20; double Arg2 = 0.5; verify_case(1, Arg2, winChance(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"0909","9090","0909","9090"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 20; double Arg2 = 0.5; verify_case(2, Arg2, winChance(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"888","808","888","000","000","999","999"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; double Arg2 = 0.537037037037037; verify_case(3, Arg2, winChance(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"29368","65609","67539","57982","71709"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; double Arg2 = 0.5440401329247544; verify_case(4, Arg2, winChance(Arg0, Arg1)); }
	void test_case_5() { string Arr0[] = {"4225271513","8352579454","1582795371","3365182453","7374843700","3262631490","5261771017","5124728129","1537793032","1147236439"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 20; double Arg2 = 0.5055321764007881; verify_case(5, Arg2, winChance(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
  PerfectlyFairGame ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
