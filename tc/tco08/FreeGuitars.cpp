// BEGIN CUT HERE

// END CUT HERE
#line 5 "FreeGuitars.cpp"

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
int n;
int graph[maxn][maxn];
int visited[maxn];

class FreeGuitars {
	public:
	int minimumCosts(int _n, vector <string> tr) {
		n=_n;
		memset(graph, -1, sizeof(graph));
		FE(it, tr){
			istringstream ss(*it);
			int a, b, c;
			ss>>a>>b>>c;
			graph[a-1][b-1]=graph[b-1][a-1]=c;
		}
		int c=0;
		priority_queue<pii> q;
		q.push(MP(0, 0));
		memset(visited, 0, sizeof(visited));
		while(!q.empty()){
			pii p=q.top(); q.pop();
			if (visited[p.ND])continue;
			c+=-p.ST;
			visited[p.ND]=1;
			REP(i, n) if (!visited[i] && graph[p.ND][i]!=-1) q.push(MP(-graph[p.ND][i], i));
		}
		REP(i, n) if (!visited[i])return -1;
		return c;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; string Arr1[] = {"1 2 6", "1 3 4", "2 3 1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; verify_case(0, Arg2, minimumCosts(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 3; string Arr1[] = {"1 3 56"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(1, Arg2, minimumCosts(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 5; string Arr1[] = {"1 2 88",
"1 3 37",
"1 4 73",
"1 5 58",
"2 3 59",
"2 4 30",
"2 5 98",
"3 4 28",
"3 5 85",
"4 5 82"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 153; verify_case(2, Arg2, minimumCosts(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 15; string Arr1[] = {"12 2 90", "14 4 11", "6 4 18", "5 8 35", "7 13 54", "11 2 33", "12 5 52",
 "13 2 98", "10 3 3", "4 7 63", "15 11 46", "11 7 4", "11 6 24", "9 7 30",
 "13 12 19", "5 10 82", "9 1 94", "13 3 30", "11 5 12", "10 1 10", "6 9 74",
 "12 8 55", "4 11 3", "12 4 71", "9 10 90"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 306; verify_case(3, Arg2, minimumCosts(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  FreeGuitars ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
