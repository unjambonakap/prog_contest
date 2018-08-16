// BEGIN CUT HERE

// END CUT HERE
#line 5 "LongJourney.cpp"

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


const int maxn=57;
int dist[maxn][maxn];
int seen[maxn][maxn];
int n;

struct state{
	int a, b; 
	ll c;
	state(int a, int b, ll c):a(a), b(b), c(c){}
	bool operator<(const state &s)const{
		if (c!=s.c)return c>s.c;
		if (a!=s.a) return a<s.a;
		return b<s.b;
	}
};




class LongJourney {
	public:
	long long minimumCost(vector <int> fp, int ft, vector <string> roads) {
		n=fp.size();
		string s;
		FE(it, roads) s+=*it;
		memset(dist, -1, sizeof(dist));
		REP(i, s.length()) if (s[i]==',')s[i]=' ';
		istringstream ss(s);
		{
		int a, b, c;
		while(ss>>a>>b>>c) dist[a][b]=dist[b][a]=c;
		}
		REP(i, n) dist[i][i]=0;
		REP(k, n) REP(i, n) REP(j, n)  if (dist[i][k]!=-1 && dist[k][j]!=-1 && (dist[i][j]==-1 || dist[i][j]>dist[i][k]+dist[k][j]))  dist[i][j]=dist[i][k]+dist[k][j];
		REP(i, n) REP(j, n) if (dist[i][j]>ft) dist[i][j]=-1;


		priority_queue<state> q;
		q.push(state(0, n, 0));
		memset(seen, 0, sizeof(seen));
		while(!q.empty()){
			state p=q.top(); q.pop();
			if (seen[p.a][p.b]) continue;

			if (p.a==1) return p.c;
			seen[p.a][p.b]=1;

			int rf=0;
			if (p.b!=n) rf=ft-dist[p.b][p.a];
			
			REP(i, n) if (dist[p.a][i]!=-1){
			   	if (!seen[i][n]){
					ll nc=ll(fp[p.a])*max(0, dist[p.a][i]-rf)+p.c;
					q.push(state(i, n, nc));
				}if (!seen[i][p.a]){
					ll nc=ll(fp[p.a])*(ft-rf)+p.c;
					q.push(state(i, p.a, nc));
				}
			}
		}
		return -1;

	}

	// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	//void test_case_0() { int Arr0[] = {5,6,1,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 100; string Arr2[] = {"0,2,2 ","0,3,5 ","1,3,3"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 20LL; verify_case(0, Arg3, minimumCost(Arg0, Arg1, Arg2)); }
	void test_case_0() { int Arr0[] = {4, 1, 1, 2, 4, 2, 1, 3, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 999947; string Arr2[] = {"0,1,310 0,8,20 1,4,56 1,5,194 1,7,272 2,3,77 2,5,3", "02 3,6,286 3,8,5 4,6,311 4,7,42 5,6,310"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 20LL; verify_case(0, Arg3, minimumCost(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {5,6,1,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 100; string Arr2[] = {"0,2,2 "
		,"0,3,1 "
			,"1,3,7"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 19LL; verify_case(1, Arg3, minimumCost(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {10,15,5,20}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 500; string Arr2[] = {"0,2,50","0 2,3,50"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = -1LL; verify_case(2, Arg3, minimumCost(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {8131,12392,4152,7482,124208,1,1800,19,33791,2,4970,635157,7089,194,279,162627}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 985516; string Arr2[] = {"0,2,885843 0,5,948680 0,6,814375 0,7,254140 0,9,96"
		,"5704 0,11,950391 0,12,2234 0,13,666704 0,14,757770"
			," 1,4,233 1,5,850136 1,8,792847 1,9,62147 1,13,8726"
			,"80 1,14,827511 1,15,253774 2,3,4831 2,4,63 2,5,660"
			,"053 2,6,1079 2,7,379766 2,8,681543 2,9,910853 2,11"
			,",871528 2,12,587492 2,13,762963 2,14,3761 3,4,3462"
			,"62 3,5,147581 3,6,881103 3,8,426200 3,9,39902 3,10"
			,",915751 3,11,293781 3,14,722019 3,15,394147 4,5,39"
			,"5608 4,8,972273 4,9,855758 4,10,423924 4,12,974268"
			," 4,15,931000 5,6,831319 5,7,76 5,8,53136 5,9,42289"
			,"6 5,11,12626 5,13,220080 5,14,321058 5,15,6 6,7,51"
			,"0462 6,10,926807 6,11,659470 6,12,702857 6,13,8555"
			,"66 6,14,719994 6,15,868043 7,10,821770 7,13,216703"
			," 7,15,758397 8,9,267740 8,10,772522 8,13,279514 9,"
			,"10,24592 9,11,680535 9,12,624855 9,14,132484 10,15"
			,",869307 11,12,28 11,13,493421 11,14,590457 12,14,3"
			,"16607 13,14,542254"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 108021568LL; verify_case(3, Arg3, minimumCost(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {1000000,1000000}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1000000; string Arr2[] = {"0,1,1000000"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 1000000000000LL; verify_case(4, Arg3, minimumCost(Arg0, Arg1, Arg2)); }

	// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	LongJourney ___test; 
	___test.run_test(-1);
} 
// END CUT HERE
