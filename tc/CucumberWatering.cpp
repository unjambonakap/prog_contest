// BEGIN CUT HERE

// END CUT HERE
#line 5 "CucumberWatering.cpp"

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

const int maxn=55;
int n;


ll dpa[maxn][maxn], dpb[maxn][maxn];
vi dest[maxn];
int rmp[maxn];
vi x;
ll dist(int a, int b){return abs(x[a]-x[b]);}

ll min(ll a, ll b){return a>b?b:a;}

ll go1(int nk, int a){
    if (!a) return 0;
    ll &r=dpa[nk][a];
    if (r!=-1) return r;
    r=1e18;
    if (!nk){
        ll val=0;
        REP(j,a){
            REP(k,dest[j].size()){
                int b=dest[j][k];
                if (b>=a) val+=dist(a,j);
                else if (b<j) val+=dist(b,j);
            }
        }
        r=min(r,val);
        return r;
    }

    REP(i,a){
        ll nr=go1(nk-1,i);
        FOR(j,i+1,a){
            REP(k,dest[j].size()){
                int b=dest[j][k];
                if (b<=i || b>=a) nr+=min(dist(i,j),dist(a,j));
                else if (b<j){
                    ll d=dist(b,j);
                    d=min(d,dist(j,i)+dist(a,b));
                    d=min(d,dist(j,a)+dist(i,b));
                    nr+=d;
                }
            }
        }
        checkmin(r,nr);
    }
    return r;
}

ll go2(int nk, int a){
    if (a==n-1) return 0;
    ll &r=dpb[nk][a];
    if (r!=-1) return r;
    r=1e18;
    if (!nk){
        ll val=0;
        FOR(j,a+1,n){
            REP(k,dest[j].size()){
                int b=dest[j][k];
                if (b<=a) val+=dist(a,j);
                else if (b<j) val+=dist(b,j);
            }
        }
        r=min(r,val);
        return r;
    }

    FOR(i,a+1,n){
        ll nr=go2(nk-1,i);
        FOR(j,a+1,i){
            REP(k,dest[j].size()){
                int b=dest[j][k];
                if (b<=a || b>=i) nr+=min(dist(i,j),dist(a,j));
                else if (b<j){
                    ll d=dist(b,j);
                    d=min(d,dist(j,i)+dist(a,b));
                    d=min(d,dist(j,a)+dist(i,b));
                    nr+=d;
                }
            }
        }
        checkmin(r,nr);
    }
    return r;
}


class CucumberWatering {
    public:
        long long theMin(vector <int> _x, int K) {
            x=_x;
            n=x.size();
            vi xl;
            REP(i,n) xl.pb(x[i]);
            sort(ALL(xl));
            REP(i,n) rmp[i]=lower_bound(ALL(xl),x[i])-xl.begin();
            REP(i,n) dest[i].clear();
            REP(i,n-1) dest[rmp[i]].pb(rmp[i+1]), dest[rmp[i+1]].pb(rmp[i]);

            sort(ALL(x));
            memset(dpa,-1,sizeof(dpa));
            memset(dpb,-1,sizeof(dpb));

            ll res=1e18;
            REP(i,K) REP(j,n){
                checkmin(res,go1(i,j)+go2(K-1-i,j));
            }
            return res;
        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
//        void test_case_0() { int Arr0[] = {0, 6, 8, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; long long Arg2 = 6LL; verify_case(0, Arg2, theMin(Arg0, Arg1)); }
        void test_case_0() { int Arr0[] = {-485419501, 869992369, -237766831, -536692389, 587917460, -724559331, 165037606, -237315266, 379784329, -762332332, 36584326, -348342877, -324203280, 121982811, 745436682, -408401971, -770873170, -623866964, -743993184, 447999658, 655140981, 832021770, -899092739, 940920896, 519872561, -235259365, 987281, -576059810, -912995787, 684161129, 357569150, -212923458, 340007420, -392843948, -333464533, -185197708, -438253069, -512405373, 474896293, -114986051, 207049741, 781811135, -528800398, 883537430, 459635399, -836994604, 963298347, -113930922, -153493438, -484278794}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; long long Arg2 = 6LL; verify_case(0, Arg2, theMin(Arg0, Arg1)); }
        void test_case_1() { int Arr0[] = {-1000000000, 1000000000, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; long long Arg2 = 3000000000LL; verify_case(1, Arg2, theMin(Arg0, Arg1)); }
        void test_case_2() { int Arr0[] = {58, 2012}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 50; long long Arg2 = 0LL; verify_case(2, Arg2, theMin(Arg0, Arg1)); }
        void test_case_3() { int Arr0[] = {9, -3, 14, 6, 5, -9, 32, 7, -5, 26, 2, 11}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; long long Arg2 = 58LL; verify_case(3, Arg2, theMin(Arg0, Arg1)); }

        // END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
    CucumberWatering ___test; 
    ___test.run_test(0); 
} 
// END CUT HERE
