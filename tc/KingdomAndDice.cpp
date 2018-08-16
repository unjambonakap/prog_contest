// BEGIN CUT HERE

// END CUT HERE
#line 5 "KingdomAndDice.cpp"

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

const int maxn=53;
int dp[2][maxn*maxn][maxn*maxn];//pos,nwin
int n;
int tb[maxn*maxn];
int val[maxn*maxn];
int m;
set<int> have;

class KingdomAndDice {
	public:
	double newFairness(vector <int> a, vector <int> b, int X) {
        have.clear();
        REP(i,a.size()) have.insert(a[i]);
        REP(i,b.size()) have.insert(b[i]);

        n=b.size();
        sort(ALL(b));
        int rem=0;
        int st=0;
        REP(i,a.size()){
            if (!a[i]) ++rem; 
            else REP(j,n) if (a[i]>b[j]) ++st;
        }

        m=0;
        tb[m]=0, val[m]=0, ++m;
        b.pb(X+1);
        if (rem){
            REP(i,rem) tb[m]=0, val[m]=0, ++m;
            FOR(i,1,b.size()){
                int diff=b[i]-b[i-1]-1;
                int lvl=val[m-1]+1;
                if (diff>200) REP(j,rem) tb[m]=b[i]-1, val[m]=i, ++m;
                else{
                    int cnt=rem;
                    FOR(j,b[i-1]+1,b[i]) if (!have.count(j) && cnt) tb[m]=j, val[m]=i, ++m, --cnt;
                }

            }
        }

        int p=0, np=1;
        memset(dp[p],0,sizeof(dp[p]));
        dp[p][0][st]=1;
        REP(i,rem){
            memset(dp[np],0,sizeof(dp[np]));
            REP(j,m) REP(k,n*n) if (dp[p][j][k]) dp[p][j+1][k]=1, dp[np][j+1][k+val[j]]=1;
            p=np; np^=1;
        }

        double best;
        double bestv=1e9;
        REP(k,n*n+1) REP(i,m+1) if (dp[p][i][k]){
            double p=1.*k/n/n;
            if (fabs(p-0.5)+1e-9<bestv) best=p, bestv=fabs(p-0.5);
        }



        return best;
    }

    // BEGIN CUT HERE
    public:
    void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
    private:
    template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
    void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
    void test_case_0() { int Arr0[] = {36171694, 1158, 999803038, 999802999, 988671211, 1037946, 0, 951709561, 142585856, 695964, 674, 57, 999803053, 1, 0, 999318574, 376859, 0, 1164, 991427936, 999802816, 27763, 999803055, 3279343, 999799870, 999801567, 972921101, 0, 0, 56, 36255018, 999695474, 0, 31, 158094, 999802733, 22657616, 22081511, 920220257}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {25, 4, 3206507, 3132331, 11, 6, 1151, 29872584, 12, 998894418, 59, 365, 999802930, 1531520, 1882783, 16591095, 999803060, 747515203, 50, 947532182, 7, 3, 999803048, 16157, 999803061, 12539481, 998875380, 999803006, 876391765, 745537229, 472708, 999802825, 999757173, 999621256, 35, 8179, 997870511, 919095840, 7114}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 999803062; double Arg3 = 0.4375; verify_case(0, Arg3, newFairness(Arg0, Arg1, Arg2)); }
    //void test_case_0() { int Arr0[] = {0, 2, 7, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {6, 3, 8, 10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 12; double Arg3 = 0.4375; verify_case(0, Arg3, newFairness(Arg0, Arg1, Arg2)); }
    void test_case_1() { int Arr0[] = {0, 2, 7, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {6, 3, 8, 10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 10; double Arg3 = 0.375; verify_case(1, Arg3, newFairness(Arg0, Arg1, Arg2)); }
    void test_case_2() { int Arr0[] = {0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {5, 8}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 47; double Arg3 = 0.5; verify_case(2, Arg3, newFairness(Arg0, Arg1, Arg2)); }
    void test_case_3() { int Arr0[] = {19, 50, 4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {26, 100, 37}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1000; double Arg3 = 0.2222222222222222; verify_case(3, Arg3, newFairness(Arg0, Arg1, Arg2)); }
    void test_case_4() { int Arr0[] = {6371, 0, 6256, 1852, 0, 0, 6317, 3004, 5218, 9012}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1557, 6318, 1560, 4519, 2012, 6316, 6315, 1559, 8215, 1561}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 10000; double Arg3 = 0.49; verify_case(4, Arg3, newFairness(Arg0, Arg1, Arg2)); }

    // END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
    KingdomAndDice ___test; 
    ___test.run_test(0); 
} 
// END CUT HERE
