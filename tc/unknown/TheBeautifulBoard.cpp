// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheBeautifulBoard.cpp"

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

const int mod=1234567891;

const int maxm=5000001;
int fact[maxm];
int faste(ll a, int p){
    ll x=1;
    for (; p; p>>=1, a=a*a%mod) if (p&1) x=x*a%mod;
    return x;
}

int inv(int a){return faste(a, mod-2);}

int cnk(ll n, ll k){
    ll b=1;
    FOR(i, 1, k+1) b=(n-i+1)%mod*b%mod;
    return b*inv(fact[k])%mod;
}

int _cnk(int n, int k){return 1LL*fact[n]*inv(fact[k])%mod*inv(fact[n-k])%mod;}

class TheBeautifulBoard {
	public:
	int count(int _m, vector <int> a) {
        fact[0]=1;
        FOR(i, 1, maxm) fact[i]=1LL*i*fact[i-1]%mod;

        ll m=_m;
        int n=a.size();
        int s=0;
        REP(i, n) s+=a[i];
        if (s>m*m) return 0;

        ll ans=0;
        ll x=1;
        REP(i, n) x=x*fact[a[i]]%mod;
        ans+=1LL*cnk(m*m, s)*fact[s]%mod*inv(x)%mod;

        ll tmp=1;

        if (m&1){
            int cnt=0;
            REP(i, n){
                if (a[i]%4==1){ if (++cnt>1){tmp=0; break;}}
                else if (a[i]%4){tmp=0; break;}
                tmp=tmp*fact[a[i]/4]%mod;
            }
            if (tmp) tmp=1LL*fact[s/4]*cnk(m*m/4, s/4)%mod*inv(tmp)%mod;

        }else{
            REP(i, n){
                if (a[i]%4){tmp=0; break;}
                tmp=tmp*fact[a[i]/4]%mod;
            }
            if (tmp) tmp=1LL*fact[s/4]*cnk(m*m/4, s/4)%mod*inv(tmp)%mod;
        }
        ans=(ans+tmp*2)%mod;


        tmp=1;
        if (m&1){
            int cnt=0;
            REP(i, n){
                if (a[i]%2==1){ if (++cnt>1){tmp=0; break;}}
                tmp=tmp*fact[a[i]/2]%mod;
            }
            if (tmp) tmp=1LL*fact[s/2]*cnk(m*m/2, s/2)%mod*inv(tmp)%mod;

        }else{
            REP(i, n){
                if (a[i]%2){tmp=0; break;}
                tmp=tmp*fact[a[i]/2]%mod;
            }
            if (tmp) tmp=1LL*fact[s/2]*cnk(m*m/2, s/2)%mod*inv(tmp)%mod;
        }


        ans=(ans+tmp)%mod;


		
        return ans*inv(4)%mod;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
    //void test_case_0() { int Arg0 = 1; int Arr1[] = {1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(0, Arg2, count(Arg0, Arg1)); }
	void test_case_0() { int Arg0 = 91000; int Arr1[] = {43500, 4828, 64332, 83280, 88564, 91336, 69864, 42196, 85468, 97060, 15908, 84040, 28844, 53356, 44844, 19252, 83940, 61144, 15488, 85240, 35116, 63928, 61011, 91892, 16140, 81548, 79240, 19708, 82796, 78064, 71392, 43764, 34708, 17376, 34504, 16916, 48280, 55020, 1652, 20200, 93244, 32880, 33404, 1392}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(0, Arg2, count(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 2; int Arr1[] = {1, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(1, Arg2, count(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 3; int Arr1[] = {1, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 18; verify_case(2, Arg2, count(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 3; int Arr1[] = {4, 2, 1, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(3, Arg2, count(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
  TheBeautifulBoard ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE
