// BEGIN CUT HERE

// END CUT HERE
#line 5 "MagicalHats.cpp"

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

const int maxn=14;
const int maxm=1594323+100;

char dp[maxn][maxm];
int can[maxm];

int ra[maxn], ca[maxn];
int rb[maxn], cb[maxn];
int n,nc;
int pw[maxn];



int go1(int a){
    int &r=can[a];
    if (r!=-1) return r;
    r=0;
    int v=a;
    vi have;
    REP(i,n){
        if (!(v%3)) return r=go1(a+pw[i])|go1(a+2*pw[i]);
        if (v%3==2) have.pb(i);
        v/=3;
    }
    if (have.size()!=nc) return 0;
    memset(rb,0,sizeof(rb));
    memset(cb,0,sizeof(cb));
    REP(i,n) rb[ra[i]]^=1, cb[ca[i]]^=1;
    REP(i,have.size()) rb[ra[have[i]]]^=1, cb[ca[have[i]]]^=1;
    REP(i,maxn) if (rb[i] || cb[i]) return r=0;
    return r=1;
}

char go2(int p, int a){
    char &r=dp[p][a];
    if (r!=-1) return r;
    r=0;
    assert(go1(a));

    int cnt=0;
    int v=a;
    vi have;
    REP(i,n){
        if (!(v%3)) have.pb(i);
        else if (v%3==2) ++cnt;
        v/=3;
    }
    if (!p) return r=cnt;
    REP(i,have.size()){
        char x=111;
        if (cnt<nc && go1(a+2*pw[have[i]])) x=min(x,go2(p-1,a+2*pw[have[i]]));
        if (go1(a+pw[have[i]])) x=min(x,go2(p-1,a+pw[have[i]]));
        r=max(r,x);
    }
    return r;
}


class MagicalHats {
	public:
	int findMaximumReward(vector <string> board, vector <int> coins, int numGuesses) {
        nc=coins.size();
        n=0;
        REP(i,board.size()) REP(j,board[0].size()) if (board[i][j]=='H') ra[n]=i, ca[n++]=j;

        memset(dp,-1,sizeof(dp));
        memset(can,-1,sizeof(can));
        pw[0]=1;
        REP(i,maxn-1) pw[i+1]=pw[i]*3;
        if (!go1(0)) return -1;
        int u=go2(numGuesses,0);
        int res=0;
        sort(ALL(coins));
        REP(i,u) res+=coins[i];
        return res;
    }

    // BEGIN CUT HERE
    public:
    void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); }
    private:
    template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
    void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
    void test_case_0() { string Arr0[] = {"H"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; int Arg3 = 1; verify_case(0, Arg3, findMaximumReward(Arg0, Arg1, Arg2)); }
    void test_case_1() { string Arr0[] = {"HHH",
        "H.H",
        "HH."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {9}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; int Arg3 = 9; verify_case(1, Arg3, findMaximumReward(Arg0, Arg1, Arg2)); }
    void test_case_2() { string Arr0[] = {"HH",
        "HH"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,3,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; int Arg3 = 6; verify_case(2, Arg3, findMaximumReward(Arg0, Arg1, Arg2)); }
    void test_case_3() { string Arr0[] = {"HHH",
        "HHH",
        "H.H"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {13,13,13,13}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; int Arg3 = 13; verify_case(3, Arg3, findMaximumReward(Arg0, Arg1, Arg2)); }
    void test_case_4() { string Arr0[] = {"HHH",
        "HHH",
        "H.H"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {13,13,13,13}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; int Arg3 = 26; verify_case(4, Arg3, findMaximumReward(Arg0, Arg1, Arg2)); }
    void test_case_5() { string Arr0[] = {"H.H.",
        ".H.H",
        "H.H."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {17}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 6; int Arg3 = -1; verify_case(5, Arg3, findMaximumReward(Arg0, Arg1, Arg2)); }
    void test_case_6() { string Arr0[] = {"HHH",
        "H.H",
        "HHH",
        "H.H",
        "HHH"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {33,337,1007,2403,5601,6003,9999}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; int Arg3 = 1377; verify_case(6, Arg3, findMaximumReward(Arg0, Arg1, Arg2)); }
    void test_case_7() { string Arr0[] = {".............",
        ".............",
        ".............",
        ".............",
        ".............",
        ".............",
        ".....H.H.....",
        "......H......",
        ".....H.H.....",
        ".............",
        ".............",
        ".............",
        "............."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {22}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; int Arg3 = 22; verify_case(7, Arg3, findMaximumReward(Arg0, Arg1, Arg2)); }

    // END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
    MagicalHats ___test; 
    ___test.run_test(-1); 
} 
// END CUT HERE
