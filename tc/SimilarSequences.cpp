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
#define FOR(i, a, b) for(int i = (int)(a); i < (int)(b); ++i)

#define FE(i,t) for (__typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (__typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

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
typedef vector<string> vs;

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n==0)?0:1+count_bit(n&(n-1));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int mod=1e9+9;
const int maxn=44;
int H=53;
int n;
int tb[maxn];
int aa[maxn];

class SimilarSequences{ 
    public: 
        int count(vector <int> seq, int bound){ 
            n=seq.size();
            vi lst;
            REP(i,n) lst.pb(seq[i]);

            sort(ALL(lst));
            lst.resize(unique(ALL(lst))-lst.begin());
            int m=lst.size();
            REP(i,n) tb[i]=lower_bound(ALL(lst),seq[i])-lst.begin();

            int res=0;
            REP(i,n) if (!i || tb[i]!=tb[i-1]) res=(res+1ll*n*(bound-m))%mod;

            vector<ll> hl;
            REP(i,n) REP(j,n) REP(v,m){
                int p=0;
                REP(l,n) if (l!=i) aa[p++]=tb[l];
                for (int l=n-1; l>j; --l) aa[l]=aa[l-1];
                aa[j]=v;
                ll h=0;
                REP(l,n) h=H*h+aa[l];
                hl.pb(h);
            }
            sort(ALL(hl));
            res+=unique(ALL(hl))-hl.begin();
            res%=mod;
            return res;
        } 

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        void test_case_0() { int Arr0[] = {1, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 5; verify_case(0, Arg2, count(Arg0, Arg1)); }
        void test_case_1() { int Arr0[] = {1, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 4; verify_case(1, Arg2, count(Arg0, Arg1)); }
        void test_case_2() { int Arr0[] = {999999999}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1000000000; int Arg2 = 1000000000; verify_case(2, Arg2, count(Arg0, Arg1)); }
        void test_case_3() { int Arr0[] = {1, 2, 3, 4, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; int Arg2 = 97; verify_case(3, Arg2, count(Arg0, Arg1)); }
        void test_case_4() { int Arr0[] = {5, 8, 11, 12, 4, 1, 7, 9}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1000000000; int Arg2 = 999999363; verify_case(4, Arg2, count(Arg0, Arg1)); }

        // END CUT HERE

}; 

// BEGIN CUT HERE 
int main(){
    SimilarSequences ___test;
    ___test.run_test(-1);
} 
// END CUT HERE
