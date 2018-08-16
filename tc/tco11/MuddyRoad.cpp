// BEGIN CUT HERE

// END CUT HERE
#line 5 "MuddyRoad.cpp"

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


const int maxn=55;

vector<double> road;
int n;
double A[maxn][3][3];//pos, state+1, state+2 : state in {non muddy, muddy, undecided}
int F[maxn][3][3];

double proc(int p, int a, int b){
    if (p>=n-3) return 0.;
    double &r=A[p][a][b];
    if (F[p][a][b]) return r;
    F[p][a][b]=1;
    r=0.;
    if (a==2) r=proc(p, 0, b)*(1-road[p+1])+proc(p, 1, b)*road[p+1];
    else if (b==2) r=proc(p, a, 0)*(1-road[p+2])+proc(p, a, 1)*road[p+2];
    else{
        if (!b) r=proc(p+2, 2, 2);
        else if (!a) r=proc(p+1, b, 2);
        else r=1+proc(p+2, 2, 2);
    }
    return r;
    

}

class MuddyRoad {
	public:
	double getExpectedValue(vector <int> _road) {
        n=_road.size();
        road.clear();
        REP(i, n) road.pb(_road[i]/100.);
        memset(F, 0, sizeof(F));
        return proc(0, 2, 2);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0, 60, 60, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 0.36; verify_case(0, Arg1, getExpectedValue(Arg0)); }
	void test_case_1() { int Arr0[] = {0, 50, 50, 50, 50, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 0.5625; verify_case(1, Arg1, getExpectedValue(Arg0)); }
	void test_case_2() { int Arr0[] = {0, 0, 100, 100, 100, 100, 100, 100, 0, 0, 100, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 3.0; verify_case(2, Arg1, getExpectedValue(Arg0)); }
	void test_case_3() { int Arr0[] = {0, 12, 34, 56, 78, 91, 23, 45, 67, 89, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 1.7352539420031923; verify_case(3, Arg1, getExpectedValue(Arg0)); }
	void test_case_4() { int Arr0[] = {0, 50, 50, 100, 50, 100, 50, 50, 100, 66, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 2.288125; verify_case(4, Arg1, getExpectedValue(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  MuddyRoad ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
