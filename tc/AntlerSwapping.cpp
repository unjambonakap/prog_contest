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
#define FOR(i, a, b) for(int i = (int)(a); i < (int)(b); ++i)

#define FE(i,t) for (__typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (__typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

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
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=16;
const int oo=1e9;
int dp[1<<maxn];
int ta[maxn], tb[maxn];
int n, C;

int solve(){

    int M=1<<n;
    dp[0]=0;
    REP(i,M) if (i){
        vi lst;
        REP(j,n) if (i&1<<j) lst.pb(ta[j]), lst.pb(tb[j]);
        sort(ALL(lst));

        int ok=1;
        REP(j,lst.size()/2) if (lst[2*j+1]-lst[2*j]>C){ok=0; break;}
        dp[i]=ok?lst.size()/2-1:oo;
    }
    for (int i=1; i<M; ++i) for (int j=i; j; j=(j-1)&i){
        int b=dp[j]+dp[i^j];
        if (dp[i]>b) dp[i]=b;
    }

    return dp[M-1]>=oo?-1:dp[M-1];
}

class AntlerSwapping{ 
    public: 
    int getmin(vector <int> antler1, vector <int> antler2, int capacity){ 
        n=antler1.size();
        REP(i,n) ta[i]=antler1[i];
        REP(i,n) tb[i]=antler2[i];
        C=capacity;
        return solve();

    } 
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {3, 2, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3, 5, 5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; int Arg3 = 1; verify_case(0, Arg3, getmin(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {4, 2, 6, 4, 8, 5, 2, 3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3, 4, 5, 2, 8, 5, 7, 6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; int Arg3 = 2; verify_case(1, Arg3, getmin(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {12, 34, 56, 78}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1234, 2345, 3456, 4567}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 100; int Arg3 = -1; verify_case(2, Arg3, getmin(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {47, 58, 2013}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {49, 55, 2013}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; int Arg3 = 0; verify_case(3, Arg3, getmin(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {4, 1, 7, 5, 7, 8, 2, 1, 3, 1, 7, 5, 9, 4, 9, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {10, 6, 5, 3, 1, 8, 4, 4, 4, 7, 1, 4, 6, 5, 10, 10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; int Arg3 = 7; verify_case(4, Arg3, getmin(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
}; 

// BEGIN CUT HERE 
int main(){
    AntlerSwapping ___test;
    ___test.run_test(-1);
} 
// END CUT HERE
