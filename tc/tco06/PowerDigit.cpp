// BEGIN CUT HERE

// END CUT HERE
#line 5 "PowerDigit.cpp"

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


const int maxv=1e5;

class PowerDigit {
	public:
	int digitK(int _x, int y, int k) {
        ll e=1;
        ll x=_x;
        int of=0;
        while(y){
            if (y&1){
                e=e*x;
                if (e>=maxv) of=1;
                e%=maxv;
            }
            
            y>>=1;
            if (y){
                x=x*x;
                if (x>=maxv) of=1;
                x%=maxv;
            }
        }

        if (k==0) return e%10;
        while(k--) e/=10;
        if (!of && e==0) return -1;
        return e%10;

    }

    // BEGIN CUT HERE
    public:
    void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
    private:
    template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
    void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
    //void test_case_0() { int Arg0 = 2; int Arg1 = 10; int Arg2 = 1; int Arg3 = 2; verify_case(0, Arg3, digitK(Arg0, Arg1, Arg2)); }
    void test_case_0() { int Arg0 = 9731; int Arg1 = 1; int Arg2 = 4; int Arg3 = 2; verify_case(0, Arg3, digitK(Arg0, Arg1, Arg2)); }
    void test_case_1() { int Arg0 = 2; int Arg1 = 10; int Arg2 = 4; int Arg3 = -1; verify_case(1, Arg3, digitK(Arg0, Arg1, Arg2)); }
    void test_case_2() { int Arg0 = 2; int Arg1 = 1000; int Arg2 = 0; int Arg3 = 6; verify_case(2, Arg3, digitK(Arg0, Arg1, Arg2)); }
    void test_case_3() { int Arg0 = 9999; int Arg1 = 10000; int Arg2 = 4; int Arg3 = 0; verify_case(3, Arg3, digitK(Arg0, Arg1, Arg2)); }

    // END CUT HERE

};

// BEGIN CUT HERE
int main(){
    PowerDigit ___test; 
    ___test.run_test(-1); 
} 
// END CUT HERE
