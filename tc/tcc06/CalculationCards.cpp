// BEGIN CUT HERE

// END CUT HERE
#line 5 "CalculationCards.cpp"

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

int n, m;
int cards[maxn];
double dp[maxn];
double cnk[maxn][maxn];

double prob(int a){
    double res=0.;
    res+=cnk[n+m-1-a][n-a];
    if (m>1) res+=cnk[n+m-2-a][n-a]*(n+m-1-a);
    return res/(n+m)/cnk[n+m-1][n];

}

double proc(){
    double res=0.;
    if (m==0) return 0;
    REP(i, n+1){
        memset(dp, 0, sizeof(dp));
        dp[0]=1./cnk[n][i]*prob(i);
        REP(j, n) REPV(k, min(i, j+1)) dp[k+1]+=dp[k]*cards[j];
        res+=dp[i];
    }
    return res;
}


class CalculationCards {
	public:
	double getExpected(vector <string> cx) {
        n=0;
        m=cx.size();
        int s=0;
        memset(cnk, 0, sizeof(cnk));
        REP(i, maxn) cnk[i][0]=cnk[i][i]=1.;
        FOR(i, 1, maxn-1) FOR(j, 1, maxn-1) cnk[i][j]=cnk[i-1][j-1]+cnk[i-1][j];

        REP(i, m){
            if (cx[i][0]=='*') cards[n++]=cx[i][1]-'0';
            else s+=(cx[i][1]-'0')*(cx[i][0]=='+'?1:-1);
        }
        m-=n;
        return s*proc();
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	//void test_case_0() { string Arr0[] = { "+1", "-2", "*3" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = -1.6666666666666667; verify_case(0, Arg1, getExpected(Arg0)); }
	void test_case_0() { string Arr0[] = {"*1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = -1.6666666666666667; verify_case(0, Arg1, getExpected(Arg0)); }
	void test_case_1() { string Arr0[] = { "+1", "+2", "+3" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 6.0; verify_case(1, Arg1, getExpected(Arg0)); }
	void test_case_2() { string Arr0[] = { "+3", "-7", "*4", "+6" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 3.5; verify_case(2, Arg1, getExpected(Arg0)); }
	void test_case_3() { string Arr0[] = { "+1", "*2", "*3" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 3.1666666666666665; verify_case(3, Arg1, getExpected(Arg0)); }
	void test_case_4() { string Arr0[] = { "*7", "-2", "*0", "+3", "*8" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 5.633333333333334; verify_case(4, Arg1, getExpected(Arg0)); }
	void test_case_5() { string Arr0[] = { "+1", "*9", "*9", "*9", "*9", "*9", "*9", "*9", "*9", "*9", "*9" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 3.5660295009090906E8; verify_case(5, Arg1, getExpected(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  CalculationCards ___test; 
        ___test.run_test(0);
        } 
// END CUT HERE
