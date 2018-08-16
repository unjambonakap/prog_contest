// BEGIN CUT HERE

// END CUT HERE
#line 5 "MaxKTrace.cpp"

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
const int inf=1e5;
int dp[maxn][maxn][maxn];
int n, k;
int mat[maxn][maxn];


int solve(int pos, int a, int c){
    if (pos==n) return (a!=k?-inf:0);

    if (a==k) return 0;
    if (c==n) return -inf;


    int &r=dp[pos][a][c];
    if (r!=-1) return r;
    r=solve(pos+1, a, c);
    checkmax(r, solve(pos, a, c+1));
    checkmax(r, solve(pos+1, a+1, c+1)+mat[pos][c]);
    return r;


}


class MaxKTrace {
	public:
	int getLargest(vector <string> _mat, int _k) {
        k=_k;
        n=_mat.size();
        REP(i, n) REP(j, n) mat[i][j]=_mat[i][j]-'0';
        memset(dp, -1, sizeof(dp));
        return solve(0, 0, 0);


    }

    // BEGIN CUT HERE
    public:
    void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
    private:
    template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
    void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
    //	void test_case_0() { string Arr0[] = {
    //"123",
    //"456",
    //"789"
    //}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 15; verify_case(0, Arg2, getLargest(Arg0, Arg1)); }
    void test_case_0() { string Arr0[] = {"000000000000000", "000000000000000", "000000090000000", "000000000000000", "000000000000000", "000000000000000", "000000000000000", "000000000000000", "000000000000000", "000000000000900", "000000000000000", "000000000000000", "000000000000000", "000000000000090", "000000000000009"};
        vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 15; verify_case(0, Arg2, getLargest(Arg0, Arg1)); }
        void test_case_1() { string Arr0[] = {
            "12",
            "93"
        }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 9; verify_case(1, Arg2, getLargest(Arg0, Arg1)); }
        void test_case_2() { string Arr0[] = {
            "12689",
            "55555",
            "55555",
            "55555",
            "55555"
        }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 16; verify_case(2, Arg2, getLargest(Arg0, Arg1)); }
        void test_case_3() { string Arr0[] = {
            "494599520389852", 
            "303896953907791", 
            "287493604901139", 
            "149554299340006", 
            "893640109028429", 
            "564962730433253", 
            "075854577852319", 
            "453201529585621", 
            "950489162577436",
            "630040569640126", 
            "415141646262027", 
            "837673828874883", 
            "785041862021729", 
            "850806584119109", 
            "217671590991247"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; int Arg2 = 45; verify_case(3, Arg2, getLargest(Arg0, Arg1)); }

        // END CUT HERE

};

// BEGIN CUT HERE
int main(){
    MaxKTrace ___test; 
    ___test.run_test(0);
} 
// END CUT HERE
