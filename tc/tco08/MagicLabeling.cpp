// BEGIN CUT HERE

// END CUT HERE
#line 5 "MagicLabeling.cpp"

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

const int MAX_N=50;
const int MOD=1000003;

int label[MAX_N];
int graph[MAX_N][MAX_N];
int val[MAX_N];
int n, m;

int setVal(int p, int v, int mv){
	if (v<=0 || v>m)return 0;
	if (val[p]!=-1) return val[p]==v;
	val[p]=v;
	int i;
	REP(i, n) if (graph[p][i] && !setVal(i, mv-v, mv))return 0;
	return 1;

}
void dfs(int a, int c){
	if (label[a]!=-1)return;
	label[a]=c;
	int i;
	REP(i, n)
		if (graph[a][i])dfs(i, c);

}


class MagicLabeling {
	public:
	int count(vector <string> _graph, int M) {

		m=M;
		int i, j, k;
		n=_graph.size();
		memset(graph, 0, sizeof(graph));
		REP(i, n) FOR (j, i+1, n-1) if (_graph[i][j]=='Y')graph[i][j]=graph[j][i]=1;
		memset(label, -1, sizeof(label));
		int c=0;
		REP (i, n) if (label[i]==-1) dfs(i, c++);
		vi nc(c, 0);
		vi repr(c, -1);

		REP(j, n) ++nc[label[j]], repr[label[j]]=(repr[label[j]]==-1?j:repr[label[j]]);

		int s=0;
		if (c==n){
			s=1;
			REP(i, c)
				s=(ll(s)*M)%MOD;
			return s;
		}
		FOR (i, 2, 2*M){
			int p=1;
			REP(j, c){
				if (nc[j]==1)continue;
				int np=0;
				
			   	FOR (k, 1, i-1){
					memset(val, -1, sizeof(val));
					if (setVal(repr[j], k, i))++np;
				}
				p=(ll(p)*np)%MOD;
			}
			s=(p+s)%MOD;
		}
		REP(i, c)
			if (nc[i]==1)s=(ll(s)*M)%MOD;
		
		return s;


	}

	// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = 
		{"NNNNNNNNN", "NNNNNNNNN", "NNNNNNNNN", "NNNNYYNNN", "NNNYNYNNN", "NNNYYNNNN", "NNNNNNNYN", "NNNNNNYNY", "NNNNNNNYN"}
		; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 75; int Arg2 = 970003; verify_case(0, Arg2, count(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"NNNNN",
		"NNNNN",
		"NNNNY",
		"NNNNN",
		"NNYNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 100; int Arg2 = 970003; verify_case(1, Arg2, count(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"NYY",
		"YNN",
		"YNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; int Arg2 = 100; verify_case(2, Arg2, count(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"NYNN",
		"YNNN",
		"NNNY",
		"NNYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 19; verify_case(3, Arg2, count(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"NYY",
		"YNY",
		"YYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 15; int Arg2 = 15; verify_case(4, Arg2, count(Arg0, Arg1)); }

	// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	MagicLabeling ___test; 
	___test.run_test(0); 
} 
// END CUT HERE
