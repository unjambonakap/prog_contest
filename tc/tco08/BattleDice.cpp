// BEGIN CUT HERE

// END CUT HERE
#line 5 "BattleDice.cpp"

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



#define REP(i,n) for(i = 0; i < (n); i++)

#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define FOR(i, a, b) for(i = (a); i <= (b); i++)
#define FORV(i, a, b) for(i = (a); i >= (b); i--)

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();i++)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();i++)

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

inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}

const double EPS=10e-9;

int n, r;

vi ea, eb;
vi best, cur;
double pbest;
double paa;
double probWin(const vector<int> &a, const vector<int> &b){
	int i, j;
	int na, nb;

	na=nb=0;
	REP(i, n) REP(j, n){
		if (a[i]<b[j])++na;
		else if (a[i]>b[j])++nb;
	}
	return double(nb)/(na+nb);
}

void gen(int p){
	int i, j;
	if (p==n){
		double np;
		double pa, pb;
		np=0.;
		pa=probWin(cur, ea);
		pb=probWin(cur, eb);
		np=max(np, 1-max(pa, 1-paa));
		np=max(np, 1-max(pb, paa));
		np=max(np, 1-max(1-pa, 1-pb));

		np=1-np;
		if (np>pbest+EPS)
			pbest=np, best=cur;
		return;
	}
	for (i=(p==0?1:cur[p-1]); i<=r; ++i) cur[p]=i, gen(p+1);
	

}

class BattleDice {
	public:
	vector <int> die3(vector <int> da, vector <int> db, int range) {

		vi dc;
		n=da.size();
		r=range;

		double p=probWin(da, db);
		if (fabs(p-0.5)<EPS)return vi(n, 1);
		if (p<0.5)swap(da, db);

		ea=da, eb=db;
		paa=probWin(ea, eb);
		best=vi();
		cur=vi(n, -1);
		gen(0);
		pbest=0.;

		return best;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arr0[] = { 2, 2, 5 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 2, 3, 3 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 6; int Arr3[] = {1, 3, 4 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(0, Arg3, die3(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = { 3, 5, 6 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 6, 3, 5 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 15; int Arr3[] = {1, 1, 1 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(1, Arg3, die3(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = { 1, 3, 8, 10 }
; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 1, 5, 6, 12 }
; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 12; int Arr3[] = {1, 6, 6, 7 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(2, Arg3, die3(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = { 2, 3, 4 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 5, 6, 7 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 8; int Arr3[] = {1, 6, 8 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(3, Arg3, die3(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = { 6, 6, 8, 9, 13, 13, 15 }
; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 3, 5, 8, 10, 13, 14, 14 }
; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 15; int Arr3[] = {1, 7, 9, 10, 13, 13, 14 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(4, Arg3, die3(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arr0[] = { 1, 6, 5, 1, 5 }
; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 3, 3, 7, 7, 1 }
; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 7; int Arr3[] = {4, 4, 4, 4, 4 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(5, Arg3, die3(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  BattleDice ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
