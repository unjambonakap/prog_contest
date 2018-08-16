// BEGIN CUT HERE

// END CUT HERE
#line 5 "FavouriteDigits.cpp"

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

const int maxn=22;
int digit[maxn];
int ha[maxn], hb[maxn];
ll val[maxn];
int da, db;
int x;

ll build(int n, int a, int b, ll v=0){
    if (!n){
        assert(!a && !b);
        return v;
    }
    REP(i,10) if (i || v){
        int na=max(0,a-(i==da));
        int nb=max(0,b-(i==db));
        if (n-1>=na+nb) return build(n-1,na,nb,10*v+i);
    }
    return build(n+1,a,b,v);
    assert(0);
}

ll go(int p){
    if (p==x) return build(x,max(0,ha[x]-(da==1)),max(0,hb[x]-(db==1)),1);
    int a=ha[p+1], b=hb[p+1];
    FOR(i,digit[p]+1,10){
        int na=max(0,a-(i==da));
        int nb=max(0,b-(i==db));
        if (p>=na+nb) return build(p,na,nb,10*val[p]+i);

    }
    return go(p+1);
}

class FavouriteDigits {
    public:
        long long findNext(long long N, int _da, int ca, int _db, int cb) {
            da=_da; db=_db;
            if (!ca && !cb) return N;
            if (da>db) swap(da,db), swap(ca,cb);

            ll tmp=N;
            x=0;

            while(tmp) digit[x]=tmp%10, tmp/=10, val[x]=tmp, ++x;
            if (x<ca+cb) return build(ca+cb,ca,cb);
            

            ha[x]=ca; hb[x]=cb;
            for (int i=x-1; i>=0; --i){
                ha[i]=ha[i+1];
                hb[i]=hb[i+1];
                if (digit[i]==da) ha[i]=max(0,ha[i]-1);
                else if (digit[i]==db) hb[i]=max(0,hb[i]-1);
            }

            if (!ha[0] && !hb[0]) return N;
            return go(0);
        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        void test_case_0() { long long Arg0 = 434744725433512LL; int Arg1 = 4; int Arg2 = 8; int Arg3 = 7; int Arg4 = 5; long long Arg5 = 47LL; verify_case(0, Arg5, findNext(Arg0, Arg1, Arg2, Arg3, Arg4)); }
        //void test_case_0() { long long Arg0 = 47LL; int Arg1 = 1; int Arg2 = 0; int Arg3 = 2; int Arg4 = 0; long long Arg5 = 47LL; verify_case(0, Arg5, findNext(Arg0, Arg1, Arg2, Arg3, Arg4)); }
        void test_case_1() { long long Arg0 = 47LL; int Arg1 = 5; int Arg2 = 0; int Arg3 = 9; int Arg4 = 1; long long Arg5 = 49LL; verify_case(1, Arg5, findNext(Arg0, Arg1, Arg2, Arg3, Arg4)); }
        void test_case_2() { long long Arg0 = 47LL; int Arg1 = 5; int Arg2 = 0; int Arg3 = 3; int Arg4 = 1; long long Arg5 = 53LL; verify_case(2, Arg5, findNext(Arg0, Arg1, Arg2, Arg3, Arg4)); }
        void test_case_3() { long long Arg0 = 47LL; int Arg1 = 2; int Arg2 = 1; int Arg3 = 0; int Arg4 = 2; long long Arg5 = 200LL; verify_case(3, Arg5, findNext(Arg0, Arg1, Arg2, Arg3, Arg4)); }
        void test_case_4() { long long Arg0 = 123456789012345LL; int Arg1 = 1; int Arg2 = 2; int Arg3 = 2; int Arg4 = 4; long long Arg5 = 123456789012422LL; verify_case(4, Arg5, findNext(Arg0, Arg1, Arg2, Arg3, Arg4)); }
        void test_case_5() { long long Arg0 = 92LL; int Arg1 = 1; int Arg2 = 1; int Arg3 = 0; int Arg4 = 0; long long Arg5 = 100LL; verify_case(5, Arg5, findNext(Arg0, Arg1, Arg2, Arg3, Arg4)); }

        // END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
    FavouriteDigits ___test; 
    ___test.run_test(-1); 
} 
// END CUT HERE
