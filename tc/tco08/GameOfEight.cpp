// BEGIN CUT HERE

// END CUT HERE
#line 5 "GameOfEight.cpp"

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


set<string> state;

int vx[]={-1, 0, 1, 0};
int vy[]={0, 1, 0, -1};

class GameOfEight {
	public:
	int fewestMoves(vector <string> b) {
		CLR(state);
		string s;
		FE(it, b) s+=*it;
		queue<pair<string, int> > q;
		q.push(MP(s, 0));
		string end="12345678.";
		while(!q.empty()){
			pair<string, int> pa=q.front();
			string s=pa.ST;
			q.pop();
			if (s==end)return pa.ND;

			int p=0;
			REP(i, 9)if (s[i]=='.'){p=i;break;}
			bool ok=false;
			REP(i, 4){
				int nx=p%3+vx[i], ny=p/3+vy[i];
				if (nx<0 || nx>=3 || ny<0 || ny>=3)continue;
				string ns=s;
				swap(ns[p], ns[nx+ny*3]);
				if (state.find(ns)==state.end()){q.push(MP(ns, pa.ND+1)); state.insert(ns);}
			}
		}
		return -1;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"123",
 "485",
 "76."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(0, Arg1, fewestMoves(Arg0)); }
	void test_case_1() { string Arr0[] = {"123",
 "456",
 "78."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(1, Arg1, fewestMoves(Arg0)); }
	void test_case_2() { string Arr0[] = {".23",
 "456",
 "781"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(2, Arg1, fewestMoves(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  GameOfEight ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
