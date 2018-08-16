// BEGIN CUT HERE

// END CUT HERE
#line 5 "PlaylistShuffler.cpp"

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



#define REP(i,n) for(ll i = 0; i < ll(n); ++i)
#define REPV(i, n) for (ll i = (n) - 1; (ll)i >= 0; --i)
#define FOR(i, a, b) for(ll i = (ll)(a); i <= (ll)(b); ++i)
#define FORV(i, a, b) for(ll i = (ll)(a); i >= (ll)(b); --i)

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

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
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int mod=1e6+3;
const int maxn=55;

ll cnk[maxn][maxn];
ll fact[maxn];
int pl[maxn];
int px[maxn];
int np;

ll Ka, Kb;
ll ans;
int cnt;
int n;

void goa(int p, ll v){
    if (v>Kb) return;
    if (p==np){
        int x=0;
        FOR(i, 2, n) if (v%i==0) ++x;
        ll A=ceil(1.*Ka/v)*v;
        if (A<=Kb && (x>cnt || (x==cnt && A<ans))) cnt=x, ans=A;
        return;
    }
    REP(i, px[p]+1){
        goa(p+1, v);
        v*=pl[p];
    }
}


class PlaylistShuffler {
	public:
	long long bestShuffle(int _n, int X, int Y, long long K1, long long K2) {
        Ka=K1, Kb=K2;
        n=_n;
        if (n==1) return K1;
        np=0;
        pl[np++]=2;
        FOR(i, 3, n){
            int fd=1;
            REP(j, np) if (i%pl[j]==0){fd=0; break;}
            if (fd) pl[np++]=i;
        }
        REP(i, np){
            px[i]=0;
            for (int x=pl[i]; x<=n; x=x*pl[i], ++px[i]);
        }
        ans=Kb;
        cnt=-1;
        if (X==Y) goa(0, 1);
        else{
            cnt=INT_MAX;
            FOR(i, Ka, Kb){
                int x=0;
                FOR(j, 2, n) if (i%j==0) ++x;
                if (cnt>x) ans=i, cnt=x;
                if (!cnt) break;
            }

        }
        return ans;

        //fact[0]=1; FOR(i, 1, maxn-1) fact[i]=fact[i-1]*i%mod;

        //REP(i, maxn) cnk[i][0]=cnk[i][i]=1;
        //REP(i, maxn) REP(j, i) if (j&&i) cnk[i][j]=(cnk[i-1][j]+cnk[i-1][j-1])%mod;

        //n=2;
        //ll res=0;
        //FOR(na, 1, n-1) res+=cnk[n-2][na-1]*fact[na-1]%mod*fact[n-na]%mod;
        //printf("%Ld\n", res);
        //FOR(na, 2, n) res+=cnk[n-2][na-2]*fact[n-na]%mod*fact[na-2]*(na-1)%mod;
        //res%=mod;


	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	//void test_case_0() { int Arg0 = 2; int Arg1 = 0; int Arg2 = 1; long long Arg3 = 2LL; long long Arg4 = 4LL; long long Arg5 = 3LL; verify_case(0, Arg5, bestShuffle(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_0() { int Arg0 = 41; int Arg1 = 33; int Arg2 = 0; long long Arg3 = 54322014; long long Arg4 = 668334434; long long Arg5 = 3LL; verify_case(0, Arg5, bestShuffle(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 1; int Arg2 = 1; long long Arg3 = 1LL; long long Arg4 = 10LL; long long Arg5 = 2LL; verify_case(1, Arg5, bestShuffle(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { int Arg0 = 1; int Arg1 = 0; int Arg2 = 0; long long Arg3 = 1111111111LL; long long Arg4 = 9999999999LL; long long Arg5 = 1111111111LL; verify_case(2, Arg5, bestShuffle(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { int Arg0 = 10; int Arg1 = 3; int Arg2 = 7; long long Arg3 = 1000LL; long long Arg4 = 10000LL; long long Arg5 = 1003LL; verify_case(3, Arg5, bestShuffle(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  PlaylistShuffler ___test; 
        ___test.run_test(0); 
        } 
// END CUT HERE
