// BEGIN CUT HERE

// END CUT HERE
#line 5 "VacationTours.cpp"

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


int val(char c){
	if (c>='A' && c<='Z') return c-'A';
	if (c>='a' && c<='z') return 26+c-'a';
	if (c>='0' && c<='9') return 52+c-'0';
	return (c=='+'?62:63);
}
const int maxn=57;
int cost[maxn][maxn];
int graph[2*maxn][2*maxn];
int ncost[2*maxn][2*maxn];
int rn[2*maxn][2*maxn];
int parent[2*maxn];
int dist[2*maxn];
int done[2*maxn];
int n;
int potential;

const int inf=1000000;

int dijsktra(int s){
	REP(i, n) dist[i]=inf;
	dist[s]=0;
	memset(parent, -1, sizeof(parent));
	memset(done, 0, sizeof(done));
	while(1){
		int best=-1;
		REP(i, n) if (!done[i] && (best==-1 || dist[i]<dist[best])) best=i;
		if (best==-1 || dist[best]==inf)break;
		done[best]=1;
		REP(i, n) if (!done[i] && rn[best][i] && (dist[best]+ncost[best][i]<dist[i])) dist[i]=dist[best]+ncost[best][i], parent[i]=best;
	}
	return 1;
}
void updatePot(int t){
	REP(i, n) REP(j, n) ncost[i][j]+=dist[i]-dist[j];
	potential+=dist[t];
}

int flow(int k, int s, int t, int fee){
	memcpy(rn, graph, sizeof(graph));
	int v=0;
	int res=0;
	potential=0;
	REP(step, k){

		dijsktra(s);
		int p=t;
		while(p!=s){
			assert(parent[p]!=-1);

			int tmp=rn[parent[p]][p];
			rn[parent[p]][p]-=tmp; rn[p][parent[p]]+=tmp;
			v+=ncost[parent[p]][p];
			p=parent[p];
		}
		v+=potential;
		checkmax(res, fee*(step+1)-v);
		updatePot(t);
	}

	//printf("cost %d\n", v);

	return res;

}

class VacationTours {
	public:
	int getIncome(vector <string> c, vector <string> d, int fee) {
		int s, t;
		n=c.size();
		REP(i, n) REP(j, n) cost[i][j]=val(c[i][j])*64+val(d[i][j]);
		s=0; t=1; 
		//REP(i, n){
		//	REP(j, n) printf("%d ", cost[i][j]); printf("\n");

		//}

		memset(ncost, 0, sizeof(ncost));
		REP(i, n) if (i){ ncost[s][2*i]=cost[0][i]; ncost[2*i+1][t]=cost[i][0]; }
		REP(i, n) REP(j, n) if (i && j){ncost[2*i+1][2*j]=cost[i][j]; ncost[2*j][2*i+1]=-cost[i][j];}

		memset(graph, 0, sizeof(graph));
		REP(i, n) if (i) graph[2*i][2*i+1]=1, graph[s][2*i]=1, graph[2*i+1][t]=1;
		REP(i, n) REP(j, n) if (i&&j) graph[2*i+1][2*j]=1;

		n*=2;
		return flow(n/2-1, s, t, fee);
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"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"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"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"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1700; int Arg3 = 12; verify_case(0, Arg3, getIncome(Arg0, Arg1, Arg2)); }
	//void test_case_0() { string Arr0[] = {"AAA", "AAA", "AAA"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"ABJ", "JAB", "BJA"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 15; int Arg3 = 12; verify_case(0, Arg3, getIncome(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"AAAA",
 "AAAA",
 "AAAA",
 "AAAA"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"AAAA",
 "AAAA",
 "AAAA",
 "AAAA"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 100; int Arg3 = 300; verify_case(1, Arg3, getIncome(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"A//",
 "/A/",
 "//A"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"A//",
 "/A/",
 "//A"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1000; int Arg3 = 0; verify_case(2, Arg3, getIncome(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"AAA////",
 "/AA/A//",
 "//AA/A/",
 "A//AA//",
 "///AAA/",
 "///A/AA",
 "AA////A"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"AKo////",
 "/AU/X//",
 "//AZ/o/",
 "j//AK//",
 "///XAo/",
 "///y/AK",
 "KP////A"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1000; int Arg3 = 1809; verify_case(3, Arg3, getIncome(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  VacationTours ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE
