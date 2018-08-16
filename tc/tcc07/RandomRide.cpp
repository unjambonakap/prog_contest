// BEGIN CUT HERE

// END CUT HERE
#line 5 "RandomRide.cpp"

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


const int maxn=20, maxl=51;
int seen[maxn][maxn][maxl], l;
int graph[maxn][4];
int deg[maxn];
int f[maxl];
int addt(int a, int b){
	if (a>='a')a-='a';
	if (b>='a')b-='a';
	graph[a][0]=b; graph[b][2]=a;
}int addb(int a, int b){
	if (a>='a')a-='a';
	if (b>='a')b-='a';
	graph[a][2]=b; graph[b][0]=a;
}int addl(int a, int b){
	if (a>='a')a-='a';
	if (b>='a')b-='a';
	graph[a][3]=b; graph[b][1]=a;
}int addr(int a, int b){
	if (a>='a')a-='a';
	if (b>='a')b-='a';
	graph[a][1]=b; graph[b][3]=a;
}
int middle(int p, int a){
	REP(i, 4) if (graph[a][i]==p)return graph[a][i^2];
}
int left(int p, int a){
	REP(i, 4) if (graph[a][i]==p)return (graph[a][(i+1)%4]==-1?graph[a][(i+2)%4]:graph[a][(i+1)%4]);
	assert(0);
}
int right(int p, int a){
	REP(i, 4) if (graph[a][i]==p)return (graph[a][(i+3)%4]==-1?graph[a][(i+2)%4]:graph[a][(i+3)%4]);
	assert(0);
}
int rec(int prev, int p, int t, int cnt){
	t%=l;
	if (seen[prev][p][t])return -1;
	seen[prev][p][t]=1;
	if (p==maxn-1)return cnt;
	if (deg[p]==3){
		if (f[t]) return rec(p, left(prev, p), t+1, cnt+1);
		else return rec(p, right(prev, p), t+1, cnt+1);
	}else{
		int a, b;
		a=f[t], b=f[(t+1)%l];
		if (a&&b) return rec(p, left(prev, p), t+2, cnt+2);
		if (a&&!b) return rec(p, middle(prev, p), t+2, cnt+2);
		if (!a&&b) return rec(p, right(prev, p), t+2, cnt+2);
		else return rec(prev, p, t+2, cnt+2);


	}
}

class RandomRide {
	public:
	int flipCount(string flips) {
		memset(seen, 0, sizeof(seen));
		l=flips.size(); REP(i, l) f[i]=flips[i]=='H';
		memset(graph, -1, sizeof(graph));
		int t=maxn-1;
		addl(0, t);
		addb(0, 'f');

		graph[0][0]=1; graph[1][3]=0;
		graph[0][2]='f'-'a'; graph['f'-'a'][2]=0;
		graph[1][0]='g'-'a'; graph['g'-'a'][3]=1;
		addr('b', 'c');

		addl('c', 'b');
		addt('c', 'g');
		addr('c', 'd');

		addl('d', 'c');
		addt('d', 'h');
		addr('d', 'e');

		addb('g', 'c');
		addt('g', 'i');
		addr('g', 'h');

		addl('h', 'g');
		addt('h', 'j');
		addb('h', 'd');

		addb('i', 'g');
		addr('i', 'j');

		addt('j', 'm');
		addb('j', 'h');
		addl('j', 'i');
		addr('j', 'k');

		addb('m', 'j');
		addr('m', 'n');

		addb('n', 'k');
		addl('n', 'm');
		graph['n'-'a'][1]='l'-'a';graph['l'-'a'][0]='n'-'a';
		graph['m'-'a'][3]='i'-'a';graph['i'-'a'][0]='m'-'a';

		addl('l', 'k');
		addb('l', 'f');

		addt('e', 'k');
		addr('e', 'f');
		addl('e', 'd');

		memset(deg, 0, sizeof(deg));
		REP(i, maxn) REP(j, 4) if (graph[i][j]!=-1)++deg[i];
		return rec(maxn-1, 0, 0, 0);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "H"; int Arg1 = 10; verify_case(0, Arg1, flipCount(Arg0)); }
	void test_case_1() { string Arg0 = "HHTTTTTHTHTHHHTT"; int Arg1 = 11; verify_case(1, Arg1, flipCount(Arg0)); }
	void test_case_2() { string Arg0 = "HTH"; int Arg1 = 13; verify_case(2, Arg1, flipCount(Arg0)); }
	void test_case_3() { string Arg0 = "HHHTHHHHHHTTTHHHHHHHHHTTHHT"; int Arg1 = 328; verify_case(3, Arg1, flipCount(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  RandomRide ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
