// BEGIN CUT HERE

// END CUT HERE
#line 5 "SuperWatch.cpp"

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


const int MOD=24*60;
const int MAX_N=41;

int tb[MAX_N];
int n;
int visited[MAX_N];
int ma[MAX_N];
int graph[MAX_N][MAX_N];


int dfs(int a){
	if (visited[a])return 0;
	visited[a]=1;
	int i;
	REP(i, n){
		if (graph[a][i] && (ma[i]==-1 || dfs(ma[i]))){
			ma[i]=a;
			return 1;
		}
	}
	return false;

}

class SuperWatch {
	public:
	int smallestImprecision(vector <string> times, vector <int> zones) {
		n=zones.size();
		int i, j, k;
		REP(i, n){
			times[i][2]=' ';
			istringstream ss(times[i]);
			ss>>j>>k;
			tb[i]=j*60+k;
		}

		int s=INT_MAX;
		REP(i, MOD){
			int H, L, M;
			H=MOD, L=-1;
			while(H>L+1){
				M=(H+L)/2;
				memset(graph, 0, sizeof(graph));
				REP(j, n) REP(k, n){
					int t=(tb[j]-60*zones[k]-i)%MOD;
					if (t<0)t+=MOD;
					if (t<=M)
						graph[j][k]=1;
				}

				memset(ma, -1, sizeof(ma));
				bool ok=true;
				REP(j, n){
					memset(visited, 0, sizeof(visited));
					if (!dfs(j)){
						ok=false;
						break;
					}

				}
				if (!ok) L=M;
				else H=M;
			}
			s=min(s, H);
		}
		return s;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"16:11", "15:59", "16:02", "16:13"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {5, 5, 5, 5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 14; verify_case(0, Arg2, smallestImprecision(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"12:11", "13:59", "19:02", "18:13"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 3, 7, 8}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 14; verify_case(1, Arg2, smallestImprecision(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"23:59", "00:02", "12:00", "08:01"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 0, 8, 12}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(2, Arg2, smallestImprecision(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"13:23", "11:54", "00:03", "22:22", "10:38"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 4, 13, 21, 13}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 256; verify_case(3, Arg2, smallestImprecision(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = { "00:00", "08:00", "16:00" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 0, 0, 0 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 960; verify_case(4, Arg2, smallestImprecision(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  SuperWatch ___test; 
        ___test.run_test(3); 
        } 
// END CUT HERE
