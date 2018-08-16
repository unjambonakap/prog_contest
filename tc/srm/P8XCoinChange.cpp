// BEGIN CUT HERE

// END CUT HERE
#line 5 "P8XCoinChange.cpp"

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

const int maxn=44;
const int mod=1e6+3;

int n;

struct matrix{
    int m[maxn][maxn];
    matrix(){memset(m, 0, sizeof(m));}
    matrix(const matrix &a){memcpy(m, a.m, sizeof(m));}
    matrix operator*(const matrix &a)const{
        matrix r;
        REP(i, n) REP(j, n) REP(k, n) r.m[i][j]=(r.m[i][j]+1LL*m[i][k]*a.m[k][j])%mod;
        return r;
    }
    void ident(){ REP(i, n) m[i][i]=1; }
};

matrix fast_exp(matrix a, ll p){
    matrix x; x.ident();
    while(p){
        if (p&1) x=x*a;
        p>>=1;
        a=a*a;
    }
    return x;
}


class P8XCoinChange {
	public:
	int solve(long long m, vector<long long> values) {
        n=values.size();
        matrix A[n];
        A[0].m[0][0]=1;
        REP(i, n) A[0].m[i][0]=1;
        FOR(i, 1, n){
            A[i]=fast_exp(A[i-1], values[i]/values[i-1]);
            FOR(j, i, n) A[i].m[j][i]++;
        }

        matrix res; res.ident();
        for (int i=n-1; m; m%=values[i--]){
            ll p=m/values[i];
            res=res*fast_exp(A[i], p);
        }
        ll ans=0;
        REP(i, n) ans+=res.m[n-1][i];
        
        return ans%mod;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	//void test_case_0() { long long Arg0 = 999999999999999989LL; long long Arr1[] = {1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049, 177147, 531441, 1594323, 4782969, 14348907, 43046721, 129140163, 387420489LL, 1162261467LL, 3486784401LL, 10460353203LL, 31381059609LL, 94143178827LL, 282429536481LL, 847288609443LL, 2541865828329LL, 7625597484987LL, 22876792454961LL, 68630377364883LL, 205891132094649LL, 617673396283947LL, 1853020188851841LL, 5559060566555523LL, 16677181699666569LL, 50031545098999707LL, 150094635296999121LL, 450283905890997363LL}; vector<long long> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(0, Arg2, solve(Arg0, Arg1)); }
	void test_case_0() { long long Arg0 = 1000000000000000000LL; long Arr1[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096}; vector<long long> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(0, Arg2, solve(Arg0, Arg1)); }
    
	//void test_case_0() { long long Arg0 = 4LL; long Arr1[] = {1, 3}; vector<long long> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(0, Arg2, solve(Arg0, Arg1)); }
	void test_case_1() { long long Arg0 = 4LL; long Arr1[] = {1, 2, 4}; vector<long long> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 4; verify_case(1, Arg2, solve(Arg0, Arg1)); }
	void test_case_2() { long long Arg0 = 3LL; long Arr1[] = {1, 5}; vector<long long> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(2, Arg2, solve(Arg0, Arg1)); }
	void test_case_3() { long long Arg0 = 11LL; long Arr1[] = {1, 2, 6}; vector<long long> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 9; verify_case(3, Arg2, solve(Arg0, Arg1)); }
	void test_case_4() { long long Arg0 = 1000000000000000000LL; long long Arr1[] = {1, 1000000000LL, 1000000000000000000LL}; vector<long long> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 997005; verify_case(4, Arg2, solve(Arg0, Arg1)); }
	void test_case_5() { long long Arg0 = 961320341778342848LL; long long Arr1[] = {1,2,10,30,150,300,1200,2400,4800,14400,
28800LL,57600LL,288000LL,576000LL,2304000LL,9216000LL,
18432000LL,73728000LL,221184000LL,663552000LL,
1327104000LL,5308416000LL,31850496000LL,
95551488000LL,191102976000LL,764411904000LL,
1528823808000LL,6115295232000LL,18345885696000LL,
36691771392000LL,73383542784000LL,220150628352000LL,
440301256704000LL,1320903770112000LL,3962711310336000LL,
15850845241344000LL,31701690482688000LL,95105071448064000LL,
475525357240320000LL,951050714480640000LL}; vector<long long> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 245264; verify_case(5, Arg2, solve(Arg0, Arg1)); }
	void test_case_6() { long long Arg0 = 1000000000000000000LL; long Arr1[] = {1, 2}; vector<long long> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 499989; verify_case(6, Arg2, solve(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  P8XCoinChange ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE
