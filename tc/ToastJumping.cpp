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
#define FOR(i, a, b) for(int i = (int)(a); i < (int)(b); ++i)

#define FE(i,t) for (__typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (__typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

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
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

class ToastJumping{ 
    public: 
    vector <int> minJumps(vector <int> x, vector <int> y, vector <int> d){ 
    } 
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arr0[] = {47}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {58}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {105 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(0, Arg3, minJumps(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {20}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {13}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {100}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {3 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(1, Arg3, minJumps(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2013}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {0 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(2, Arg3, minJumps(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {0,-2,-2, 2, 3, 0,-1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,-2, 2,-2, 0,-3, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {9, 9, 9, 9, 9, 9, 9}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1, 1, 1, 1, 1, 1, 2 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(3, Arg3, minJumps(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {350094485, -59465703, 301650813, 493497124, 726872905, 728267881, 646284847, 247277405, -610114152, -889290604,
942942587, 398138767, -449746422, -815547018, -829157569, 833322540, 126734904, 642504299, 15840780, -725479124,
170953687, 670642216, -41561340, 442656888, -509135940, 984522614, -666655105, 765945012, 489992336, -679507993,
55244759, -111992636, -442185089, -231578176, 816151888, -249812294, 22847214, 701440128, -264429700, 601876063,
766907868, -345564217, -958423916, -860946990, 166179838, -10540111, 818188469, 66695025, -1000000000, 1000000000}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-759562847, 388579111, 948590301, -186468629, -908936551, 552174777, 408310326, 729590393, -108146720, -894682139,
330007066, 15158681, 947447563, -135733158, 680334342, -638116658, -902688173, 762933096, 671635881, -894934498,
14012652, 49602780, 133690020, 579701461, -595752346, -842633248, -615003008, -428962476, 362158131, -723942678,
369521718, -844246119, 679476307, -876167056, 24375289, 209090170, 352850339, 289958815, 965142477, 264287292,
603563104, -918128812, -224982821, 695043550, -440442508, 826842852, -204344031, 69798816, 1000000000, -1000000000}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 3306, 11, 22196, 117523, 261753, 801826904, 9055519, 15349382, 10861,
76203, 11, 70437828, 32442, 473, 1496362, 1, 33265, 70636254, 8749345,
14160290, 2425, 33, 441909, 132481883, 5768, 409, 1137, 602, 59565889,
2283279, 9, 43, 499176, 74, 963886, 1010, 6, 194, 1093,
88, 79702, 2026016, 9079687, 191187, 17475, 4230, 7, 1, 1000000000}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1109657332, 6850833, 316196767, 3543540, 3395225, 1786395, 26998, 256001, 158156, 12135869, 3622518, 132712923, 124963, 4592709, 50316398, 858059, 1029423077, 5471023, 79936, 389492, 45583, 13686576, 26738004, 1097436, 68086, 17076224, 45773505, 26144700, 25063250, 128649, 247277, 300080813, 128652694, 1282832, 102018986, 331854, 11382269, 350720064, 74241729, 20110130, 106868942, 3475282, 691664, 367210, 1076863, 6263961, 12976696, 45497947, 2000000000, 44722 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(4, Arg3, minJumps(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
}; 

// BEGIN CUT HERE 
int main(){
    ToastJumping ___test;
    ___test.run_test(-1);
} 
// END CUT HERE
