// BEGIN CUT HERE

// END CUT HERE
#line 5 "CardsAndSlots.cpp"

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
inline int ctz(int n){return (n==0?-1:(n==1?0:ctz(n>>1)+1));}


const int maxn=55;

int graph[maxn][maxn];
int visited[maxn];
int match[maxn], rm[maxn];
int n;
pair<pii, int> remap[maxn];

int dfs(int p, int s){
	if (visited[p])return 0;
	visited[p]=1;
	FOR(i, s+1, n-1) if (graph[p][i] && (rm[i]==-1 || dfs(rm[i], s))){
		rm[i]=p, match[p]=i;
		return 1;
	}
	return 0;
	

}


class CardsAndSlots {
	public:
	string firstValid(vector <int> values, string letters, vector <int> required) {
		n=values.size();

		memset(graph, 0, sizeof(graph));
		REP(i, n) REP(j, n) graph[i][j]=(values[i]>=required[j]);

		REP(i, n) remap[i]=MP(MP(letters[i], values[i]), i);
		sort(remap, remap+n);
		memset(match, -1, sizeof(match));
		memset(rm, -1, sizeof(rm));
		REP(i, n){
			memset(visited, 0, sizeof(visited));
			if (!dfs(i, -1)){
				return "";
			}
		}

		REP(i, n){

			int e=rm[i];
			match[e]=-1; rm[i]=-1;
			REP(j, n){
				if (graph[remap[j].ND][i] && (match[remap[j].ND]==-1 || match[remap[j].ND]>=i)){
					memset(visited, 0, sizeof(visited));
					int with=match[remap[j].ND];
					rm[with]=-1;
					match[remap[j].ND]=i; rm[i]=remap[j].ND;
					if (remap[j].ND==e || dfs(e, i))break;
					match[remap[j].ND]=with, rm[with]=remap[j].ND;
					rm[i]=-1;
				}
			}
			assert(rm[i]!=-1);
		}
		string res;
		REP(i, n) res+=letters[rm[i]];
		return res;

	}

	// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	//void test_case_0() { int Arr0[] = {1, 2, 3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "ABC"; int Arr2[] = {2, 2, 1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "BCA"; verify_case(0, Arg3, firstValid(Arg0, Arg1, Arg2)); }
	//{, ", } 
	void test_case_0() { int Arr0[] = {232, 182, 170, 102, 186, 284, 328, 331, 156, 123, 168, 318, 207, 317, 143, 245, 55, 183, 206}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "HBGGVVGLUBWKMEMGANKABC"; int Arr2[] = {103, 213, 216, 262, 142, 102, 182, 47, 138, 322, 26, 117, 7, 255, 104, 128, 177, 228, 294}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "BEGGBGKAGLMMNVUWVHK"; verify_case(0, Arg3, firstValid(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {1, 2, 3, 4, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "BBBAA"; int Arr2[] = {1, 1, 1, 1, 5}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "ABBBA"; verify_case(1, Arg3, firstValid(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {1, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "AA"; int Arr2[] = {2, 2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = ""; verify_case(2, Arg3, firstValid(Arg0, Arg1, Arg2)); }

	// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	CardsAndSlots ___test; 
	___test.run_test(0);
} 
// END CUT HERE
