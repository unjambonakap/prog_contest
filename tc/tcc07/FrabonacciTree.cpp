// BEGIN CUT HERE

// END CUT HERE
#line 5 "FrabonacciTree.cpp"

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

ll fibn[55];

const ll maxn=5*(1e10)+5;

string path(int n, int i){
	if (fibn[n]==-1)return "L"+path(n-1, i-1);
	if (i==0)return "";
	if (i>fibn[n-2])return "R"+path(n-1, i-fibn[n-2]-1);
	return "L"+path(n-2, i-1);
}

class FrabonacciTree {
	public:
	string shortestPath(int n, int si, int ei) {
		memset(fibn, -1, sizeof(fibn));
		fibn[0]=fibn[1]=1;
		for (int i=1; fibn[i]<maxn; ++i) fibn[i+1]=fibn[i]+fibn[i-1]+1;
		string ss, se, s;
		ss=path(n, si-1), se=path(n, ei-1);

		int p;
		for(p=0; p<ss.length() && p<se.length(); ++p) if (ss[p]!=se[p])break;
		return string(ss.length()-p, 'U')+se.substr(p);
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }

	//{49, , }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	//void test_case_0() { int Arg0 = 3; int Arg1 = 2; int Arg2 = 4; string Arg3 = "URL"; verify_case(0, Arg3, shortestPath(Arg0, Arg1, Arg2)); }
	void test_case_0() { int Arg0 = 49; int Arg1 = 752781034; int Arg2 = 481322118; string Arg3 ="UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUULRRRRLRRRLLRRRLRRRLLRLRRLRRRRRL" ; verify_case(0, Arg3, shortestPath(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 4; int Arg2 = 2; string Arg3 = "UUL"; verify_case(1, Arg3, shortestPath(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 3; int Arg1 = 5; int Arg2 = 4; string Arg3 = "UL"; verify_case(2, Arg3, shortestPath(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 12; int Arg1 = 10; int Arg2 = 10; string Arg3 = ""; verify_case(3, Arg3, shortestPath(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  FrabonacciTree ___test; 
        ___test.run_test(0);
        } 
// END CUT HERE
