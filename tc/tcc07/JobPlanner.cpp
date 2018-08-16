// BEGIN CUT HERE

// END CUT HERE
#line 5 "JobPlanner.cpp"

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


const int maxn=51;
int cost[3*maxn+2][3*maxn+2];
int cap[3*maxn+2][3*maxn+2];
int att[maxn][maxn][maxn];
int visited[3*maxn+2], prev[3*maxn+2];


int can[maxn][maxn];
int sat[maxn];
int nw, nt;

vi maxflow(int s, int t, int n){
	memset(visited, 0, sizeof(visited));
	int val[n];
	memset(val, -1, sizeof(val));

	priority_queue<pair<int, int> > q;
	q.push(MP(0, s));
	val[s]=0;


	while(!q.empty()){
		int p=q.top().ND; q.pop();
	//	printf("on %d form %d\n", p, prev[p]);
		if (visited[p])continue;
		visited[p]=1;
		if (p==t)break;
		REP(i, n) if (!visited[i] && cap[p][i]>0 && (val[i]==-1 || val[i]>val[p]+cost[p][i])){

			prev[i]=p;
			q.push(MP(-(val[i]=val[p]+cost[p][i]), i));
		}
	}
	vi res;
	if (!visited[t])return res;
	int p=t;
	while(p!=s){
		res.pb(p);
		p=prev[p];
	}
	res.pb(s);
	reverse(ALL(res));
	return res;
}

class JobPlanner {
	public:
	int minimalCost(vector <string> _can, vector <int> _cost) {

		nw=_can.size(); nt=_can[0].length();
		memset(can, 0, sizeof(can));
		memset(att, 0, sizeof(att));
		REP(i, nw) REP(j, nt) can[i][j]=(_can[i][j]=='Y');

		memset(sat, 0, sizeof(sat));
		REP(step, nt){
			//printf("on step %d\n", step);
			memset(cap, 0, sizeof(cap));
			memset(cost, 0, sizeof(cost));
			int id[maxn];
			id[0]=0; REP(i, nw) id[i+1]=id[i]+sat[i]+1;

			int s, t; s=nt+id[nw], t=s+1;
			assert(t<3*maxn+2);
			REP(i, nt) cap[s][i]=1;
			REP(i, id[nw]) cap[nt+i][t]=1;

			REP(k, nt) REP(i, nw) if (can[i][k]) REP(j, sat[i]+1){

				int b=nt+id[i]+j;
				cost[k][b]=_cost[i]*(2*j+1);
				cost[b][k]=-cost[k][b];
				if (att[i][k][j]==0) cap[k][b]=1;
				else cap[b][k]=1, cap[s][k]=0, cap[k][s]=1, cap[b][t]=0, cap[t][b]=1;
				//		printf("%d %d with %d, cap %d\n", k, b, cost[k][b], cap[k][b]);
			}
			REP(i, nt) assert(cap[s][i]+cap[i][s]==1);
			int sa=0; REP(i, nt) REP(j, id[nw]) sa+=cap[nt+j][i]; assert(sa==step);
			sa=0; REP(i, nw)REP(j, nt) REP(k, nt) sa+=att[i][j][k];
			assert(sa==step);
			vi path=maxflow(s, t, t+1);
			//	printf("path size: %d\n", path.size());
			if (path.size()==0)return -1;
			REP(i, path.size()-1){
				int a, b;a=path[i], b=path[i+1];
				--cap[a][b], ++cap[b][a];
				int inc;
				if (a>=s || b>=s)continue;
				if (a<nt && b<s) inc=1;
				else if (b<nt && a<s) inc=-1, swap(a, b);
				else assert(0);

				REP(i, nw) if (b<nt+id[i+1]){ sat[i]+=inc; att[i][a][b-nt-id[i]]+=inc;assert(att[i][a][b-nt-id[i]]>=0); break; }
			}


		}
		int v=0;
		REP(i, nw) v+=_cost[i]*sat[i]*sat[i];
		return v;

	}

	// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	//void test_case_0() { string Arr0[] = {"YY","YY"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(0, Arg2, minimalCost(Arg0, Arg1)); }
	//{, }{, }
	void test_case_0() { string Arr0[] = {"YNNNYYYNNYNNNNYYNNYYYNNNYYYNYNYNYNY", "NNNYYYNYNYNNNYNYYNNYYNYYNYYYYYNNYYN", "NYNNYYNYNNYNYYNNNYNNNNYNYNNNYYYNYNN", "YYNNNYYNYNYYNYYYYNNYYYNNNNNNYNYYNNN", "YNYNYYNNNYYNYYNNNNYYYYNNNYNYYYNYYNN", "NNYYNYNYYYYNYYYYNNYNYNNNNYNYNYNYYNN", "NNYYYYNYYYNYYNNYNYNYNYNNYNYNNNYNYYN", "NNNYYYNYYNNNYYNYNNNYYYNYNYYYNYNNNYN", "NYNYYNNYYYYNNNNYNNYNNYYNYNYYYNYYYYY", "NYNNYNNNYYNYYYYNYYYYYYYYYNYNYNYYYNN", "YNYNNNNYYNNYYYYNYNNYNNNNNYYNNYNNYYN", "YNYNNNYNNNYYNNYNYNNNNYNNYNYYNNNNYYY", "NNNNYNNNNNYYYYYNYNYYNYNNNNYNNNNYYNN", "NYNYNNYYYNNYNYNNNNNNYYNNYNNNNYNNNYN", "YYYNYYNNNYNYNNYNNYNNNNNNNNYYNNYYNNY", "NYYYNYYNNYYYYYYYYNYNYNNNNYNNNYYNYYN", "YYYYYYYNYYNYYYYNYYYYNNNYYNNYYYNNYYN", "YYNYYNNYYYNYYYYNYYNYNNNYNYYYYYNYYYN", "YNYNNNYNNYNYNNYYYYNYNNNNNYYNNNYYYYY", "NNNYNNNYYNNYNNNYNNYNNYYYNYNNNNYYNYN", "YYYNNNYYNNNYYYNNNNNNYYNNYNYYYYYNNNY", "NYNYYYYYYNYYNYYYYYNYNYNYNYNYYNNNNNN", "NNNNNYYNNYYYYNYNYYYNYYYNYYNYYYNNYNY", "YYNNYNYYNYNNNNYYNYNYNYYNNNNNYYYYNNY", "YYNNNYNYNYNYNYYYNNYNNYYNNYYYNYYNNNY", "YNNNNYNYYYYYNNNYYYNNYNNYYYYNNYNNNNY", "YNYYNNYNNNYYYNNNNNNYNYNNNNYYNNYYYNY", "YYNYNYNNNNNNNYYNNNYYYYYYNNYNNYNNNYY", "YNNYNNYNYYYNYYYYNNNNNNNNNYNNYYYYYNY", "YYNNYNNYYNYNYNNNYYNNNYYYNNYYNYNNYNN", "YNYYYNYYYNNNYYYYYYNYYYNNNYYYYNNYNYN", "YNYNYNYNYYNYNYNYNYYNNNNNNYNNNYNNNYY", "YNNYNNNYNYYYYYYNYYNNNYNNYNYYYYNNYYY", "YYNYYYYNNYNNYNYYYYNNYNNNNNNYYYYYYNN", "YYNYYYNYYYNYNYNYYYNNNNYYYNYYYNYNNYY", "NYYYNYNNNNNNYYYYNYYNNNNNYNYYNNYYYYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {429675, 236312, 46614, 380316, 67813, 265390, 4561, 335854, 189647, 170968, 392893, 471826, 301519, 192634, 323989, 297270, 59338, 38526, 356472, 70029, 450924, 15787, 241275, 495816, 135091, 444724, 86160, 19564, 242148, 380091, 55881, 295003, 65525, 287935, 350184, 43394}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(0, Arg2, minimalCost(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"YY","YY"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 4; verify_case(1, Arg2, minimalCost(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"YN", "YY"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 6; verify_case(2, Arg2, minimalCost(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"YN", "YN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(3, Arg2, minimalCost(Arg0, Arg1)); }

	// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	JobPlanner ___test; 
	___test.run_test(0);
} 
// END CUT HERE
