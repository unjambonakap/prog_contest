// BEGIN CUT HERE

// END CUT HERE
#line 5 "Postman.cpp"

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


set<int> sa, sb;
int na, nb;
const int maxn=1310;
ll dp[maxn][maxn][2];
const ll inf=1e10;

class Postman {
	public:
	int minTime(vector <string> os, int ct) {
        string s;
        FE(it, os) s+=*it+" ";
        sa.clear(); sb.clear();
        istringstream ss(s);
        int tmp;
        while(ss>>tmp){
            if (tmp%2) sa.insert((tmp-1)/2);
            else sb.insert((tmp-1)/2);
        }
        vi a(ALL(sa)), b(ALL(sb));
        na=a.size(); nb=b.size();

        REP(i, na+1) REP(j, nb+1) REP(k, 2) dp[i][j][k]=inf;
        dp[0][0][0]=0; dp[0][0][1]=ct;

        REP(i, na+1) REP(j, nb+1){
            if (i<na) dp[i+1][j][0]=min(dp[i][j][0]+a[i]-(!i?0:a[i-1]), dp[i][j][1]+abs(a[i]-(!j?0:b[j-1]))+ct);
            if (j<nb) dp[i][j+1][1]=min(dp[i][j][1]+b[j]-(!j?0:b[j-1]), dp[i][j][0]+abs(b[j]-(!i?0:a[i-1]))+ct);
        }
        ll r=min(dp[na][nb][0], dp[na][nb][1]); 

        REP(i, na) checkmin(r, dp[i][nb][1]+ct+a[na-1]-a[i]+min(abs((!nb?0:b[nb-1])-a[na-1]), abs((!nb?0:b[nb-1])-a[i])));
        REP(i, nb) checkmin(r, dp[na][i][0]+ct+b[nb-1]-b[i]+min(abs((!na?0:a[na-1])-b[nb-1]), abs((!na?0:a[na-1])-b[i])));



        return r;

		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	//void test_case_0() { string Arr0[] = {"1 2 11 12 21 22"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 16; verify_case(0, Arg2, minTime(Arg0, Arg1)); }
	void test_case_0() { string Arr0[] = {"1 3 77 81 101 123", "3 77 1 97 105", "1013 17777", "121451", "1000001", "999999999", "765431 534673 111111"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 75; int Arg2 = 16; verify_case(0, Arg2, minTime(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"1 2 11 12 21 22"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; int Arg2 = 30; verify_case(1, Arg2, minTime(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"7 6 5 3","8 8 8 8","","35","40 42",""}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; int Arg2 = 45; verify_case(2, Arg2, minTime(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"",""}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 0; verify_case(3, Arg2, minTime(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  Postman ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE
