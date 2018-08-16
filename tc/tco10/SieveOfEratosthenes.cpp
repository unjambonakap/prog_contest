// BEGIN CUT HERE

// END CUT HERE
#line 5 "SieveOfEratosthenes.cpp"

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

bool isPrime(int a){
	if (a==2)return 1;
	if (a%2==0)return 0;
	for (int i=3; i<=sqrt(a); i+=2) if (a%i==0)return 0;
	return 1;
}

bool lowfact(int a, int b){
	if (2<b && a%2==0)return 1;
	for (int i=3; i<b; i+=2) if (a%i==0)return 1;
	return 0;

}


class SieveOfEratosthenes {
	public:
	int lastScratch(int maxNum) {
		int num=sqrt(maxNum);
		while(!isPrime(num)) --num;
		int res=num*num;
		int coeff=num+1;
		while(coeff*num<=maxNum){
			if (!lowfact(coeff,num)) res=coeff*num;
			++coeff;
		}
		return res;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 18; int Arg1 = 15; verify_case(0, Arg1, lastScratch(Arg0)); }
	void test_case_1() { int Arg0 = 7; int Arg1 = 4; verify_case(1, Arg1, lastScratch(Arg0)); }
	void test_case_2() { int Arg0 = 100; int Arg1 = 91; verify_case(2, Arg1, lastScratch(Arg0)); }
	void test_case_3() { int Arg0 = 2e9; int Arg1 = 361; verify_case(3, Arg1, lastScratch(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  SieveOfEratosthenes ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
