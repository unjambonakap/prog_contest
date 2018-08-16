// BEGIN CUT HERE

// END CUT HERE
#line 5 "BuildingReorganization.cpp"

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


class BuildingReorganization {
	public:
	long long theMin(vector <int> heights, int A, int B, int cost) {
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {5, 5, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 2; int Arg3 = 10; long long Arg4 = 215LL; verify_case(0, Arg4, theMin(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arr0[] = {5, 5, 5, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 3; int Arg3 = 10; long long Arg4 = 190LL; verify_case(1, Arg4, theMin(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arr0[] = {5, 50, 1, 50, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 4; int Arg3 = 10; long long Arg4 = 275LL; verify_case(2, Arg4, theMin(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arr0[] = {5, 50, 1, 50, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 4; int Arg3 = 1000; long long Arg4 = 10540LL; verify_case(3, Arg4, theMin(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arr0[] = {5, 50, 1, 50, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 3; int Arg3 = 1000; long long Arg4 = 104428LL; verify_case(4, Arg4, theMin(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_5() { int Arr0[] = {4,1,1,1000,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 4; int Arg3 = 1; long long Arg4 = 20LL; verify_case(5, Arg4, theMin(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_6() { int Arr0[] = {157,10,157,979797,152152152,156,4,77,157,79}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 4; int Arg3 = 123; long long Arg4 = 13041277280686205LL; verify_case(6, Arg4, theMin(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_7() { int Arr0[] = {346455317,453638062,491871419,297060164,426458223,53746370,422461742,231053793,309679268,297959075,
 76653026,277375296,411684823,427164497,257399925,224643292,114988354,457289888,51199847,199807287,
 110648220,303379857,435712111,245040291,401790144,260999362,6953083,385721020,438059362,434000869,
 481788278,70215282,135651128,68577856,448298562,11191117,408997160,407134756,10781024,267655550,
 183460325,284786399,222774818,193425138,51658225,117130718,352764522,342521474,147243649,265160879}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 44; int Arg3 = 9986066; long long Arg4 = 234928185619577559LL; verify_case(7, Arg4, theMin(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
  BuildingReorganization ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
