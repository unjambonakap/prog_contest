// BEGIN CUT HERE

// END CUT HERE
#line 5 "Regulars.cpp"

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
#define two(x) (1LL << (x))
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


const int maxn=64;
int mp[maxn], op[maxn];
int n;
map<ll, ll> mem;

ll proc(ll px){

    if (mem.count(px)) return mem[px];
    ll &r=mem[px];
    ll p=px/maxn; int a=px&maxn-1;
    r=p&two(n)?1:0;
    if (a==0) return r;

    ll x, y; x=y=0;
    int can=0;
    REP(i, n){
        if (can) x|=two(i);
        if (!op[i]){
            if (!mp[i] && (p&two(i))) can=1;
            else can=0;
        }else if (!mp[i] && (p&two(i))) can=1, x|=two(i);
    }
    if (can) x|=two(n);

    can=0;
    REP(i, n){
        if (can) y|=two(i);
        if (!op[i]){
            if (mp[i] && (p&two(i))) can=1;
            else can=0;
        }else if (mp[i] && (p&two(i))) can=1, y|=two(i);
    }
    if (can) y|=two(n);
    r+=proc(x*maxn+a-1)+proc(y*maxn+a-1);
    //printf("on %Ld %d => %Ld (%Ld %Ld => %Ld %Ld %d\n", p, a, r, x, proc(x*maxn+a-1), y, proc(y*maxn+a-1), x!=p);
    return r;
}

class Regulars {
    public:
        long long stringCt(string regex, int ml) {
            n=0;
            mem.clear();
            memset(op, 0, sizeof(op));
            FE(it, regex) if (*it=='*') op[n-1]=1; else mp[n++]=*it=='1';
            ll p=0;
            REP(i, n){
                p|=two(i);
                if (!op[i]) break;
            }
            if (p==two(n)-1) p|=two(n);

            return proc(p*maxn+ml);
        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        //void test_case_0() { string Arg0 = "0*"; int Arg1 = 5; long long Arg2 = 6LL; verify_case(0, Arg2, stringCt(Arg0, Arg1)); }
        void test_case_0() { string Arg0 = "0*0*011*0*0"; int Arg1 = 3; long long Arg2 = 6LL; verify_case(0, Arg2, stringCt(Arg0, Arg1)); }
        void test_case_1() { string Arg0 = "01*1*1*"; int Arg1 = 3; long long Arg2 = 3LL; verify_case(1, Arg2, stringCt(Arg0, Arg1)); }
        void test_case_2() { string Arg0 = "0*1*0*1*0*1*0*1*0*1*0*1*0*1*0*1*0*1*0*1*0*1*0*1*0*"; int Arg1 = 50; long long Arg2 = 1125899906842623LL; verify_case(2, Arg2, stringCt(Arg0, Arg1)); }

        // END CUT HERE

};

// BEGIN CUT HERE
int main(){
    Regulars ___test; 
    ___test.run_test(-1);
} 
// END CUT HERE
