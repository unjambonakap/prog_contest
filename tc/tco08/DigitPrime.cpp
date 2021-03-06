// BEGIN CUT HERE

// END CUT HERE
#line 5 "DigitPrime.cpp"

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


const int maxn=100000;

int prime[100];

class DigitPrime {
	public:
	int countNumbers(int a, int b) {
		
		REP(i, 100)prime[i]=1;
		for (int i=10; i<100; i+=2)prime[i]=0;
		for (int i=3; i<50; i+=2) if (prime[i]) for (int j=i+i; j<100; j+=i) prime[j]=0;

		
		int c=0;
		FOR(i, a, b){
			vi lst;
			int p=i;
			while(p!=0){
				if (p%10>0) lst.pb(p%10);
				p/=10;
			}
			FOR(j, 0, lst.size()-1) FOR(k, 0, j-1) if (prime[lst[j]*10+lst[k]]||prime[lst[k]*10+lst[j]]){++c; goto found;}
			
found:;


		}
		return c;
		
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 11; int Arg1 = 20; int Arg2 = 6; verify_case(0, Arg2, countNumbers(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 37; int Arg1 = 98; int Arg2 = 21; verify_case(1, Arg2, countNumbers(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 9003; int Arg1 = 9003; int Arg2 = 0; verify_case(2, Arg2, countNumbers(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 11; int Arg1 = 11111; int Arg2 = 8777; verify_case(3, Arg2, countNumbers(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 97463; int Arg1 = 100000; int Arg2 = 2436; verify_case(4, Arg2, countNumbers(Arg0, Arg1)); }
	void test_case_5() { int Arg0 = 33561; int Arg1 = 33601; int Arg2 = 40; verify_case(5, Arg2, countNumbers(Arg0, Arg1)); }
	void test_case_6() { int Arg0 = 11000; int Arg1 = 11999; int Arg2 = 1000; verify_case(6, Arg2, countNumbers(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  DigitPrime ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
