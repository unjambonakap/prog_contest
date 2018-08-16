// BEGIN CUT HERE

// END CUT HERE
#line 5 "FoxAndGreed.cpp"

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

const int mod=1e4+7;
const int maxn=2501;
const int maxs=111;
int S, H, W;
int pw[maxn*maxn];
int dpa[maxn][maxs];
int dpb[maxn][maxs];
int dpc[maxn][maxs];
int fact[2*maxn], ifact[2*maxn];

int cnk(int n, int k){if (k<0||k>n) return 0; return fact[n]*ifact[k]%mod*ifact[n-k]%mod;}
int faste(int a, int p){
    int x=1;
    for (; p; p>>=1, a=a*a%mod) if (p&1) x=x*a%mod;
    return x;
}


int goa(int a, int b){
    if (!a) return b==0;
    int &r=dpa[a][b];
    if (r!=-1) return r;
    r=0;
    REP(i,b+1) r=(r+goa(a-1,b-i)*i)%mod;
    return r;
}


int gob(int a, int b){
    if (!a) return b==0;
    int &r=dpb[a][b];
    if (r!=-1) return r;
    r=0;
    REP(i,b+1) r=(r+gob(a-1,b-i)*(i+1))%mod;
    return r;
}


int goc(int a, int b){
    if (!a) return b==0;
    int &r=dpc[a][b];
    if (r!=-1) return r;
    r=0;
    REP(i,b+1) r=(r+goc(a-1,b-i))%mod;
    return r;
}

int mp[10][10];

int checkita(int x, int y, int v){
    if (x==H-1&&y==W-1) return v==S;
    if (x==H-1) return checkita(x,y+1,v+mp[x][y+1]);
    if (y==W-1) return checkita(x+1,y,v+mp[x+1][y]);
    if (mp[x+1][y]>mp[x][y+1]) return checkita(x+1,y,v+mp[x+1][y]);
    else return checkita(x,y+1,v+mp[x][y+1]);

}

int gen(int a, int b){
    if (b==W) b=0, ++a;
    if (a==H){
        if (checkita(0,0,0)){
            //REP(i,H) out(mp[i],W);
            //puts("");


            return 1;
        }
        return 0;
    }
    int res=0;
    REP(i,S+1) mp[a][b]=i, res+=gen(a,b+1);
    return res;
}
int checkit(){
    return gen(0,1);
}

class FoxAndGreed {
	public:
	int count(int _H, int _W, int _S) {
        H=_H; W=_W; S=_S;
        memset(dpc,-1,sizeof(dpc));
        fact[0]=ifact[0]=1;
        FOR(i,1,2*maxn) fact[i]=fact[i-1]*i%mod, ifact[i]=faste(fact[i],mod-2);

        if (H==1) return goc(W-1,S);
        if (W==1) return goc(H-1,S);

        memset(dpa,-1,sizeof(dpa));
        memset(dpb,-1,sizeof(dpb));

        pw[0]=1;
        FOR(i,1,H*W+1) pw[i]=pw[i-1]*(S+1)%mod;



        int res=0;
        int rem=H*W-1;
        if (H<=S+1){
            REP(i,W-1){
                //last right move on (W-1,i) -> (W,i)
                int nd=H-1, nr=i;
                int tmp=cnk(nr+nd-1,nd-1);
                ll u=0;
                REP(j,S+1){// value for points (i+1,H),...,(W,H)
                    int x=goc(W-i-1,j);
                    REP(k,S-j+1){
                        u+=tmp*x%mod*gob(nr,k)%mod*goa(nd,S-j-k)%mod;//k value for right moves
                    }
                    u%=mod;
                }
                int nx=2*(nr+nd)+(W-i-1);
                res+=u*pw[rem-nx]%mod;
                res%=mod;
            }
        }

        REP(i,min(S+10,H-1)){
            //last right move on (W-1,i) -> (W,i)
            int nr=W-1, nd=i;
            int tmp=cnk(nr+nd-1,nr-1);
            ll u=0;
            REP(j,S+1){// value for points (W,i+1),...,(W,H)
                int x=goc(H-i-1,j);
                REP(k,S-j+1) u+=tmp*x%mod*gob(nr,k)%mod*goa(nd,S-j-k)%mod;//k value for right moves
                u%=mod;
            }
            int nx=2*(nr+nd)+(H-i-1);
            res+=u*pw[rem-nx]%mod;
            res%=mod;
        }
        return res;
    }

    // BEGIN CUT HERE
    public:
    void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
    private:
    template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
    void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
    void test_case_0() { int Arg0 = 2500; int Arg1 = 2500; int Arg2 = 30; int Arg3 = 4; verify_case(0, Arg3, count(Arg0, Arg1, Arg2)); }
    void test_case_1() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 2; int Arg3 = 9; verify_case(1, Arg3, count(Arg0, Arg1, Arg2)); }
    void test_case_2() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 0; int Arg3 = 1; verify_case(2, Arg3, count(Arg0, Arg1, Arg2)); }
    void test_case_3() { int Arg0 = 47; int Arg1 = 58; int Arg2 = 100; int Arg3 = 1301; verify_case(3, Arg3, count(Arg0, Arg1, Arg2)); }
    void test_case_4() { int Arg0 = 1234; int Arg1 = 2345; int Arg2 = 97; int Arg3 = 8894; verify_case(4, Arg3, count(Arg0, Arg1, Arg2)); }

    // END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
    FoxAndGreed ___test; 
    ___test.run_test(-1);
} 
// END CUT HERE
