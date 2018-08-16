// BEGIN CUT HERE

// END CUT HERE
#line 5 "SkipList.cpp"

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

const int maxn=1000;
const int maxa=10;
const int maska=two(maxa)-1;

class SkipList {
	int op[maxn];
	int num[maxn];
	vi add;
	int rem[maxn];
	int dp[maxn][two(maxa)];
	int seen[maxn][two(maxa)];
	int n, na;

	int remap[maxn];
	int preva[maxn];
	map<int, int> order;

	deque<int> qs[maxn];


	int solve(int p, int a){
		if (p==n)return 0;
		int &r=dp[p][a];
		if (seen[p][a])return r;
		seen[p][a]=1;

		if (!op[p]){
			int fd=-1;
			deque<int> &q=qs[preva[p]];
			REP(i, q.size()) if (q[i]==num[p]){fd=i; break;}
			assert(fd!=-1); bool k=bit_set(a, fd);
			r=solve(p+1, a);
			if (k){
				if (fd>0)
					r-=count_bit(a&(two(fd)-1));
			}
			else r+=order[num[p]];
			return r;
		}
		r=INT_MAX;
		REP(i, 2) checkmin(r, solve(p+1, maska&((a<<1)|i))+rem[p]*i);
		return r;
	}

	public:
	int minCost(vector <string> ops) {
		string s, t;
		REP(i, maxn) qs[i].clear();

		FE(it, ops) s+=*it;
		istringstream ss(s);
		n=0; add.clear(); na=0;
		order.clear();
		while(ss>>t){
			op[n]=(t[0]=='A');
			num[n]=toInt(t.substr(1));
			if (op[n]) add.pb(num[n]), remap[na++]=n, preva[n]=n, order[num[n]]=na;
			else preva[n]=preva[n-1];
			++n;
		}
		memset(rem, 0, sizeof(rem));
		REPV(i, n-1) rem[i]=rem[i+1]+1-op[i+1];
		deque<int> qa;
		REP(i, na){
			qa.push_front(num[remap[i]]);
			if (qa.size()>maxa) qa.pop_back();
			qs[remap[i]]=qa;
		}


		memset(seen, 0, sizeof(seen));
		return solve(0, 0);
	}

	// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	//void test_case_0() { string Arr0[] = {"A1 ","A2 ","A3"," F3"," F3"," F3"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(0, Arg1, minCost(Arg0)); }
	void test_case_0() { string Arr0[] = {"A4555 F4555 F4555 F4555 F4555 F4555 F4555 F4555 F4", "555 F4555 F4555 F4555 F4555 F4555 F4555 F4555 F455", "5 F4555 F4555 F4555 F4555 F4555 F4555 F4555 F4555 ", "F4555 F4555 F4555 F4555 F4555 F4555 F4555 F4555 F4", "555 F4555 F4555 F4555 F4555 F4555 F4555 F4555 F455", "5 F4555 F4555 F4555 F4555 F4555 F4555 F4555 F4555 ", "F4555 F4555 F4555 F4555 F4555 F4555 F4555 A5355 F5", "355 F5355 F5355 F5355 F5355 F5355 F5355 F5355 F535", "5 F5355 F5355 F5355 F5355 F5355 F5355 F5355 F5355 ", "F4555 F5355 F5355 F5355 F5355 F5355 F5355 A7971 F5", "355 F7971 F7971 F5355 F7971 F7971 F7971 F7971 F535", "5 F7971 F7971 F7971 F7971 F7971 F7971 F7971 F7971 ", "F7971 F7971 F5355 F7971 F7971 F7971 F7971 F7971 F7", "971 F7971 F7971 F7971 F7971 F7971 F5355 A1859 F185", "9 F1859 F1859 F1859 F1859 F1859 F1859 F1859 F1859 ", "F1859 F1859 F1859 F1859 F1859 F1859 F5355 F1859 F1", "859 F1859 F1859 F1859 F1859 F1859 F1859 F1859 F185", "9 F1859 F1859 F1859 F1859 F1859 F1859 F1859 F1859 ", "F1859 F1859 F1859 F1859 F1859 F1859 F1859 F1859 F1", "859 F1859 F1859 F1859 F1859 F1859 F1859 F1859 F185", "9 F1859 F1859 F1859 F1859 F1859 F1859 F1859 F1859 ", "F1859 F1859 F1859 F1859 F1859 F1859 F1859 F1859 F1", "859 F1859 F1859 F1859 F7971 F1859 F1859 F1859 F185", "9 F1859 F1859 F1859 F1859 F1859 F1859 F1859 F1859 ", "F1859 F1859 F1859 F1859 F1859 F1859 F1859 F1859 F1", "859 F1859 F1859 F1859 A9582 F1859 F9582 F1859 F185", "9 F9582 F9582 F9582 F9582 F9582 F9582 F9582 F1859 ", "F9582 F1859 F9582 F9582 F9582 F9582 F9582 F9582 F9", "582 F9582 F9582 F9582 F1859 F9582 F1859 F9582 F958", "2 F9582 F9582 F9582 F9582 F9582 F9582 F9582 F9582 ", "F9582 F1859 F9582 A2281 F1859 F2281 F2281 F2281 F2", "281 F2281 F2281 F2281 F2281 F2281 A6170 F6170 F228", "1 F6170 F6170 F6170 F2281 F2281 F6170 F2281 F2281 ", "F6170 F6170 F6170 F2281 F6170 A8371 F6170 F6170 F6", "170 F6170 F6170 F2281 A5233 F5233 F5233 F5233 F523", "3 F5233 F5233 F6170 F5233 A3947 F3947 A3104 F3104 ", "F3104 A1770 A2594 A3396"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 531; verify_case(0, Arg1, minCost(Arg0)); }
	void test_case_1() { string Arr0[] = {"A1 F1 F1 F1 A2 F1 F2 F1 F2 F1" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; verify_case(1, Arg1, minCost(Arg0)); }
	void test_case_2() { string Arr0[] = {"A1 F1 F1 F1 A2 F1 F2 F1 F2 F2 F2 F2 F2 F2" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 14; verify_case(2, Arg1, minCost(Arg0)); }
	void test_case_3() { string Arr0[] = {"A10","000 A","900 A800 F800 A1 ","F1 F1 F1 F1 A2 F1 F1 A3 F1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; verify_case(3, Arg1, minCost(Arg0)); }
	void test_case_4() { string Arr0[] = {"A1 A2 A3 A4 A5"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(4, Arg1, minCost(Arg0)); }

	// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	SkipList ___test; 
	___test.run_test(-1);
} 
// END CUT HERE
