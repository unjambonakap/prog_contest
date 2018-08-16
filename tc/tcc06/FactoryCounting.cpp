// BEGIN CUT HERE

// END CUT HERE
#line 5 "FactoryCounting.cpp"

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

const int maxk=30;
int tb[maxk];
int cnk[maxk][maxk];
int k;
int n, m;
ll ans;

void solve(int pos, int a, int ma){
    if (pos==-1){
        int c=count_bit(ma);
        ans+=cnk[c][m];
        return;
    }

    FOR(i, pos, a) solve(pos-1, i-1, ma&tb[i]);

}

class FactoryCounting {
	public:
	long long count(int _n, int _m, vector <string> county) {
        n=_n; m=_m;
        if (n>m) swap(n, m);
        int k=county.size();
        if (n+m>k) return 0;

        memset(cnk, 0, sizeof(cnk));

        REP(i, k+1) cnk[i][0]=1;
        FOR(i, 1, k-1) FOR(j, 1, min(i, m)) cnk[i][j]=cnk[i-1][j-1]+cnk[i-1][j];



        memset(tb, 0, sizeof(tb));
        REP(i, k) REP(j, k) if (county[i][j]=='Y') tb[i]|=two(j);
		
        ans=0;
        solve(n-1, k-1, two(k)-1);
        return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 1; string Arr2[] = {
 "NYY",
 "YNY",
 "YYN"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 3LL; verify_case(0, Arg3, count(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 2; string Arr2[] = {
 "NYYYYN",
 "YNYYNY",
 "YYNYYY",
 "YYYNYN",
 "YNYYNY",
 "NYYNYN"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 32LL; verify_case(1, Arg3, count(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 1; int Arg1 = 1; string Arr2[] = {
 "NNNNYN",
 "NNNYNN",
 "NNNNYN",
 "NYNNYN",
 "YNYYNN",
 "NNNNNN"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 8LL; verify_case(2, Arg3, count(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 3; int Arg1 = 3; string Arr2[] = {
 "NYYYNYYNYY",
 "YNYYYYYYYN",
 "YYNYYYNYYN",
 "YYYNYYNYNY",
 "NYYYNYYYYY",
 "YYYYYNYYNY",
 "YYNNYYNYYN",
 "NYYYYYYNNY",
 "YYYNYNYNNY",
 "YNNYYYNYYN"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 308LL; verify_case(3, Arg3, count(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 7; int Arg1 = 8; string Arr2[] = {
 "NYYYYYNYYYYYNYYYYYYYYYYNYYYYYY",
 "YNYYYYYYYYYYYYYYYNYYYYYYYYYYYY",
 "YYNYYYYYYYYYYYYNYNYYYNNYYYNYYY",
 "YYYNYYYYYYYYNYYYYYNYYYYYYNYYYY",
 "YYYYNYYYYYYYYYNYYYYYYYYYYYNYYY",
 "YYYYYNYYNYYYYNYYYYYNYYYYYYYNNY",
 "NYYYYYNYYYYYYYYYNYYYYNYYYYYYYY",
 "YYYYYYYNYYYYYYYYYYYYYYYYYYYYYY",
 "YYYYYNYYNYYYYNNYYYYYYYYNYYNNYY",
 "YYYYYYYYYNYYNYYNYNYYNYYYYYYYYY",
 "YYYYYYYYYYNYYNYYYYYYYNYYYYYYYY",
 "YYYYYYYYYYYNYYYYNYYYYYYYYYYYYY",
 "NYYNYYYYYNYYNYYYNYNYYYYYNYYYYY",
 "YYYYYNYYNYNYYNYYYYYYYYYYYNYYNY",
 "YYYYNYYYNYYYYYNNNYYYYYYYYYYYYY",
 "YYNYYYYYYNYYYYNNYNYYYYYNNYYYNY",
 "YYYYYYNYYYYNNYNYNNYYNYYYYYNYNY",
 "YNNYYYYYYNYYYYYNNNYYNYYYYYYYYY",
 "YYYNYYYYYYYYNYYYYYNNYYNYYYYYYY",
 "YYYYYNYYYYYYYYYYYYNNYYYYYYYYYY",
 "YYYYYYYYYNYYYYYYNNYYNYYYYYNYYY",
 "YYNYYYNYYYNYYYYYYYYYYNYYYYYYYY",
 "YYNYYYYYYYYYYYYYYYNYYYNYYYYYYY",
 "NYYYYYYYNYYYYYYNYYYYYYYNYYYYYY",
 "YYYYYYYYYYYYNYYNYYYYYYYYNYYYYY",
 "YYYNYYYYYYYYYNYYYYYYYYYYYNYYYY",
 "YYNYNYYYNYYYYYYYNYYYNYYYYYNYYY",
 "YYYYYNYYNYYYYYYYYYYYYYYYYYYNYY",
 "YYYYYNYYYYYYYNYNNYYYYYYYYYYYNN",
 "YYYYYYYYYYYYYYYYYYYYYYYYYYYYNN"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 522891760LL; verify_case(4, Arg3, count(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arg0 = 8; int Arg1 = 8; string Arr2[] = {
 "NYYYYYYYYYYYYYYYYYYYYYYYYYYYYY",
 "YNYYYYYYYYYYYYYYYYYYYYYYYYYYYY",
 "YYNYYYYYYYYYYYYYYYYYYYYYYYYYYY",
 "YYYNYYYYYYYYYYYYYYYYYYYYYYYYYY",
 "YYYYNYYYYYYYYYYYYYYYYYYYYYYYYY",
 "YYYYYNYYYYYYYYYYYYYYYYYYYYYYYY",
 "YYYYYYNYYYYYYYYYYYYYYYYYYYYYYY",
 "YYYYYYYNYYYYYYYYYYYYYYYYYYYYYY",
 "YYYYYYYYNYYYYYYYYYYYYYYYYYYYYY",
 "YYYYYYYYYNYYYYYYYYYYYYYYYYYYYY",
 "YYYYYYYYYYNYYYYYYYYYYYYYYYYYYY",
 "YYYYYYYYYYYNYYYYYYYYYYYYYYYYYY",
 "YYYYYYYYYYYYNYYYYYYYYYYYYYYYYY",
 "YYYYYYYYYYYYYNYYYYYYYYYYYYYYYY",
 "YYYYYYYYYYYYYYNYYYYYYYYYYYYYYY",
 "YYYYYYYYYYYYYYYNYYYYYYYYYYYYYY",
 "YYYYYYYYYYYYYYYYNYYYYYYYYYYYYY",
 "YYYYYYYYYYYYYYYYYNYYYYYYYYYYYY",
 "YYYYYYYYYYYYYYYYYYNYYYYYYYYYYY",
 "YYYYYYYYYYYYYYYYYYYNYYYYYYYYYY",
 "YYYYYYYYYYYYYYYYYYYYNYYYYYYYYY",
 "YYYYYYYYYYYYYYYYYYYYYNYYYYYYYY",
 "YYYYYYYYYYYYYYYYYYYYYYNYYYYYYY",
 "YYYYYYYYYYYYYYYYYYYYYYYNYYYYYY",
 "YYYYYYYYYYYYYYYYYYYYYYYYNYYYYY",
 "YYYYYYYYYYYYYYYYYYYYYYYYYNYYYY",
 "YYYYYYYYYYYYYYYYYYYYYYYYYYNYYY",
 "YYYYYYYYYYYYYYYYYYYYYYYYYYYNYY",
 "YYYYYYYYYYYYYYYYYYYYYYYYYYYYNY",
 "YYYYYYYYYYYYYYYYYYYYYYYYYYYYYN"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 1871589827250LL; verify_case(5, Arg3, count(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  FactoryCounting ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
