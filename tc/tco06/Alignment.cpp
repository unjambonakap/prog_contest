// BEGIN CUT HERE

// END CUT HERE
#line 5 "Alignment.cpp"

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

const int maxn=55;
string a, b;
int n, m;
int x;
int dp[maxn][maxn][2*maxn][2];

int solve(int i, int j, int nx, int s){
    int &r=dp[i][j][nx][s];
    if (r!=-1) return r;

    if (i==n) return r=(!nx?0:x+nx)+(m-j==0?0:x+m-j);;
    if (j==m) return r=(!nx?0:x+nx)+(n-i==0?0:x+n-i);;

    r=INT_MAX;
    if (!s) checkmin(r, solve(i, j+1, nx+1, 0));
    else checkmin(r, solve(i, j+1, 1, 0)+(!nx?0:x+nx));
    if (s) checkmin(r, solve(i+1, j, nx+1, 1));
    else checkmin(r, solve(i+1, j, 1, 1)+(!nx?0:x+nx));
    if (a[i]==b[j]) checkmin(r, solve(i+1, j+1, 0, 0)+(!nx?0:x+nx));
    return r;


}

class Alignment {
	public:
	int align(string A, string B, int _x) {
        x=_x;
        a=A; b=B;
        n=a.length();
        m=b.length();
        memset(dp, -1, sizeof(dp));
        return solve(0, 0, 0, 0);


	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "ABC"; string Arg1 = "ACE"; int Arg2 = 1; int Arg3 = 4; verify_case(0, Arg3, align(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arg0 = "AAABAAAABAA"; string Arg1 = "AAAABAABAAA"; int Arg2 = 1; int Arg3 = 7; verify_case(1, Arg3, align(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arg0 = "AAABAAAABAA"; string Arg1 = "AAAABAABAAA"; int Arg2 = 10; int Arg3 = 28; verify_case(2, Arg3, align(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arg0 = "AA"; string Arg1 = "B"; int Arg2 = 1; int Arg3 = 5; verify_case(3, Arg3, align(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  Alignment ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
