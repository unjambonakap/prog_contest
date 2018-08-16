// BEGIN CUT HERE

// END CUT HERE
#line 5 "PolishNotation.cpp"

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
string s;
int n;
ll dp[maxn][maxn];
map<char, int> op;

ll proc(int a, int b){
	ll &r=dp[a][b];
	if (r!=-1) return r;

	r=0;
	if (!op.count(s[a]) || s[a]=='-'){
		bool ok=true;

		if (s[a]=='-' && b==a+1)return 0;
		FOR(j, a+1, b-1) if (op.count(s[j])){ok=false; break;}
		if (ok) ++r;

	}
	if (op.count(s[a])) FOR(j, a+2, b-1) r+=proc(a+1, j)*proc(j, b);

	return r;

}

class PolishNotation {
	public:
	long long waysToDecode(string _s) {
		s=_s; n=s.length();
		memset(dp, -1, sizeof(dp));
		op.insert(MP('+', 1)); op.insert(MP('-', 2)); op.insert(MP('*', 3)); op.insert(MP('/', 4));

		return proc(0, n);
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "01234567890123456789"; long long Arg1 = 1LL; verify_case(0, Arg1, waysToDecode(Arg0)); }
	void test_case_1() { string Arg0 = "+1234567"; long long Arg1 = 6LL; verify_case(1, Arg1, waysToDecode(Arg0)); }
	void test_case_2() { string Arg0 = "23/33"; long long Arg1 = 0LL; verify_case(2, Arg1, waysToDecode(Arg0)); }
	void test_case_3() { string Arg0 = "/-010"; long long Arg1 = 3LL; verify_case(3, Arg1, waysToDecode(Arg0)); }
	void test_case_4() { string Arg0 = "-*123"; long long Arg1 = 1LL; verify_case(4, Arg1, waysToDecode(Arg0)); }
	void test_case_5() { string Arg0 = "--1"; long long Arg1 = 0LL; verify_case(5, Arg1, waysToDecode(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  PolishNotation ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
