// BEGIN CUT HERE

// END CUT HERE
#line 5 "EllysNumbers.cpp"

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

ll gcd(ll a, ll b){return b?gcd(b,a%b):a;}

const int maxv=1e5;
const int maxn=555;
int isp[maxv];
int pl[maxv];
int np;
int m;

ll dp[two(20)];



class EllysNumbers {
	public:
	long long getSubsets(long long n, vector <string> special) {
        vi lst;
        string s;
        FE(it,special) s+=*it;
        istringstream ss(s);
        int a;
        int mul=1;
        while(ss>>a) if (gcd(n,a)==a){
            if (a==1) mul=2;
            else lst.pb(a);
        }

        np=0;
        memset(isp,1,sizeof(isp));
        FOR(i,2,maxv) if (isp[i]){
            for (ll j=1ll*i*i; j<maxv; j+=i) isp[j]=0;
            pl[np++]=i;
        }


        vector<vector<pii> > decomp;
        REP(i,lst.size()){
            int val=lst[i];
            vector<pii> tb;
            REP(j,np){
                int cnt=0;
                while(val%pl[j]==0) ++cnt, val/=pl[j];
                if (cnt) tb.pb(MP(j,cnt));
            }
            if (val!=1){
                pl[np++]=val;
                tb.pb(MP(np-1,1));
            }
            decomp.pb(tb);
        }
        ll val=n;
        vector<pii> tb;
        REP(j,np){
            int cnt=0;
            while(val%pl[j]==0) ++cnt, val/=pl[j];
            if (cnt) tb.pb(MP(j,cnt));
        }
        if (val!=1) return 0;
        map<int,int> rmp;
        REP(i,tb.size()) rmp[tb[i].ST]=i;
        vi x;
        REP(i,decomp.size()){
            int ok=1;
            int mask=0;
            FE(it,decomp[i]) if (it->ND!=tb[rmp[it->ST]].ND){ok=0; break;} else mask|=two(rmp[it->ST]);
            if (ok) x.pb(mask);
        }
        memset(dp,0,sizeof(dp));
        int M=two(tb.size())-1;
        dp[0]=1;
        REP(i,x.size()){
            int j=M^x[i];
            ++dp[x[i]];
            for (int k=j; k; k=j&(k-1)){
                dp[k|x[i]]+=dp[k];
            }
        }


        return dp[M]*mul;
    }

    // BEGIN CUT HERE
    public:
    void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
    private:
    template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
    void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
    void test_case_0() { long long Arg0 = 12LL; string Arr1[] = {"4 2 5 6 3"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 1LL; verify_case(0, Arg2, getSubsets(Arg0, Arg1)); }
    void test_case_1() { long long Arg0 = 42LL; string Arr1[] = {"1 2 3 4 5 6 7 13 14 21 42"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 10LL; verify_case(1, Arg2, getSubsets(Arg0, Arg1)); }
    void test_case_2() { long long Arg0 = 1337LL; string Arr1[] = {"1 13 42 666 2674"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 0LL; verify_case(2, Arg2, getSubsets(Arg0, Arg1)); }
    void test_case_3() { long long Arg0 = 1073741824LL; string Arr1[] = {"1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192 1",
        "6384 32768 65536 131072 262144 524288 1048576 2097",
        "152 4194304 8388608 16777216 33554432 67108864 134",
        "217728 268435456 536870912"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 0LL; verify_case(3, Arg2, getSubsets(Arg0, Arg1)); }
    void test_case_4() { long long Arg0 = 7420738134810LL; string Arr1[] = {"435 625199055 4199 33263 17 222870 284870433 72093",
        "2379 7 11 31 247110827 23 1771 81809 851968487 13 ", 
        "476379795 1001 5 435274114 38264554 7429 239906525",
        " 3 227183706 887045414 606786670 3795 797605175 29",
        " 30 747186719 19 2 562347843 74 2294 588002688 743",
        "6429 703 591740547 36657492 37 444178205 1002001 2",
        "17626404"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 110LL; verify_case(4, Arg2, getSubsets(Arg0, Arg1)); }

    // END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
    EllysNumbers ___test; 
    ___test.run_test(-1); 
} 
// END CUT HERE
