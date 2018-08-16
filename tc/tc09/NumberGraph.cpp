// BEGIN CUT HERE

// END CUT HERE
#line 5 "NumberGraph.cpp"

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
inline int get_fb(int n){return n-(n&(n-1));}

const int MAX_N=85;

int graph[MAX_N][MAX_N], ng[MAX_N][MAX_N];
int visited[MAX_N];
int matched[MAX_N];

vi va, vb;
int nva, nvb;

int dfs(int p){
	if (visited[p])return 0;
	visited[p]=1;
	for (int i=0; i<nva+nvb; ++i) if (ng[p][i])
		if (matched[i]==-1 || dfs(matched[i])){
			matched[i]=p, matched[p]=i;
			return 1;
		}
	return 0;

	

	

}

class NumberGraph {
	public:

		int largestSet(vector <string> graphSet, vector <int> joiningSet) {
			string s;
			int i, j, k, c;
			FE(it, graphSet)
				s+=*it;

			c=get_fb(joiningSet[0]);

			vector<int> sa, sb;
			istringstream ss(s);
			while(ss>>i){
				if (i&c)sa.pb(i);
				else sb.pb(i);
			}
			int na, nb;
			na=sa.size(), nb=sb.size();
			memset(graph, 0, sizeof(graph));
			REP(i, na)
				REP(j, nb)
					FE(it, joiningSet)
						if (abs(sa[i]-sb[j])==*it)
							graph[i][j]=1;

			int res=1;
			REP(i, na)
				REP(j, nb)
					if (graph[i][j]){
						CLR(va); CLR(vb);
						REP(k, nb)
							if (k!=j && graph[i][k])
								vb.pb(k);
						REP(k, na)
							if (k!=i && graph[k][j])
								va.pb(k);

						memset(ng, 0, sizeof(ng));
						nva=va.size(), nvb=vb.size();

						int u, v;
						REP(u, nva)
							REP(v, nvb)
								if (!graph[va[u]][vb[v]])ng[u][nva+v]=ng[nva+v][u]=1;
						memset(matched, -1, sizeof(matched));
						int nc=0;
						REP(k, nva){
							memset(visited, 0, sizeof(visited));
							if (dfs(k))++nc;
						}
						res=max(res, 2+nva+nvb-nc);
					}
					

			
			return res;


		}











		// BEGIN CUT HERE
	public:
		void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
		template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
		void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
		void test_case_0() { string Arr0[] = {"1 2 3 4 6 9 13 15 16 18 21 26"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,6,10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 4; verify_case(0, Arg2, largestSet(Arg0, Arg1)); }
		void test_case_1() { string Arr0[] = {"4 11 12 10 9 6 2 7 1 8 5"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3,5,1,7}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 9; verify_case(1, Arg2, largestSet(Arg0, Arg1)); }
		void test_case_2() { string Arr0[] = {"100 260 164 244 84 340 52 2"
			,"12 388 4 308 180 228 484"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {16,176,208,48,240,80}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 8; verify_case(2, Arg2, largestSet(Arg0, Arg1)); }
		void test_case_3() { string Arr0[] = {"10 6 130 162 164 39 73 27 72 167 41"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3,63,95,123,57,91,35,137
			,135,125,33,121,17,5,31
				,45,67,29,157}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 8; verify_case(3, Arg2, largestSet(Arg0, Arg1)); }
		void test_case_4() { string Arr0[] = {"2136 2108 876 8"
			,"6 348 8 1784 1146 1596 608 446 14"
				,"64"
				," 344 1452 1938 692 376 1482 860 1870"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {644,844,348,604,1260,516,868,2100,260
					,1492,316,1076,268,852,12,1500,4,772
						,1108,188,1444,1764,84,1732,532,332
						,1588,500,700,1116,252,1060,68,1092
						,724,132,484,340,684,1276,28,1788,588}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 12; verify_case(4, Arg2, largestSet(Arg0, Arg1)); }
		void test_case_5() { string Arr0[] = {"1000000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(5, Arg2, largestSet(Arg0, Arg1)); }
		void test_case_6() { string Arr0[] = {"1 2 3 4 5 6 7 8"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(6, Arg2, largestSet(Arg0, Arg1)); }

		// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	NumberGraph ___test; 
	___test.run_test(-1);
} 
// END CUT HERE
