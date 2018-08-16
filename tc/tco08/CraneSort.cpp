// BEGIN CUT HERE

// END CUT HERE
#line 5 "CraneSort.cpp"

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



const int maxn=52;
int n;
int tbn[4];

int parent[4];
int eslot[4];
int getParent(int a){return (parent[a]==-1)?a:parent[a]=getParent(parent[a]);}

int graph[5][5];
int visited[5];
int pid[4];
int section(int p){
	if (p<0 || p>=n)return 4;
	REP(i, 3) if (p>=pid[i] && p<pid[i+1])return i;
	return 3;
}

int dfs(int p){
	if (visited[p])return 0;
	visited[p]=1;
	int c=0;
	REP(i, 5) if (i!=p && graph[p][i]>0) c+=graph[p][i]+dfs(i);
	return c;

}
class CraneSort {
	public:
	int moves(string s) {
		memset(tbn, 0, sizeof(tbn));
		n=s.length();
		REP(i, n) ++tbn[s[i]-'A'];
		int id[4];
		vector<int> perm;
		perm.pb(0); perm.pb(1); perm.pb(2); perm.pb(3); 
		int best=INT_MAX;
		while(1){
			FOR (i, -n, n){
				int p=i;
				REP(k, 4) pid[k]=p, p+=tbn[perm[k]];
				memset(visited, 0, sizeof(visited));
				memset(graph, 0, sizeof(graph));

				int sa, sb;
				REP(k, 4) FOR(j, pid[k], pid[k]+tbn[perm[k]]-1)
					++graph[perm[k]][j>=0 && j<n?s[j]-'A':4];

				int cnt=0;

				memset(parent, -1, sizeof(parent));
				memset(eslot, 0, sizeof(eslot));
				REP(j, 4) REP(k, 4) if (j!=k && graph[j][k] && (getParent(k)==-1 || getParent(k)!=getParent(j)))parent[getParent(k)]=getParent(j);
				REP(j, 4) if (graph[j][4]>0)eslot[getParent(j)]=1;

				memset(visited, 0, sizeof(visited));

				REP(k, 4){
				   	int a=dfs(k);
					if (parent[k]==-1 && !eslot[k]) REP(j, 4) if (k!=j && graph[k][j]>0){++a;break;}
					
					
					cnt+=a;
				}
				//REP(j, 4)printf("%d ", parent[j]);
				//printf("\n");
				//REP(j, 4)printf("%d ", perm[j]);
				//printf("\n");
				//printf("=>>%d\n", i);
				//REP(j, 4){
				//   	REP(k, 5)printf("%d ", graph[j][k]);
				//	printf("\n");
				//}
				//printf("\n");
				best=min(best, cnt);
			}

			if (!next_permutation(ALL(perm)))break;
		}

		return best;

	}

	// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "DACDACBACB"; int Arg1 = 0; verify_case(0, Arg1, moves(Arg0)); }
	void test_case_1() { string Arg0 = "ABCAA"; int Arg1 = 1; verify_case(1, Arg1, moves(Arg0)); }
	void test_case_2() { string Arg0 = "CCCCCCCCBAAABA"; int Arg1 = 3; verify_case(2, Arg1, moves(Arg0)); }

	// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	CraneSort ___test; 
	___test.run_test(-1);
} 
// END CUT HERE
