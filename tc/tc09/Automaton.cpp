// BEGIN CUT HERE

// END CUT HERE
#line 5 "Automaton.cpp"

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

const int MAX_L=125005;//ceil(ln(MAX_L)/ln(2))+1 = 18
const int MAX_N=10, MAX_M=10;

int tsf[MAX_N][MAX_M];
int tree[two(18)][10];
int leafId[two(17)];
vector<int> x0;
int n, m;

void merge(int *a, int *b, int *c){
	for (int i=0; i<n; ++i)
		a[i]=c[b[i]];
}
void init(int id, int L, int H){

	if (L>=H){
		leafId[L]=id;
		for (int i=0; i<n; ++i)
			tree[id][i]=(L>H?i:tsf[i][0]);
		return;
	}
	int ida, idb, M;
	ida=id*2+1, idb=id*2+2;
	M=(L+H)/2;
	init(ida, L, M); init(idb, M+1, H);
	merge(tree[id], tree[ida], tree[idb]);

}
void update(int id){
	merge(tree[id], tree[id*2+1], tree[id*2+2]);
	if (id!=0)
		update((id-1)/2);
}

class Automaton {
	public:
	int numberOfMatchings(vector <string> _tl, int sl, vector <int> x0, vector <int> xa, vector <int> c0, vector <int> ca, int modifications) {
		int i, j, k;
		m=_tl[0].length();
		n=_tl.size();
		
		int initElements=x0.size();
		int x[modifications], c[modifications];
		


		for (int i = 0; i < initElements; i++) {
			x[i] = x0[i]%sl;
			c[i] = c0[i]%m;
		}

		for (int i = initElements; i < modifications; i++) {
			x[i] = 0;
			c[i] = 0;	
			for (int j = i - initElements; j < i; j++) {
				x[i] = (x[i] + xa[j - i + initElements] * x[j])%sl;
				c[i] = (c[i] + ca[j - i + initElements] * c[j])%m;
			}
		}

		for (i=0; i<n; ++i)
			for (j=0; j<m; ++j)
				tsf[i][j]=_tl[i][j]-'A';

		int res=0;

		init(0, 0, sl-1);
		if (tree[0][0]==n-1)
			++res;
		for (i=0; i<modifications; ++i){
			for (j=0; j<n; ++j)
				tree[leafId[x[i]]][j]=tsf[j][c[i]];
			if (leafId[x[i]]>0)
				update((leafId[x[i]]-1)/2);

			if (tree[0][0]==n-1)
				++res;
		}
		return res;
	}


	// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"AA"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arr2[] = {0, 0, 0, 0, 0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {0, 0, 0, 0, 0}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {1, 0, 1, 0, 1}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {0, 0, 0, 0, 0}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arg6 = 5; int Arg7 = 6; verify_case(0, Arg7, numberOfMatchings(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_1() { string Arr0[] = {"BA", "AB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arr2[] = {0, 0, 0, 0, 0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {0, 0, 0, 0, 0}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {1, 0, 1, 0, 1}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {0, 0, 0, 0, 0}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arg6 = 5; int Arg7 = 3; verify_case(1, Arg7, numberOfMatchings(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_2() { string Arr0[] = {"BC", "CA", "AB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; int Arr2[] = {0, 1, 2, 3, 4}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {0, 0, 0, 0, 0}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {1, 1, 1, 1, 1}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {0, 0, 0, 0, 0}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arg6 = 5; int Arg7 = 2; verify_case(2, Arg7, numberOfMatchings(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_3() { string Arr0[] = {"ABB", "BAA"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arr2[] = {0, 1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1, 1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {0, 1}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {1, 1}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arg6 = 10; int Arg7 = 5; verify_case(3, Arg7, numberOfMatchings(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_4() { string Arr0[] = {"BA", "AB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arr2[] = {0, 3, 5}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {10, 9, 7}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {1, 2, 4}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {5, 1, 3}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arg6 = 2400; int Arg7 = 1601; verify_case(4, Arg7, numberOfMatchings(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }

	// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	Automaton ___test; 
	___test.run_test(-1); 
} 
// END CUT HERE
