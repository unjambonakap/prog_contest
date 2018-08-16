// BEGIN CUT HERE

// END CUT HERE
#line 5 "ToolingUp.cpp"

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


const int maxv=1010;
int lst[maxv];
int prime[maxv];
ll tg;
ll dp[maxv][maxv];

ll proc(int s, int a){
	if (a>maxv) return 1;
	if (!prime[a]) return proc(s, a+1);

	ll &r=dp[s][a];
	if (r!=-1) return r;
	r=proc(s, a+1);
	int v=1;
	REP(i, lst[a]) v*=a;
	int nv=a;
	while(v*nv<=s) checkmax(r, proc(s-v*nv, a+1)*nv), nv*=a;
	return r;

}


class ToolingUp {
	public:
	int cost(string targetLcm, vector <int> sizes) {
		int n=sizes.size();
		istringstream(targetLcm)>>tg;
		memset(lst, 0, sizeof(lst));
		memset(prime, 0, sizeof(prime));
		FOR(i, 2, maxv-1){
			prime[i]=1;
		   	FOR(j, 2, i-1) if (i%j==0){prime[i]=0; break;}
		}
		REP(i, n) FOR(j, 2, sizes[i]) if (prime[j] && sizes[i]%j==0){
			int t=sizes[i];
			int cnt=0;
			while(t%j==0) ++cnt, t/=j;
			checkmax(lst[j], cnt);
		}

		ll prod=1;
		REP(i, maxv){
			REP(j, lst[i]){
			   	prod*=i;
				if (prod>=tg) return 0;
			}
		}
		memset(dp, -1, sizeof(dp));
		REP(i, maxv) if (proc(i, 2)*prod>=tg) return i;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "193"; int Arr1[] = {82,13,100}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(0, Arg2, cost(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "1000000"; int Arr1[] = {100,92,77}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 9; verify_case(1, Arg2, cost(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "999999"; int Arr1[] = {124,600,7,8}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 11; verify_case(2, Arg2, cost(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "123456789123"; int Arr1[] = {31,1,1,6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 120; verify_case(3, Arg2, cost(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  ToolingUp ___test; 
        ___test.run_test(3); 
        } 
// END CUT HERE
