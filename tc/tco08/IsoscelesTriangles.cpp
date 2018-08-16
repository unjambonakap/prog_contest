// BEGIN CUT HERE

// END CUT HERE
#line 5 "IsoscelesTriangles.cpp"

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




class IsoscelesTriangles {
	public:
	long long count(int N, int M) {

		vector<pair<int, pii> > edges;

		FOR(i, -N, N) FOR (j, -M, M) edges.pb(MP(i*i+j*j, MP(i, j)));
		sort(ALL(edges));
		int i, j;
		i=0;
		ll res=0;
		while(i<edges.size()){
			j=i+1;

			while(j<edges.size() && edges[j].ST==edges[i].ST)++j;
			FOR (ka, i, j-1) FOR(kb, ka+1, j-1){
				int xa, xb, ya, yb;

				xa=edges[ka].ND.ST, ya=edges[ka].ND.ND, xb=edges[kb].ND.ST, yb=edges[kb].ND.ND;
				int bx=-min(min(0, xa), xb), by=-min(min(0, ya), yb);

				if (xa*yb-ya*xb==0)continue;
				int mx, my;
				mx=bx+max(0, max(xa, xb)); my=by+max(0, max(ya, yb));
				if (mx<N && my<M) res+=(N-mx)*(M-my);
				
			}
			i=j;


		}
		return res;

		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 10; int Arg1 = 10; long long Arg2 = 0LL; verify_case(0, Arg2, count(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 2; long long Arg2 = 4LL; verify_case(1, Arg2, count(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 2; int Arg1 = 3; long long Arg2 = 10LL; verify_case(2, Arg2, count(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 5; int Arg1 = 4; long long Arg2 = 248LL; verify_case(3, Arg2, count(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  IsoscelesTriangles ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
