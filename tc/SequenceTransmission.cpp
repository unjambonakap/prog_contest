// BEGIN CUT HERE

// END CUT HERE
#line 5 "SequenceTransmission.cpp"

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


const int maxs=1<<16;
const int maxb=40;
const int MASK=maxs-1;

int next[maxs], of[maxs];
int cntx[maxs];
ll dp[maxb][maxs];
ll a, b;

int q(int a){
    int f=a&1;
    int res=0;
    while(a){
        int nf=a&1;
        if (f==nf) continue;
        else ++res, f=nf;
    }
    return res;
}


class SequenceTransmission {
	public:
	long long signalChanges(long long _a, long long _b, long long n) {
        a=_a; b=_b;
        ll res=0;
        if (a&1) res+=b&1?n/2:(n-1)/2;
        else res+=b&1?n-1:0;
        int u=b+a&MASK;
        memset(next,-1,sizeof(next));
        int uo=u;
        while(next[u]==-1){
            next[u]=u+a&MASK;
            cntx[u]=q(u);
            if (u+a>MASK) of[u]=1;
            u=next[u];
        }
        u=uo;
        memset(dp,-1,sizeof(dp));

        ll st=a+b;
        st-=(a+b)&MASK;
        vi tb;
        int F;
        st>>=16;
        if (!st){
            F=0;
            tb.pb(maxb-1);
        }else{
            F=st&1;
            int prev=F;
            int cnt=0;
            while(st){
                int fu=st&1;
                if (fu==prev) ++cnt;
                else tb.pb(cnt), cnt=1, prev=fu;
                st>>=1;
            }
            tb.pb(cnt);
        }
        int NB=0;
        reverse(ALL(tb));
        while(n){
            if (!F){
                NB+=tb.back(), tb.pop_back(), F=1;
            }else{
                while(n){
                    --n;
                    if ((u>>maxs-1)!=F) ++res;
                    res+=cntx[u]+tb.size();
                    if (of[u]){
                        NB+=tb.back();
                        tb.pop_back();
                        u=next[u];
                        break;
                    }
                    u=next[u];
                }
            }
        }
        return res;
    }

    // BEGIN CUT HERE
    public:
    void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
    private:
    template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
    void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
    void test_case_0() { long long Arg0 = 3LL; long long Arg1 = 5LL; long long Arg2 = 4LL; long long Arg3 = 8LL; verify_case(0, Arg3, signalChanges(Arg0, Arg1, Arg2)); }
    void test_case_1() { long long Arg0 = 1LL; long long Arg1 = 576460752303423487LL; long long Arg2 = 1LL; long long Arg3 = 1LL; verify_case(1, Arg3, signalChanges(Arg0, Arg1, Arg2)); }
    void test_case_2() { long long Arg0 = 1LL; long long Arg1 = 1LL; long long Arg2 = 10LL; long long Arg3 = 18LL; verify_case(2, Arg3, signalChanges(Arg0, Arg1, Arg2)); }
    void test_case_3() { long long Arg0 = 40000LL; long long Arg1 = 1000000000000000000LL; long long Arg2 = 1000000000000LL; long long Arg3 = 27066924353831LL; verify_case(3, Arg3, signalChanges(Arg0, Arg1, Arg2)); }

    // END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
    SequenceTransmission ___test; 
    ___test.run_test(-1); 
} 
// END CUT HERE
