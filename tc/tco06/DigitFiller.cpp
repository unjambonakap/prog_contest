// BEGIN CUT HERE

// END CUT HERE
#line 5 "DigitFiller.cpp"

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


const int maxc=20;
const int maxm=1e4+10;
int c, m;
string k;
ll dp[maxc][maxm];
ll solve(int p, int v, int pw){
    if (p==c) return v==0;
    ll &r=dp[p][v];
    if (r!=-1) return r;

    r=0;
    if (k[p]=='X'){
        REP(i, 10) r+=solve(p+1, (v+pw*i)%m, (pw*10)%m);
    }else r=solve(p+1, (v+pw*(k[p]-'0'))%m, (pw*10)%m);

    return r;


}

class DigitFiller {
	public:
	long long howMany(string _k, int num) {
        k=_k;
        m=num;
        reverse(ALL(k));
        c=k.length();
        memset(dp, -1, sizeof(dp));
        return solve(0, 0, 1);

		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "8X"; int Arg1 = 9; long long Arg2 = 1LL; verify_case(0, Arg2, howMany(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "1XX"; int Arg1 = 10; long long Arg2 = 10LL; verify_case(1, Arg2, howMany(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "14"; int Arg1 = 7; long long Arg2 = 1LL; verify_case(2, Arg2, howMany(Arg0, Arg1)); }
	//void test_case_3() { string Arg0 = "9999999999999X"; int Arg1 = 3; long long Arg2 = 4LL; verify_case(3, Arg2, howMany(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "9XXXXXXXXXXXXXXXXX"; int Arg1 = 1; long long Arg2 = 4LL; verify_case(3, Arg2, howMany(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "23X34XX24XX34X"; int Arg1 = 17; long long Arg2 = 58823LL; verify_case(4, Arg2, howMany(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  DigitFiller ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
