// BEGIN CUT HERE

// END CUT HERE
#line 5 "FoxAverageSequence.cpp"

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

const int maxn=41;
const int mod=1e9+7;

int dp[2][maxn][maxn*maxn][2];
int a[maxn];
int n;

class FoxAverageSequence {
	public:
	int theCount(vector <int> seq) {
        n=seq.size();
        REP(i,n) a[i]=seq[i];
        memset(dp, 0, sizeof(dp));
        int p=0, np=1;
        dp[0][0][0][0]=1;
        REP(i,n){
            memset(dp[np], 0, sizeof(dp[np]));
            REP(j,maxn) REP(k,(i+1)*maxn){
                int va=dp[p][j][k][0], vb=dp[p][j][k][1];
                int bd=i?k/i:40;
                if (va){
                    if (a[i]==-1){
                        REP(u,j){
                            if (u>bd) continue;
                            int &b=dp[np][u][k+u][1];
                            b=(b+va)%mod;
                        }
                        FOR(u,j,maxn){
                            if (u>bd) continue;
                            int &b=dp[np][u][k+u][0];
                            b=(b+va)%mod;
                        }
                    }else if (a[i]<=bd){
                        if (a[i]<j){
                            int &b=dp[np][a[i]][k+a[i]][1];
                            b=(b+va)%mod;
                        }else{
                            int &b=dp[np][a[i]][k+a[i]][0];
                            b=(b+va)%mod;
                        }
                    }
                }if (vb){
                    if (a[i]==-1){
                        FOR(u,j,maxn){
                            if (u>bd) continue;
                            int &b=dp[np][u][k+u][0];
                            b=(b+vb)%mod;
                        }
                    }else if (a[i]<=bd){
                        if (a[i]<j);
                        else{
                            int &b=dp[np][a[i]][k+a[i]][0];
                            b=(b+vb)%mod;
                        }
                    }

                }
            }
            p=np; np^=1;
        }
        int res=0;
        REP(i,maxn) REP(j,maxn*maxn) REP(f,2)res=(res+dp[p][i][j][f])%mod;
        return res;
    }

    // BEGIN CUT HERE
    public:
    void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
    private:
    template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
    void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
    void test_case_0() { int Arr0[] = {3, -1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(0, Arg1, theCount(Arg0)); }
    void test_case_1() { int Arr0[] = {5, 3, -1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(1, Arg1, theCount(Arg0)); }
    void test_case_2() { int Arr0[] = {-1, 0, 40}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(2, Arg1, theCount(Arg0)); }
    void test_case_3() { int Arr0[] = {-1, 40, -1, -1, -1, 10, -1, -1, -1, 21, -1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 579347890; verify_case(3, Arg1, theCount(Arg0)); }
    void test_case_4() { int Arr0[] = {-1, 12, 25, 0, 18, -1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 58; verify_case(4, Arg1, theCount(Arg0)); }

    // END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
    FoxAverageSequence ___test; 
    ___test.run_test(3); 
} 
// END CUT HERE
