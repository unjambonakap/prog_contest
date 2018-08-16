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

const int maxn=55;
int deg[maxn];
int g[maxn][maxn];

class PenguinSledding{ 
    public: 
    long long countDesigns(int n, vector <int> a, vector <int> b){ 
        ll res=1;
        int m=a.size();
        res+=m;
        memset(deg,0,sizeof(deg));
        memset(g,0,sizeof(g));
        REP(i,m) --a[i], --b[i];
        REP(i,m) g[a[i]][b[i]]=g[b[i]][a[i]]=1;
        
        REP(i,m) ++deg[a[i]], ++deg[b[i]];
        REP(i,n) REP(j,i) REP(k,j) if (g[i][j]&&g[j][k]&&g[k][i]) ++res;
        REP(i,n) res+=(1ll<<deg[i])-deg[i]-1;
        return res;
    } 
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arr1[] = {1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 2LL; verify_case(0, Arg3, countDesigns(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 4; int Arr1[] = {1,2,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2,3,4}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 6LL; verify_case(1, Arg3, countDesigns(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 6; int Arr1[] = {1,3,6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2,4,4}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 5LL; verify_case(2, Arg3, countDesigns(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 50; int Arr1[] = {40, 40, 40, 40, 40, 40, 40, 40, 
 40, 40, 40, 40, 50, 40, 40, 40, 
 23, 4, 24, 40, 22, 40, 8, 40, 40,
 40, 34, 21, 40, 40, 38, 40, 40, 
 40, 40, 40, 28, 40, 40, 40, 40, 
 46, 13, 40, 40, 40, 47, 40, 40}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {45, 42, 20, 48, 12, 32, 25, 10, 
 26, 39, 16, 2, 19, 43, 37, 17, 
 19, 19, 19, 18, 19, 27, 19, 29, 
 11, 36, 19, 19, 1, 41, 19, 35, 
 14, 33, 49, 3, 19, 7, 5, 19, 31, 
 19, 19, 6, 9, 15, 19, 44, 30}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 68719493118LL; verify_case(3, Arg3, countDesigns(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 36; int Arr1[] = {13, 24, 24, 20, 31, 16, 10, 36, 34, 32, 
 28, 5, 20, 29, 23, 2, 14, 4, 9, 5, 19, 
 21, 8, 1, 26, 27, 25, 15, 22, 30, 30, 
 6, 11, 7, 2, 35, 13, 29, 4, 12, 33, 18, 
 13, 14, 17, 35, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {10, 15, 27, 1, 29, 11, 5, 18, 33, 1, 9,
 2, 31, 6, 19, 10, 33, 18, 6, 27, 3, 22,
 4, 12, 31, 30, 34, 16, 7, 24, 3, 28, 15,
 21, 22, 8, 26, 20, 14, 32, 25, 17, 35,
 8, 36, 26, 23}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 162LL; verify_case(4, Arg3, countDesigns(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
}; 

// BEGIN CUT HERE 
int main(){
    PenguinSledding ___test;
    ___test.run_test(-1);
} 
// END CUT HERE
