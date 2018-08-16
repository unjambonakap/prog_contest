// BEGIN CUT HERE

// END CUT HERE
#line 5 "BishopOnTheBoard.cpp"

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


pii lt, rt, lb, rb;
const int maxn=50007;

void proc_uv(int &u, int &v, int xa, int ya, int xb, int yb){
    //xa+u-v=xb
    //ya+u+v=yb
    u=(xb+yb-xa-ya)/2;
    v=yb-u-ya;
}

class BishopOnTheBoard {
	public:
	int countReachableCells(int xs, int ys, int x, int y, int k) {
        if (xs<ys) swap(xs, ys), swap(x, y);
        if (!k) return 0;
        --xs; --ys;


        int d;
        d=min(x, y); lb=MP(x-d, y-d);
        d=min(x, ys-y); lt=MP(x-d, y+d);
        d=min(xs-x, y); rb=MP(x+d, y-d);
        d=min(xs-x, ys-y); rt=MP(x+d, y+d);
        if (k==1) return rt.ST-lb.ST+1+rb.ST-lt.ST;
        
        int lcnt=0, rcnt=0;
        int bit=(x+y)&1;


        if (lb.ST==0) ++lcnt;
        if (lt.ST==0) ++lcnt;
        if (rb.ST==xs) ++rcnt;
        if (rt.ST==xs) ++rcnt;

        REP(i, k-1){
            pii nlt, nrt, nlb, nrb;
            d=min(lt.ST, lt.ND); nlb=MP(lt.ST-d, lt.ND-d);
            d=min(lb.ST, ys-lb.ND); nlt=MP(lb.ST-d, lb.ND+d);
            d=min(xs-rt.ST, rt.ND); nrb=MP(rt.ST+d, rt.ND-d);
            d=min(xs-rb.ST, ys-rb.ND); nrt=MP(rb.ST+d, rb.ND+d);
            if (nlb.ST<lb.ST) lb=nlb;
            if (nlt.ST<lt.ST) lt=nlt;
            if (nrb.ST>rb.ST) rb=nrb;
            if (nrt.ST>rt.ST) rt=nrt;
            if (lb.ST==0) ++lcnt;
            if (lt.ST==0) ++lcnt;
            if (rb.ST==xs) ++rcnt;
            if (rt.ST==xs) ++rcnt;
        }


        checkmin(lcnt, 2); checkmin(rcnt, 2);

        int lc[maxn], rc[maxn];

        memset(rc, -1, sizeof(rc));
        memset(lc, -1, sizeof(lc));

        ++xs; ++ys;
        int u, v;
        if (lcnt==2) REP(i, ys) lc[i]=0+(i%2==bit?0:1);
        else if (lcnt==1){
            if (lt.ST==0){
                FOR(i, lt.ND, ys-1) lc[i]=0+(i%2==bit?0:1);
                proc_uv(u, v, lb.ST, lb.ND, 0, lt.ND);
                REP(i, v) lc[lt.ND-i-1]=lc[lt.ND-i]+1;
                REP(i, u) lc[lt.ND-v-i-1]=lc[lt.ND-v-i]-1;
            }else{
                REP(i, lb.ND+1)  lc[i]=0+(i%2==bit?0:1);
                proc_uv(u, v, 0, lb.ND, lt.ST, lt.ND);
                REP(i, u) lc[lb.ND+i+1]=lc[lb.ND+i]+1;
                REP(i, v) lc[lb.ND+u+i+1]=lc[lb.ND+u+i]-1;
            }
        }else{
            int u, v;
            proc_uv(u, v, lb.ST, lb.ND, lt.ST, lt.ND);
            REP(i, u+1) lc[i]=lb.ST+i;
            REP(i, v) lc[u+i+1]=lc[u]-i-1;
        }
        if (rcnt==2) REP(i, ys) rc[i]=xs-1-((i+xs-1)%2==bit?0:1);
        else if (rcnt==1){
            if (rt.ST==xs-1){
                FOR(i, rt.ND, ys-1) rc[i]=xs-1-((i+xs-1)%2==bit?0:1);
                proc_uv(u, v, lb.ST, lb.ND, xs-1, lt.ND);
                REP(i, u) rc[rt.ND-i-1]=rc[rt.ND-i]-1;
                REP(i, v) rc[rt.ND-u-i-1]=rc[rt.ND-u-i]+1;
            }else{
                REP(i, rb.ND+1)  rc[i]=xs-1-((i+xs-1)%2==bit?0:1);
                proc_uv(u, v, xs-1, lb.ND, lt.ST, lt.ND);
                REP(i, v) rc[rb.ND+i+1]=rc[rb.ND+i]-1;
                REP(i, u) rc[rb.ND+v+i+1]=rc[rb.ND+v+i]+1;
            }
        }else{
            int u, v;
            proc_uv(u, v, rb.ST, rb.ND, rt.ST, rt.ND);
            REP(i, v+1) rc[i]=rb.ST-i;
            REP(i, u) rc[v+i+1]=rc[v]+i+1;
        }

        ll res=0;
        REP(i, ys){
            assert((rc[i]-lc[i])%2==0);
            res+=(rc[i]-lc[i])/2+1;
        }



        return res;




    }

    // BEGIN CUT HERE
    public:
    void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
    private:
    template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
    void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
    //void test_case_0() { int Arg0 = 8; int Arg1 = 8; int Arg2 = 0; int Arg3 = 0; int Arg4 = 2; int Arg5 = 32; verify_case(0, Arg5, countReachableCells(Arg0, Arg1, Arg2, Arg3, Arg4)); }
    void test_case_0() { int Arg0 = 4318; int Arg1 = 9643; int Arg2 = 361; int Arg3 = 5347; int Arg4 = 2; int Arg5 = 32; verify_case(0, Arg5, countReachableCells(Arg0, Arg1, Arg2, Arg3, Arg4)); }
    void test_case_1() { int Arg0 = 8; int Arg1 = 4; int Arg2 = 0; int Arg3 = 0; int Arg4 = 2; int Arg5 = 12; verify_case(1, Arg5, countReachableCells(Arg0, Arg1, Arg2, Arg3, Arg4)); }
    void test_case_2() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 0; int Arg3 = 0; int Arg4 = 1; int Arg5 = 2; verify_case(2, Arg5, countReachableCells(Arg0, Arg1, Arg2, Arg3, Arg4)); }
    void test_case_3() { int Arg0 = 11; int Arg1 = 5; int Arg2 = 0; int Arg3 = 1; int Arg4 = 2; int Arg5 = 17; verify_case(3, Arg5, countReachableCells(Arg0, Arg1, Arg2, Arg3, Arg4)); }
    void test_case_4() { int Arg0 = 278; int Arg1 = 17; int Arg2 = 37; int Arg3 = 11; int Arg4 = 5; int Arg5 = 912; verify_case(4, Arg5, countReachableCells(Arg0, Arg1, Arg2, Arg3, Arg4)); }

    // END CUT HERE

};

// BEGIN CUT HERE
int main(){
    BishopOnTheBoard ___test; 
    ___test.run_test(-1); 
} 
// END CUT HERE
