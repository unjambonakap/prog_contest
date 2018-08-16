// BEGIN CUT HERE

// END CUT HERE
#line 5 "ElevenMultiples.cpp"

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

const int maxn=52;
const int mod=1e9+7;

int a[maxn], b[maxn];
int na, nb;
int dp[maxn][maxn][maxn];//pos,num b used, num -1 used
int dp2[maxn][maxn][maxn][11];//pos,num 1,num -1,mod
int dp3[maxn][maxn][11];
int fact[maxn];



int go1(int p, int ub, int ua){
    if (ua<0) return 0;
    if (p==na) return !ua;
    int &r=dp[p][ub][ua];
    if (r!=-1) return r;

    ll x=0;
    if (ub<nb) x+=go1(p,ub+1,ua);
    x+=go1(p+1,ub,ua-(ub&1));
    return r=x%mod;
}


int go2(int p, int ua, int ub, int m){
    if (p==nb) return ub==p/2&&!m;
    int &r=dp2[p][ua][ub][m];
    if (r!=-1) return r;

    ll x=0;
    x+=1ll*go2(p+1,ua,ub+1,(m+b[p]+11)%11)*(ub+1);
    x+=1ll*go2(p+1,ua+1,ub,(m-b[p]+11)%11)*(ua+1);
    return r=x%mod;
}

int go3(int p, int ua, int m){
    if (ua<0) return 0;
    if (p==na) return !ua&&!m;
    int &r=dp3[p][ua][m];
    if (r!=-1) return r;
    ll x=0;
    x+=1ll*go3(p+1,ua-1,(m+a[p]+11)%11);
    x+=1ll*go3(p+1,ua,(m-a[p]+11)%11);
    return r=x%mod;
}

class ElevenMultiples {
	public:
	int countMultiples(vector <string> pieces) {
        int n=pieces.size();
        fact[0]=1;
        FOR(i,1,maxn) fact[i]=1ll*i*fact[i-1]%mod;

        na=nb=0;
        REP(i,n){
            int f=1;
            int x=0;
            for (int j=pieces[i].size()-1; j>=0; --j) x+=(pieces[i][j]-'0')*f, f*=-1;
            x=(x%11+11)%11;
            if (f==1) a[na++]=x;
            else b[nb++]=x;
        }

        memset(dp,-1,sizeof(dp)); memset(dp2,-1,sizeof(dp2)); memset(dp3,-1,sizeof(dp3));
        ll res=0;
        REP(j,na+1) REP(i,11) res+=1ll*go1(0,0,j)*go2(0,0,0,(11-i)%11)%mod*go3(0,j,i)%mod*fact[j]%mod*fact[na-j]%mod, res%=mod;
        
        return res;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"58", "2012", "123"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(0, Arg1, countMultiples(Arg0)); }
	void test_case_1() { string Arr0[] = {"1", "1111", "1", "11"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 24; verify_case(1, Arg1, countMultiples(Arg0)); }
	void test_case_2() { string Arr0[] = {"43925486943738659795389387498953274"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(2, Arg1, countMultiples(Arg0)); }
	void test_case_3() { string Arr0[] = {"983", "4654", "98", "3269", "861", "30981"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 96; verify_case(3, Arg1, countMultiples(Arg0)); }
	void test_case_4() { string Arr0[] = {"193", "8819", "40676", "97625892", "5719", "45515667", "32598836", "70559374", "38756", "724",
"93391", "942068", "506", "901150", "874", "895567", "7560480", "7427691", "799450", "85127"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 537147821; verify_case(4, Arg1, countMultiples(Arg0)); }
	void test_case_5() { string Arr0[] = {"687045939630", "997856158148599044", "2014910234712225061", "9658113323175370226", "1584118137",
"67925153345598920", "6960366756", "863413844386808834", "799302243562410012", "44481835751",
"8004606814733183", "19623906615609", "23859998326058162", "461385591582", "9261878982390119",
"1569373294276", "318106951168934", "65389049931", "12791173342", "507877942026",
"3947173045690", "472425746178910", "524552931853595", "40771812249667850232", "563988469071932",
"28147819070", "797007158858587", "5716177008624223", "387565700495309324", "4716621063133318"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 814880650; verify_case(5, Arg1, countMultiples(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
  ElevenMultiples ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE
