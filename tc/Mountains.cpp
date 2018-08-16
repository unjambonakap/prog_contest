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

const int mod=1e9+9;
const int X=55;
const int maxn=11;

map<ll,int> dp[maxn];
int is[maxn], is2[maxn];
vi h;
int vis[maxn][X];
int n,w;

void unpack(ll a, vi &x){
    while(a) x.pb(a%X-1), a/=X;
}


int go(int a, ll b){
    if (a==-1) return 1;
    if (dp[a].count(b)) return dp[a][b];
    int &r=dp[a][b];

    vi x;
    unpack(b,x);
    int st=-1;
    REP(i,w){
        int ok=1;
        REP(j,w){
            int ha=h[a]-abs(i-j);
            int hb=0;
            REP(k,x.size()) hb=max(hb,h[a+k+1]-abs(x[k]-j));
            if (vis[a][j]!=(ha>hb)){ok=0; break;}
        }
        if (!ok) continue;

        ll nb=is[a]?0:b*X;
        if (st==-1) st=i;

        if (!is2[a]) st=i;
        nb+=st+1;

        r+=go(a-1,nb);
        if (r>=mod) r-=mod;
    }
    return r;
}



class Mountains{ 
    public: 
        int countPlacements(vector <int> heights, vector <string> vv){ 
            h=heights; 
            n=h.size(); w=vv[0].size();
            REP(i,n) REP(j,w) vis[i][j]=vv[i][j]=='X';

            REP(i,n){
                is[i]=1; is2[i]=1;
                REP(j,w) if (vv[i][j]=='-') is[i]=0; else is2[i]=0;
            }
            REP(i,maxn) dp[i].clear();
            return go(n-1,0);
        } 

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        void test_case_0() { int Arr0[] = {2, 3, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"------",
            "XXXX--",
            "---XXX"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 4; verify_case(0, Arg2, countPlacements(Arg0, Arg1)); }
        void test_case_1() { int Arr0[] = {4, 3, 4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"XXXXX--------",
            "----------XXX",
            "----XXXXXXX--"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 4; verify_case(1, Arg2, countPlacements(Arg0, Arg1)); }
        void test_case_2() { int Arr0[] = {13, 2, 3, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"XXXXXXXXX",
            "-XXX-----",
            "----XXXXX",
            "-----XXX-"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 9; verify_case(2, Arg2, countPlacements(Arg0, Arg1)); }
        void test_case_3() { int Arr0[] = {8, 2, 9, 3, 10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"X------",
            "-------",
            "------X",
            "-------",
            "XXXXXXX"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 98; verify_case(3, Arg2, countPlacements(Arg0, Arg1)); }
        void test_case_4() { int Arr0[] = {20, 20, 20, 20, 20, 20, 45, 50, 49, 50}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"-------------------",
            "-------------------",
            "-------------------",
            "-------------------",
            "-------------------",
            "-------------------",
            "-------------------",
            "------------XXXXXXX",
            "XXXXXXX------------",
            "XXXXXXXXXXXXXXXXXXX"}
        ; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 973726691; verify_case(4, Arg2, countPlacements(Arg0, Arg1)); }

        // END CUT HERE

}; 

// BEGIN CUT HERE 
int main(){
    Mountains ___test;
    ___test.run_test(-1);
} 
// END CUT HERE
