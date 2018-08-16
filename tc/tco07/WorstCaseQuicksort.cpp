// BEGIN CUT HERE

// END CUT HERE
#line 5 "WorstCaseQuicksort.cpp"

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


const int maxn=1005;
typedef pair<int, vi> state;
vi pos;

state dp[maxn];
int seen[maxn];

state proc(int n){


	if (seen[n])return dp[n];
	seen[n]=1;
	state &best=dp[n];
	if (n==0) return best=state(0, vi());
	if (n==1)return best=state(1, vi(1, 1));
	vi l;
	FE(it, pos) l.pb((*it*n)/1000);
	sort(ALL(l));

	best.ST=-1;

	int same=(l[0]==l[1] || l[2]==l[1]);
	REP(i, n){
		if ((i==0 || i==n-1) && !same)continue;
		state sa, sb;
		sa=proc(i); sb=proc(n-1-i);
		state cnd=MP(max(sa.ST, sb.ST)+1, vi());
		if (best.ST>cnd.ST)continue;
		bool needa, needb;
		needa=needb=1;
		int pa, pb;
		if (same) needa=needb=0;
		pa=pb=0;
		REP(j, n){
			if (j==l[1]) cnd.ND.pb(i+1);
			else if (j==l[0] && !same) cnd.ND.pb(sa.ND[pa++]), needa=0;
			else if (j==l[2] && !same) cnd.ND.pb(sb.ND[pb++]+i+1), needb=0;
			else if (pa<sa.ND.size()-needa) cnd.ND.pb(sa.ND[pa++]);
			else if (pb<sb.ND.size()-needb) cnd.ND.pb(sb.ND[pb++]+i+1);
			else assert(0);
		}
		REP(j, n) REP(k, j) assert(cnd.ND[j]!=cnd.ND[k]);
		if (best.ST<cnd.ST || cnd.ND<best.ND) best=cnd;
	}
	assert(best.ND.size()==n);
	return best;
}

class WorstCaseQuicksort {
	public:
		vector <int> worstInput(int n, vector <int> _pos) {
			memset(seen, 0, sizeof(seen));
			pos=_pos;
			vi res=proc(n).ND;
			return res;
		}

		// BEGIN CUT HERE
	public:
		void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
		template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
		void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
		void test_case_0() { int Arg0 = 394; int Arr1[] = {330, 366, 169}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 3, 8, 11, 14, 17, 19, 23, 25, 29, 31, 35, 37, 41, 43, 47, 49, 53, 55, 59, 61, 65, 67, 71, 73, 77, 79, 83, 85, 89, 91, 95, 97, 101, 105, 107, 111, 113, 117, 119, 123, 125, 129, 131, 135, 137, 141, 143, 147, 149, 153, 155, 159, 161, 165, 167, 171, 173, 177, 179, 183, 185, 189, 191, 195, 197, 201, 205, 207, 211, 213, 217, 219, 223, 225, 229, 231, 235, 237, 241, 243, 247, 249, 253, 255, 259, 261, 265, 267, 271, 273, 277, 279, 283, 285, 289, 291, 295, 297, 301, 305, 307, 311, 313, 317, 319, 323, 325, 329, 331, 335, 337, 341, 343, 347, 349, 353, 355, 359, 361, 365, 367, 371, 373, 377, 379, 383, 385, 389, 391, 393, 387, 381, 375, 369, 363, 357, 351, 345, 339, 333, 327, 321, 315, 394, 392, 390, 309, 388, 386, 384, 382, 303, 380, 378, 376, 374, 299, 372, 370, 368, 366, 293, 364, 362, 360, 287, 358, 356, 354, 352, 281, 350, 348, 346, 344, 275, 342, 340, 338, 336, 269, 334, 332, 330, 263, 328, 326, 324, 322, 257, 320, 318, 316, 314, 251, 312, 310, 308, 306, 245, 304, 302, 300, 239, 298, 296, 294, 292, 233, 290, 288, 286, 284, 227, 282, 280, 278, 221, 276, 274, 272, 270, 215, 268, 266, 264, 262, 209, 260, 258, 256, 254, 203, 252, 250, 248, 199, 246, 244, 242, 240, 193, 238, 236, 234, 232, 187, 230, 228, 226, 224, 181, 222, 220, 218, 175, 216, 214, 212, 210, 169, 208, 206, 204, 202, 163, 200, 198, 196, 157, 194, 192, 190, 188, 151, 186, 184, 182, 180, 145, 178, 176, 174, 172, 139, 170, 168, 166, 133, 164, 162, 160, 158, 127, 156, 154, 152, 150, 121, 148, 146, 144, 142, 115, 140, 138, 136, 109, 134, 132, 130, 128, 103, 126, 124, 122, 120, 99, 118, 116, 114, 112, 93, 110, 108, 106, 87, 104, 102, 100, 98, 81, 96, 94, 92, 90, 75, 88, 86, 84, 69, 82, 80, 78, 76, 63, 74, 72, 70, 68, 57, 66, 64, 62, 60, 51, 58, 56, 54, 45, 52, 50, 48, 46, 39, 44, 42, 40, 38, 33, 36, 34, 32, 30, 27, 28, 26, 24, 20, 21, 18, 16, 15, 13, 12, 2, 10, 9, 7, 6, 4, 5, 22}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, worstInput(Arg0, Arg1)); }
		//void test_case_0() { int Arg0 = 5; int Arr1[] = {0,500,999}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 2, 3, 4, 5 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, worstInput(Arg0, Arg1)); }
		void test_case_1() { int Arg0 = 8; int Arr1[] = {500, 500, 500}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 3, 5, 7, 8, 6, 4, 2 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, worstInput(Arg0, Arg1)); }
		void test_case_2() { int Arg0 = 10; int Arr1[] = {800, 100, 400}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 2, 5, 7, 9, 3, 6, 8, 10, 4 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, worstInput(Arg0, Arg1)); }
		void test_case_3() { int Arg0 = 1000; int Arr1[] = {800,150,800}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 2, 3, 4, 6, 7, 8, 9, 11, 12, 13, 14, 16, 17, 18, 19, 21, 22, 23, 24, 26, 27, 28, 29, 30, 25, 20, 15, 10, 5 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, worstInput(Arg0, Arg1)); }

		// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	WorstCaseQuicksort ___test; 
	___test.run_test(0); } 
// END CUT HERE
