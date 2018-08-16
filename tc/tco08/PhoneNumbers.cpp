// BEGIN CUT HERE

// END CUT HERE
#line 5 "PhoneNumbers.cpp"

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



#define REP(i,n) for(i = 0; i < (n); i++)

#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define FOR(i, a, b) for(i = (a); i <= (b); i++)
#define FORV(i, a, b) for(i = (a); i >= (b); i--)

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();i++)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();i++)

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


const int MAX_N=55;

string dps[MAX_N][3];
int dp[MAX_N][3];
int n;
string number;

int cost(int p, int na){
	++na;
	if (na==0)
		return 0;
	if (na==2)
		return number[p]==number[p-1]?2:0;

	int c=0;
	for (int i=0; i<=2; ++i)
		if (number[p-i]==number[p-(i+1)%3])++c;
	
	return min(c, 2);

}
int solve(int p, int na){
	if (p==n){
		dps[p][na]="";
		if (na==1)
			return -1;
		dps[p][na]=number.substr(p-na);
		return cost(p-1, na);
	}


	int &r=dp[p][na];
	if (r!=-1)return r;

	int nr;
	string ns;
	if (na<=1){
		nr=solve(p+1, na+1), ns=dps[p+1][na+1];
		if (nr!=-1)
			r=nr, dps[p][na]=ns;
	}
	if (na>=1){
		nr=solve(p+1, 0), ns=number.substr(p-na, na+1)+"-"+dps[p+1][0];
		if (nr!=-1){
			nr+=cost(p, na);
			if (r==-1 || nr>r || (nr==r && ns<dps[p][na]))r=nr, dps[p][na]=ns;
		}
	}
	return r;

}

class PhoneNumbers {
	public:
	string bestNumber(string _number) {
		number=_number;
		n=number.length();
		memset(dp, -1, sizeof(dp));
		solve(0, 0);

		if (dps[0][0][dps[0][0].length()-1]=='-')dps[0][0].erase(dps[0][0].length()-1);
		return dps[0][0];
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "5088638"; string Arg1 = "50-88-638"; verify_case(0, Arg1, bestNumber(Arg0)); }
	void test_case_1() { string Arg0 = "0123456789"; string Arg1 = "01-23-45-67-89"; verify_case(1, Arg1, bestNumber(Arg0)); }
	void test_case_2() { string Arg0 = "09"; string Arg1 = "09"; verify_case(2, Arg1, bestNumber(Arg0)); }
	void test_case_3() { string Arg0 = "54545454545454545454"; string Arg1 = "54-545-454-545-454-545-454"; verify_case(3, Arg1, bestNumber(Arg0)); }
	void test_case_4() { string Arg0 = "00110001011100010111"; string Arg1 = "00-11-00-010-11-10-00-101-11"; verify_case(4, Arg1, bestNumber(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  PhoneNumbers ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
