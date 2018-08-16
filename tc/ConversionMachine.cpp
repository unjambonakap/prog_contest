// BEGIN CUT HERE

// END CUT HERE
#line 5 "ConversionMachine.cpp"

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

const int mod=1e9+7;
const ll big=7e18;
const int maxn=12;

struct matrix{
    int n;
    int m[80][80];
    matrix(int n):n(n){memset(m,0,sizeof(m));}
    matrix(const matrix &a){n=a.n; memcpy(m,a.m,sizeof(m));}
    void ident(){REP(i,n) m[i][i]=1;}
    matrix operator*(const matrix &a)const{
        matrix r(n);
        REP(i,n) REP(j,n){
            ll v=0;
            REP(k,n){
                v+=1ll*m[i][k]*a.m[k][j];
                if (v>=big) v%=mod;
            }
            r.m[i][j]=v%mod;
        }
        return r;
    }
};

matrix faste(matrix a, int p){
    matrix x(a.n); x.ident();
    for (; p; p>>=1, a=a*a) if (p&1) x=x*a;
    return x;
}

int rmp[maxn][maxn];
class ConversionMachine {
	public:
	int countAll(string wa, string wb, vector <int> costs, int maxCost) {
        int n=wa.size();
        int m=0;
        ll bc=0, u=0;
        ll nc=costs[0]+costs[1]+costs[2];
        REP(i,n+1) REP(j,n+1-i) rmp[i][j]=m++;
        int na=0, nb=0;

        REP(i,n){
            char c=wa[i]-'a';
            int d=(3+wb[i]-wa[i])%3;
            if (d==0) ++na;
            else if (d==1) ++nb;
            u+=d;
            REP(j,d) bc+=costs[(c+j)%3];
        }


        matrix a(m+1);
        REP(i,n+1) REP(j,n+1-i){
            int k=n-i-j;
            if (i) a.m[rmp[i][j]][rmp[i-1][j]]+=i;
            if (j) a.m[rmp[i][j]][rmp[i+1][j-1]]+=j;
            if (k) a.m[rmp[i][j]][rmp[i][j+1]]+=k;
        }
        a.m[rmp[n][0]][m]=1;
        a.m[m][m]=1;

        if (maxCost<bc) return 0;
        int pw=(maxCost-bc)/nc;
        a=faste(a,pw*3+u+1);
        return a.m[rmp[na][nb]][m];
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "aaaaaaaaaaa"; string Arg1 = "cbcbaaaacaa"; int Arr2[] = {1,1,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1e9; int Arg4 = 2; verify_case(0, Arg4, countAll(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { string Arg0 = "abcba"; string Arg1 = "abcba"; int Arr2[] = {67,23,43}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 0; int Arg4 = 1; verify_case(1, Arg4, countAll(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { string Arg0 = "cccccccc"; string Arg1 = "aaaaaaaa"; int Arr2[] = {10000000,1,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 100; int Arg4 = 40320; verify_case(2, Arg4, countAll(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { string Arg0 = "aa"; string Arg1 = "cc"; int Arr2[] = {1,10,100}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1787; int Arg4 = 123611681; verify_case(3, Arg4, countAll(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
  ConversionMachine ___test; 
        ___test.run_test(0); 
        } 
// END CUT HERE
