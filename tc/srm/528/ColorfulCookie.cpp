// BEGIN CUT HERE

// END CUT HERE
#line 5 "ColorfulCookie.cpp"

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

const int maxn=64;
const int inf=1e6;
int X, Y;
int n;
vi tb;
int M;
int dp[maxn][2222];


int go(int p, int a){
    checkmax(a, 0);
    if (p==n) return a?-inf:0;
    int &r=dp[p][a];
    if (r!=-1) return r;
    r=-inf;
    REP(i, tb[p]/X+1){
        int j=(tb[p]-i*X)/Y;
        if (i+j>M) checkmax(r, max(go(p+1, a-i)+M-i, go(p+1, a-(M-j))+j));
        else checkmax(r, go(p+1, a-i)+j);

    }
    return r;
}



class ColorfulCookie {
	public:
	int getMaximum(vector <int> cookies, int P1, int P2) {
        tb=cookies;
        n=tb.size();
        X=P1; Y=P2;
        int H=2111, T=0;
        memset(dp, -1, sizeof(dp));
        while(T+1<H){
            M=(T+H)/2;
            memset(dp, -1, sizeof(dp));
            if (go(0,M)>=M) T=M;
            else H=M;
        }
        return T*(X+Y);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	//void test_case_0() { int Arr0[] = {1958, 1892, 1921, 1851, 1891, 1991, 1944, 1840, 1824, 1934, 1879, 1841, 1962, 1821, 1885, 1955, 1977, 1827, 1807, 1911, 1963, 1886, 1935, 1810, 1891, 1984, 1840, 1820, 1974, 1952, 1880, 1804, 1975, 1848, 1824, 1941, 1829, 1869, 1911, 1987, 1800, 1957, 1836, 1975, 1802, 1860, 1963, 1845, 1897, 1934}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 93; int Arg2 = 107; int Arg3 = 200; verify_case(0, Arg3, getMaximum(Arg0, Arg1, Arg2)); }
	void test_case_0() { int Arr0[] = {1603, 416}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 126; int Arg2 = 179; int Arg3 = 200; verify_case(0, Arg3, getMaximum(Arg0, Arg1, Arg2)); }
	//void test_case_0() { int Arr0[] = {100, 100}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 50; int Arg2 = 50; int Arg3 = 200; verify_case(0, Arg3, getMaximum(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {50, 250, 50}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 50; int Arg2 = 100; int Arg3 = 300; verify_case(1, Arg3, getMaximum(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {2000}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 100; int Arg2 = 200; int Arg3 = 0; verify_case(2, Arg3, getMaximum(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {123, 456, 789, 555}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 58; int Arg2 = 158; int Arg3 = 1728; verify_case(3, Arg3, getMaximum(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
  ColorfulCookie ___test; 
        ___test.run_test(0);
        } 
// END CUT HERE
