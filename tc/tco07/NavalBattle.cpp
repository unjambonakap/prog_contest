// BEGIN CUT HERE

// END CUT HERE
#line 5 "NavalBattle.cpp"

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
int npos=0;
int sl, fl, n;

int mp[maxn];
int dp[maxn][maxn];

int proc(int a, int b){
	int &r=dp[a][b];
	if (r!=-1)return r;
	r=1;
	if (a>=b)return r;
	if (mp[a]!=1 && proc(a+1, b))return r;
	if (a+sl<b){ if (mp[a+sl]!=1 && proc(a+sl+1, b))return r; }
	else if (a+sl==b) return r;

	return r=0;
}

int checkit(){
	int last=0;
	vector<pii> range;
	REP(i, fl){
		if (mp[i]==0){
			if (i-last>=sl) range.pb(MP(last, i));
			else FOR(j, last, i-1) if (mp[j]==1)return 0;
			last=i+1;
		}
	}if (fl-last>=sl) range.pb(MP(last, fl));
	else FOR(j, last, fl-1) if (mp[j]==1)return 0;
	if (!range.size()) return 0;
	memset(dp, -1, sizeof(dp));
	REP(i, range.size()) if (!proc(range[i].ST, range[i].ND))return 0;
	return 1;
}


class NavalBattle {
	public:
	int firstDishonestMove(int _fl, int _sl, vector <int> shots, string ans) {
		sl=_sl, fl=_fl; n=shots.size();
		memset(mp, -1, sizeof(mp));

		REP(i, n){
			if (mp[shots[i]]!=-1 && mp[shots[i]]!=ans[i]-'0')return i;
			mp[shots[i]]=ans[i]-'0';
			if (!checkit())return i;
		}
		return -1;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	//void test_case_0() { int Arg0 = 1; int Arg1 = 1; int Arr2[] = {0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "1"; int Arg4 = -1; verify_case(0, Arg4, firstDishonestMove(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_0() { int Arg0 = 23; int Arg1 = 11; int Arr2[] = {16, 18, 21, 20, 7, 17, 22, 10, 8, 11, 11}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "11111110000"; int Arg4 = -1; verify_case(0, Arg4, firstDishonestMove(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 2; int Arr2[] = {0, 2, 1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "110"; int Arg4 = 1; verify_case(1, Arg4, firstDishonestMove(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 5; int Arg1 = 2; int Arr2[] = {0, 4, 1, 3, 2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "11110"; int Arg4 = -1; verify_case(2, Arg4, firstDishonestMove(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 10; int Arg1 = 1; int Arr2[] = {4, 7, 8, 2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "0110"; int Arg4 = 2; verify_case(3, Arg4, firstDishonestMove(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arg0 = 10; int Arg1 = 10; int Arr2[] = {4, 2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "01"; int Arg4 = 0; verify_case(4, Arg4, firstDishonestMove(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  NavalBattle ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE
