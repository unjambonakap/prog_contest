// BEGIN CUT HERE

// END CUT HERE
#line 5 "YetAnotherRobotSimulation.cpp"

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
#define FOR(i, a, b) for(int i = (int)(a); i <= (int)(b); ++i)
#define FORV(i, a, b) for(int i = (int)(a); i >= (int)(b); --i)

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

#define SZ(a) (int((a).size()))
#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()


#define pb push_back
#define PF push_front
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:(n==1?0:ctz(n>>1)+1));}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=54;

long double cnk[maxn][maxn];
long double proba[maxn][maxn];
long double probx[2*maxn];
long double proby[2*maxn];

class YetAnotherRobotSimulation {
	public:
	double getMaximumProbability(int L, vector <int> lx, vector <int> ly) {
            cnk[0][0]=1;
            REP(i, L+1) if (i){
                cnk[i][0]=cnk[i][i]=1;
                REP(j, i) if (j) cnk[i][j]=cnk[i-1][j-1]+cnk[i-1][j];
            }
            REP(i, L+1) REP(j, i+1) proba[i][j]=cnk[i][j]*pow(1/2., i);

            double res=0., best=0.;
            REP(xa, L+1) REP(xb, L+1-xa) REP(ya, L+1-xa-xb){
                res=0.;
                int yb=L-xa-xb-ya;
                memset(probx, 0, sizeof(probx));
                memset(proby, 0, sizeof(proby));
                REP(i, xa+1) REP(j, xb+1) probx[maxn+i-j]+=proba[xa][i]*proba[xb][j];
                REP(i, ya+1) REP(j, yb+1) proby[maxn+i-j]+=proba[ya][i]*proba[yb][j];

                REP(i, lx.size()) if (abs(lx[i])<maxn && abs(ly[i])<maxn) res+=probx[lx[i]+maxn]*proby[ly[i]+maxn];
                checkmax(best, res);
            }
            return best;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	//void test_case_0() { int Arg0 = 3; int Arr1[] = {1,2,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1,1,0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 0.5; verify_case(0, Arg3, getMaximumProbability(Arg0, Arg1, Arg2)); }
	void test_case_0() { int Arg0 = 50; int Arr1[] = {-59, 57, -61, -33, -87, -80, 72, 29, 10, -79, -100, 57, 14, 23, 20, 97, 35, -96, -88, 60, -1, 22, -88, 76, 49, -86, 62, -33, -73, 21, -52, -58, 50, -62, 54, 62, 33, -100, 14, 85, 94, 93, 26, -74, -23}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {-70, 97, -96, -15, -52, -45, 41, -28, 87, -99, -85, -21, -67, -1, 10, 98, 24, 32, -47, -59, -36, -87, -84, 80, -30, 19, 75, -48, -97, -16, -22, 60, 64, -9, -39, 49, -90, -22, -34, -15, 89, -97, -13, -61, 11}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 0.5; verify_case(0, Arg3, getMaximumProbability(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 5; int Arr1[] = {0,0,0,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0,1,2,3}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 0.9375; verify_case(1, Arg3, getMaximumProbability(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 1; int Arr1[] = {0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 0.5; verify_case(2, Arg3, getMaximumProbability(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 8; int Arr1[] = {2,3,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1,1,0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 0.41015625; verify_case(3, Arg3, getMaximumProbability(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 36; int Arr1[] = {6,7,12,-21,5,5,2,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {4,5,-2,4,5,12,5,7} ; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 0.1323284485260956; verify_case(4, Arg3, getMaximumProbability(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  YetAnotherRobotSimulation ___test; 
        ___test.run_test(0);
        } 
// END CUT HERE
