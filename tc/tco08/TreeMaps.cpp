// BEGIN CUT HERE

// END CUT HERE
#line 5 "TreeMaps.cpp"

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

inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}



const int maxn=51;
vector<int> cd[maxn];
int sz[maxn];
string type;
int n;

pii queryv(int p, double x, double y, double w, double h);
pii queryh(int p, double x, double y, double w, double h){

	double sp=h/sz[p];
	
	int t=0;
	FE(it, cd[p])t+=sz[*it];
	assert(t==sz[p]);
	double c=0.;
	FE(it, cd[p]){
		if (y<c+sp*sz[*it])
			if (type[*it]=='F'){
				int k=*it;
				cd[p].erase(it);
				sz[p]-=sz[k];
				return MP(k, sz[k]);
			}else{
				assert(sz[*it]<=sz[p]);
				pii q=queryv(*it, x, y-c, w, sp*sz[*it]);
				sz[p]-=q.ND;
				return q;
			}
		c+=sp*sz[*it];
	}
	assert(0);

}
pii queryv(int p, double x, double y, double w, double h){

	double sp=w/sz[p];
	double c=0.;
	int t=0;

	FE(it, cd[p]){
		if (x<c+sp*sz[*it])
			if (type[*it]=='F'){
				int k=*it;
				cd[p].erase(it);
				sz[p]-=sz[k];
				return MP(k, sz[k]);
			}else{
				assert(sz[*it]<=sz[p]);
				pii q=queryh(*it, x-c, y, sp*sz[*it], h);
				sz[p]-=q.ND;
				return q;
			}
		c+=sp*sz[*it];
	}

	assert(0);
}

class TreeMaps {
	public:
	vector <int> eraseFiles(string _type, vector <int> parent, vector <int> size, int width, int height, vector <int> px, vector <int> py) {
		type=_type;
		n=type.size();
		int root=0;
		REP(i, n) CLR(cd[i]);
		REP(i, n) if (parent[i]!=-1) cd[parent[i]].pb(i);
		REP(i, n){ 
			sz[i]=size[i];
			sort(ALL(cd[i]));
		}

		vi res;
		REP(i, px.size()) 
			res.pb(queryv(0, px[i], py[i], width, height).ST);
		

		return res;



	}

	// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arg0 = "DFFDFFFFF"; int Arr1[] = {-1, 0, 0, 0, 3, 3, 3, 3, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {10, 2, 2, 4, 1, 1, 1, 1, 2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 20; int Arg4 = 8; int Arr5[] = {12, 12}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {1, 4}; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); int Arr7[] = {4, 6 }; vector <int> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); verify_case(0, Arg7, eraseFiles(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_1() { string Arg0 = "DFFDFFFFF"; int Arr1[] = {-1, 0, 0, 0, 3, 3, 3, 3, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {10, 2, 2, 4, 1, 1, 1, 1, 2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 20; int Arg4 = 8; int Arr5[] = {12, 12, 12, 12, 12}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {1, 1, 1, 1, 1}; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); int Arr7[] = {4, 5, 6, 7, 2 }; vector <int> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); verify_case(1, Arg7, eraseFiles(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_2() { string Arg0 = "DDDFFDFFF"; int Arr1[] = {-1, 0, 0, 1, 1, 2, 2, 5, 5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {10, 4, 6, 2, 2, 5, 1, 2, 3}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 50; int Arg4 = 50; int Arr5[] = {16, 41, 32}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {10, 38, 29}; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); int Arr7[] = {3, 8, 7 }; vector <int> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); verify_case(2, Arg7, eraseFiles(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_3() { string Arg0 = "DFFFFD"; int Arr1[] = {-1, 5, 5, 5, 5, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {10, 4, 2, 3, 1, 10}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 20; int Arg4 = 20; int Arr5[] = {1, 1}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {2, 18}; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); int Arr7[] = {1, 4 }; vector <int> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); verify_case(3, Arg7, eraseFiles(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }

	// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	TreeMaps ___test; 
	___test.run_test(-1); 
} 
// END CUT HERE
