// BEGIN CUT HERE

// END CUT HERE
#line 5 "OddGraph.cpp"

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


const int maxn=41;

set<vi> seen[maxn];
int tb[maxn];
int dp[maxn];

void rec(int p, int l, int rem, int d){
	if (l==0){ 
		if (rem==0) seen[d-1].insert(vi(tb, tb+p-1));
		return;
	}
	FOR(i, 0, min(l, rem)){
		tb[p]=i;
		rec(p+1, i, rem-i, d);
	}
	tb[p]=0;
}

int solve(int p, int c){
	if (p==0)return 1;
	int &r=dp[p-1];
	if (r!=-1)return r;
	r=0;
	if (p==5)printf("for %d %d\n", p, seen[p-1].size());
	FE(it, seen[p-1]) if (!c || it->size()%2==0){
		vi t=*it;
		if (p==5) out(t);
		int temp=1;
		for (int cnt=1, l=0; l<t.size(); ++l, ++cnt){

			if (l==t.size()-1 || t[l]!=t[l+1]){
				int k=solve(t[l]-1, 1);
				if (k==0){temp=0; break;}
				int s=1;//proc C(n+k-1, k)

				FOR(i, max(cnt+1, k), cnt+k-1)s*=i;
				FOR(i, 2, min(cnt, k-1))s/=i;
				//printf("%d %d => %d\n", k, cnt, s);
				if (k==3 && cnt==6)
				exit(0);
				assert(s!=0);
				temp*=s;
				cnt=0;
			}
		}
		r+=temp;
	}
	return r;
}

class OddGraph {
	public:
	int count(int n) {
	
		REP(i, n) rec(0, i+1, i+1, i+1);
		memset(dp, -1, sizeof(dp));
		return solve(n, 0);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 5; int Arg1 = 4; verify_case(0, Arg1, count(Arg0)); }
	void test_case_1() { int Arg0 = 1; int Arg1 = 1; verify_case(1, Arg1, count(Arg0)); }
	void test_case_2() { int Arg0 = 40; int Arg1 = 929556155; verify_case(2, Arg1, count(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  OddGraph ___test; 
        ___test.run_test(2);
        } 
// END CUT HERE
