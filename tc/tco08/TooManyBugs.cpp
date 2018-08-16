// BEGIN CUT HERE

// END CUT HERE
#line 5 "TooManyBugs.cpp"

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




class TooManyBugs {
	public:
	int bestBugFixing(vector <string> info) {
		map<pii, int> bug;
		map<int, int> day;
		FE(it, info){
			int a, b;
			istringstream ss(*it);
			ss>>a;
			if (ss>>b){
				if (bug.find(MP(a, b))==bug.end()) bug.insert(MP(MP(a, b), 0));
				++bug[MP(a, b)];
			}
			else{
				if (day.find(a)==day.end())day.insert(MP(a, 0));
				++day[a];
			}
		}
		int c=0;
		map<int, int>::iterator ita;
		FEV(it, bug) 
			REP(k, it->ND){
				if ((ita=day.lower_bound(it->ST.ND))!=day.end()){
					if (ita->ST<it->ST.ND){ 
						if (ita==day.begin())continue;
						--ita;
					}
					--ita->ND;
					if (ita->ND==0) day.erase(ita);
					c+=it->ST.ST;
				}
			}
		return c;

	}

	// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"5 3", "20 20", "125"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 20; verify_case(0, Arg1, bestBugFixing(Arg0)); }
	void test_case_1() { string Arr0[] = {"5 3", "20 20", "15"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(1, Arg1, bestBugFixing(Arg0)); }
	void test_case_2() { string Arr0[] = {"5 3", "20 20", "25", "15", "6 15"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 26; verify_case(2, Arg1, bestBugFixing(Arg0)); }
	void test_case_3() { string Arr0[] = {"5 3", "20 20", "7 2", 
		"25", "3", "15", "6 15"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 33; verify_case(3, Arg1, bestBugFixing(Arg0)); }
	void test_case_4() { string Arr0[] = {"5 3", "20 20", "125", "125", "125", "125"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 25; verify_case(4, Arg1, bestBugFixing(Arg0)); }
	void test_case_5() { string Arr0[] = {"2 4", "5 1", "5 1", "9 1", "3 10", "4 8", "4 7", 
		"9", "8", "4", "2"}
		; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 23; verify_case(5, Arg1, bestBugFixing(Arg0)); }

		// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	TooManyBugs ___test; 
	___test.run_test(-1); 
} 
// END CUT HERE
