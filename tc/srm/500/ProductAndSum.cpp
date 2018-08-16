// BEGIN CUT HERE

// END CUT HERE
#line 5 "ProductAndSum.cpp"

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

const int mod=500500573;

const int maxn=2555;

int faste(int a, int p=mod-2){
    int x=1;
    for (; p; p>>=1, a=1ll*a*a%mod) if (p&1) x=1ll*x*a%mod;
    return x;
}
int fact[maxn], ifact[maxn];
ll px[maxn];


ll go(int a, int b, int c){ return 1ll*b*c%mod*a%mod; }
class ProductAndSum {
	public:
	int getSum(int a, int b, int p5, int p7, int S) {
        ll res=0;
        fact[0]=ifact[0]=1;
        FOR(i, 1, maxn) fact[i]=1ll*i*fact[i-1]%mod, ifact[i]=faste(fact[i]);

        px[0]=1;
        ll pa=1;
        FOR(i, 1, maxn) pa=pa*10%mod, px[i]=(px[i-1]+pa)%mod;


        REP(p6, min(a,b)+1){
            int p2a=a-p6, p3a=b-p6;
            REP(p9, p3a/2+1){
                int p3=p3a-p9*2;
                if (p3*3+p9*9+p6*6>S) continue;
                REP(p8, p2a/3+1){
                    int p2b=p2a-3*p8;
                    if (p3*3+p9*9+p6*6+8*p8>S) continue;
                    REP(p4, p2b/2+1){
                        int p2=p2b-p4*2;
                        int s=2*p2+p4*4+8*p8+3*p3+6*p6+5*p5+7*p7+9*p9;
                        int p1=S-s;
                        if (p1<0) continue;
                        int na=p1+p2+p3+p4+p5+p6+p7+p8+p9;
                        ll tmp=px[na-1];


                        int v=1ll*fact[na-1]
                            *ifact[p1]%mod
                            *ifact[p2]%mod
                            *ifact[p3]%mod
                            *ifact[p4]%mod
                            *ifact[p5]%mod
                            *ifact[p6]%mod
                            *ifact[p7]%mod
                            *ifact[p8]%mod
                            *ifact[p9]%mod;

                        res+=1ll*tmp*go(p1,1,v)%mod;
                        res+=1ll*tmp*go(p2,2,v)%mod;
                        res+=1ll*tmp*go(p3,3,v)%mod;
                        res+=1ll*tmp*go(p4,4,v)%mod;
                        res+=1ll*tmp*go(p5,5,v)%mod;
                        res+=1ll*tmp*go(p6,6,v)%mod;
                        res+=1ll*tmp*go(p7,7,v)%mod;
                        res+=1ll*tmp*go(p8,8,v)%mod;
                        res+=1ll*tmp*go(p9,9,v)%mod;
                        res%=mod;

                    }
                }
            }
        }
        return res%mod;

    }

    // BEGIN CUT HERE
    public:
    void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
    private:
    template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
    void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
    //void test_case_0() { int Arg0 = 2; int Arg1 = 0; int Arg2 = 0; int Arg3 = 0; int Arg4 = 4; int Arg5 = 26; verify_case(0, Arg5, getSum(Arg0, Arg1, Arg2, Arg3, Arg4)); }
    void test_case_0() { int Arg0 = 100; int Arg1 = 100; int Arg2 = 100; int Arg3 = 100; int Arg4 = 2500; int Arg5 = 26; verify_case(0, Arg5, getSum(Arg0, Arg1, Arg2, Arg3, Arg4)); }
    void test_case_1() { int Arg0 = 0; int Arg1 = 0; int Arg2 = 0; int Arg3 = 0; int Arg4 = 10; int Arg5 = 110109965; verify_case(1, Arg5, getSum(Arg0, Arg1, Arg2, Arg3, Arg4)); }
    void test_case_2() { int Arg0 = 2; int Arg1 = 0; int Arg2 = 0; int Arg3 = 0; int Arg4 = 5; int Arg5 = 610; verify_case(2, Arg5, getSum(Arg0, Arg1, Arg2, Arg3, Arg4)); }
    void test_case_3() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 1; int Arg3 = 1; int Arg4 = 10; int Arg5 = 0; verify_case(3, Arg5, getSum(Arg0, Arg1, Arg2, Arg3, Arg4)); }
    void test_case_4() { int Arg0 = 5; int Arg1 = 5; int Arg2 = 5; int Arg3 = 5; int Arg4 = 100; int Arg5 = 61610122; verify_case(4, Arg5, getSum(Arg0, Arg1, Arg2, Arg3, Arg4)); }

    // END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
    ProductAndSum ___test; 
    ___test.run_test(-1); 
} 
// END CUT HERE
