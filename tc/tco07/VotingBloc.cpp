// BEGIN CUT HERE

// END CUT HERE
#line 5 "VotingBloc.cpp"

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

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:(n==1?0:ctz(n>>1)+1));}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}


const int maxn=55;
int n;
int choice[maxn];
int ally[maxn][maxn];
int visited[maxn];

int graph[maxn][maxn];
int remap[maxn][2];
int nt[2];
int match[maxn][2];
int lock[maxn];


int dfs(int p){
	if (lock[remap[p][0]] || visited[p])return 0;
	visited[p]=1;
	REP(i, nt[1]) if (!lock[remap[i][1]] && graph[p][i] && (match[i][1]==-1 || dfs(match[i][1]))){
		match[i][1]=p; match[p][0]=i;
		return 1;
	}
	return 0;
}
int doit(){
	memset(match, -1, sizeof(match));
	int cnt=0;
	REP(i, nt[0]){
		memset(visited, 0, sizeof(visited));
		if (dfs(i)) ++cnt;
	}
	return cnt;
}

class VotingBloc {
	public:
		vector <int> abstainers(vector <string> voter) {
			n=voter.size(); memset(ally, 0, sizeof(ally));
			memset(remap, -1, sizeof(remap));
			REP(i, n){
				istringstream ss(voter[i]);
				string c; ss>>c;
				choice[i]=(c[0]=='Y');
				int p;
				ally[i][i]=1;
				while(ss>>p) --p, ally[i][p]=ally[p][i]=1;
			}
			memset(graph, 0, sizeof(graph)); nt[0]=nt[1]=0;
			REP(i, n) remap[nt[choice[i]]++][choice[i]]=i;
			if (!nt[0] || !nt[1])return vi();

			REP(i, nt[0]) REP(j, nt[1]) if (ally[remap[i][0]][remap[j][1]]) graph[i][j]=1;

			memset(lock, 0, sizeof(lock));
			int cnt=doit();

			vi tb;
			REP(i, n){
				lock[i]=1;
				if (doit()==cnt-1) tb.pb(i+1), --cnt;
				else lock[i]=0;
			}

			return tb;


		}

		// BEGIN CUT HERE
	public:
		void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
		template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
		void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
		void test_case_0() { string Arr0[] ={"Y 3 17 19 20 25 26", "Y 4 5 20 30", "N 4 16 17 18 19 22", "N 12 23 27", "N 6 17 22 28", "Y 8 11 16 18 22", "Y 8 11 16 25 27 29 30", "N 11 14 15 27 29 30", "Y 29", "Y 13 16 19 20", "N 19 22 27 30", "N 21 22 24", "Y 16 19 26 28", "N 19 20 22", "N 18", "Y 17 26 27", "Y 24 27 29 30", "N 26 30", "Y 21 26 28", "N 26 28", "N 22 30", "N 29", "Y", "Y 26 27", "N", "N 27", "N", "Y 29", "N", "N"} ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, abstainers(Arg0)); }
		//void test_case_0() { string Arr0[] = {"Y 2","N"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, abstainers(Arg0)); }
		void test_case_1() { string Arr0[] = {"N 2","N 3","Y"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, abstainers(Arg0)); }
		void test_case_2() { string Arr0[] = {"N 2 3 4","N 3 4","Y 4","Y"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 2 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, abstainers(Arg0)); }
		void test_case_3() { string Arr0[] = {"N 2 3 4","N 3 4","Y 4","N"} ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, abstainers(Arg0)); }
		void test_case_4() { string Arr0[] = {"Y 2 3 4","Y 3 4","Y 4","Y"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(4, Arg1, abstainers(Arg0)); }

		// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	VotingBloc ___test; 
	___test.run_test(-1);
} 
// END CUT HERE
