// BEGIN CUT HERE

// END CUT HERE
#line 5 "BlockCounter.cpp"

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



ll cb(string sa, int &s, int &e){
	ll res;
	if (sa.length()==1){
		s=e=sa[0];
		return 1;
	}
	if (sa[0]=='A' || sa[0]=='B'){
		res=cb(sa.substr(1), s, e);
		res+=(s!=sa[0]);
		s=sa[0];
		return res;
	}
	if (sa[1]<='9'){
		int n=0, i=1;
		while(sa[i]>='0' && sa[i]<='9') n=n*10+sa[i++]-'0';
		int p=i;
		int c=1;
		for (; c>0; ++i){
			if (sa[i]==')')--c;
			else if (sa[i]=='(')++c;
		}
		--i;
		assert(i<sa.length());
		res=cb(sa.substr(p+1, i-p-1), s, e);

		int ns, ne;
		if (s==e) res=(res-1)*n+1;
		else res=res*n;
		if (i!=sa.length()-1){
			res+=cb(sa.substr(i+1), ns, ne);
			if (ns==e)--res;
			e=ne;
		}
		return res;
	}
	assert(0);

}

class BlockCounter {
	public:
	long long countBlocks(string word) {
		ll res=0;
		int s, e;
		return cb(word, s, e);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	//void test_case_0() { string Arg0 = "(2,A(3,AB))"; long long Arg1 = 12LL; verify_case(0, Arg1, countBlocks(Arg0)); }
	void test_case_0() { string Arg0 = "(2,B)ABABA"; long long Arg1 = 12LL; verify_case(0, Arg1, countBlocks(Arg0)); }
	void test_case_1() { string Arg0 = "A(1,A)A(5,AAA)"; long long Arg1 = 1LL; verify_case(1, Arg1, countBlocks(Arg0)); }
	void test_case_2() { string Arg0 = "ABA(2,ABA)(3,ABA)"; long long Arg1 = 13LL; verify_case(2, Arg1, countBlocks(Arg0)); }
	void test_case_3() { string Arg0 = "(3,(2,(1,AB)))B"; long long Arg1 = 12LL; verify_case(3, Arg1, countBlocks(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  BlockCounter ___test; 
        ___test.run_test(0);
        } 
// END CUT HERE
