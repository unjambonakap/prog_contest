// BEGIN CUT HERE

// END CUT HERE
#line 5 "RemoveGame.cpp"

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
typedef vector<string> vs;

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

const int maxn=44;
string s;
int R;
ll A[maxn][maxn][maxn][2];//left,right,num of o, player (num of x=n-num of o)
int n;


ll solve(int a, int b, int o, int p){
    ll &r=A[a][b][o][p];
    if (r!=-1) return r;
    if (s[a+1]=='o') return r=solve(a+1, b, o+1, p);
    if (s[b-1]=='x') return r=solve(a, b-1, o, p);
    if (a==b+1) return r=(o>=n-o&&o>=R);

    r=0;
    if (!p){
        r+=solve(a+1, b, o, p^1);
        if (s[a+1]=='?') r+=solve(a+1, b, o+1, p^1);
    }else{
        r+=solve(a, b-1, o, p^1);
        if (s[b-1]=='?') r+=solve(a, b-1, o, p^1);
    }
    return r;
}

class RemoveGame {
	public:
	long long countWinning(string field, int _R) {
        s=field;
        R=_R;
        n=s.length();
        memset(A, -1, sizeof(A));

        return solve(0, n-1, 1, 0);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "o??x"; int Arg1 = 2; long long Arg2 = 2LL; verify_case(0, Arg2, countWinning(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "o??x"; int Arg1 = 3; long long Arg2 = 1LL; verify_case(1, Arg2, countWinning(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "oxxxxoooox"; int Arg1 = 2; long long Arg2 = 1LL; verify_case(2, Arg2, countWinning(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "ooooxxoxxx"; int Arg1 = 1; long long Arg2 = 0LL; verify_case(3, Arg2, countWinning(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "ox?o?ox"; int Arg1 = 3; long long Arg2 = 3LL; verify_case(4, Arg2, countWinning(Arg0, Arg1)); }
	void test_case_5() { string Arg0 = "o????xooxooxxxxxxx"; int Arg1 = 5; long long Arg2 = 1LL; verify_case(5, Arg2, countWinning(Arg0, Arg1)); }
	void test_case_6() { string Arg0 = "oxxxxxxxxxoooxooxoooooooooooo??????x"; int Arg1 = 5; long long Arg2 = 64LL; verify_case(6, Arg2, countWinning(Arg0, Arg1)); }
	void test_case_7() { string Arg0 = "oo???xx???xx???oxox???xx"; int Arg1 = 7; long long Arg2 = 126LL; verify_case(7, Arg2, countWinning(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  RemoveGame ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
