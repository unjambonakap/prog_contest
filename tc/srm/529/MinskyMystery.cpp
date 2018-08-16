// BEGIN CUT HERE

// END CUT HERE
#line 5 "MinskyMystery.cpp"

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

const int mod=1e9+9;


int checkit(ll N){
    ll res=1;
    FOR(i, 2, N+1){
        ++res;
        res+=3*N+(N+i-1)/i;
        res%=mod;
        if (N%i==0) return res;
        res+=N;
    }
    assert(0);

}


int proc(ll N){
    if (N<2) return -1;

    ll res=1;
    ll ub=(int)sqrt(N)+1;
    FOR(i, 2, ub){
        ++res;
        res+=3*N+(N+i-1)/i;
        res%=mod;
        if (N%i==0) return res;
        res+=N;
    }
    res+=(N-ub)%mod*4%mod*(N%mod)%mod;
    res+=N-ub+1;//add bag 1
    res+=3*N;
    ++res;
    ll prev=N;
    FOR(i, 2, ub+1){
        --prev;
        assert((N+prev-1)/prev==i);
        ll T=ub, H=prev;
        while(T<H){
            ll M=(T+H)/2;
            if ((N+M-1)/M>i) T=M+1;
            else H=M;
        }
        res+=(prev-T+1)%mod*i%mod;
        res%=mod;
        prev=T;
    }
    return res%mod;

}

class MinskyMystery {
    public:
        int computeAnswer(long long N) {
            return proc(N);
        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        //oid test_case_0() { long long Arg0 = 2LL; int Arg1 = 9; verify_case(0, Arg1, computeAnswer(Arg0)); }
        void test_case_0() { long long Arg0 = 999663912463LL; int Arg1 = 9; verify_case(0, Arg1, computeAnswer(Arg0)); }
        void test_case_1() { long long Arg0 = 3LL; int Arg1 = 27; verify_case(1, Arg1, computeAnswer(Arg0)); }
        void test_case_2() { long long Arg0 = 4LL; int Arg1 = 16; verify_case(2, Arg1, computeAnswer(Arg0)); }
        void test_case_3() { long long Arg0 = 2401LL; int Arg1 = 59058; verify_case(3, Arg1, computeAnswer(Arg0)); }
        void test_case_4() { long long Arg0 = 24LL; int Arg1 = 86; verify_case(4, Arg1, computeAnswer(Arg0)); }

        // END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
    MinskyMystery ___test; 
    ___test.run_test(-1); 
} 
// END CUT HERE
