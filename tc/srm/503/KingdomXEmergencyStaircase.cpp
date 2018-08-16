// BEGIN CUT HERE

// END CUT HERE
#line 5 "KingdomXEmergencyStaircase.cpp"

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


const int maxn=51;
const int maxd=11;
vi cost;
int D;
int n[2];
int tb[2][maxn];
ll dp[2][maxn][maxd][maxd][maxd][maxd];

ll go(int p, int h, int a, int b, int c, int d){
    ll &r=dp[p][h][a][b][c][d];
    if (r!=-1) return r;
    r=0;

    return r;
}



class KingdomXEmergencyStaircase {
	public:
	long long determineCost(string lb, string rb, vector <int> _cost) {
        cost=_cost;
        n[0]=lb.size(); n[1]=rb.size();
        REP(i,n) tb[0][i]=lb[i]=='Y';
        REP(i,m) tb[1][i]=rb[i]=='Y';
        D=cost.size();
        memset(dp,-1,sizeof(dp));
        return min(go(0,D,D,0,0,0), go(1,D,D,0,0,0));
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "YNYY"; string Arg1 = "NNNY"; int Arr2[] = {10, 40, 18, 25}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 98LL; verify_case(0, Arg3, determineCost(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arg0 = "N"; string Arg1 = "Y"; int Arr2[] = {1, 1000}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 1000LL; verify_case(1, Arg3, determineCost(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arg0 = "NNNNNNNY"; string Arg1 = "NNNNNNNY"; int Arr2[] = {1, 2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 17LL; verify_case(2, Arg3, determineCost(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arg0 = "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN"; string Arg1 = "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNY"; int Arr2[] = {800000000,800000000,800000000,800000000,800000000,800000000,800000000,800000000}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 6400000000LL; verify_case(3, Arg3, determineCost(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arg0 = "NNY"; string Arg1 = "NNYYY"; int Arr2[] = {10000, 10, 40, 10000, 80, 80}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 220LL; verify_case(4, Arg3, determineCost(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
  KingdomXEmergencyStaircase ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
