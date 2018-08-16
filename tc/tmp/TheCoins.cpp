// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheCoins.cpp"

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


class TheCoins {
	public:
	long long find(int n, int m, int dr, int dc, vector <int> row, vector <int> column) {
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 3; int Arg2 = 1; int Arg3 = 1; int Arr4[] = {}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); long long Arg6 = 6LL; verify_case(0, Arg6, find(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_1() { int Arg0 = 5; int Arg1 = 4; int Arg2 = 2; int Arg3 = 1; int Arr4[] = {3, 3}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {2, 3}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); long long Arg6 = 10LL; verify_case(1, Arg6, find(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_2() { int Arg0 = 100; int Arg1 = 100; int Arg2 = 4; int Arg3 = 7; int Arr4[] = {}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); long long Arg6 = 9520LL; verify_case(2, Arg6, find(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_3() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 1; int Arg3 = 1; int Arr4[] = {1, 2}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {2, 1}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); long long Arg6 = 2LL; verify_case(3, Arg6, find(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_4() { int Arg0 = 5; int Arg1 = 4; int Arg2 = 1; int Arg3 = 1; int Arr4[] = {2, 4, 3, 5, 2, 2, 5, 4}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {2, 2, 2, 2, 3, 4, 4, 4}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); long long Arg6 = 0LL; verify_case(4, Arg6, find(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_5() { int Arg0 = 84; int Arg1 = 71; int Arg2 = 74; int Arg3 = 22; int Arr4[] = {50, 47, 11, 57, 12, 58, 16, 5, 77, 26, 71, 45, 53, 70, 3, 50, 65,
 11, 44, 58, 59, 12, 30, 78, 12, 19, 48, 53, 19, 71, 52, 77, 73, 33,
 63, 73, 55, 10, 14, 66, 67, 46, 34, 60, 71, 12, 83, 18}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {27, 50, 59, 37, 6, 26, 41, 67, 68, 70, 12, 3, 1, 62, 25, 70, 46,
 48, 26, 5, 16, 62, 44, 39, 60, 19, 47, 32, 50, 21, 14, 38, 13, 58,
 37, 70, 10, 70, 5, 6, 1, 54, 52, 9, 69, 49, 41, 58}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); long long Arg6 = 970LL; verify_case(5, Arg6, find(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_6() { int Arg0 = 122677; int Arg1 = 996231; int Arg2 = 41759; int Arg3 = 481285; int Arr4[] = {25581, 10405, 37052, 85448, 62794, 103890, 75143, 34652, 96573, 107497,
 49592, 117281, 4466, 44553, 9760, 62266, 122175, 84237, 86788, 38864, 
 83124, 108358, 98854, 103177, 86381, 11519, 61147, 33170, 11043, 17402,
 107658, 71673, 102550, 70823, 20568, 81613, 83067, 72136, 34569, 6513,
 24505, 112416, 75208, 4463, 86507, 86558, 45844, 53233, 87815, 50610}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {275695, 51848, 173581, 533376, 882202, 994201, 319894, 128485, 370593,
 1655, 185488, 955779, 731743, 729992, 641079, 530134, 332977, 289273,
 779908, 528428, 700671, 509104, 364078, 429286, 105101, 851418, 592063,
 198998, 745550, 128128, 905177, 806990, 929477, 82009, 432238, 549661,
 939922, 740977, 372638, 67868, 525232, 289171, 493261, 178561, 208168,
 960711, 584970, 920830, 607658, 270535}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); long long Arg6 = 80700538590LL; verify_case(6, Arg6, find(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
  TheCoins ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
