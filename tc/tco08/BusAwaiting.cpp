// BEGIN CUT HERE

// END CUT HERE
#line 5 "BusAwaiting.cpp"

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




class BusAwaiting {
	public:
	int waitingTime(vector <string> buses, int arrivalTime) {
		int s=INT_MAX;
		FE(it, buses){
			istringstream ss(*it);
			int a, b, c;
			ss>>a>>b>>c;
			if (arrivalTime<a){
				s=min(s, a-arrivalTime);
				continue;
			}
			int ta=arrivalTime-a;
			int temp=ceil(double(ta)/b);
			if (temp<c)s=min(s, temp*b-ta);


		}
		if (s==INT_MAX)return -1;
		return s;
		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"150 50 10"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 285; int Arg2 = 15; verify_case(0, Arg2, waitingTime(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"123456 10000 1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 123456; int Arg2 = 0; verify_case(1, Arg2, waitingTime(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"270758 196 67",
 "904526 8930 66",
 "121164 3160 56"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 121163; verify_case(2, Arg2, waitingTime(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"718571 2557 74",
 "480573 9706 54",
 "16511 6660 90"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1000000; int Arg2 = -1; verify_case(3, Arg2, waitingTime(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"407917 8774 24",
 "331425 4386 58",
 "502205 9420 32",
 "591461 1548 79",
 "504695 8047 53"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 395439; int Arg2 = 1776; verify_case(4, Arg2, waitingTime(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  BusAwaiting ___test; 
        ___test.run_test(-1); 
        } 
// END CUT HERE
